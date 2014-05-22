#version 430

in vec4 ex_Color;

uniform sampler2D textureMap;

void main(void) {

	gl_FragColor = texture2D(textureMap, gl_TexCoord[0].st) * ex_Color;
}