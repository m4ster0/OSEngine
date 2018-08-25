#shader vertex
#version 330 core

in vec2 aPosition;
in vec3 aColor;

out vec3 vColor;

void main()
{
    vColor = aColor;
    gl_Position = vec4(aPosition.x, aPosition.y * -1.0, 0, 1.0);
}
#shader

#shader fragment
#version 330 core

out vec4 outColor;

in vec3 vColor;

void main()
{
    outColor = vec4(vColor, 1.0f);
}
#shader