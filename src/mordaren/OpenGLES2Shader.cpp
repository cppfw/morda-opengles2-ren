#include <utki/debug.hpp>
#include <utki/Exc.hpp>

#include <vector>

#include "OpenGLES2Shader.hpp"
#include "OpenGLES2_util.hpp"
#include "OpenGLES2VertexArray.hpp"
#include "OpenGLES2IndexBuffer.hpp"
#include "OpenGLES2VertexBuffer.hpp"


#include <GLES2/gl2.h>


using namespace mordaren;

const OpenGLES2Shader* OpenGLES2Shader::boundShader = nullptr;


GLenum OpenGLES2Shader::modeMap[] = {
	GL_TRIANGLES,			//TRIANGLES
	GL_TRIANGLE_FAN,		//TRIANGLE_FAN
	GL_LINE_LOOP,			//LINE_LOOP
	GL_TRIANGLE_STRIP		//TRIANGLE_STRIP
};




namespace{
//return true if not compiled
bool checkForCompileErrors(GLuint shader) {
	GLint value = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &value);
	if (value == 0) { //if not compiled
		GLint logLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 1) {//1 char is a terminating 0
			std::vector<char> log(logLen);
			GLint len;
			glGetShaderInfoLog(shader, GLsizei(log.size()), &len, &*log.begin());
			TRACE( << "===Compile log===\n" << &*log.begin() << std::endl)
		} else {
			TRACE( << "Shader compile log is empty" << std::endl)
		}
		return true;
	}
	return false;
}

//return true if not linked
bool checkForLinkErrors(GLuint program){
	GLint value = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &value);
	if(value == 0){ //if not linked
		GLint logLen = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
		if(logLen > 1){ //1 is for terminating 0 character.
			std::vector<char> log(logLen);
			GLint len;
			glGetProgramInfoLog(program, GLsizei(log.size()), &len, &*log.begin());
			TRACE(<< "===Link log===\n" << &*log.begin() << std::endl)
		}
		return true;
	}
	return false;
}

}



ShaderWrapper::ShaderWrapper(const char* code, GLenum type) {
	this->s = glCreateShader(type);

	if (this->s == 0) {
		throw utki::Exc("glCreateShader() failed");
	}

	const char* c = code;

	glShaderSource(this->s, 1, &c, 0);
	glCompileShader(this->s);
	if (checkForCompileErrors(this->s)) {
		TRACE( << "Error while compiling:\n" << c << std::endl)
		glDeleteShader(this->s);
		throw utki::Exc("Error compiling shader");
	}
}


ProgramWrapper::ProgramWrapper(const char* vertexShaderCode, const char* fragmentShaderCode) :
		vertexShader(vertexShaderCode, GL_VERTEX_SHADER),
		fragmentShader(fragmentShaderCode, GL_FRAGMENT_SHADER)
{
	this->p = glCreateProgram();
	glAttachShader(this->p, vertexShader.s);
	glAttachShader(this->p, fragmentShader.s);
	
	GLint maxAttribs;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttribs);
	ASSERT(maxAttribs >= 0)
	
	for(GLuint i = 0; i < GLuint(maxAttribs); ++i){
		std::stringstream ss;
		ss << "a" << i;
//		TRACE(<< ss.str() << std::endl)
		glBindAttribLocation(this->p, i, ss.str().c_str());
		assertOpenGLNoError();
	}
	
	glLinkProgram(this->p);
	if (checkForLinkErrors(this->p)) {
		TRACE( << "Error while linking shader program" << vertexShaderCode << std::endl << fragmentShaderCode << std::endl)
		glDeleteProgram(this->p);
		throw utki::Exc("Error linking shader program");
	}
}




OpenGLES2Shader::OpenGLES2Shader(const char* vertexShaderCode, const char* fragmentShaderCode) :
		program(vertexShaderCode, fragmentShaderCode),
		matrixUniform(this->getUniform("matrix"))
{
}

GLint OpenGLES2Shader::getUniform(const char* n) {
	GLint ret = glGetUniformLocation(this->program.p, n);
	if(ret < 0){
		throw utki::Exc("No uniform found in the shader program");
	}
	return ret;
}

void OpenGLES2Shader::render(const kolme::Matr4f& m, const morda::VertexArray& va)const{
	ASSERT(this->isBound())
	
	ASSERT(dynamic_cast<const OpenGLES2IndexBuffer*>(va.indices.operator ->()))
	auto& ivbo = static_cast<const OpenGLES2IndexBuffer&>(*va.indices);
	
	this->setMatrix(m);
	
	for(unsigned i = 0; i != va.buffers.size(); ++i){
		ASSERT(dynamic_cast<OpenGLES2VertexBuffer*>(va.buffers[i].operator->()))
		auto& vbo = static_cast<OpenGLES2VertexBuffer&>(*va.buffers[i]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo.buffer);
		assertOpenGLNoError();
		
//		TRACE(<< "vbo.numComponents = " << vbo.numComponents << " vbo.type = " << vbo.type << std::endl)
		
		glVertexAttribPointer(i, vbo.numComponents, vbo.type, GL_FALSE, 0, nullptr);
		assertOpenGLNoError();
		
		glEnableVertexAttribArray(i);
		assertOpenGLNoError();
	}
	
	{
		ASSERT(dynamic_cast<OpenGLES2IndexBuffer*>(va.indices.operator->()))
		auto& ivbo = static_cast<OpenGLES2IndexBuffer&>(*va.indices);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ivbo.buffer);
		assertOpenGLNoError();
	}
	

//	TRACE(<< "ivbo.elementsCount = " << ivbo.elementsCount << " ivbo.elementType = " << ivbo.elementType << std::endl)
	
	glDrawElements(modeToGLMode(va.mode), ivbo.elementsCount, ivbo.elementType, nullptr);
	assertOpenGLNoError();
}

