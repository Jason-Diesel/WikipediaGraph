#version 420 core
        
layout(location = 0) out vec4 finalPixel;

in vec3 o_color;

void main(){ 
    //finalPixel = vec4(o_colors, 1);
    finalPixel = vec4(o_color, 1);
}