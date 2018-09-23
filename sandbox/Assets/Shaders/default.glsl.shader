%%vertex
#version 330 core

in vec3 aPosition;
in vec3 aColor;
in vec2 aTexCoord0;

out vec3 vColor;
out vec2 vTexCoord0;

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vColor = aColor;
    vTexCoord0 = aTexCoord0;
    //float posX = aPosition.x + max(0, aPosition.y) / aPosition.y * 0.2 * sin(time / 2.0);
    //float posY = aPosition.y + max(0, aPosition.y) / aPosition.y * 0.1 * cos(sin(time) * 6.14);
    gl_Position = vec4(aPosition, 1.0) * model * view * projection;
}
%%vertex

%%fragment
#version 330 core

out vec4 FragColor;

in vec3 vColor;
in vec2 vTexCoord0;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    FragColor = mix(texture(texture0, vTexCoord0), texture(texture1, vTexCoord0), 0.2);
}
%%fragment