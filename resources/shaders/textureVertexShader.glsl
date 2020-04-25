
#version 330 core

layout (location = 0) in vec3 a_Position; 
layout (location = 1) in vec2 a_TexCoord; 

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoords;

void main(){
	gl_Position = u_Transform * u_ViewProjection * vec4(a_Position, 1.0);
	v_TexCoords = a_TexCoord;
}	