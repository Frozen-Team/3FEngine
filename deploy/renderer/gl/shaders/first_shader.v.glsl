#version 430
in vec3 vertex;
uniform mat4 mvp;
out vec3 f_color;

void main(void)
{
  gl_Position = mvp * vec4(vertex, 1.0f);
  f_color = vec3(0.5f, 0.5f, 0.5f);
}