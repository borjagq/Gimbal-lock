/**
 * @file object.h
 * @brief Object class header file.
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

#ifndef BGQ_OPENGL_CLASSES_OBJECT_H_
#define BGQ_OPENGL_CLASSES_OBJECT_H_

#include <vector>

#include "classes/geometry/geometry.h"
#include "structs/bounding_box/bounding_box.h"

namespace bgq_opengl {

	class Object {
	
		public:
			
			/**
			 * @brief Loads a model in the specified format.
			 *
			 * Loads in a model from a file.
			 * 
			 * @param filename The name of the model file.
			 * @param filetype The type of the model file.
			 */
			Object(const char* filename, const char *filetype);

			/**
			 * @brief Loads the object from specified geometries.
			 * 
			 * Loads the object from specified geometries.
			 * 
			 * @param geometries The geometries that will be part of the object.
			 */
			Object(std::vector<Geometry> geometries);
        
            /**
             * @brief Add a new texture to all geometries.
             *
             * Add a new texture that will be passed to the shader.
             *
             * @param image Image containing the texture.
             * @param name Texture type.
             */
            void addTexture(const char* image, const char* name);
            
            /**
             * @brief Add a new texture to the specified geometry.
             *
             * Add a new texture that will be passed to the shader.
             *
             * @param num The geometry index this will apply to.
             * @param image Image containing the texture.
             * @param name Texture type.
             */
            void addTexture(int num, const char* image, const char* name);

			/**
			 * @brief Draws this object.
			 *
			 * Draws this object.
			 */
			void draw(Shader &shader, Camera &camera);

			/**
			 * @brief Gets the bounding box.
			 *
			 * Gets the bounding box of all the geometries.
			 *
			 * @returns The bounding box struct.
			 */
			BoundingBox getBoundingBox();

			/**
			 * @brief Get the geometries of the object.
			 * 
			 * Get the geometries of the object.
			 */
			std::vector<Geometry> getGeometries();

			/**
			 * @brief Get the matrices of the geometries.
			 * 
			 * Get the matrices of the geometries.
			 */
			std::vector<glm::mat4> getGeometryMatrices();
        
            /**
             * @brief Set the object shininess.
             *
             * Set the object shininess.
             */
            void setShininess(float shine);
        
            /**
             * @brief Get the current transform matrix.
             *
             * Get the current transform matrix.
             *
             * @param num The geometry index this will apply to.
             *
             * @returns The transform matrix.
             */
            glm::mat4 getTransformMat(int num);

            /**
             * @brief Set the transform matrix.
             *
             * Set the transform matrix.
             *
             * @param num The geometry index this will apply to.
             * @param transform The transform matrix.
             */
            void setTransformMat(int num, glm::mat4 transform);
        
            /**
             * @brief Get the number of geometries.
             *
             * Get the number of geometries inside this object.
             *
             * @returns The number of geometries.
             */
            size_t getNumOfGeometries();

			/**
			 * @brief Reset 
			 *
			 * Add a translation matrix to the model.
			 */
			void resetTransforms();

			/**
			 * @brief Add a translation matrix to the model.
			 *
			 * Add a translation matrix to the model.
			 *
			 * @param x The x rotation.
			 * @param y The y rotation.
			 * @param z The z rotation.
			 * @param angle The angle to rotate.
			 */
			void rotate(float x, float y, float z, float angle);

			/**
			 * @brief Add a translation matrix to the model.
			 *
			 * Add a translation matrix to the model.
			 *
			 * @param num The geometry index this will apply to.
			 * @param x The x rotation.
			 * @param y The y rotation.
			 * @param z The z rotation.
			 * @param angle The angle to rotate.
			 */
			void rotate(int num, float x, float y, float z, float angle);

			/**
			 * @brief Add a translation matrix to the model.
			 *
			 * Add a translation matrix to the model.
			 *
			 * @param x The x scale.
			 * @param y The y scale.
			 * @param z The z scale.
			 */
			void scale(float x, float y, float z);

			/**
			 * @brief Add a translation matrix to the model.
			 *
			 * Add a translation matrix to the model.
			 *
			 * @param num The geometry index this will apply to.
			 * @param x The x scale.
			 * @param y The y scale.
			 * @param z The z scale.
			 */
			void scale(int num, float x, float y, float z);

			/**
			 * @brief Add a translation matrix to the model.
			 * 
			 * Add a translation matrix to the model.
			 * 
			 * @param x The x translation.
			 * @param y The y translation.
			 * @param z The z translation.
			 */
			void translate(float x, float y, float z);

			/**
			 * @brief Add a translation matrix to the model.
			 *
			 * Add a translation matrix to the model.
			 * 
			 * @param num The geometry index this will apply to.
			 * @param x The x translation.
			 * @param y The y translation.
			 * @param z The z translation.
			 */
			void translate(int num, float x, float y, float z);

		private:

			// All the geometries and transformations
			std::vector<Geometry> geoms;
			std::vector<glm::mat4> matrices_geoms;

	};

}

#endif  //!BGQ_OPENGL_CLASSES_OBJECT_H_
