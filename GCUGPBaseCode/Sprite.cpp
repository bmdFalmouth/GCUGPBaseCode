#include "Sprite.h"


Sprite * CreateSprite(float size)
{
	Sprite * s=new Sprite();

	float halfSize=size/2;

	//top left
	s->coords[0]=glm::vec3(-halfSize,halfSize,0.0f);
	s->textureCoords[0]=glm::vec2(0.0f,0.0f);

	//top right
	s->coords[1]=glm::vec3(halfSize,halfSize,0.0f);
	s->textureCoords[1]=glm::vec2(1.0f,0.0f);

	//botton right
	s->coords[2]=glm::vec3(halfSize,-halfSize,0.0f);
	s->textureCoords[2]=glm::vec2(1.0f,1.0f);

	//bottom left
	s->coords[3]=glm::vec3(-halfSize,-halfSize,0.0f);
	s->textureCoords[3]=glm::vec2(0.0f,1.0f);

	s->position=glm::vec3(0.0f,0.0f,-1.0f);
	s->rotation=glm::vec3(0.0f,0.0f,0.0f);
	s->scale=glm::vec3(1.0f,1.0f,1.0f);
	s->textureID=-1;

	return s;
}

Sprite * CreateSpriteUsingTexture(float size, const char * filename)
{
	Sprite * s=CreateSprite(size);
	sf::Image image;
    if (!image.loadFromFile(filename))
		{
			delete s;
			return NULL;
		}
	glGenTextures(1, &s->textureID);
	glBindTexture(GL_TEXTURE_2D, s->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, image.getSize().x, image.getSize().y,0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	return s;
}