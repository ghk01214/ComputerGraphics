#version 450

in vec3 v_pos;

out vec3 f_texture;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	f_texture = v_pos;

	vec4 pos = projection * view * vec4(v_pos, 1.0);
	gl_Position = pos.xyww;
}