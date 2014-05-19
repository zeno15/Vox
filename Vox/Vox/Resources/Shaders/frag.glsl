#version 430

in  vec3 ex_Color;

uniform sampler2D textureMap;
 
void main(void) {
    //gl_FragColor = vec4(ex_Color, 1.0f);

	vec4 col = texture2D(textureMap, gl_TexCoord[0].st);

	gl_FragColor = vec4(ex_Color, 1.0f) * col;
}