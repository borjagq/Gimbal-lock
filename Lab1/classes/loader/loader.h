/**
 * @file loader.h
 * @brief Loader class header file.
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

#ifndef BGQ_OPENGL_CLASSES_LOADER_H_
#define BGQ_OPENGL_CLASSES_LOADER_H_

#include <string>
#include <vector>

#include "classes/geometry/geometry.h"

namespace bgq_opengl {

	/**
	 * @brief Implements a Loader class.
	 * 
	 * Implements a loader class that will allow us to load models.
	 * 
	 * @author Borja García Quiroga <garcaqub@tcd.ie>
	 */
	class Loader {

		public:

			/**
			 * @brief Declares the types of Loaders available.
			 *
			 * Declares the types of Loaders available.
			 */
			enum LoaderTypes { GLTF };

			/**
			 * @brief Build a loader instance.
			 * 
			 * Build a loader instance.
			 */
			Loader(const char *filename);

			/**
			 * @brief Get the geometries from the loaded model.
			 *
			 * Get the geometries from the loaded model.
			 *
			 * @param geoms Outputs the geometries returned.
			 * @param matrices Outputs the transformation matrices.
			 */
			virtual void getGeometries(std::vector<Geometry> *geoms, std::vector<glm::mat4> *matrices) = 0;

			/**
			 * @brief Loads the data from the file.
			 * 
			 * Loads the data from the file.
			 */
			virtual void loadModel() = 0;

			/**
			 * @brief Gets the content of a file as a string.
			 *
			 * Gets the contents of a file, given its filename, and returns it as a string.
			 *
			 * @param filename The name of the file to be read.
			 *
			 * @throws 121-1001 Could not read file.
			 */
			static std::string readFileContents(const char* filename);

		protected:

			std::vector<Geometry> geometries;			/// The Geometries loaded by the model loader.
			const char *filename;						/// Name of the file containing the model.
			std::vector<glm::mat4> transform_matrixes;	/// Transform matrixes for each Geometry in the object.

	};

}

#endif  //!BGQ_OPENGL_CLASSES_LOADER_H_
