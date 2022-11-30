#version 450

in vec3 f_texture;

out vec4 color;

uniform samplerCube tex_sampler;

void main()
{
	color = texture(tex_sampler, f_texture);
}