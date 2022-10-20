#version 450

in vec3 f_normal;
in vec2 f_texture;

out vec4 color;

uniform vec3 f_color;

void main()
{
	color = vec4(f_color, 1.0);
}