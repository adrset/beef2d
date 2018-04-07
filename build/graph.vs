#version 330 core
layout (location = 0) in vec2 aPos;
out vec4 out_color;

void main()
{
    //vec2 pos = vec2(aPos.x + 1, aPos.y + 1) / 2; 
    out_color = vec4(0.5,0.9,0.2,1.0);
    gl_Position = vec4(aPos, 0.0, 1.0);
}
