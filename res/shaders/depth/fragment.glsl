#version 330 core

out float outColor;

flat in uint gID;

void main(){
    outColor = float(gID) / 255.0;
}