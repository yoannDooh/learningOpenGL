#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 normalVec;
layout(location = 2) in vec2 aTextCoord;
layout(location = 3) in int cubePoint;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float cubeEdge;
uniform mat4 orbit;
mat4 newModel;
vec3 elipseCenterCoord = vec3(0.0f, 0.0f, 0.0f);


mat4 BuildTranslation(vec3 delta) //from https://stackoverflow.com/questions/33807535/translation-in-glsl-shader
{
	return mat4(
		vec4(1.0, 0.0, 0.0, 0.0),
		vec4(0.0, 1.0, 0.0, 0.0),
		vec4(0.0, 0.0, 1.0, 0.0),
		vec4(delta, 1.0));
}

void setOrbit()
{
	float halfCubeEdge = cubeEdge / 2;
	vec4 centerCoordAfterElipsTrans = orbit * vec4(elipseCenterCoord.xyz, 1.0);

	switch (cubePoint)
	{
	case 0: //bottomFaceTopLeft
	{
		newModel = BuildTranslation(vec3(centerCoordAfterElipsTrans.x - halfCubeEdge, centerCoordAfterElipsTrans.y - halfCubeEdge, centerCoordAfterElipsTrans.z - halfCubeEdge)) * model;
	}

	case 1: //bottomFaceBottomLeft
	{
		newModel = BuildTranslation(vec3(centerCoordAfterElipsTrans.x - halfCubeEdge, centerCoordAfterElipsTrans.y - halfCubeEdge, centerCoordAfterElipsTrans.z + halfCubeEdge)) * model;
	}

	case 2: //bottomFaceBottomRight
	{
		newModel = BuildTranslation(vec3(centerCoordAfterElipsTrans.x + halfCubeEdge, centerCoordAfterElipsTrans.y - halfCubeEdge, centerCoordAfterElipsTrans.z + halfCubeEdge)) * model;
	}

	case 3: //bottomFaceTopRight
	{
		newModel = BuildTranslation(vec3(centerCoordAfterElipsTrans.x + halfCubeEdge, centerCoordAfterElipsTrans.y - halfCubeEdge, centerCoordAfterElipsTrans.z - halfCubeEdge)) * model;
	}

	case 4: //topFaceTopLeft
	{
		newModel = BuildTranslation(vec3(centerCoordAfterElipsTrans.x - halfCubeEdge, centerCoordAfterElipsTrans.y + halfCubeEdge, centerCoordAfterElipsTrans.z - halfCubeEdge)) * model;
	}

	case 5: //topFaceBottomLeft
	{
		newModel = BuildTranslation(vec3(centerCoordAfterElipsTrans.x - halfCubeEdge, centerCoordAfterElipsTrans.y + halfCubeEdge, centerCoordAfterElipsTrans.z + halfCubeEdge)) * model;
	}

	case 6: //topFaceBottomRight
	{
		newModel = BuildTranslation(vec3(centerCoordAfterElipsTrans.x + halfCubeEdge, centerCoordAfterElipsTrans.y + halfCubeEdge, centerCoordAfterElipsTrans.z + halfCubeEdge)) * model;
	}

	case 7: //topFaceTopRight
	{
		newModel = BuildTranslation(vec3(centerCoordAfterElipsTrans.x + halfCubeEdge, centerCoordAfterElipsTrans.y + halfCubeEdge, centerCoordAfterElipsTrans.z - halfCubeEdge)) * model;
	}
	}
}

void main()
{
	setOrbit();
	gl_Position = projection * view * newModel * vec4(aPos.xyz, 1.0);
}


