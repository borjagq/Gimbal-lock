/**
 * @file ebo.cpp
 * @brief EBO class implementation file.
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

#include "ebo.h"

#include <vector>

#include "GL/glew.h"

namespace bgq_opengl {

	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO::EBO(const std::vector<GLuint> &indices) {
		
		// Generate the buffer.
		glGenBuffers(1, &this->ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);

		// Link the indices.
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	
	}

	void EBO::bind() {

		// Binds the EBO.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
	
	}

	void EBO::remove() {

		glDeleteBuffers(1, &this->ID);

	}

	void EBO::unbind() {

		// Unbinds the EBO.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	}	

}  // namespace bgq_opengl
