#version 450

layout(location = 0) out vec4 color;

in vec3 f_position;
in vec3 f_normal;
in vec4 f_color;

// Light
uniform vec3 ambient_light;
uniform vec3 light_position;
uniform vec3 light_color;
uniform int shininess;
uniform vec3 view_position;

vec3 AmbientLight()
{
	return ambient_light * light_color;
}

vec3 DiffuseLight(vec3 normal_vector, vec3 light_direction)
{
	float diffuse_light = max(dot(normal_vector, light_direction), 0.0);
	
	return diffuse_light * light_color;
}

vec3 SpecularLight(vec3 normal_vector, vec3 light_direction)
{
	vec3 view_direction = normallize(view_position - f_position);
	vec3 reflect_direction = reflect(-light_direction, normal_vector);

	float specular_light = max(dot(view_direction, reflect_direction), 0.0);
	specular_light = pow(specular_light, shininess);

	return specular_light * light_color;
}

void main()
{
	vec3 normal_vector = normalize(f_normal);
	vec3 light_direction = normalize(light_position - f_position);

	// ambient light(주변 조명)
	//color = vec4((AmbientLight() * f_color), 1.0);

	// ambient + diffuse light(주변 조명 + 산란 반사 조명)
	//color = vec4((AmbientLight() + DiffuseLight(normal_vector, light_direction)) * f_color, 1.0);

	// ambient + diffuse + specular light(주변 조명 + 산란 반사 조명 + 거울 반사 조명)
	color = vec4((AmbientLight() + DiffuseLight(normal_vector, light_direction) + SpecularLight(normal_vector, light_direction)) * f_color, 1.0);
}