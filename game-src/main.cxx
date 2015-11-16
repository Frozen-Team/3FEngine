#include <engine.hpp>
#include <renderer/gl/f_gl_renderer.hpp>

#include "game_loop.hpp"

namespace fe = fengine;

int main(int argc, char* args[])
{
	auto& engine = fe::Engine::GetInstance();
	engine.Initialize<GameLoop, fengine::FGlRenderer>();
	auto ret_code = engine.Exec();
	fe::Engine::Release();
	return ret_code;

	//	//fengine::FEventsManager::GetInstance().HandleEvents();
	//}

	////fengine::FGlShader shader(ShaderType::kVertexShader);

	//SDL_DestroyWindow(window);
	//SDL_GL_DeleteContext(context);
	//

	//return 100500;
}