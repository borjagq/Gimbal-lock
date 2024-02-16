/**
 * @file loader.cpp
 * @brief Loader class implementation file.
 * @version 1.0.0 (2022-11-27)
 * @date 2022-11-27
 * @author Borja García Quiroga <garcaqub@tcd.ie>
 *
 *
 * Copyright (c) Borja García Quiroga, All Rights Reserved.
 *
 * The information and material provided below was developed as partial
 * requirements for the MSc in Computer Science at Trinity College Dublin,
 * Ireland.
 */

#include "loader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace bgq_opengl {

	Loader::Loader(const char* filename) {

		this->filename = filename;

	}

    inline void Loader::loadModel() {}

	std::string Loader::readFileContents(const char* filename) {

		// Open the file stream.
		std::ifstream file_stream(filename, std::ios::binary);

		// If it was opened, continue, otherwise, throw an exception.
		if (file_stream) {

			// Init the resulting string.
			std::string file_contents;

			// Set the input to the final position.
			file_stream.seekg(0, std::ios::end);

			// Get the size of the file.
			std::streamoff file_size = file_stream.tellg();
			
			// Resize the string to hold all apropriate data.
			file_contents.resize(file_size);

			// Move the cursor to the beginning.
			file_stream.seekg(0, std::ios::beg);

			// Read the file to the string.
			file_stream.read(&file_contents[0], file_contents.size());

			file_stream.close();

			return(file_contents);

		}

		throw(errno);

    }

}
