#include "SDL_main.h"
#include "SDL.h"
#include "SDL_opengl.h"

#include <stdio.h>
#include <iostream>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	auto window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}
	
	auto context = SDL_GL_CreateContext(window);

	auto info = glGetString(GL_VERSION);

	if (info != nullptr) {
		std::cout << "Version: " << info;
	} else {
		std::cout << "Beda" << std::endl;
	}
	
	

	SDL_Delay(2000);



	SDL_DestroyWindow(window);

	SDL_GL_DeleteContext(context);

	SDL_Quit();

	return 0;
}