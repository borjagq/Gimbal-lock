/**
 * @file main.h
 * @brief Main header aladdin 3d file.
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

#ifndef BGQ_OPENGL_MAIN_H_
#define BGQ_OPENGL_MAIN_H_

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 800
#define GAME_NAME "Real-time animation"
#define NORM_SIZE 1.0

#include <vector>
#include <string>
#include <ctime>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "classes/camera/camera.h"
#include "classes/object/object.h"
#include "classes/shader/shader.h"
#include "classes/skybox/skybox.h"
#include "classes/texture/texture.h"
#include "classes/turbulence/turbulence.h"

std::vector<bgq_opengl::Camera> cameras;	/// Holds all the existing cameras.
std::vector<bgq_opengl::Object> objects;	/// Holds all the displayed objects.
std::vector<bgq_opengl::Shader> shaders;    /// Holds all the initialized shanders.
std::vector<bgq_opengl::Skybox> skyboxes;   /// Holds all the initialized skyboxes.
int current_camera = 0;                     /// Current camera activated.
int current_shader = 0;                     /// Current shader activated.
int current_scene = 0;
GLFWwindow *window = 0;						/// Window ID.
double internal_time = 0;					/// Time that will rule everything in the game.
double time_start = 0;						/// Time that will count as the beginning.
bgq_opengl::Light scene_light;              /// The light in the scene.
float pitching = 0.0;
float rolling = 0.0;
float yawing = 0.0;
float propeller_rpm = 5 * 60;
bgq_opengl::Turbulence *turbulence_pitching;
bgq_opengl::Turbulence *turbulence_rolling;

const glm::vec4 background(82 / 255.0, 103 / 255.0, 125 / 255.0, 1.0);	/// This is just the fog color.

/**
 * @brief Clean everything to end the program.
 *
 * Clean everything to end the program.
 */
void clean();

/**
 * @brief Clear the viewport.
 *
 * Clear the viewport before printing anything else.
 */
void clear();

/**
 * @brief Display the OpenGL elements.
 *
 * Display all the OpenGL elements in the scene.
 */
void displayElements();

/**
 * @brief Display the GUI.
 *
 * This function will display the GUI elements.
 */
void displayGUI();

/**
 * @brief Handles the key events.
 *
 * Handles the freeglut key events.
 */
void handleKeyEvents(unsigned char key, int x, int y);

/**
 * @brief Init the elements of the program
 *
 * Initialize the objects, elements and all.
 */
void initElements();

/**
 * @brief Init the environment.
 *
 * Initialize the OpenGL, Glew and Freeglut environments.
 */
void initEnvironment(int argc, char** argv);

/**
 * @brief Main function.
 * 
 * Main function.
 */
int main(int argc, char** argv);

#endif  //!BGQ_OPENGL_MAIN_H_
