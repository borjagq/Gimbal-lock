/**
 * @file cubemap.h
 * @brief Cubemap class header file.
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
 *
 * This code is largely based on learnopengl.org tutorials.
 */

#ifndef BGQ_OPENGL_CLASSES_CUBEMAP_H_
#define BGQ_OPENGL_CLASSES_CUBEMAP_H_

#include <string>
#include <vector>

#include "GL/glew.h"

namespace bgq_opengl {

    /**
     * @brief Implements a skybox class.
     *
     * Implements a skybox class to handle the background texture on OpenGL.
     *
     * @author Borja García Quiroga <garcaqub@tcd.ie>
     */
    class Cubemap {

        public:
        
            /**
             * @brief Copies a cubemap from another.
             *
             * Copies a cubemap from another.
             *
             * @param id The cubemap to be copied.
             * @param name The name of this texture.
             * @param slot The slot for this texture.
             */
            Cubemap(GLuint id, std::string name, GLuint slot);

            /**
             * @brief Constructs a skybox instance.
             *
             * Constructs a skybox instance.
             *
             * @param textures_faces A vector containing the skybox faces in the right, left, top, bottom, back, and front order.
             * @param type Texture type.
             * @param slot Texture slot.
             */
            Cubemap(const std::vector<std::string> &textures_faces, const char* type, GLuint slot);

            /**
             * @brief Get the ID of the texture.
             *
             * Get the ID of the texture.
             *
             * @returns The ID of the texture.
             */
            GLuint getID();

            /**
             * @brief Get the slot of the texture.
             *
             * Get the slot of the texture.
             *
             * @returns The slot of the texture.
             */
            GLuint getSlot();

            /**
             * @brief Gets the texture name.
             *
             * Gets the texture name as a char array.
             *
             * @returns A char string containing the name name of the texture.
             */
            std::string getName();

            /**
             * @brief Binds the texture.
             *
             * Binds the texture.
             */
            void bind();

            /**
             * @brief Removes the texture from OpenGL.
             *
             *  Removes the texture from OpenGL.
             */
            void remove();

            /**
             * @brief Unbinds the texture.
             *
             * Unbinds the texture.
             */
            void unbind();

        private:

            GLuint ID;                      /// Texture OpenGL ID.
            GLuint slot;                    /// Stores the texture slot number.
            std::string name;               /// Texture name.

    };

}  // namespace bgq_opengl

#endif  //!BGQ_OPENGL_CLASSES_CUBEMAP_H_
