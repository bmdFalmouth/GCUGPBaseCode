#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <gl/glu.h>                             

#include "Sprite.h"

Sprite * g_pTestSprite=NULL;

//InitGL
void InitGL()
{
	//Enable some GL States
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

//InitGame Stuff
void InitGame()
{
	g_pTestSprite=CreateSpriteUsingTexture(1.0f,"resources/texture.jpg");
}

//Update
void Update()
{
	//Swith to model view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();  
	//Apply rotation
	glRotatef(g_pTestSprite->rotation.x,1.0f,0.0f,0.0f);
	glRotatef(g_pTestSprite->rotation.y,0.0f,1.0f,0.0f);
	glRotatef(g_pTestSprite->rotation.z,0.0f,0.0f,1.0f);
	//Scale
	glScalef(g_pTestSprite->scale.x,g_pTestSprite->scale.y,g_pTestSprite->scale.z);
	//translation
	glTranslatef(g_pTestSprite->position.x,g_pTestSprite->position.y,g_pTestSprite->position.z); 
}

//Draw
void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glDepthMask(GL_TRUE);
	//Enable texturing

	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 500.f);
	//Bind texture for this sprite
	glBindTexture(GL_TEXTURE_2D,g_pTestSprite->textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glBegin(GL_QUADS);                      // Draw A Quad
	glVertex3f(g_pTestSprite->coords[0].x,g_pTestSprite->coords[0].y,g_pTestSprite->coords[0].z);              // Top Left
	glTexCoord2f(g_pTestSprite->textureCoords[0].x,g_pTestSprite->textureCoords[0].y);
	glVertex3f(g_pTestSprite->coords[1].x,g_pTestSprite->coords[1].y,g_pTestSprite->coords[1].z);                // Top Right
	glTexCoord2f(g_pTestSprite->textureCoords[1].x,g_pTestSprite->textureCoords[1].y);
	glVertex3f(g_pTestSprite->coords[2].x,g_pTestSprite->coords[2].y,g_pTestSprite->coords[2].z);                // Bottom Right
	glTexCoord2f(g_pTestSprite->textureCoords[2].x,g_pTestSprite->textureCoords[2].y);
	glVertex3f(g_pTestSprite->coords[3].x,g_pTestSprite->coords[3].y,g_pTestSprite->coords[3].z);               // Bottom Left
	glTexCoord2f(g_pTestSprite->textureCoords[3].x,g_pTestSprite->textureCoords[3].y);
	glEnd();                            // Done Drawing The Quad
}

//OnExit
void OnExit()
{
	if (g_pTestSprite)
	{
		delete g_pTestSprite;
		g_pTestSprite=NULL;
	}

}

//Main
int main()
{
	//Create Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);

	InitGL();

	InitGame();
	
	//Game Loop
	bool running=true;
	while (running)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
				running=false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		Update();
		Draw();

		window.display();
	}

	OnExit();

	return 0;
}