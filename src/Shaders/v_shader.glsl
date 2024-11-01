#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

attribute vec4 a_position;
attribute float size;
uniform mat4 mvp_matrix;

void main()
{
    gl_Position = mvp_matrix * a_position;
    gl_PointSize = size;
}
