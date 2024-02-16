/**
 * @file shader.cpp
 * @brief Shader class implementation file.
 * @version 1.0.0 (2022-10-21)
 * @date 2022-10-21
 * @author Borja García Quiroga <garcaqub@tcd.ie>
 *
 *
 * Copyright (c) Borja García Quiroga, All Rights Reserved.
 *
 * The information and material provided below was developed as partial
 * requirements for the MSc in Computer Science at Trinity College Dublin,
 * Ireland.
 */

#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "classes/camera/camera.h"
#include "classes/light/light.h"
#include "classes/texture/texture.h"

namespace bgq_opengl {

    Shader::Shader() {
    
        this->programID = NULL;

        this->light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
    
    }
    
    Shader::Shader(const char* vertex_filename, const char* fragment_filename) {

        this->light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

        // Init the strings to store the source code in.
        std::string vertex_source_code = "";
        std::string fragment_source_code = "";

        try {
            
            readFileContents(vertex_filename, &vertex_source_code);

        } catch (std::ifstream::failure& e) {
            
            std::cerr << "Shader error - Could not read the vertex shader file: " << e.what() << std::endl;
            exit(1);
        
        }

        try {

            readFileContents(fragment_filename, &fragment_source_code);

        } catch (std::ifstream::failure& e) {

            std::cerr << "Shader error - Could not read the fragment shader file: " << e.what() << std::endl;
            exit(1);

        }

        // Convert it to char.
        const char* vertex_code_char = vertex_source_code.c_str();
        const char* fragment_code_char = fragment_source_code.c_str();

        // Create and compile the vertex shader.
        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertex_code_char, NULL);
        glCompileShader(vertex);

        // Check for errors.
        std::string error_msg = "";
        if (!Shader::checkShader(vertex, "VERTEX", &error_msg)) {

            std::cerr << "Vertex shader error - Could not compile the shader: " << error_msg << std::endl;
            exit(1);

        }

