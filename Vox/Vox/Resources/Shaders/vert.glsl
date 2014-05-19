#version 430

in vec3 in_Position;
in vec3 in_Color;
in vec3 in_Normal;
in vec2 in_TexUV;

uniform mat4 mv;
uniform mat4 mvp;
uniform mat4 nor;
uniform vec3 light;
 
out vec3 ex_Color;

void main(void) {

	gl_Position = mvp * vec4(in_Position, 1.0f);

	ex_Color = in_Color;

	gl_TexCoord[0].xy = in_TexUV;
}