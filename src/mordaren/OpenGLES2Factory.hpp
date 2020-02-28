#pragma once

#include <morda/render/render_factory.hpp>


namespace mordaren{

class OpenGLES2Factory : public morda::render_factory{
public:
	OpenGLES2Factory();
	
	OpenGLES2Factory(const OpenGLES2Factory&) = delete;
	OpenGLES2Factory& operator=(const OpenGLES2Factory&) = delete;
	
	virtual ~OpenGLES2Factory()noexcept;

	std::shared_ptr<morda::texture_2d> create_texture_2d(morda::texture_2d::type type, r4::vec2ui dims, const utki::span<uint8_t> data)override;

	std::shared_ptr<morda::vertex_buffer> create_vertex_buffer(const utki::span<r4::vec4f> vertices)override;
	std::shared_ptr<morda::vertex_buffer> create_vertex_buffer(const utki::span<r4::vec3f> vertices)override;
	std::shared_ptr<morda::vertex_buffer> create_vertex_buffer(const utki::span<r4::vec2f> vertices)override;
	std::shared_ptr<morda::vertex_buffer> create_vertex_buffer(const utki::span<float> vertices)override;

	std::shared_ptr<morda::index_buffer> create_index_buffer(const utki::span<uint16_t> indices)override;
	
	std::shared_ptr<morda::vertex_array> create_vertex_array(
			std::vector<std::shared_ptr<morda::vertex_buffer>>&& buffers,
			std::shared_ptr<morda::index_buffer> indices,
			morda::vertex_array::mode rendering_mode
		)override;

	std::unique_ptr<shaders> create_shaders()override;
	
	std::shared_ptr<morda::frame_buffer> create_framebuffer(std::shared_ptr<morda::texture_2d> color)override;
};

}
