/**
 * @file main.cpp
 * @brief Main aladdin 3d file.
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

#define GLM_ENABLE_EXPERIMENTAL

#include "main.h"

#include <math.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/common.hpp"
#include "glm/gtx/string_cast.hpp"

#include "classes/camera/camera.h"
#include "classes/cubemap/cubemap.h"
#include "classes/light/light.h"
#include "classes/object/object.h"
#include "classes/shader/shader.h"
#include "classes/skybox/skybox.h"
#include "structs/bounding_box/bounding_box.h"

void clean() {

	// Delete all the shaders.
	for (size_t i = 0; i < shaders.size(); i++)
		shaders[i].remove();
    
    // Terminate ImGUI.
    ImGui_ImplGlfwGL3_Shutdown();
    
    // Close GL context and any other GLFW resources.
    glfwTerminate();

}

void clear() {
    
    // Specify the color of the background
    glClearColor(background.x, background.y, background.z, background.w);

    // Clean the back buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
}

void displayElements() {
    
    // Get the program internal time.
    auto current_time = std::chrono::system_clock::now();
    double real_time = std::chrono::duration<double>(current_time.time_since_epoch()).count();
    internal_time = real_time - time_start;
    
    // Pass the parameters to the shaders.
    shaders[current_shader].activate();
    shaders[current_shader].passLight(scene_light);
    
    // Choose the scene.
    if (current_scene == 0) {
        
        // Print all the objects.
        for (int i = 0; i < objects.size(); i++) {
            
            // Get info from the model.
            bgq_opengl::BoundingBox bb = objects[i].getBoundingBox();
            glm::vec3 centre = (bb.min + bb.max) / 2.0f;
            glm::vec3 size = bb.max - bb.min;
            float max_dim = std::max(size.x, std::max(size.y, size.z));
            float scale_rat = NORM_SIZE / max_dim;
            
            objects[i].resetTransforms();
            
            // Resize it to normalize it.
            objects[i].scale(scale_rat, scale_rat, scale_rat);
            
            // Rotate
            // Apply the rotations.
            // The order is relevant.
            objects[i].rotate(0.0, 1.0, 0.0, yawing);
            objects[i].rotate(1.0, 0.0, 0.0, pitching);
            objects[i].rotate(0.0, 0.0, 1.0, rolling);
            
            // If we are on camera 1, that means rotating.
            if (current_camera == 1) {
                
                cameras[current_camera].resetTransforms();
                cameras[current_camera].rotate(0.0, 1.0, 0.0, yawing);
                cameras[current_camera].rotate(1.0, 0.0, 0.0, pitching);
                cameras[current_camera].rotate(0.0, 0.0, 1.0, rolling);
                
            }
            
            // Center the object and get it in the right position.
            objects[i].translate(-centre.x, -centre.y, -centre.z);
            
            // Do the same but for the propeller.
            int propeller_ind = 0;
            bgq_opengl::BoundingBox bb_propeller = objects[i].getGeometries()[propeller_ind].getBoundingBox();
            glm::vec3 centre_propeller = (bb_propeller.min + bb_propeller.max) / 2.0f;
            
            // bring it back to its original position.
            objects[i].translate(propeller_ind, centre_propeller.x, centre_propeller.y, centre_propeller.z);
            
            // Rotate it as if was running.
            float current_rev = fmod((internal_time * propeller_rpm / 60 * 360), 360);
            objects[i].rotate(propeller_ind, 0.0, 0.0, 1.0, current_rev);

            // Center the object and get it in the right position.
            objects[i].translate(propeller_ind, -centre_propeller.x, -centre_propeller.y, -centre_propeller.z);
            
            // Pass variables to the shaders.
            shaders[current_shader].activate();
            shaders[current_shader].passFloat("etaR", 1.0f);
            shaders[current_shader].passFloat("etaG", 1.0f);
            shaders[current_shader].passFloat("etaB", 1.0f);
            shaders[current_shader].passFloat("fresnelPower", 0.0f);
            shaders[current_shader].passFloat("mixColor", 0.2f);
            shaders[current_shader].passFloat("lightPower", 10.0f);
            shaders[current_shader].passFloat("minAmbientLight", 0.5f);
            shaders[current_shader].passFloat("materialShininess", 0.5f);
            
            // Pass the textures.
            bgq_opengl::Cubemap skycubemap = skyboxes[0].getCubemap();
            skycubemap.bind();
            shaders[current_shader].passCubemap(skycubemap);
            
            // Draw the object.
            objects[i].getGeometries()[0].draw(shaders[current_shader], cameras[current_camera]);
            objects[i].getGeometries()[1].draw(shaders[current_shader], cameras[current_camera]);
            
            shaders[current_shader].passFloat("mixColor", 0.6f);
            objects[i].getGeometries()[2].draw(shaders[current_shader], cameras[current_camera]);

        }
        
    } else if (current_scene == 1) {
        
        // Print all the objects.
        for (int i = 0; i < objects.size(); i++) {
            
            // Get info from the model.
            bgq_opengl::BoundingBox bb = objects[i].getBoundingBox();
            glm::vec3 centre = (bb.min + bb.max) / 2.0f;
            glm::vec3 size = bb.max - bb.min;
            float max_dim = std::max(size.x, std::max(size.y, size.z));
            float scale_rat = NORM_SIZE / max_dim;
            
            objects[i].resetTransforms();
            
            // Resize it to normalize it.
            objects[i].scale(scale_rat, scale_rat, scale_rat);
            
            // Rotate
            // Build the quaternion.
            glm::vec3 euler_angles(pitching, yawing, rolling);
            euler_angles = glm::radians(euler_angles);
            glm::quat rot_quat = glm::quat(euler_angles);
            glm::mat4 rotation = glm::toMat4(rot_quat);
            
            // Loop through the geometries to apply it individually, as each
            // could have a different transform matrix (hierarchy, you know).
            for (int j = 0; j < objects[i].getNumOfGeometries(); j++) {
                                
                // Get this transform matrix.
                glm::mat4 trans = objects[i].getTransformMat(j);
                
                // Set this quaternion matrix as the transfrom matrix.
                objects[i].setTransformMat(j, trans * rotation);

            }
            
            // If we are on camera 1, that means rotating.
            if (current_camera == 1) {
                
                cameras[current_camera].resetTransforms();
                
                // Get this transform matrix.
                glm::mat4 trans = cameras[current_camera].getTransformMat();
                
                // Set this quaternion matrix as the transfrom matrix.
                cameras[current_camera].setTransformMat(trans * rotation);
                
            }
            
            // Center the object and get it in the right position.
            objects[i].translate(-centre.x, -centre.y, -centre.z);
            
            // Do the same but for the propeller.
            int propeller_ind = 0;
            bgq_opengl::BoundingBox bb_propeller = objects[i].getGeometries()[propeller_ind].getBoundingBox();
            glm::vec3 centre_propeller = (bb_propeller.min + bb_propeller.max) / 2.0f;
            
            // bring it back to its original position.
            objects[i].translate(propeller_ind, centre_propeller.x, centre_propeller.y, centre_propeller.z);
            
            // Rotate it as if was running.
            float current_rev = fmod((internal_time * propeller_rpm / 60 * 360), 360);
            objects[i].rotate(propeller_ind, 0.0, 0.0, 1.0, current_rev);

            // Center the object and get it in the right position.
            objects[i].translate(propeller_ind, -centre_propeller.x, -centre_propeller.y, -centre_propeller.z);
            
            // Pass variables to the shaders.
            shaders[current_shader].activate();
            shaders[current_shader].passFloat("etaR", 1.0f);
            shaders[current_shader].passFloat("etaG", 1.0f);
            shaders[current_shader].passFloat("etaB", 1.0f);
            shaders[current_shader].passFloat("fresnelPower", 0.0f);
            shaders[current_shader].passFloat("mixColor", 0.2f);
            shaders[current_shader].passFloat("lightPower", 10.0f);
            shaders[current_shader].passFloat("minAmbientLight", 0.5f);
            shaders[current_shader].passFloat("materialShininess", 0.5f);
            
            // Pass the textures.
            bgq_opengl::Cubemap skycubemap = skyboxes[0].getCubemap();
            skycubemap.bind();
            shaders[current_shader].passCubemap(skycubemap);
            
            // Draw the object.
            objects[i].getGeometries()[0].draw(shaders[current_shader], cameras[current_camera]);
            objects[i].getGeometries()[1].draw(shaders[current_shader], cameras[current_camera]);
            
            shaders[current_shader].passFloat("mixColor", 0.6f);
            objects[i].getGeometries()[2].draw(shaders[current_shader], cameras[current_camera]);

        }

    } else if (current_scene == 2) {
        
        // Print all the objects.
        for (int i = 0; i < objects.size(); i++) {
            
            // Get info from the model.
            bgq_opengl::BoundingBox bb = objects[i].getBoundingBox();
            glm::vec3 centre = (bb.min + bb.max) / 2.0f;
            glm::vec3 size = bb.max - bb.min;
            float max_dim = std::max(size.x, std::max(size.y, size.z));
            float scale_rat = NORM_SIZE / max_dim;
            
            objects[i].resetTransforms();
            
            // Resize it to normalize it.
            objects[i].scale(scale_rat, scale_rat, scale_rat);

            // Calculate the turbulence offsets.
            glm::vec3 turbulence_offset((*turbulence_pitching).solveSinusoids(internal_time), 0.0, (*turbulence_rolling).solveSinusoids(internal_time));
            
            // Rotate
            // Build the quaternion.
            glm::vec3 euler_angles(pitching, yawing, rolling);
            euler_angles = glm::radians(euler_angles + turbulence_offset);
            glm::quat rot_quat = glm::quat(euler_angles);
            glm::mat4 rotation = glm::toMat4(rot_quat);
            
            // Loop through the geometries to apply it individually, as each
            // could have a different transform matrix (hierarchy, you know).
            for (int j = 0; j < objects[i].getNumOfGeometries(); j++) {
                                
                // Get this transform matrix.
                glm::mat4 trans = objects[i].getTransformMat(j);
                
                // Set this quaternion matrix as the transfrom matrix.
                objects[i].setTransformMat(j, trans * rotation);

            }
            
            // Center the object and get it in the right position.
            objects[i].translate(-centre.x, -centre.y, -centre.z);
            
            // Do the same but for the propeller.
            int propeller_ind = 0;
            bgq_opengl::BoundingBox bb_propeller = objects[i].getGeometries()[propeller_ind].getBoundingBox();
            glm::vec3 centre_propeller = (bb_propeller.min + bb_propeller.max) / 2.0f;
            
            // bring it back to its original position.
            objects[i].translate(propeller_ind, centre_propeller.x, centre_propeller.y, centre_propeller.z);
            
            // Rotate it as if was running.
            float current_rev = fmod((internal_time * propeller_rpm / 60 * 360), 360);
            objects[i].rotate(propeller_ind, 0.0, 0.0, 1.0, current_rev);

            // Center the object and get it in the right position.
            objects[i].translate(propeller_ind, -centre_propeller.x, -centre_propeller.y, -centre_propeller.z);
            
            // Pass variables to the shaders.
            shaders[current_shader].activate();
            shaders[current_shader].passFloat("etaR", 1.0f);
            shaders[current_shader].passFloat("etaG", 1.0f);
            shaders[current_shader].passFloat("etaB", 1.0f);
            shaders[current_shader].passFloat("fresnelPower", 0.0f);
            shaders[current_shader].passFloat("mixColor", 0.2f);
            shaders[current_shader].passFloat("lightPower", 10.0f);
            shaders[current_shader].passFloat("minAmbientLight", 0.5f);
            shaders[current_shader].passFloat("materialShininess", 0.5f);
            
            // Pass the textures.
            bgq_opengl::Cubemap skycubemap = skyboxes[0].getCubemap();
            skycubemap.bind();
            shaders[current_shader].passCubemap(skycubemap);
            
            // Draw the object.
            objects[i].getGeometries()[0].draw(shaders[current_shader], cameras[current_camera]);
            objects[i].getGeometries()[1].draw(shaders[current_shader], cameras[current_camera]);
            
            shaders[current_shader].passFloat("mixColor", 0.6f);
            objects[i].getGeometries()[2].draw(shaders[current_shader], cameras[current_camera]);

        }

    }
    
    // Print the skybox.
    skyboxes[0].draw(shaders[1], cameras[current_camera]);
        
}

void displayGUI() {
    
    // Init ImGUI for rendering.
    ImGui_ImplGlfwGL3_NewFrame();
    
    // Begin the new widget.
    ImGui::Begin("Parameters");
    
    // Pass these values to the shaders.
    ImGui::Text("Scene");
    ImGui::RadioButton("Basic euler angles", &current_scene, 0);
    ImGui::RadioButton("Quaternions", &current_scene, 1);
    ImGui::RadioButton("Turbulence", &current_scene, 2);
    
    // Pass these values to the shaders.
    ImGui::Text("Camera");
    ImGui::RadioButton("3rd person", &current_camera, 0);
    ImGui::RadioButton("1st person", &current_camera, 1);

    // Choose the scene.
    if (current_scene == 0) {
        
        ImGui::Text("Rotation");
        ImGui::SliderFloat("Pitching", &pitching, -180.0, 180.0);
        ImGui::SliderFloat("Rolling", &rolling, -180.0, 180.0);
        ImGui::SliderFloat("Yawing", &yawing, -180.0, 180.0);
        
    } else if (current_scene == 1) {
        
        ImGui::Text("Rotation");
        ImGui::SliderFloat("Pitching", &pitching, -180.0, 180.0);
        ImGui::SliderFloat("Rolling", &rolling, -180.0, 180.0);
        ImGui::SliderFloat("Yawing", &yawing, -180.0, 180.0);
        
        
        
    } else if (current_scene == 2) {
        
        ImGui::Text("Rotation");
        ImGui::SliderFloat("Pitching", &pitching, -180.0, 180.0);
        ImGui::SliderFloat("Rolling", &rolling, -180.0, 180.0);
        ImGui::SliderFloat("Yawing", &yawing, -180.0, 180.0);
        
    }
    
    ImGui::Text("Other parameters");
    ImGui::SliderFloat("Propeller RPM", &propeller_rpm, 0.0, 20.0 * 60);
    
    ImGui::End();
    
    // Render ImGUI.
    ImGui::Render();
    
}

void handleKeyEvents() {
    
    // Key W will move camera 0 forward.
    if (ImGui::IsKeyPressed('W')) {

        // Move forward.
        cameras[current_camera].moveFront();
        
    }

    // Key S will move camera 0 backwards.
    if (ImGui::IsKeyPressed('S')) {

        // Move backwards.
        cameras[current_camera].moveBack();

    }

    // Key D will move camera 0 to the right.
    if (ImGui::IsKeyPressed('D')) {

        // Move right.
        cameras[current_camera].moveRight();

    }

    // Key A will move camera 0 to the right.
    if (ImGui::IsKeyPressed('A')) {

        // Move to the left.
        cameras[current_camera].moveLeft();

    }

    // Key R will move camera up.
    if (ImGui::IsKeyPressed('R')) {

        // Move up.
        cameras[current_camera].moveUp();

    }

    // Key F will move camera down.
    if (ImGui::IsKeyPressed('F')) {

        // Move up.
        cameras[current_camera].moveDown();

    }

    // Key E will rotate camera left.
    if (ImGui::IsKeyPressed('E')) {

        // Move up.
        cameras[current_camera].rotateLeft();

    }

    // Key Q will rotate the camera right.
    if (ImGui::IsKeyPressed('Q')) {

        // Move up.
        cameras[current_camera].rotateRight();

    }

    // Key T will bring the camera up.
    if (ImGui::IsKeyPressed('T')) {

        // Move up.
        cameras[current_camera].rotateUp();

    }

    // Key G will bring the camera down.
    if (ImGui::IsKeyPressed('G')) {

        // Move up.
        cameras[current_camera].rotateDown();

    }
    
}

void initElements() {
    
    // Init the turbulence.
    turbulence_pitching = new bgq_opengl::Turbulence(10, -0.2f, 0.2f, 0.0f, 0.0f, 0.1f, 2.0f);
    turbulence_rolling = new bgq_opengl::Turbulence(20, -0.6f, 0.6f, 0.0f, 0.0f, 0.1f, 4.0f);
    
	// Create a white light in the center of the world.
    scene_light = bgq_opengl::Light(glm::vec3(2.0f, 8.0, 2.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	// Get the shaders.
	bgq_opengl::Shader blinn_phong("blinnPhongFresnel.vert", "blinnPhongFresnel.frag");
    shaders.push_back(blinn_phong);

	// Creates the first camera object
    bgq_opengl::Camera camera(glm::vec3(1.0f, 0.5f, 1.0f), glm::vec3(-1.0f, -0.5f, -1.0f), 45.0f, 0.1f, 300.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
	cameras.push_back(camera);
    bgq_opengl::Camera first_person(glm::vec3(0.0f, 0.0f, -1.5f), glm::vec3(0.0f, 0.0f, 1.0f), 45.0f, 0.1f, 300.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
    cameras.push_back(first_person);
    
    // Load the skyboxes.
    std::vector<std::string> faces {
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
    };
    
    // Load the textures.
    bgq_opengl::Cubemap skycubemap(faces, "skybox", 1);
    bgq_opengl::Skybox skybox(skycubemap);
    skyboxes.push_back(skybox);
    
    bgq_opengl::Shader sky_shader("skybox.vert", "skybox.frag");
    shaders.push_back(sky_shader);
    
    // Load the objects.
    bgq_opengl::Object plane("Plane.dae", "Assimp");
    plane.addTexture(0, "Red.jpg", "baseColor");
    plane.addTexture(1, "Red.jpg", "baseColor");
    plane.addTexture(2, "Window.png", "baseColor");
    plane.setShininess(200.0);
    objects.push_back(plane);
    
}

void initEnvironment(int argc, char** argv) {
    
    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit()) {
        
        std::cerr << "ERROR: could not start GLFW3" << std::endl;
        exit(1);

    }
    
    // MacOS initializations.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Create the window.
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME, NULL, NULL);
    if (!window) {
        
        std::cerr << "Error 121-1001 - Failed to create the window." << std::endl;
        glfwTerminate();
        exit(1);

    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW and OpenGL.
    GLenum res = glewInit();

    // Check for any errors.
    if (res != GLEW_OK) {

        std::cerr << "Error 121-1002 - GLEW could not be initialized:" << glewGetErrorString(res) << std::endl;
        exit(1);

    }
    
    // Get version info.
    std::cerr << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cerr << "OpenGL version supported " << glGetString(GL_VERSION) << std::endl;
    std::cerr << "GLSL version supported " << (char *) glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    
    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(window, true);

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
    
    // Init the initial time.
    auto current_time = std::chrono::system_clock::now();
    time_start = std::chrono::duration<double>(current_time.time_since_epoch()).count();

}

int main(int argc, char** argv) {

	// Initialise the environment.
    initEnvironment(argc, argv);
    
	// Initialise the objects and elements.
	initElements();

	// Main loop.
    while(!glfwWindowShouldClose(window)) {
        
        // Clear the scene.
        clear();
        
        // Handle key events.
        handleKeyEvents();
        
        // Display the scene.
        displayElements();
        
        // Make the things to print everything.
        displayGUI();
        
        // Update other events like input handling.
        glfwPollEvents();
        glfwSwapBuffers(window);
        
    }

	// Clean everything and terminate.
	clean();

}
