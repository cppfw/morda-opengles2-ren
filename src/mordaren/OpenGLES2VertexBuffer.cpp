#include "OpenGLES2VertexBuffer.hpp"

#include "OpenGLES2_util.hpp"

using namespace mordaren;

void OpenGLES2VertexBuffer::init(GLsizeiptr size, const GLvoid* data) {
	glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
	assertOpenGLNoError();
	
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	assertOpenGLNoError();
	
	//TODO: remove this
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	assertOpenGLNoError();
}


OpenGLES2VertexBuffer::OpenGLES2VertexBuffer(const utki::Buf<kolme::Vec4f> vertices) :
		morda::VertexBuffer(vertices.size()),
		numComponents(4),
		type(GL_FLOAT)
{
	this->init(vertices.sizeInBytes(), &*vertices.begin());
}

OpenGLES2VertexBuffer::OpenGLES2VertexBuffer(const utki::Buf<kolme::Vec3f> vertices) :
		morda::VertexBuffer(vertices.size()),
		numComponents(3),
		type(GL_FLOAT)
{
	this->init(vertices.sizeInBytes(), &*vertices.begin());
}

OpenGLES2VertexBuffer::OpenGLES2VertexBuffer(const utki::Buf<kolme::Vec2f> vertices) :
		morda::VertexBuffer(vertices.size()),
		numComponents(2),
		type(GL_FLOAT)
{
	this->init(vertices.sizeInBytes(), &*vertices.begin());
}
