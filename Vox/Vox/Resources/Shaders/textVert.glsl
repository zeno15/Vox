#version 430

in vec2 in_Position;
in vec4 in_Color;
in vec2 in_TexUV;

uniform mat4 mvp;

out vec4 ex_Color;

void main(void) {

	gl_Position = mvp * vec4(in_Position, 0.0f, 1.0f);

	ex_Color = in_Color;

	gl_TexCoord[0].xy = in_TexUV;
}