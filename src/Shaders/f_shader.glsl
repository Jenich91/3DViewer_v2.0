#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

uniform mediump vec4 color;

void main()
{
    gl_FragColor = color;
}
