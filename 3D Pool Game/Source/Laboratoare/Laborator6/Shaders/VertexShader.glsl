#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 t_coordinate;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

// TODO: output values to fragment shader
out vec3 frag_color;
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_t_coordinate;

void main()
{
	// TODO: send output to fragment shader
	frag_color = v_color * abs(cos(time));
	frag_position = v_position;
	frag_normal = v_normal;
	frag_t_coordinate = t_coordinate;

	vec3 new_pos = v_position;
	new_pos += cos(time) * 3;

	// TODO: compute gl_Position
	gl_Position = Projection * View * Model * vec4(new_pos, 1.0);
}
