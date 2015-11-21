#ifndef _3FENGINE_SRC_RENDERER_GL_F_GL_INCLUDE_HPP_
#define _3FENGINE_SRC_RENDERER_GL_F_GL_INCLUDE_HPP_

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <fcomponents/f_logger.hpp>
#include <renderer/gl/f_gl_helper.hpp>

namespace fengine
{
#define F_GL_DEBUG

#ifdef F_GL_DEBUG
#define F_GL_CHECK(statement) statement; LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error:" << FGlHelper::GetErrorsDescription();
#define F_GL_CHECK_M(statement, msg) statement; LOG_IF(FGlHelper::CheckErrors(), FATAL) << msg << " OpenGL error:" FGlHelper::GetErrorsDescription();
#else
#define F_GL_CHECK(statement) statement;
#define F_GL_CHECK_M(statement, msg) statement;
#endif
}

#endif // _3FENGINE_SRC_RENDERER_GL_F_GL_INCLUDE_HPP_