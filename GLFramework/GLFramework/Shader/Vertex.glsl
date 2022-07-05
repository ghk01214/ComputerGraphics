#version 450

in vec3 position;

in vec4 in_color;
out vec4 out_color;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = /*projection * view */ transform * vec4(position, 1.0);

	out_color = in_color;
}