#include <fstream>
#include <sstream>
#include <iostream>

#include "../../include/GL/glew.h"
#include "../../include/GLFW/glfw3.h"
#include "../../include/renderer/OpenGL/Shader.h"

namespace fgengine {
	namespace renderer {
		namespace opengl {
			Shader::Shader() {}

			void Shader::init(const std::string& vertex, const std::string& fragment) {
				vertexCode = vertex;
				fragmentCode = fragment;
				compile();
				link();
			}

			void Shader::compile() {
				const char* vcode = vertexCode.c_str();
				vertexID = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(vertexID, 1, &vcode, NULL);
				glCompileShader(vertexID);

				const char* fcode = fragmentCode.c_str();
				fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(fragmentID, 1, &fcode, NULL);
				glCompileShader(fragmentID);
				checkCompileErr();
			}

			void Shader::link() {
				ID = glCreateProgram();
				glAttachShader(ID, vertexID);
				glAttachShader(ID, fragmentID);
				glLinkProgram(ID);
				checkLinkingErr();
				glDeleteShader(vertexID);
				glDeleteShader(fragmentID);
			}

			void Shader::use() {
				glUseProgram(ID);
			}

			template<>
			void Shader::setUniform<int>(const std::string& name, int val) {
				glUniform1i(glGetUniformLocation(ID, name.c_str()), val);
			}

			template<>
			void Shader::setUniform<bool>(const std::string& name, bool val) {
				glUniform1i(glGetUniformLocation(ID, name.c_str()), val);
			}

			template<>
			void Shader::setUniform<float>(const std::string& name, float val) {
				glUniform1f(glGetUniformLocation(ID, name.c_str()), val);
			}

			template<>
			void Shader::setUniform<float>(const std::string& name, float val1, float val2) {
				glUniform2f(glGetUniformLocation(ID, name.c_str()), val1, val2);
			}

			template<>
			void Shader::setUniform<float>(const std::string& name, float val1, float val2, float val3) {
				glUniform3f(glGetUniformLocation(ID, name.c_str()), val1, val2, val3);
			}

			template<>
			void Shader::setUniform<float*>(const std::string& name, float* val) {
				glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, val);
			}

			void Shader::checkCompileErr() {
				int success;
				char infoLog[1024];
				glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(vertexID, 1024, NULL, infoLog);
					std::cout << "Error compiling Vertex Shader:\n" << infoLog << std::endl;
				}
				glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(fragmentID, 1024, NULL, infoLog);
					std::cout << "Error compiling Fragment Shader:\n" << infoLog << std::endl;
				}
			}

			void Shader::checkLinkingErr() {
				int success;
				char infoLog[1024];
				glGetProgramiv(ID, GL_LINK_STATUS, &success);
				if (!success) {
					glGetProgramInfoLog(ID, 1024, NULL, infoLog);
					std::cout << "Error Linking Shader Program:\n" << infoLog << std::endl;
				}
			}
		}
	}
}