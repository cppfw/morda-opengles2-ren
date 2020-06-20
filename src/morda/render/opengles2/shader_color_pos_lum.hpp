#pragma once

#include <morda/render/coloring_shader.hpp>
#include "shader_base.hpp"

namespace morda{ namespace render_opengles2{

class shader_color_pos_lum :
		public morda::coloring_shader,
		private shader_base
{
	GLint colorUniform;
public:
	shader_color_pos_lum();
	
	shader_color_pos_lum(const shader_color_pos_lum&) = delete;
	shader_color_pos_lum& operator=(const shader_color_pos_lum&) = delete;
	
	using morda::coloring_shader::render;
	
	void render(const r4::mat4f& m, const morda::vertex_array& va, r4::vec4f color)const override;
};

}}
