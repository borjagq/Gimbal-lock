#version 330 core

layout (location = 0) in vec3 inVertex;    // Vertex.

uniform mat4 View;            // Imports the View matrix.
uniform mat4 Projection;    // Imports the projection matrix.

out vec3 texCoords;

void main() {
    
    // Flip the coordinates to fix the weird issue.
    texCoords = vec3(inVertex.x, inVertex.y, -inVertex.z);
    
    // Apply the transformations so that it moves with the camera.
    vec4 newPosition = Projection * View * vec4(inVertex, 1.0f);
    
    // We have to make Z == W so that it's always in the back.
    gl_Position = vec4(newPosition.x, newPosition.y, newPosition.w, newPosition.w);

}
