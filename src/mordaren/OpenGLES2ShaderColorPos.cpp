#include "OpenGLES2ShaderColorPos.hpp"

using namespace mordaren;

OpenGLES2ShaderColorPos::OpenGLES2ShaderColorPos() :
		OpenGLES2Shader(
				R"qwertyuiop(
						#ifndef GL_ES
						#	define highp
						#	define mediump
						#	define lowp
						#endif

						attribute highp vec4 a0;

						uniform highp mat4 matrix;
						
						void main(void){
							gl_Position = matrix * a0;
						}
					)qwertyuiop",
				R"qwertyuiop(
						#ifndef GL_ES
						#	define highp
						#	define mediump
						#	define lowp
						#endif
		
						uniform lowp vec4 uniformColor;
		
						void main(void){
							gl_FragColor = uniformColor;
						}
				)qwertyuiop"
			)
{
	this->colorUniform = this->getUniform("uniformColor");
}

void OpenGLES2ShaderColorPos::render(const kolme::Matr4f& m, kolme::Vec4f color, const morda::VertexArray& va) {
	this->bind();
	
	this->setUniform4f(this->colorUniform, color.x, color.y, color.z, color.w);
	
	this->OpenGLES2Shader::render(m, va);
}
