/**
 * @file cubemap.h
 * @brief Cubemap class implementation file.
 * @version 1.0.0 (2023-02-01)
 * @date 2023-02-01
 * @author Borja García Quiroga <garcaqub@tcd.ie>
 *
 *
 * Copyright (c) Borja García Quiroga, All Rights Reserved.
 *
 * The information and material provided below was developed as partial
 * requirements for the MSc in Computer Science at Trinity College Dublin,
 * Ireland.
 */

#include "cubemap.h"

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "GL/glew.h"
#include "stb/stb_image.h"

namespace bgq_opengl {

    Cubemap::Cubemap(GLuint id, std::string name, GLuint slot) {
        
        this->ID = id;
        this->slot = slot;
        this->name = name;
        
    }

    Cubemap::Cubemap(const std::vector<std::string> &textures_faces, const char* type, GLuint slot) {
        
        // The slot has to be a positive number because OpenGL does weird stuff on macOS else.
        if (slot < 1) assert(false);

        // Generate a texture in OpenGL and store the parameters in the attributes.
        glGenTextures(1, &this->ID);
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->ID);
        
        this->name = std::string(name);
        this->slot = slot;
        
        int width, height, channels;
        
        // Loop through the images, load them and pass them to OpenGL.
        for (unsigned int i = 0; i < textures_faces.size(); i++) {
            
            unsigned char *data = stbi_load(textures_faces[i].c_str(), &width, &height, &channels, 0);
            if (data) {
                
                // Get the color model for the image.
                GLenum color_model = GL_RGBA;

                if (channels == 4)
                    color_model = GL_RGBA;
                else if (channels == 3)
                    color_model = GL_RGB;
                else if (channels == 1)
                    color_model = GL_RED;
                else
                    assert(false);
                
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, color_model, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
                stbi_image_free(data);
                
            } else {
                
                std::cerr << "Cubemap error: cubemap " << textures_faces[i] << " could not be loaded." << std::endl;
                stbi_image_free(data);
                exit(1);
                
            }
            
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        
        // Unbinds the OpenGL Texture.
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        
    }

    GLuint Cubemap::getID() {
        
        return this->ID;
        
    }

    GLuint Cubemap::getSlot() {
        
        return this->slot;
        
    }

    std::string Cubemap::getName() {
        
        return this->name;
        
    }

    void Cubemap::bind() {
        
        // Activate the texture and bind it.
        glActiveTexture(GL_TEXTURE0 + this->slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->ID);
        
    }

    void Cubemap::remove() {
        
        glDeleteTextures(1, &this->ID);
        
    }

    void Cubemap::unbind() {
        
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        
    }

}  // namespace bgq_opengl
