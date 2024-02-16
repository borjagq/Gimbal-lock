/**
 * @file texture.cpp
 * @brief Texture class implementation file.
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

#define STB_IMAGE_IMPLEMENTATION

#include "texture.h"

#include <assert.h>

#include "GL/glew.h"
#include "stb/stb_image.h"

namespace bgq_opengl {

	Texture::Texture(const char* image, const char* name, GLuint slot) {
        
        // The slot has to be a positive number because OpenGL does weird stuff on macOS else.
        if (slot < 1) assert(false);

		// Generate a texture in OpenGL and store the parameters in the attributes.
		glGenTextures(1, &this->ID);
		this->name = std::string(name);
		this->slot = slot;

		// This function has to be used because OpenGL loads texture the opposite way
		// than this library, so images appear upside down.
		stbi_set_flip_vertically_on_load(true);

		// Read the texture image and its information.
		unsigned char* image_bytes = stbi_load(image, &this->texture_width,
				&this->texture_height, &this->texture_channels, 0);

		// Set the slot for the texture.
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, this->ID);

		// Configure the magnifying algorithm, minifying algorithm and repetition.
		// This tells OpenGL how to apply intrpolation.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Get the color model for the image.
		GLenum color_model = GL_RGBA;

		if (this->texture_channels == 4)
			color_model = GL_RGBA;
		else if (this->texture_channels == 3)
			color_model = GL_RGB;
		else if (this->texture_channels == 1)
			color_model = GL_RED;
		else
			assert(false);

		// Load the image to OpenGL.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->texture_width, this->texture_height,
				0, color_model, GL_UNSIGNED_BYTE, image_bytes);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Clean the memory.
		stbi_image_free(image_bytes);

		// Unbinds the OpenGL Texture.
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	GLuint Texture::getID() {

		return this->ID;

	}

	GLuint Texture::getSlot() {

		return this->slot;

	}

	int Texture::getWidth() {

		return this->texture_width;

	}

	int Texture::getHeight() {

		return this->texture_height;

	}

	int Texture::getChannels() {

		return this->texture_channels;

	}

	std::string Texture::getName() {

		return this->name;

	}

	void Texture::bind() {

		// Activate the texture and bind it.
		glActiveTexture(GL_TEXTURE0 + this->slot);
		glBindTexture(GL_TEXTURE_2D, this->ID);

	}

	void Texture::remove() {

		glDeleteTextures(1, &this->ID);

	}

	void Texture::unbind() {

		glBindTexture(GL_TEXTURE_2D, 0);

	}

} // namespace bgq_opengl
