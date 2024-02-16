/**
 * @file vao.h
 * @brief VAO class header file.
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

#ifndef BGQ_OPENGL_CLASS_VAO_H_
#define BGQ_OPENGL_CLASS_VAO_H_

#include "GL/glew.h"

#include "classes/vbo/vbo.h"

namespace bgq_opengl {

	/**
	 * @brief Implementation of a VAO class.
	 *
	 * Implementation of a VAO class that will allow us to bind it to the
	 * OpenGL pipe, destroy it or deactivate it.
	 *
	 * @author Borja García Quiroga <garcaqub@tcd.ie>
	 */
	class VAO {

	public:

		/**
		 * @brief Constructs a Vertex Array Object.
		 *
		 * Constructs a Vertex Array Object.
		 */
		VAO();

		/**
		 * @brief Binds the VBO.
		 *
		 * Binds the VBO in the GL pipe.
		 */
		void bind();

		/**
		 * @brief Links a VBO attribute to the VAO.
		 *
		 * Links a VBO attribute such as color, UV, or others.
		 *
		 * @param vbo The VBO to link the attribute to.
		 * @param layout The layout identifier that will be used in the shader.
		 * @param num_components The number of components that are in the list.
		 * @param type The type of data that we will be passing.
		 * @param step The amount of bytes we have to skip to find the next item.
		 * @param offset The amount of data we have to skip to find the first item.
		 */
		void link_attribute(VBO& vbo, GLuint layout, GLuint num_components, GLenum type,
			GLsizeiptr step, void* offset);

		/**
		 * @brief Remove the VAO.
		 *
		 * Removes the VAO in GL.
		 */
		void remove();

		/**
		 * @brief Unbinds the VBO.
		 *
		 * Unbinds the VBO in the GL pipe.
		 */
		void unbind();

	private:

		GLuint ID; /// OpenGL VAO ID.
	};

}  // namespace bgq_opengl

#endif  //! BGQ_OPENGL_CLASS_VAO_H_
