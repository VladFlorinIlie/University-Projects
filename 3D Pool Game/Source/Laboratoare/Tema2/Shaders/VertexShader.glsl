#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float impulse;
uniform vec3 direction;

out vec3 frag_poz;
out vec3 frag_normal;

void main()
{
	//-- for color --
	frag_poz = (Model * vec4(v_position, 1)).xyz;
	frag_normal = mat3(Model) * v_normal;

	//-- for position --
	/*vec3 new_pos = vec3(v_position.x, v_position.y, v_position.z + impulse * 5); // spatiul obiect

	gl_Position = Projection * View * Model * vec4(new_pos, 1.0);*/

	vec3 posWorld = (Model * vec4(v_position, 1.0)).xyz; // if working in world space
	posWorld -= direction * impulse * 5;

	gl_Position = Projection * View * vec4(posWorld, 1.0);
}
