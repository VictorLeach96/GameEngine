#version 400

layout(location=0) in vec3 inPosition;
layout(location=1) in vec3 inColour;

uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjMat;

out vec3 vColour;

void main(void){
	gl_Position = uProjMat * uViewMat * uModelMat * vec4(inPosition, 1);
	vColour = inColour;
}