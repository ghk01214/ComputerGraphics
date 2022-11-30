#version 450

in vec3 f_normal;
in vec2 f_texture;
in vec4 f_color;

out vec4 color;

void main()
{
	color = f_color;
}