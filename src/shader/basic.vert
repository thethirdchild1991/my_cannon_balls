#version 410

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColor;
layout (location=2) in vec2 VertexTexCoord;

out vec3 Color;
out vec2 TexCoord;

uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

void main()
{
    Color = vec3(0.2, 0.4, 0.5);//VertexColor;    
    TexCoord = VertexTexCoord;
    gl_Position = projection_mat * view_mat * model_mat * vec4(VertexPosition,1.0);
}
