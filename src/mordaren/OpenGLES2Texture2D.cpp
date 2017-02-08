#include "OpenGLES2Texture2D.hpp"

#include "OpenGLES2_util.hpp"

using namespace mordaren;

OpenGLES2Texture2D::OpenGLES2Texture2D(kolme::Vec2f dim) :
		morda::Texture2D(dim)
{
	glGenTextures(1, &this->tex);
	assertOpenGLNoError();
	ASSERT(this->tex != 0)
}


OpenGLES2Texture2D::~OpenGLES2Texture2D()noexcept{
	glDeleteTextures(1, &this->tex);
}

void OpenGLES2Texture2D::bind(unsigned unitNum) const {
	glActiveTexture(GL_TEXTURE0 + unitNum);
	assertOpenGLNoError();
	glBindTexture(GL_TEXTURE_2D, this->tex);
	assertOpenGLNoError();
}
