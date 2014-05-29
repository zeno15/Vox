#version 430

in  vec3 ex_Color;

uniform sampler2D textureMap;
 
void main(void) {
	vec4 col = texture2D(textureMap, gl_TexCoord[0].st);

	gl_FragColor = col;
}