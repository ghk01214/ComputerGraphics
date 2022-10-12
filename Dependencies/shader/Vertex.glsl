#version 450

in vec3 v_pos;
in vec3 v_color;

out vec3 f_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 pos;

void main()
{
	gl_Position = /*projection * view * model */ vec4(v_pos, 1.0);

	f_color = v_color;
}