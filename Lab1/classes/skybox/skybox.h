/**
 * @file skybox.h
 * @brief Skybox class header file.
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

#ifndef BGQ_OPENGL_CLASSES_SKYBOX_H_
#define BGQ_OPENGL_CLASSES_SKYBOX_H_

#include <vector>

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "classes/camera/camera.h"
#include "classes/shader/shader.h"
#include "classes/cubemap/cubemap.h"
#include "classes/ebo/ebo.h"
#include "classes/vbo/vbo.h"
#include "classes/vao/vao.h"
#include "structs/vertex/vertex.h"
#include "structs/bounding_box/bounding_box.h"

namespace bgq_opengl {

	/**
	* @brief Implementation of a Skybox class.
	*
	* Implementation of a Geometry class that will allow us to handle the geometric part
	* of the objects in the VBOs.
	*
	* @author Borja García Quiroga <garcaqub@tcd.ie>
	*/
	class Skybox {

		public:
			
			/**
			 * @brief Initializes the Skybox.
			 * 
			 * Initializes the geometry and stores it.
			 *
			 * @param cubemap Textures in connection with this geometry.
			 */
            Skybox(Cubemap cubemap);
			
			/**
			 * @brief Get the textures.
			 *
			 * Get the textures.
             *
             * @returns The cubemap.
			 */
			Cubemap getCubemap();
        
            /**
             * @brief Get the textures.
             *
             * Get the textures.
             *
             * @param cubemap The cubemap that will be set as the current cubemap.
             */
            void setCubemap(Cubemap cubemap);

			/**
			 * @brief Draws the Geometry.
			 *
			 * Displays the Geometry in OpenGL.
			 */
			void draw(Shader &shader, Camera &camera);

		private:

            Cubemap cubemap = Cubemap(0, "", 0);    /// The cubemap texture that will color this skybox.
            unsigned int vao, vbo, ebo;             /// The IDs of the buffers of OpenGL.

	};

}  // namespace bgq_opengl

#endif  //! BGQ_OPENGL_CLASSES_SKYBOX_H_
