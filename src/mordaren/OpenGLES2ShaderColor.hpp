#pragma once

#include <morda/render/ShaderColor.hpp>

#include "OpenGLES2ShaderBase.hpp"

namespace mordaren{

class OpenGLES2ShaderColor :
		public morda::ShaderColor,
		public OpenGLES2ShaderBase
{
	GLint colorUniform;
public:
	OpenGLES2ShaderColor();

	OpenGLES2ShaderColor(const OpenGLES2ShaderColor&) = delete;
	OpenGLES2ShaderColor& operator=(const OpenGLES2ShaderColor&) = delete;


	void render(const r4::mat4f& m, const morda::VertexArray& va, r4::vec4f color)const override;
};

}
