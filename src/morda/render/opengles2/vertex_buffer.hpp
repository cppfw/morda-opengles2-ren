#pragma once

#include <utki/span.hpp>

#include <r4/vector2.hpp>

#include <morda/render/vertex_buffer.hpp>

#include "opengl_buffer.hpp"

namespace morda{ namespace render_opengles2{

class vertex_buffer : public morda::vertex_buffer, public opengl_buffer{
public:
	const GLint numComponents;
	const GLenum type;
	
	vertex_buffer(utki::span<const r4::vec4f> vertices);
	
	vertex_buffer(utki::span<const r4::vec3f> vertices);
	
	vertex_buffer(utki::span<const r4::vec2f> vertices);
	
	vertex_buffer(utki::span<const float> vertices);
	
	vertex_buffer(const vertex_buffer&) = delete;
	vertex_buffer& operator=(const vertex_buffer&) = delete;

private:
	void init(GLsizeiptr size, const GLvoid* data);
};

}}
