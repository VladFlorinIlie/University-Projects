#version 330

in vec3 frag_poz;
in vec3 frag_normal;

uniform vec3 color;

uniform vec3 light_position;
uniform vec3 light_position2;
uniform vec3 light_position3;
uniform vec3 light_direction;

uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform int should_shine;

layout(location = 0) out vec4 out_color;

void main()
{
	vec3 N = normalize(frag_normal);
	float cut_off = radians(25);
	float spot_light_limit = cos(cut_off);
	float ambient_light = material_kd * 0.25f;
	vec3 final_col = vec3(0);

	for (int i = 0; i < 3; i++) {
		vec3 light_pos;
		if (i == 0) {
			light_pos = light_position;
		} else if (i == 1) {
			light_pos = light_position2;
		} else {
			light_pos = light_position3;
		}

		vec3 L = normalize(light_pos - frag_poz);
		vec3 V = normalize(eye_position - frag_poz);

		float spot_light = dot(-L, light_direction);
		float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
		float light_att_factor = pow(linear_att, 2);

		if (spot_light <= cos(cut_off))
		{
			final_col += color * ambient_light;
			continue;
		}

		float diffuse_light = material_kd * max(dot(N, L), 0);

		float specular_light = 0;
		if (diffuse_light > 0 && should_shine == 1)
		{
			vec3 H = normalize(L + V);
			specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);
		}

		float d = distance(light_pos, frag_poz) / 5;
		float col = ambient_light + 1.0 / pow(d, 2) * (diffuse_light + specular_light) * light_att_factor;

		final_col += color * col;
	}

	out_color = vec4(final_col, 1);
}