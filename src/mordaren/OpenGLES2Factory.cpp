#include <utki/config.hpp>

#include "OpenGLES2Factory.hpp"

#include "OpenGLES2VertexBuffer.hpp"
#include "OpenGLES2VertexArray.hpp"

#include "OpenGLES2_util.hpp"
#include "OpenGLES2IndexBuffer.hpp"

#include "OpenGLES2Texture2D.hpp"
#include "OpenGLES2ShaderPosTex.hpp"
#include "OpenGLES2ShaderColorPos.hpp"
#include "OpenGLES2ShaderPosClr.hpp"
#include "OpenGLES2ShaderColorPosTex.hpp"
#include "OpenGLES2FrameBuffer.hpp"


#if M_OS_NAME == M_OS_NAME_IOS
#	include <OpenGlES/ES2/glext.h>
#else
#	include <GLES2/gl2.h>
#endif


using namespace mordaren;

OpenGLES2Factory::OpenGLES2Factory(){
	//TODO:
}


OpenGLES2Factory::~OpenGLES2Factory()noexcept{
	//TODO:
}



std::shared_ptr<morda::Texture2D> OpenGLES2Factory::createTexture2D(morda::Texture2D::TexType_e type, kolme::Vec2ui dim, const utki::Buf<std::uint8_t>& data) {
	//TODO: turn these asserts to real checks with exceptions throwing
	ASSERT(data.size() % morda::Texture2D::bytesPerPixel(type) == 0)
	ASSERT(data.size() % dim.x == 0)

	ASSERT(data.size() == 0 || data.size() / morda::Texture2D::bytesPerPixel(type) / dim.x == dim.y)
	
	auto ret = utki::makeShared<OpenGLES2Texture2D>(dim.to<float>());
	
	//TODO: save previous bind and restore it after?
	ret->bind(0);
	
	GLint internalFormat;
	switch(type){
		default:
			ASSERT(false)
		case decltype(type)::GREY:
			internalFormat = GL_LUMINANCE;
			break;
		case decltype(type)::GREYA:
			internalFormat = GL_LUMINANCE_ALPHA;
			break;
		case decltype(type)::RGB:
			internalFormat = GL_RGB;
			break;
		case decltype(type)::RGBA:
			internalFormat = GL_RGBA;
			break;
	}

	//we will be passing pixels to OpenGL which are 1-byte aligned.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	assertOpenGLNoError();

	glTexImage2D(
			GL_TEXTURE_2D,
			0,//0th level, no mipmaps
			internalFormat, //internal format
			dim.x,
			dim.y,
			0,//border, should be 0!
			internalFormat, //format of the texel data
			GL_UNSIGNED_BYTE,
			data.size() == 0 ? nullptr : &*data.begin()
		);
	assertOpenGLNoError();

	//NOTE: on OpenGL ES 2 it is necessary to set the filter parameters
	//      for every texture!!! Otherwise it may not work!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	assertOpenGLNoError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	assertOpenGLNoError();
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	return ret;
}

std::shared_ptr<morda::VertexBuffer> OpenGLES2Factory::createVertexBuffer(const utki::Buf<kolme::Vec4f> vertices){
	return utki::makeShared<OpenGLES2VertexBuffer>(vertices);
}

std::shared_ptr<morda::VertexBuffer> OpenGLES2Factory::createVertexBuffer(const utki::Buf<kolme::Vec3f> vertices){
	return utki::makeShared<OpenGLES2VertexBuffer>(vertices);
}

std::shared_ptr<morda::VertexBuffer> OpenGLES2Factory::createVertexBuffer(const utki::Buf<kolme::Vec2f> vertices){
	return utki::makeShared<OpenGLES2VertexBuffer>(vertices);
}

std::shared_ptr<morda::VertexArray> OpenGLES2Factory::createVertexArray(std::vector<std::shared_ptr<morda::VertexBuffer>>&& buffers, std::shared_ptr<morda::IndexBuffer> indices, morda::VertexArray::Mode_e mode) {
	return utki::makeShared<OpenGLES2VertexArray>(std::move(buffers), std::move(indices), mode);
}

std::shared_ptr<morda::IndexBuffer> OpenGLES2Factory::createIndexBuffer(const utki::Buf<std::uint16_t> indices) {
	return utki::makeShared<OpenGLES2IndexBuffer>(indices);
}

std::unique_ptr<morda::RenderFactory::Shaders> OpenGLES2Factory::createShaders() {
	auto ret = utki::makeUnique<morda::RenderFactory::Shaders>();
	ret->posTex = utki::makeUnique<OpenGLES2ShaderPosTex>();
	ret->colorPos = utki::makeUnique<OpenGLES2ShaderColorPos>();
	ret->posClr = utki::makeUnique<OpenGLES2ShaderPosClr>();
	ret->colorPosTex = utki::makeUnique<OpenGLES2ShaderColorPosTex>();
	return ret;
}

std::shared_ptr<morda::FrameBuffer> OpenGLES2Factory::createFramebuffer(std::shared_ptr<morda::Texture2D> color) {
	return utki::makeShared<OpenGLES2FrameBuffer>(std::move(color));
}

