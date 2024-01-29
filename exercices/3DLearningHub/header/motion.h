#pragma once

#include <array>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../header/shaderAndLight.h"
#include "../header/mesh.h"
#include "../header/window.h"

//forward declaration
class Cube;
class Square;

enum Effects
{
	inverse, //inverse color
	greyscale,// B&W color

	//Kernel effects
	blur,
	edgeDetection,
};

class FrameBuffer
{
public:
	unsigned int id{};
	unsigned int texId{};
	unsigned int renderId{};

	FrameBuffer(bool activateBufferTex, bool activateRenderBuff);
	FrameBuffer(bool shadowMap);

	unsigned int SHADOW_WIDTH{};
	unsigned int SHADOW_HEIGHT{};


private:
	void genFrameBuffTex(int width, int height, bool depthAttachment);
	void genRenderBuff();
};

/*CAMERA AND MOUSE*/
class Camera
{
public:
	Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float speed)
	{
		this->pos = pos;
		this->front = front;
		this->up = up;
		this->speed = speed;
	}

	void setCameraPos(glm::vec3 pos)
	{
		this->pos = pos;// set employees's name
	}

	void setCameraFront(glm::vec3 front)
	{
		this->front = front;// set employees's name
	}

	void setCameraUp(glm::vec3 up)
	{
		this->up = up;// set employees's name
	}


	void moveCamera(char keyPressed, float deltaTime)
	{
		switch (keyPressed)
		{
		case 'z':
			this->pos += this->speed * deltaTime * this->front;
			break;

		case 'q':
			this->pos -= glm::normalize(glm::cross(this->front, this->up)) * this->speed * deltaTime;
			break;

		case 's':
			this->pos -= this->speed * deltaTime * this->front;
			break;

		case 'd':
			this->pos += glm::normalize(glm::cross(this->front, this->up)) * this->speed * deltaTime;
			break;

		case 'u': //for up
			this->pos += this->speed * deltaTime * this->up;
			break;

		case 'w': //for down
			this->pos -= this->speed * deltaTime * this->up;
			break;

		}
	}

	glm::vec3 pos{};
	glm::vec3 front{};
	glm::vec3 up{};
	float speed{};
	float yawAngle{ -90.0f };
	float pitchAngle{};
};

namespace Object
{
	struct Model
	{
		glm::mat4 model{};
		glm::mat4 localOrigin{ glm::mat4(1.0f) };
		bool outLine{ false };
	};

}

namespace Mouse
{
	extern float sensitivity;
	extern float lastX;
	extern float lastY;
	extern bool firstMouseInput;
	extern float fov;
}

/*FrameRate*/
namespace Time
{
	extern float deltaTime; // Time between current frame and last frame in sec
	extern float previousDelta; //Time of previous frame in sec
	extern float deltaSum; //summ of the seconds passed since the beggening (by adding all deltaTime)
	extern float currentFrameTime;
	extern float lastFrameTime;
	extern int sec; //how many entire seconds has passed
	extern int currentFrame;
	extern int totalFrame;
}

//GLOBAL VARIABLES
namespace World
{
	extern Camera camera;
	extern glm::mat4 view;
	extern glm::mat4 projection;
	extern float projectionWidth;
	extern float projectionHeight;
	extern float projectionNear;
	extern float projectionFar;
	extern Object::Model woodCube;
	extern int mapWidth;
	extern int mapHeight;
}

namespace lightVar
{
	//sunlight Ambient 
	extern glm::vec3 sunLightColor;
	extern light::DirectLight sunLight;
}


//shadows functions
glm::mat4 toDirectionalLightSpaceMat(float lightRange, glm::vec3 lightPos, glm::vec3 lookAtLocation);
void setupShadowMap(Shader& shader, FrameBuffer depthMap, glm::mat4 lightSpaceMat);


//Animations 
void passViewProject(Shader& shader); //pass view and projection matrix to shader 

//emissionMap
float frameGlow(); //return currentFrameGlowStrenght for emmision map

//setup lights and orbit
void rotatePlane (light::lightPointCube& light, int index);
void setLightCube(Shader& shader, float cubeEdge, std::vector<light::lightPointCube>& lightCubes);


void setLighting(Shader& shader, std::vector<light::lightPointCube>& lightCubes);

//orbit and 
glm::mat4 orbit(light::lightPointCube& light);
void animateLightsCube(Shader& shader, Cube lightCubeVao, std::vector<light::lightPointCube>& lightCubes);
void updateViewProject(); //update world::view and world::projection

void setWoodCube(Shader& shader, std::vector<light::lightPointCube>& lightCubes);//just translate and scale then pass to shader 
void animateWoodCube(Shader& shader,unsigned int cubeMapTexture,Cube woodCubeVao, std::vector<light::lightPointCube>& lightCubes);


/*POST PROCESSING EFFECT*/
void animateWoodCubeAndOutline(Shader& shader, Shader& outlineShader, unsigned int cubemapTexture, Cube woodCubeVao, std::vector<light::lightPointCube>& lightCubes);
void setEffect(Shader& shader, Effects effect);