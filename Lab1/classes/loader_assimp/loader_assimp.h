/**
 * @file loader_assimp.h
 * @brief Loader GLTF class header file.
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

#ifndef BGQ_OPENGL_CLASSES_LOADER_ASSIMP_H_
#define BGQ_OPENGL_CLASSES_LOADER_ASSIMP_H_

#include "classes/loader/loader.h"

#include <vector>

#include "glm/glm.hpp"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace bgq_opengl {

	/**
	 * @brief Implements a GLTF Loader class.
	 *
	 * Implements a loader class that will allow us to load GLTF models.
	 *
	 * @author Borja García Quiroga <garcaqub@tcd.ie>
	 */
	class LoaderAssimp : public Loader {

		public:

			/**
			 * @brief Build a loader instance.
			 *
			 * Build a loader instance.
			 */
			LoaderAssimp(const char* filename);

			/**
			 * @brief Get the geometries from the loaded model.
			 * 
			 * Get the geometries from the loaded model.
			 * 
			 * @param geoms Outputs the geometries returned.
			 * @param matrices Outputs the transformation matrices.
			 */
			void getGeometries(std::vector<Geometry> *geoms, std::vector<glm::mat4> *matrices);

			/**
			 * @brief Loads the data from the file.
		 	 *
			 * Loads the data from the file.
			 */
			void loadModel();

		private:

			/**
			 * @brief Loads a mesh by its index.
			 *
			 * Loads a mesh by its index.
			 *
			 * @param mesh the assimp  mesh.
			 */
			void loadGeometry(const aiScene* scene, const aiMesh* mesh);
        
            /**
             * @brief Load the textures for this model.
             *
             * Load the textures for this model.
             */
            std::vector<bgq_opengl::Texture> getTextures();

	};

}

#endif  //!BGQ_OPENGL_CLASSES_LOADER_ASSIMP_H_

