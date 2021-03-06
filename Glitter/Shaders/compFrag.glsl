#version 450 core

in vec2 uv;
out vec4 FragColor;

layout(binding=0) uniform sampler2D texture_2D;

uniform vec2 resolution;

#define  offset_x  1. / resolution.x
#define  offset_y  1. / resolution.y

vec4 gaussianBlur(sampler2D tex, vec2 uv){
    vec2 offsets[9] = vec2[](
    vec2(-offset_x,  offset_y), // top-left
    vec2( 0.0f,    offset_y), // top-center
    vec2( offset_x,  offset_y), // top-right
    vec2(-offset_x,  0.0f),   // center-left
    vec2( 0.0f,    0.0f),   // center-center
    vec2( offset_x,  0.0f),   // center-right
    vec2(-offset_x, -offset_y), // bottom-left
    vec2( 0.0f,   -offset_y), // bottom-center
    vec2( offset_x, -offset_y)  // bottom-right
    );

    float kernel[9] = float[](
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16
    );

    vec4 sampleTex[9];

    for(int i = 0; i < 9; i++)
    {
        vec4 pixel = texture(tex, uv.st + offsets[i]);
        sampleTex[i] = pixel;
    }
    vec4 col = vec4(0.0);
    for(int i = 0; i < 9; i++)
    col += sampleTex[i] * kernel[i];

    return col;
}

void main()
{
    vec4 color = gaussianBlur(texture_2D,uv);
    FragColor = color;
//    FragColor = texture(texture_2D, uv);
}