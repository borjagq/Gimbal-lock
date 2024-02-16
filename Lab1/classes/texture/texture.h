/**
 * @file texture.h
 * @brief Texture class header file.
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

#ifndef BGQ_OPENGL_CLASS_TEXTURE_H_
#define BGQ_OPENGL_CLASS_TEXTURE_H_

#include <string>

#include "GL/glew.h"

namespace bgq_opengl {

	/**
	 * @brief Implements a texture class to handle object textures.
	 * 
	 * Implements a texture object to handle textures and their content to use
	 * with the objects.
	 * 
	 * @author Borja García Quiroga <garcaqub@tcd.ie>
	 */
	class Texture {
	
		public:

			/**
			 * @brief Creates a texture from an image.
			 * 
			 * Creates a textures and passes it to OpenGL.
			 * 
			 * @param image Image containing the texture.
			 * @param type Texture type.
			 * @param slot Texture slot.
			 */
			Texture(const char* image, const char* type, GLuint slot);

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
			 * @brief Gets the width of the image.
			 * 
			 * Gets the width of the image in pixels.
			 * 
			 * @returns The width of the image in pixels.
			 */
			int getWidth();

			/**
			 * @brief Get the height of the image.
			 * 
			 * Gets the height of the image in pixels.
			 * 
			 * @returns The height of the image in pixels.
			 */
			int getHeight();

			/**
			 * @brief Gets the number of channels of the texture.
			 * 
			 * Gets the number of channels that the texture has.
			 * 
			 * @returns The number of channels the texture has.
			 */
			int getChannels();

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

			GLuint ID;					/// Texture OpenGL ID.
			GLuint slot;				/// Stores the texture slot number.
			int texture_width = 0;		/// Width of the texture in pixels.
			int texture_height = 0;		/// Height of the texture in pixels.
			int texture_channels = 0;	/// Number of channels of the texture.
			std::string name;			/// Texture name.

	};

}

#endif // !BGQ_OPENGL_CLASS_TEXTURE_H_
