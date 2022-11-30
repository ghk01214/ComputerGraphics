#version 450

in vec3 v_pos;
in vec3 v_normal;
in vec2 v_texture;
in vec4 v_color;

out vec3 f_pos;
out vec3 f_normal;
out vec2 f_texture;
out vec4 f_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(v_pos, 1.0);

	f_pos = vec3(model * vec4(v_pos, 1.0));
	f_normal = mat3(transpose(inverse(model))) * v_normal;
	f_texture = v_texture;
	//f_color = v_color;
}