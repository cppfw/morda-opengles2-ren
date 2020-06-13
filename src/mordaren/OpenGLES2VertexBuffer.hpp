#pragma once

#include <utki/span.hpp>

#include <r4/vector2.hpp>

#include <morda/render/vertex_buffer.hpp>

#include "OpenGLES2Buffer.hpp"

namespace mordaren{

class OpenGLES2VertexBuffer : public morda::vertex_buffer, public OpenGLES2Buffer{
public:
	const GLint numComponents;
	const GLenum type;
	
	OpenGLES2VertexBuffer(utki::span<const r4::vec4f> vertices);
	
	OpenGLES2VertexBuffer(utki::span<const r4::vec3f> vertices);
	
	OpenGLES2VertexBuffer(utki::span<const r4::vec2f> vertices);
	
	OpenGLES2VertexBuffer(utki::span<const float> vertices);
	
	OpenGLES2VertexBuffer(const OpenGLES2VertexBuffer&) = delete;
	OpenGLES2VertexBuffer& operator=(const OpenGLES2VertexBuffer&) = delete;

private:
	void init(GLsizeiptr size, const GLvoid* data);
};


}
