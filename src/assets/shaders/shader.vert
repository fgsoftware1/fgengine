#version 410 core

precision mediump int;
precision mediump float;

uniform mat4 matrix;
attribute vec4 position;
attribute vec2 atexcoord;
varying vec2 vtexcoord;

void main()
{
	gl_Position = matrix * position;
    vtexcoord = atexcoord;
}
