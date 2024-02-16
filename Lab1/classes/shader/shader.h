/**
 * @file shader.h
 * @brief Shader class header file.
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

#ifndef BGQ_OPENGL_SHADER_H_
#define BGQ_OPENGL_SHADER_H_

#include <string>

#include "glm/glm.hpp"

#include "classes/camera/camera.h"
#include "classes/cubemap/cubemap.h"
#include "classes/light/light.h"
#include "classes/texture/texture.h"

namespace bgq_opengl {
    
    /**
     * @brief Implementation of a Shader class.
     *
     * Implementation of a Shader class to handle loading, activation and
     * errors in vertex and fragment shaders.
     *
     * @author Borja García Quiroga <garcaqub@tcd.ie>
     */
	class Shader {

    public:

        /**
         * @brief Construct the shader instance.
         *
         * Construct the shader instance by passing no files.
         */
        Shader();

        /**
         * @brief Construct the shader instance.
         *
         * Construct the shader instance by passing the shaders' files.
         *
         * @param vertex_filename Vertex shader filename.
         * @param fragment_filename Fragment shader filename.
         */
        Shader(const char* vertex_filename, const char* fragment_filename);

        /**
         *@brief Returns the program ID.
         *
         * Returns the program ID for this Shader program.
         * 
         * @returns The program ID as an unsigned integer.
         */
        unsigned int getProgramID();

        /**
         * @brief Activate this shader program.
         * 
         * Activate this shader program and start using it.
         */
        void activate();

        /**
         * @brief Pass a given bool to the shaders.
         * 
         * Pass a given bool variable to the shader program.
         * 
         * @param name The name that the variable will receive within the shaders.
         * @param value The bool to be passed to the program.
         */
        void passBool(const std::string& name, bool value);

        /**
         * @brief Pass the camera matrix and camera position to the shader.
         *
         * Pass the camera matrix and camera position to the shader.
         *
         * @param camera The camera.
         */
        void passCamera(Camera camera);
        
        /**
         * @brief Pass a cubemap to the shader.
         *
         * Pass a cubemap texture to the shader.
         *
         * @param cubemap The cubemap that will be passed.
         */
        void passCubemap(Cubemap cubemap);

        /**
         * @brief Pass a light to the shader.
         * 
         * Pass a light to the shader.
         * 
         * @param light the light that will be passed to tha shader.
         */
        void passLight(Light light);

        /**
         * @brief Pass a given integer to the shaders.
         *
         * Pass a given integer variable to the shader program.
         *
         * @param name The name that the variable will receive within the shaders.
         * @param value The int to be passed to the program.
         */
        void passInt(const std::string& name, int value);

        /**
         * @brief Pass a given float to the shaders.
         *
         * Pass a given float variable to the shader program.
         *
         * @param name The name that the variable will receive within the shaders.
         * @param value The float to be passed to the program.
         */
        void passFloat(const std::string& name, float value);

        /**
         * @brief Pass a texture to the shader.
         * 
         * Pass a texture to the shader.
         * 
         * @param texture The texture itself.
         */
        void passTexture(Texture texture);
        
        /**
         * @brief Pass a vector of size 2 to the shader.
         *
         * Pass a vector of size 2 to the shader.
         *
         * @param name Name of the variable in the shader.
         * @param value The vector that will be passed.
         */
        void passVec(const std::string& name, glm::vec2 value);

        /**
         * @brief Pass a vector of size 3 to the shader.
         *
         * Pass a vector of size 3 to the shader.
         *
         * @param name Name of the variable in the shader.
         * @param value The vector that will be passed.
         */
        void passVec(const std::string& name, glm::vec3 value);

        /**
         * @brief Pass a vector of size 4 to the shader.
         *
         * Pass a vector of size 4 to the shader.
         *
         * @param name Name of the variable in the shader.
         * @param value The vector that will be passed.
         */
        void passVec(const std::string& name, glm::vec4 value);

        /**
         * @brief Pass a matrix of size 2 to the shader.
         *
         * Pass a matrix of size 2 to the shader.
         *
         * @param name Name of the variable in the shader.
         * @param value The matrix that will be passed.
         */
        void passMat(const std::string& name, glm::mat2 value);

        /**
         * @brief Pass a matrix of size 3 to the shader.
         *
         * Pass a matrix of size 3 to the shader.
         *
         * @param name Name of the variable in the shader.
         * @param value The matrix that will be passed.
         */
        void passMat(const std::string& name, glm::mat3 value);

        /**
         * @brief Pass a matrix of size 4 to the shader.
         *
         * Pass a matrix of size 4 to the shader.
         *
         * @param name Name of the variable in the shader.
         * @param value The matrix that will be passed.
         */
        void passMat(const std::string& name, glm::mat4 value);

        /**
         * @brief Remove the shader from OpenGL.
         * 
         * Remove the shader from OpenGL.
         */
        void remove();

    private:

        /**
         * @brief Check for errors in the program or shader.
         * 
         * Checks for compilation or linking errors and returns the log message.
         * 
         * @param shader An integer containing the ID to the program or shader to check.
         * @param type Type of the check to perform (PROGRAM, VALIDATE, VERTEX, FRAGMENT).
         * @param log_str Output variable for the logging error message.
         * 
         * @returns True if compilation / linking was successful. False it errors occurred.
         */
        static bool checkShader(unsigned int shader, std::string type, std::string* log_str);

        /**
         * @brief Gets the content of a file as a string.
         *
         * Gets the contents of a file, given its filename, and returns it as a string.
         *
         * @param filename The name of the file to be read.
         * @param file_contents An output string containing the contents of the file.
         *
         * @throws 121-1001 Could not read file.
         */
        static void readFileContents(const char* filename, std::string *file_contents);

        Light* light; /// The light that will be used in the shader.
        unsigned int programID = -1; /// OpenGL ID for this shader program.

    };

}  // namespace bgq_opengl

#endif // !BGQ_OPENGL_SHADER_H_
