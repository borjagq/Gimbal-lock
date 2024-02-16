/**
 * @file vbo.h
 * @brief VBO class header file.
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

#ifndef BGQ_OPENGL_CLASS_VBO_H_
#define BGQ_OPENGL_CLASS_VBO_H_

#include <vector>

#include "GL/glew.h"

#include "structs/vertex/vertex.h"

namespace bgq_opengl {

	/**
	 * @brief Implementation of a VBO class.
	 *
	 * Implementation of a VBO class that will allow us to bind it to the
	 * OpenGL pipe, destroy it or deactivate it.
	 *
	 * @author Borja García Quiroga <garcaqub@tcd.ie>
	 */
	class VBO {

	public:

		/**
		 * @brief Constructs a Vertex Buffer Object.
		 *
		 * Constructs a Vertex Buffer Object and links its vertices.
		 *
		 * @param vertices Vertices that will be linked.
		 */
		VBO(const std::vector<Vertex> &vertices);

		/**
		 * @brief Binds the VBO.
		 *
		 * Binds the VBO in the GL pipe.
		 */
		void bind();

		/**
		 * @brief Removes the VBO.
		 *
		 * Removes the VBO from OpenGL.
		 */
		void remove();

		/**
		 * @brief Unbinds the VBO.
		 *
		 * Unbinds the VBO in the GL pipe.
		 */
		void unbind();

	private:

		GLuint ID; // GL ID of the VBO.

	};

}  // namespace bgq_opengl

#endif //!BGQ_OPENGL_CLASS_VBO_H_
