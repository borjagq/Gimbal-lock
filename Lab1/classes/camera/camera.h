/**
 * @file camera.h
 * @brief Camera class header file.
 * @version 1.0.0 (2022-11-23)
 * @date 2022-11-23
 * @author Borja García Quiroga <garcaqub@tcd.ie>
 *
 *
 * Copyright (c) Borja García Quiroga, All Rights Reserved.
 *
 * The information and material provided below was developed as partial
 * requirements for the MSc in Computer Science at Trinity College Dublin,
 * Ireland.
 */

#ifndef BGQ_OPENGL_CLASSES_CAMERA_H_
#define BGQ_OPENGL_CLASSES_CAMERA_H_

#include "glm/glm.hpp"

namespace bgq_opengl {

	/**
	 * @brief Implements a camera class.
	 * 
	 * Implements a camera class to handle the POV of OpenGL as well as the interactions
	 * with the window.
	 * 
	 * @author Borja García Quiroga <garcaqub@tcd.ie>
	 */
	class Camera {

		public:

			/**
			 * @brief Constructs a camera instance.
			 * 
			 * Constructs a camera instance and sets its initial values.
			 * 
			 * @param position The camera coordinates.
			 * @param direction Where the camera is looking.
			 * @param fov Camera field of view.
			 * @param near Minimum distance rendered.
			 * @param far maximum distance rendered.
			 * @param width The camera width.
			 * @param height The camera height.
			 */
			Camera(glm::vec3 position, glm::vec3 direction, float fov, float near, float far, int width, int height);

			/**
			 * @brief Get the camera matrix.
			 *
			 * Get the camera matrix.
			 */
			glm::mat4 getCameraMatrix();

			/**
			 * @brief Get the camera direction.
			 * 
			 * Get the camera direction.
			 */
			glm::vec3 getDirection();

			/**
			 * @brief Get the camera position.
			 *
			 * Get the camera position.
			 */
			glm::vec3 getPosition();

			/**
			 * @brief Get the projection matrix.
			 * 
			 * Get the projection matrix corresponding to this camera.
			 */
			glm::mat4 getProjection();

			/**
			 * @brief Get the camera up vector.
			 *
			 * Get the camera up vector.
			 */
			glm::vec3 getUp();

			/**
			 * @brief Get the view matrix.
			 * 
			 * Get the view matrix corresponding to this camera.
			 */
			glm::mat4 getView();

			/**
			 * @brief Move tha camera backwards.
			 * 
			 * Move tha camera backwards.
			 */
			void moveBack();

			/**
			 * @brief Move tha camera down.
			 *
			 * Move tha camera down.
			 */
			void moveDown();

			/**
			 * @brief Move the camera forward.
			 * 
			 * Move the camera forward.
			 */
			void moveFront();

			/**
			 * @brief Move the camera: to the left, to the left.
			 *
			 * Move the camera: to the left, to the left.
			 */
			void moveLeft();

			/**
			 * @brief Move the camera to the right.
			 *
			 * Move the camera to the right.
			 */
			void moveRight();
			
			/**
			 * @brief Move tha camera up.
			 *
			 * Move tha camera up.
			 */
			void moveUp();

			/**
			 * @brief Rotate the camera down.
			 * 
			 * Rotate the camera down.
			 */
			void rotateDown();

			/**
			 * @brief Rotate the camera left.
			 * 
			 * Rotate the camera left.
			 */
			void rotateLeft();

			/**
			 * @brief Rotate the camera right.
			 * 
			 * Rotate the camera right.
			 */
			void rotateRight();

			/**
			 * @brief Rotate the camera up.
			 * 
			 * Rotate the camera up.
			 */
			void rotateUp();
        
            /**
             * @brief Reset
             *
             * Add a translation matrix to the model.
             */
            void resetTransforms();

            /**
             * @brief Add a translation matrix to the camera.
             *
             * Add a translation matrix to the camera.
             *
             * @param x The x rotation.
             * @param y The y rotation.
             * @param z The z rotation.
             * @param angle The angle to rotate.
             */
            void rotate(float x, float y, float z, float angle);

            /**
             * @brief Add a translation matrix to the camera.
             *
             * Add a translation matrix to the camera.
             *
             * @param x The x translation.
             * @param y The y translation.
             * @param z The z translation.
             */
            void translate(float x, float y, float z);
        
            /**
             * @brief Get the current transform matrix.
             *
             * Get the current transform matrix.
             *
             * @returns The transform matrix.
             */
            glm::mat4 getTransformMat();
        
            /**
             * @brief Set the transform matrix.
             *
             * Set the transform matrix.
             *
             * @param transform The transform matrix.
             */
            void setTransformMat(glm::mat4 transform);

		private:

			glm::vec3 direction;		/// Vector indicating where the camera is looking.
			float far;					/// Maximum clipping limit.
			float fov;					/// Field of view;
			float near;					/// Minimum clipping limit.
			glm::vec3 position;			/// Coordinates of the camera.
			glm::vec3 up;				/// Vector that tells us the rotation of the camera.
			int window_height;			/// Height of the GLUT window.
			int window_width;			/// Width of the GLUT window.
            glm::mat4 transforms = glm::mat4(1.0f); /// Tranform matrixes that will be passed to the shader.

			const float speed = 0.25f;				/// Speed of the camera movement.
			const float horizontal_rotation = 3.0f;	/// How much it rotates for every step.
			const float vertical_rotation = 0.1f;	/// How much it rotates for every step.

	};

}  // namespace bgq_opengl

#endif  //!BGQ_OPENGL_CLASSES_CAMERA_H_
