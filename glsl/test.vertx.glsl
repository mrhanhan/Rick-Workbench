#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 input_color;
// 模型
uniform mat4 model;
// 相机
uniform mat4 view;
// 投影
uniform mat4 projection;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) * model * view * projection;
    gl_PointSize = 30.0f;
    input_color = aColor;
}