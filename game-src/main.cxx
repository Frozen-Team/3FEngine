#include "SDL_main.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <stdio.h>
#include <iostream>
#include <assert.h>
#include "settings\f_settings.hpp"
#include "Eigen\Dense"
#include "utils\f_singleton.hpp"
#include <memory>
#include "engine.hpp"
#include "utils\f_json.hpp"
#include "scene/camera/f_camera.hpp"

#include "resources/f_resource_loader.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

namespace FE = fengine;

int main(int argc, char* args[])
{
	auto engine = fengine::Engine::GetInstance();	

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	auto window = SDL_CreateWindow("Main window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
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
	SDL_GL_SetSwapInterval(-1);
	
	auto i = 0;
	while (true)
	{
		i++;
		if (i > 100000) {
			break;
		}
		SDL_Delay(1);
		glClearColor(float(rand() % 256) / 256, float(rand() % 256) / 256, float(rand() % 256) / 256, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);

		fengine::FEventsManager::GetInstance()->HandleEvents();
	}

	//SDL_JoystickClose(gGameController);
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;
}