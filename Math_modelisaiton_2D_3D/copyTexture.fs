#version 330 core

varying vec2 v_texCoords;
uniform sampler2D u_texture;

void main(void)
{
	gl_FragColor = texture2D(u_texture, v_texCoords);
}