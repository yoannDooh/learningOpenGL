#version 460 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inUV;

out vec2 UV;

void main()
{
	gl_Position = vec4(inPos.x, inPos.y,inPos.z,1.0);
	UV = inUV;
}