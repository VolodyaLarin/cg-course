#version 330 core

// Interpolated values from the vertex shaders
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDir_cameraspace;
in vec3 MaterialColor;
in vec4 finalPos;
in vec3 texCoord;

uniform vec3 Color;
uniform samplerCube TEX;

// Ouput data
out vec4 o_vFragColor;

// Values that stay constant for the whole mesh.
uniform vec3 LightPos;


void main() {
	gl_FragColor = vec4(Color, 1.0);
}