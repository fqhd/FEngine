#version 330 core

layout (location = 0) in vec2 aPosition;

out vec2 vUV;
out vec2 v_rgbNW;
out vec2 v_rgbNE;
out vec2 v_rgbSW;
out vec2 v_rgbSE;
out vec2 v_rgbM;
uniform ivec2 iResolution;

void main(){
    gl_Position = vec4(aPosition, 0.0, 1.0);
    vUV = (aPosition + 1.0) / 2.0;
    vec2 fragCoord = vUV * iResolution;
    vec2 inverseVP = 1.0 / iResolution.xy;
	v_rgbNW = (fragCoord + vec2(-1.0, -1.0)) * inverseVP;
	v_rgbNE = (fragCoord + vec2(1.0, -1.0)) * inverseVP;
	v_rgbSW = (fragCoord + vec2(-1.0, 1.0)) * inverseVP;
	v_rgbSE = (fragCoord + vec2(1.0, 1.0)) * inverseVP;
	v_rgbM = vec2(fragCoord * inverseVP);
}