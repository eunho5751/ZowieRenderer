
#include "shader.hpp"

#include <glad/glad.h>

#include <iostream>
#include <utility>

Shader::Shader() : id_(0), is_compiled_(false)
{

}

Shader::~Shader()
{
	if (is_compiled_)
	{
		glDeleteProgram(id_);
	}
}

void Shader::Compile()
{
	if (is_compiled_)
	{
		return;
	}

	unsigned int vertex_shader = 0;
	unsigned int fragment_shader = 0;
	unsigned int program = 0;

	int success = false;
	char compile_log[512];
	do
	{
		// Vertex Shader
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		auto* vertex_code = vs_.c_str();
		glShaderSource(vertex_shader, 1, &vertex_code, nullptr);
		glCompileShader(vertex_shader);

		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex_shader, sizeof(compile_log), nullptr, compile_log);
			break;
		}

		// Fragment Shader
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		auto* fragment_code = fs_.c_str();
		glShaderSource(fragment_shader, 1, &fragment_code, nullptr);
		glCompileShader(fragment_shader);

		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment_shader, sizeof(compile_log), nullptr, compile_log);
			break;
		}

		// Program
		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(program, sizeof(compile_log), nullptr, compile_log);
			break;
		}

		id_ = program;
		is_compiled_ = true;
	} while (false);

	glDetachShader(program, vertex_shader);
	glDetachShader(program, fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	if (!is_compiled_)
	{
		std::cout << "Failed to compile shader.\n" << compile_log << std::endl;
		glDeleteProgram(program);
	}
}

void Shader::Use()
{
	glUseProgram(id_);
}

void Shader::SetBool(std::string_view name, bool value)
{
	glUniform1i(glGetUniformLocation(id_, name.data()), static_cast<int>(value));
}

void Shader::SetInt(std::string_view name, int value)
{
	glUniform1i(glGetUniformLocation(id_, name.data()), value);
}

void Shader::SetFloat(std::string_view name, float value)
{
	glUniform1f(glGetUniformLocation(id_, name.data()), value);
}

void Shader::set_vertex_shader(std::string vs)
{
	vs_ = std::move(vs);
}

void Shader::set_fragment_shader(std::string fs)
{
	fs_ = std::move(fs);
}

bool Shader::is_compiled() const
{
	return is_compiled_;
}
