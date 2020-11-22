#version 330

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

layout(location=0) in vec3 vertex_position;
layout(location=1) in vec2 vertex_uv0;

out vec2 uv0;

void main()
{
	gl_Position = projection * view * model * vec4(vertex_position, 1.0);
	uv0 = vertex_uv0;
}