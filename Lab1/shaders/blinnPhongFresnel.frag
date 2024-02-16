#version 330 core

in vec3 vertexPosition;             // Position from the VS.
in vec3 vertexNormal;               // Normal from the VS.
in vec3 vertexColor;                // Color from the VS.
in vec2 vertexUV;                   // UV coordinates from the VS.
in vec3 Reflect;                    // The reflect color.
in vec3 RefractR;                   // The refracttion of the red channel.
in vec3 RefractG;                   // The refracttion of the green channel.
in vec3 RefractB;                   // The refracttion of the blue channel.
in float Ratio;                     // The reflection refraction ratio.

uniform vec4 lightColor;            // Light color.
uniform vec3 lightPos;              // Light position.
uniform vec3 cameraPosition;        // Position of the camera.
uniform float materialShininess;    // Extra shininess.
uniform float etaR;                 // Fresnel red ratio.
uniform float etaG;                 // Fresnel green ratio.
uniform float etaB;                 // Fresnel blue ratio.
uniform float fresnelPower;         // The fresnel interpolation step.
uniform float mixColor;             // The color/fresnel ratio.
uniform sampler2D baseColor;        // The color texture.
uniform samplerCube skybox;         // The skybox.
uniform float minAmbientLight;      // The minimum ambient that will control ambient light.
uniform float lightPower;           // The power that light has to light up the scene.

const float screenGamma = 2.2;      // Used for gamma corrections.

out vec4 outColor;                  // Outputs color in RGBA.

void main() {
    
    // Get the base color from the texture.
    vec4 textureColor = texture(baseColor, vertexUV);
        
    // Get the colors for the refraction from the skybox.
    vec3 refractColor = vec3(0.0, 0.0, 0.0);
    refractColor.r = vec3(texture(skybox, RefractR)).r;
    refractColor.g = vec3(texture(skybox, RefractG)).g;
    refractColor.b = vec3(texture(skybox, RefractB)).b;
    
    // Get the reflected colors.
    vec3 reflectColor = vec3(texture(skybox, Reflect));
    
    // Get the final fresnel color after mixing both reflection and refraction.
    vec3 fresnelColor = mix(refractColor, reflectColor, Ratio);
    
    // Get the normal ready to use.
    vec3 normal = normalize(vertexNormal);
    
    // Get the light direction.
    vec3 lightDir = lightPos - vertexPosition;

    // Get the distance from the light to this fragment.
    float dist = length(lightDir);
    dist = dist * dist;

    // Normalize the light direction as a vector.
    lightDir = normalize(lightDir);

    // Get the lambertian component as stated in the docs.
    float lambertian = max(dot(lightDir, normal), 0.0);
    
    // Get the surface color after joining the texture and the fresnel.
    vec4 surfaceColor = vec4(mix(textureColor.xyz, fresnelColor, mixColor), 1.0);

    // Calculate the specular component.
    float specular = 0.0;
    if (lambertian > 0.0) {

        // Get the direction from the position to the camera as a vector.
        vec3 viewDir = normalize(-vertexPosition);

        // Blinn-phong calculations.
        vec3 halfAngle = normalize(lightDir + viewDir);
        float specAngle = max(dot(halfAngle, normal), 0.0);
        specular = pow(specAngle, materialShininess);
       
    }
    
    // Get the minimum color.
    vec3 ambientColor = vec3(surfaceColor) * minAmbientLight;

    // Get the diffuse final color.
    vec3 diffuseColor = vec3(surfaceColor) * lambertian * vec3(lightColor) * lightPower / dist;

    // Get the specular final color.
    vec3 specularColor = vec3(surfaceColor) * specular * vec3(lightColor) * lightPower / dist;

    // Get the final color that would go in the fragment.
    vec3 fragmentColor = ambientColor + diffuseColor + specularColor;

    // Apply gamma correction.
    fragmentColor = pow(fragmentColor, vec3(1.0 / screenGamma));

    // Final color.
    outColor = vec4(fragmentColor, 1.0);
    
}
