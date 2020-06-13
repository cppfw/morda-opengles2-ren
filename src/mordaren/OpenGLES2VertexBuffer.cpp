#include "OpenGLES2VertexBuffer.hpp"

#include "OpenGLES2_util.hpp"

using namespace mordaren;

void OpenGLES2VertexBuffer::init(GLsizeiptr size, const GLvoid* data) {
	glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
	assertOpenGLNoError();
	
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	assertOpenGLNoError();
}

OpenGLES2VertexBuffer::OpenGLES2VertexBuffer(utki::span<const r4::vec4f> vertices) :
		morda::vertex_buffer(vertices.size()),
		numComponents(4),
		type(GL_FLOAT)
{
	this->init(vertices.size_bytes(), &*vertices.begin());
}

OpenGLES2VertexBuffer::OpenGLES2VertexBuffer(utki::span<const r4::vec3f> vertices) :
		morda::vertex_buffer(vertices.size()),
		numComponents(3),
		type(GL_FLOAT)
{
	this->init(vertices.size_bytes(), &*vertices.begin());
}

OpenGLES2VertexBuffer::OpenGLES2VertexBuffer(utki::span<const r4::vec2f> vertices) :
		morda::vertex_buffer(vertices.size()),
		numComponents(2),
		type(GL_FLOAT)
{
	this->init(vertices.size_bytes(), &*vertices.begin());
}

OpenGLES2VertexBuffer::OpenGLES2VertexBuffer(utki::span<const float> vertices) :
		morda::vertex_buffer(vertices.size()),
		numComponents(1),
		type(GL_FLOAT)
{
	this->init(vertices.size_bytes(), &*vertices.begin());
}