        // Create and compile the fragment shader.
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragment_code_char, NULL);
        glCompileShader(fragment);

        // Check for errors.
        error_msg = "";
        if (!Shader::checkShader(fragment, "FRAGMENT", &error_msg)) {

            std::cerr << "Fragment shader error - Could not compile the shader: " << error_msg << std::endl;
            exit(1);

        }

        // Create the program and add the vertex and fragment shaders.
        this->programID = glCreateProgram();
        glAttachShader(this->programID, vertex);
        glAttachShader(this->programID, fragment);

        // Link this program and check for program errors.
        glLinkProgram(this->programID);
        error_msg = "";
        if (!Shader::checkShader(this->programID, "PROGRAM", &error_msg)) {

            std::cerr << "Shader program error - Could not link the shaders: " << error_msg << std::endl;
            exit(1);

        }

        // Clean the shaders.
        // They are in the compiled program now, so clean them.
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        /*
        // Validate the program.
        glValidateProgram(this->programID);
        error_msg = "";
        if (!Shader::checkShader(this->programID, "VALIDATE", &error_msg)) {

            std::cerr << "Shader program error - Could not validate the program: " << error_msg << std::endl;
            exit(1);

        }
         */

    }

    unsigned int Shader::getProgramID() {

        return this->programID;

    }

    void Shader::activate() {

        if (this->programID == -1)
            throw std::runtime_error("Shader was not initialized.");

        glUseProgram(this->programID);

    }

    void Shader::passBool(const std::string& name, bool value) {

        glUniform1i(glGetUniformLocation(this->programID, name.c_str()), (int)value);

    }

    void Shader::passCamera(Camera camera) {

        // Pass the View matrix to the shader.
        glm::mat4 view_matrix = camera.getView();
        GLint location = glGetUniformLocation(this->programID, "View");
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view_matrix));

        // Pass the Projection matrix to the shader.
        glm::mat4 projection_matrix = camera.getProjection();
        location = glGetUniformLocation(this->programID, "Projection");
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection_matrix));

        // Get the camera info and pass it to the shader.
        glm::vec4 color = (*this->light).getColor();
        glm::vec3 position = (*this->light).getPosition();

        // Transform the camera position to view.
        position = glm::vec3(view_matrix * glm::vec4(position, 1.0f));

        // Pass it to the shader.
        glUniform4f(glGetUniformLocation(this->programID, "lightColor"), color.x, color.y, color.z, color.w);
        glUniform3f(glGetUniformLocation(this->programID, "lightPos"), position.x, position.y, position.z);

    }

    void Shader::passCubemap(Cubemap cubemap) {
        
        // Gets the location of the uniform.
        GLuint location = glGetUniformLocation(this->programID, cubemap.getName().c_str());

        // Activate the shader.
        this->activate();
        
        // Get the slot.
        int slot = cubemap.getSlot();
        
        // Activate this texture.
        glActiveTexture(GL_TEXTURE0 + slot);

        // Sets the value of the texture uniform.
        glUniform1i(location, slot);
        
    }

    void Shader::passLight(Light lightParam) {

        // Store the light.
        this->light = new Light(lightParam.getPosition(), lightParam.getColor());

    }

    void Shader::passInt(const std::string& name, int value) {

        glUniform1i(glGetUniformLocation(this->programID, name.c_str()), value);

    }

    void Shader::passFloat(const std::string& name, float value) {

        glUniform1f(glGetUniformLocation(this->programID, name.c_str()), value);

    }

    void Shader::passTexture(Texture texture) {

        // Gets the location of the uniform.
        GLuint location = glGetUniformLocation(this->programID, texture.getName().c_str());

        // Activate the shader.
        this->activate();
        
        // Get the slot.
        int slot = texture.getSlot();
        
        // Activate this texture.
        glActiveTexture(GL_TEXTURE0 + slot);

        // Sets the value of the texture uniform.
        glUniform1i(location, slot);

    }

    void Shader::passVec(const std::string& name, glm::vec2 value) {
        
        // Gets the location of the uniform.
        GLuint location = glGetUniformLocation(this->programID, name.c_str());

        // Sets the value of the texture uniform.
        glUniform2f(location, value.x, value.y);

    }

    void Shader::passVec(const std::string& name, glm::vec3 value) {
        
        // Gets the location of the uniform.
        GLuint location = glGetUniformLocation(this->programID, name.c_str());

        // Sets the value of the texture uniform.
        glUniform3f(location, value.x, value.y, value.z);

    }

    void Shader::passVec(const std::string& name, glm::vec4 value) {
        
        // Gets the location of the uniform.
        GLuint location = glGetUniformLocation(this->programID, name.c_str());

        // Sets the value of the texture uniform.
        glUniform4f(location, value.x, value.y, value.z, value.w);

    }

    void Shader::passMat(const std::string& name, glm::mat2 value) {

        // Gets the location of the uniform.
        GLuint location = glGetUniformLocation(this->programID, name.c_str());

        glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));

    }

    void Shader::passMat(const std::string& name, glm::mat3 value) {

        // Gets the location of the uniform.
        GLuint location = glGetUniformLocation(this->programID, name.c_str());

        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));

    }

    void Shader::passMat(const std::string& name, glm::mat4 value) {

        // Gets the location of the uniform.
        GLuint location = glGetUniformLocation(this->programID, name.c_str());

        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));

    }

    void Shader::remove() {

        glDeleteProgram(this->programID);

    }

    bool Shader::checkShader(unsigned int shader, std::string type, std::string* log_str) {

        // Create the variables to check the status and the message.
        int success = true;
        char log_msg[1024] = "";

        if (type == "PROGRAM") {

            glGetProgramiv(shader, GL_LINK_STATUS, &success);

            if (!success)
                glGetProgramInfoLog(shader, sizeof(log_msg), NULL, log_msg);

        } else if (type == "VALIDATE") {

            glGetProgramiv(shader, GL_VALIDATE_STATUS, &success);

            if (!success)
                glGetProgramInfoLog(shader, sizeof(log_msg), NULL, log_msg);

        } else {

            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

            if (!success)
                glGetShaderInfoLog(shader, sizeof(log_msg), NULL, log_msg);

        }

        // Get the message into the variable.
        *log_str = std::string(log_msg, sizeof(log_msg));

        return success;

    }

    void Shader::readFileContents(const char* filename, std::string *file_contents) {

        try {

            // Create a filestream and open it using the filename provided.
            std::ifstream filestream;
            filestream.open(filename);

            // Create a string stream where we will add everything in the file.
            std::stringstream str_stream;

            // Read the file buffers and store it into the string stream.
            str_stream << filestream.rdbuf();

            // Close the file.
            filestream.close();

            // Convert the stream into a regular string that can be used.
            *file_contents = str_stream.str();

        } catch (std::ifstream::failure& e) {

            // Build the new message for the exception.
            std::string msg = "121-1001 - Could not read file. ";
            msg.append(e.what());

            // Build a new exception to rethrow it.
            std::ifstream::failure new_exception(msg);
            throw new_exception;

        }

    }

}  // namespace bgq_opengl
