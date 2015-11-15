#version 430
in vec3 vertex;
in vec3 vertex_color;
uniform mat4 mvp;
out vec3 f_color;

void main(void)
{
  gl_Position = mvp * vec4(vertex, 1.0f);
  f_color = vertex_color;
}