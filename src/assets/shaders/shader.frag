#version 410 core

precision mediump int;
precision mediump float;

uniform sampler2D texture;
varying vec2 texcoord;

void main()
{
  gl_FragColor = texture2D(texture, texcoord);
}
