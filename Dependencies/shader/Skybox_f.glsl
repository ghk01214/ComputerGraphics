#version 450

in vec3 f_texture;

out vec4 color;

uniform bool flip_horizontal;
uniform bool flip_vertical;

uniform samplerCube tex_sampler;

void main()
{
	vec3 pos = f_texture;

	if (flip_vertical == true)
		pos = vec3(pos.x, 1.0 - pos.y, pos.z);
	
	if (flip_horizontal == true)
		pos = vec3(1.0 - pos.x, pos.y, pos.z);

	color = texture(tex_sampler, pos);
}