#type vertex
#version 330 core
layout(location = 0) in vec3 aPos;
uniform mat4 u_ViewProject;
uniform mat4 u_Model;
void main()
{
    gl_Position = u_ViewProject * u_Model * vec4(aPos , 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;
uniform vec4 u_color;
void main()
{
    color = u_color;
}