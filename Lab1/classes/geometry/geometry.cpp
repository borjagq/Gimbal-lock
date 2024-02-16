/**
 * @file geometry.cpp
 * @brief Geometry class implementation file.
 * @version 1.0.0 (2022-11-26)
 * @date 2022-11-26
 * @author Borja García Quiroga <garcaqub@tcd.ie>
 *
 *
 * Copyright (c) Borja García Quiroga, All Rights Reserved.
 *
 * The information and material provided below was developed as partial
 * requirements for the MSc in Computer Science at Trinity College Dublin,
 * Ireland.
 */

#include "geometry.h"

#include <vector>
#include <stdexcept>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "classes/camera/camera.h"
#include "classes/ebo/ebo.h"
#include "classes/shader/shader.h"
#include "classes/texture/texture.h"
#include "classes/vao/vao.h"
#include "structs/vertex/vertex.h"
#include "structs/bounding_box/bounding_box.h"

namespace bgq_opengl {

	Geometry::Geometry(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices, const std::vector<Texture> &textures, const float shininess) {

		// Store a copy of these in the attributes.
		this->vertices = vertices;
		this->indices = indices;
        this->textures = textures;
        this->shininess = shininess;

		// Generate a VAO and bind it, generate a VBO for the vertices and a EBO for the indices.
		this->vao.bind();
		VBO vbo(vertices);
		EBO ebo(indices);

		// Links VBO attributes such as coordinates and colors to VAO.
		vao.link_attribute(vbo, 0, 3, GL_FLOAT, sizeof(bgq_opengl::Vertex), (void*)0);
		vao.link_attribute(vbo, 1, 3, GL_FLOAT, sizeof(bgq_opengl::Vertex), (void*)(3 * sizeof(float)));
		vao.link_attribute(vbo, 2, 3, GL_FLOAT, sizeof(bgq_opengl::Vertex), (void*)(6 * sizeof(float)));
        vao.link_attribute(vbo, 3, 2, GL_FLOAT, sizeof(bgq_opengl::Vertex), (void*)(9 * sizeof(float)));
        vao.link_attribute(vbo, 4, 1, GL_FLOAT, sizeof(bgq_opengl::Vertex), (void*)(11 * sizeof(float)));

		vao.unbind();
		vbo.unbind();
		ebo.unbind();

	}

	std::vector<GLuint> Geometry::getIndices() {

		return this->indices;

	}

	std::vector<Texture>  Geometry::getTextures() {

		return this->textures;

	}

	VAO Geometry::getVAO() {

		return this->vao;

	}

	std::vector<Vertex> Geometry::getVertices() {

		return this->vertices;

	}

    float Geometry::getShininess() {
        
        return this->shininess;
        
    }

    void Geometry::setShininess(float shine) {
        
        this->shininess = shine;
        
    }

    glm::mat4 Geometry::getTransformMat() {
        
        return this->transforms;
        
    }

    void Geometry::setTransformMat(glm::mat4 transform) {
        
        this->transforms = transform;
        
    }

    void Geometry::addTexture(const char* image, const char* name) {
        
        // Create the new texture from the parameters.
        Texture new_tex(image, name, (int) this->textures.size() + 1);
        
        // Add this texture to the texture vector.
        this->textures.push_back(new_tex);
        
    }

	void Geometry::draw(Shader &shader, Camera &camera) {

		// Activate the VAO and the shader to access the uniforms.
		shader.activate();
		vao.bind();

		for (size_t i = 0; i < textures.size(); i++) {

			std::string name = textures[i].getName();
			std::string id = "";
			
            textures[i].bind();
			shader.passTexture(textures[i]);

		}

		// Pass the camera to the shader.
		shader.passCamera(camera);
        
        // Pass the shininess to the shader.
        shader.passFloat("materialShininess", this->shininess);
        
		// Get the model matrix and pass it.
		glm::mat4 model = this->transforms;
		glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "Model"), 1, GL_FALSE, glm::value_ptr(model));

		// Get the View matrix and compute the modelView;
		glm::mat4 view = camera.getView();
		glm::mat4 model_view = view * model;
		glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "modelView"), 1, GL_FALSE, glm::value_ptr(model_view));

		// Get the normal matrix and pass it.
		glm::mat4 normal_matrix = glm::transpose(glm::inverse(model_view));
		glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normal_matrix));

		// Draw the actual Geometry
		glDrawElements(GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_INT, 0);

	}

	BoundingBox Geometry::getBoundingBox() {

		// Create the bb.
		BoundingBox bb;

		// Init the bounding box with the first vertex.
		bb.min = glm::vec3(this->vertices[0].position.x, this->vertices[0].position.y, this->vertices[0].position.z);
		bb.max = glm::vec3(this->vertices[0].position.x, this->vertices[0].position.y, this->vertices[0].position.z);

		// Loop through the vertices and get tge min and max values.
		for (int i = 1; i < this->vertices.size(); i++) {

			if (bb.min.x > this->vertices[i].position.x)
				bb.min.x = this->vertices[i].position.x;

			if (bb.min.y > this->vertices[i].position.y)
				bb.min.y = this->vertices[i].position.y;

			if (bb.min.z > this->vertices[i].position.z)
				bb.min.z = this->vertices[i].position.z;

			if (bb.max.x < this->vertices[i].position.x)
				bb.max.x = this->vertices[i].position.x;

			if (bb.max.y < this->vertices[i].position.y)
				bb.max.y = this->vertices[i].position.y;

			if (bb.max.z < this->vertices[i].position.z)
				bb.max.z = this->vertices[i].position.z;

		}

		return bb;

	}

	void Geometry::resetTransforms() {

		this->transforms = glm::mat4(1.0f);

	}

	void Geometry::rotate(float x, float y, float z, float angle) {

		// Get the angle as radians.
		float radians = glm::radians(angle);

		// Create a rotation matrix.
		glm::mat4 identity_matrix(1.0f);
		glm::mat4 rotation_matrix = glm::rotate(identity_matrix, radians, glm::vec3(x, y, z));

		this->transforms *= rotation_matrix;

	}

	void Geometry::scale(float x, float y, float z) {

		// Create the scale matrix.
		glm::mat4 identity_matrix(1.0f);
		glm::mat4 scale_matrix = glm::scale(identity_matrix, glm::vec3(x, y, z));

		this->transforms *= scale_matrix;

	}

	void Geometry::translate(float x, float y, float z) {

		// Get the translation matrix.
		glm::mat4 trans_matrix = glm::translate(glm::mat4(1.0), glm::vec3(x, y, z));

		// Apply it to the transormations.
		this->transforms *= trans_matrix;

	}

}  // namespace bgq_opengl
