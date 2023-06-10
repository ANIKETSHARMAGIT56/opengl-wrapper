#version 440 core
layout (location=0) out vec4 color;
in vec2 v_TexCoord;
in float f_tex_index;
uniform sampler2D u_texture[2];

void main()
{
    int index = int(f_tex_index);
    color = texture(u_texture[index],v_TexCoord);    
    // if(index==1){

    // vec4 texColor = texture(u_texture[1],v_TexCoord);
    // color = texColor;
    // }
    //     else{

    // vec4 texColor = texture(u_texture[0],v_TexCoord);
    // color = texColor;
    // }
    // color = vec4(int(f_tex_index),int(f_tex_index),int(f_tex_index),1.0);
    // }
    // else {
        // color =v_vec_color;
    // }

    // color = v_vec_color;
}