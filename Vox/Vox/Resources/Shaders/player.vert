#version 430

in vec3 in_Position;
in vec3 in_Color;

uniform mat4 mvp;

out vec4 ex_Color;

void main(void) {

	gl_Position = mvp * vec4(in_Position, 1.0f);

	ex_Color = vec4(in_Color, 1.0);
}