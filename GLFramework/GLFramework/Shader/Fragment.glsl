#version 450

layout(location = 0) out vec4 color;

in vec4 out_color;

void main()
{
	color = vec4(out_color);
}