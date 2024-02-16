/**
 * @file vao.cpp
 * @brief VAO class implementation file.
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

#include "vao.h"

#include "GL/glew.h"

#include "classes/vbo/vbo.h"

namespace bgq_opengl {

	VAO::VAO() {

		// Generate the buffer.
		glGenVertexArrays(1, &this->ID);
		glBindBuffer(GL_ARRAY_BUFFER, this->ID);

	}

	void VAO::bind() {

		// Bind the VAO.
		glBindVertexArray(this->ID);

	}

	void VAO::link_attribute(VBO& vbo, GLuint layout, GLuint num_components, GLenum type,
		GLsizeiptr step, void* offset) {

		// Bind the VBO.
		vbo.bind();

		// Tell OpenGL where the data in the VBO is located and activate the layout.
		glVertexAttribPointer(layout, num_components, type, GL_FALSE, (GLsizei) step, offset);
		glEnableVertexAttribArray(layout);

		// Unbind the vbo again.
		vbo.unbind();

	}

	void VAO::remove() {

		// Deletes the VAO from the GL pipe.
		glDeleteVertexArrays(1, &this->ID);

	}

	void VAO::unbind() {

		// Unbind the VAO by binding no VAO.
		glBindVertexArray(0);

	}

} // namespace bgq_opengl
