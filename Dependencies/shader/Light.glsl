#version 450

in vec3 f_pos;
in vec3 f_normal;
in vec2 f_texture;

out vec4 color;

uniform vec3 ambient_light;
uniform int shininess;
uniform vec3 view_pos;

uniform vec3 light_pos;
uniform vec3 obj_color;
uniform vec3 light_color;

vec3 Ambient()
{	
	return ambient_light * light_color;
}

vec3 Diffuse(vec3 normal, vec3 light_direction)
{
	return max(dot(normal, light_direction), 0.0) * light_color;
}

vec3 Specular(vec3 normal, vec3 light_direction)
{
	vec3 view_direction = normalize(view_pos - f_pos);
	vec3 reflect_direction = reflect(-light_direction, normal);
	float specular_light = max(dot(view_direction, reflect_direction), 0.0);

	return pow(specular_light, shininess) * light_color;
}

void main()
{
	vec3 normal = normalize(f_normal);
	vec3 light_direction = normalize(light_pos - f_pos);

	vec3 result = (Ambient() + Diffuse(normal, light_direction) + Specular(normal, light_direction)) * obj_color;

	color = vec4(result, 1.0);
}