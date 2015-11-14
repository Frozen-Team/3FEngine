#include "renderer/gl/f_gl_include.hpp"
#include "engine.hpp"
#include "GameLoop.hpp"
#include <fcomponents/f_events_manager.hpp>

namespace fe = fengine;

int main(int argc, char* args[])
{
	auto& engine = fe::Engine::GetInstance();
	engine.Initialize<GameLoop>();
	auto ret_code = engine.Exec();
	fe::Engine::Release();
	return ret_code;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	auto window = SDL_CreateWindow("Main window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, SDL_WINDOW_OPENGL);
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
		if (i > 10) {
			break;
		}
		SDL_Delay(1);
		glClearColor(float(rand() % 256) / 256, float(rand() % 256) / 256, float(rand() % 256) / 256, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);

		fengine::FEventsManager::GetInstance().HandleEvents();
	}

	//fengine::FGlShader shader(ShaderType::kVertexShader);

	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);
	

	return 100500;
}