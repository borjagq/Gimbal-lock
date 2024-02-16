/**
 * @file vbo.cpp
 * @brief VBO class implementation file.
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

#include "vbo.h"

#include <vector>

#include "GL/glew.h"

#include "structs/vertex/vertex.h"

namespace bgq_opengl {

	VBO::VBO(const std::vector<Vertex> &vertices) {

		// Generate the buffer.
		glGenBuffers(1, &this->ID);
		glBindBuffer(GL_ARRAY_BUFFER, this->ID);

		// Link the vertices.
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	}

	void VBO::bind() {

		// Bind the VBO.
		glBindBuffer(GL_ARRAY_BUFFER, this->ID);

	}

	void VBO::remove() {

		// Delete the buffer in OpenGL.
		glDeleteBuffers(1, &this->ID);

	}

	void VBO::unbind() {

		// Unbind it.
		// To do so, just bind nothing.
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

}  // namespace bgq_opengl
