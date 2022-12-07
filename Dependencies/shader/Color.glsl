#version 450

out vec4 color;

uniform vec4 obj_color;

void main()
{
	color = obj_color;
}