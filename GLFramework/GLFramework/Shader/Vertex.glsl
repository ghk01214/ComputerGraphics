#version 450

// ambient, diffuse, specular 전부 적용

// vectex shader
in vec3 v_position;
in vec3 v_normal;
in vec4 v_color;

// fragment shader
out vec3 f_position;
out vec3 f_normal;
out vec4 f_color;

// Transform Matrix
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec3 world = transform * vec4(v_position, 1.0);

	gl_Position = /*projection * view */ world;

	f_position = world;
	f_normal = v_normal;
	f_color = v_color;
}