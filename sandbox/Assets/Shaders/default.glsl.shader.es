%%vertex

attribute vec3 aPosition;
attribute vec3 aColor;
attribute vec2 aTexCoord0;

varying vec3 vColor;
varying vec2 vTexCoord0;

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
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
}
%%vertex

%%fragment
precision mediump float;

varying vec3 vColor;
varying vec2 vTexCoord0;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    //gl_FragColor = texture2D(texture0, vTexCoord0) + texture2D(texture1, vTexCoord0);
    gl_FragColor = mix(texture2D(texture0, vTexCoord0), texture2D(texture1, vTexCoord0), 0.2);
}
%%fragment