#version 450

in vec3 f_pos;
in vec3 f_normal;
in vec2 f_texture;
in vec4 f_color;

out vec4 color;

uniform mat4 model;

uniform float ambient_strength;
uniform float specular_strength;
uniform int shininess;
uniform vec3 light_pos;
uniform vec3 light_color;

uniform vec3 view_pos;
uniform vec4 obj_color;

uniform bool light_on;

uniform bool have_texture;
uniform sampler2D tex_sampler;
uniform bool flip_horizontal;
uniform bool flip_vertical;

vec3 Ambient()
{	
	return ambient_strength * light_color;
}

vec3 Diffuse(vec3 normal, vec3 light_direction)
{
	return max(dot(normal, light_direction), 0.0) * light_color;
}

vec3 Specular(vec3 normal, vec3 light_direction)
{
	vec3 view_direction = normalize(view_pos - f_pos);
	vec3 reflect_direction = reflect(-light_direction, normal);
	float specular_light = pow(max(dot(view_direction, reflect_direction), 0.0), shininess);

	return specular_strength * specular_light * light_color;
}

vec3 Phong(vec3 normal, vec3 light_direction)
{
	return Ambient() + Diffuse(normal, light_direction) + Specular(normal, light_direction);
}

void main()
{
	vec3 normal = normalize(f_normal);
	vec3 light_direction = normalize(light_pos - f_pos);
	
	vec4 result = vec4(Phong(normal, light_direction), 1.0) * obj_color;

	if (light_on == true)
	{
		if (have_texture == true)
		{
			vec2 tex_pos = f_texture;
			
			if (flip_vertical == true)
				tex_pos = vec2(tex_pos.x, 1.0 - tex_pos.y);
			
			if (flip_horizontal == true)
				tex_pos = vec2(1.0 - tex_pos.x, tex_pos.y);

			color = texture(tex_sampler, tex_pos) * result;
		}
		else
		{
			color = result;
		}
	}
	else
	{
		if (have_texture == true)
		{
			vec2 tex_pos = f_texture;
			
			if (flip_vertical == true)
				tex_pos = vec2(tex_pos.x, 1.0 - tex_pos.y);
			
			if (flip_horizontal == true)
				tex_pos = vec2(1.0 - tex_pos.x, tex_pos.y);

			color = texture(tex_sampler, tex_pos);
		}
		else
		{
			color = obj_color;
		}
	}
}