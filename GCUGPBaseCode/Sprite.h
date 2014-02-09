#ifndef _SPRITE_H
#define _SPRITE_h

#include "glm\glm.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

//this sprite is located around a centre(middle of the sprite)
struct Sprite
{
	//position
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	//for drawing
	glm::vec2 textureCoords[4];
	glm::vec3 coords[4];

	unsigned int textureID;

	//deconstructor
	~Sprite()
	{
		glDeleteTextures(1, &textureID);
	};
	
};

Sprite * CreateSprite(float size);

Sprite * CreateSpriteUsingTexture(float size, const char * filename);

#endif