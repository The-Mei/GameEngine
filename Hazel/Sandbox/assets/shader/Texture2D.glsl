
#type vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
uniform mat4 u_ViewProject;
uniform mat4 u_Model;
out vec2 u_TexCoord;
void main()
{
    gl_Position = u_ViewProject * u_Model * vec4(aPos , 1.0);
    u_TexCoord = aTexCoord;
}

#type fragment
#version 330 core
in vec2 u_TexCoord;
uniform sampler2D sampler;
uniform vec4 u_color;
out vec4 color;
void main()
{
    color = texture(sampler, u_TexCoord) * u_color;
}