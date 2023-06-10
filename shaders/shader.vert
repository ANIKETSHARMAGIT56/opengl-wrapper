#version 330 core
layout (location=0) in vec4 position;
layout (location=1) in vec2 texCoord;
layout (location=2) in vec4 vec_color;
layout (location=2) in float tex_index ;
out vec2 v_TexCoord;
out float f_tex_index;
uniform mat4 u_mvp;
void main()
{
gl_Position = u_mvp * position;
f_tex_index = tex_index;
v_TexCoord = texCoord;
}