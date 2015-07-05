#version 330 core
attribute vec4 a_position;

varying vec2 v_texCoords;

void main(void)
{
	v_texCoords = ((a_position + 1.0) / 2.0).xy;
	gl_poition = a_positon;
}