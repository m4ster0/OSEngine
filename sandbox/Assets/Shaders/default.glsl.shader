%%vertex
#version 330 core

in vec2 aPosition;
in vec3 aColor;
in vec2 aTexCoord0;

out vec3 vColor;
out vec2 vTexCoord0;

void main()
{
    vColor = aColor;
    vTexCoord0 = aTexCoord0;
    gl_Position = vec4(aPosition.x, aPosition.y * -1.0, 0, 1.0);
}
%%vertex

%%fragment
#version 330 core

out vec4 FragColor;

in vec3 vColor;
in vec2 vTexCoord0;

uniform sampler2D texture0;

void main()
{
    FragColor = texture(texture0, vTexCoord0);
}
%%fragment