#pragma once

#include <utki/config.hpp>

#include <morda/render/VertexArray.hpp>

#if M_OS_NAME == M_OS_NAME_IOS
#	include <OpenGlES/ES2/glext.h>
#else
#	include <GLES2/gl2.h>
#endif


namespace mordaren{

class OpenGLES2VertexArray : public morda::VertexArray{
public:	
	OpenGLES2VertexArray(std::vector<std::shared_ptr<morda::VertexBuffer>>&& buffers, std::shared_ptr<morda::IndexBuffer> indices, Mode_e mode);
	
	OpenGLES2VertexArray(const OpenGLES2VertexArray&) = delete;
	OpenGLES2VertexArray& operator=(const OpenGLES2VertexArray&) = delete;

	
private:

};

}
