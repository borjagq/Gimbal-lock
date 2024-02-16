/**
 * @file skybox.cpp
 * @brief Skybox class implementation file.
 * @version 1.0.0 (2023-02-04)
 * @date 2023-02-04
 * @author Borja García Quiroga <garcaqub@tcd.ie>
 *
 *
 * Copyright (c) Borja García Quiroga, All Rights Reserved.
 *
 * The information and material provided below was developed as partial
 * requirements for the MSc in Computer Science at Trinity College Dublin,
 * Ireland.
 */

#include "skybox.h"

#include <vector>
#include <stdexcept>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "classes/camera/camera.h"
#include "classes/shader/shader.h"
#include "classes/cubemap/cubemap.h"

namespace bgq_opengl {

    Skybox::Skybox(Cubemap cubemap) {
        
        // Store the cubemap.
        this->cubemap = cubemap;
        
        float vertices[] = {
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f
        };

        unsigned int indices[] = {
            1, 2, 6,
            6, 5, 1,
            0, 4, 7,
            7, 3, 0,
            4, 5, 6,
            6, 7, 4,
            0, 3, 2,
            2, 1, 0,
            0, 1, 5,
            5, 4, 0,
            3, 7, 6,
            6, 2, 3
        };
        
        // Create VAO, VBO, and EBO for the skybox.
        glGenVertexArrays(1, &this->vao);
        glGenBuffers(1, &this->vbo);
        glGenBuffers(1, &this->ebo);
        
        // Bind them.
        glBindVertexArray(this->vao);
        
        // Fill the VBo with the vertices.
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
        
        // Fill the indices into the EBO.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
        
        // Pass the data to the layout.
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        
        // Unbind everything.
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }

    Cubemap Skybox::getCubemap() {
        
        return this->cubemap;
        
    }

    void Skybox::setCubemap(Cubemap cubemap) {
        
        this->cubemap = cubemap;
        
    }

    void Skybox::draw(Shader &shader, Camera &camera) {
        
        // We do this so that OpenGL does not discard the object.
        glDepthFunc(GL_LEQUAL);

        // Activate the shader.
        shader.activate();
                
        // Apply this tranformation to the view so that it won't move with the camera.
        glm::mat4 view = glm::mat4(glm::mat3(camera.getView()));
        glm::mat4 projection = camera.getProjection();

        // Pass these matrices to the shaders.
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "View"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "Projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Draws the cubemap as the last object so we can save a bit of performance by discarding all fragments
        // where an object is present (a depth of 1.0f will always fail against any object's depth value)
        glBindVertexArray(this->vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap.getID());
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Switch back to the normal depth function
        glDepthFunc(GL_LESS);

	}

}  // namespace bgq_opengl
