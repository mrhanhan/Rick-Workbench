#version 330 core
out vec4 FragColor;
in vec3 input_color;
void main()
{
    FragColor = vec4(input_color, 1.0f);
}