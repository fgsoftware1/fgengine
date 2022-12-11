#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <vector>

namespace fgengine {
	namespace renderer {
		namespace opengl {
			class Shader
			{
			public:
				Shader();
				void init(const std::string& vertex, const std::string& fragment);
				void use();
				template<typename T> void setUniform(const std::string& name, T val);
				template<typename T> void setUniform(const std::string& name, T val1, T val2);
				template<typename T> void setUniform(const std::string& name, T val1, T val2, T val3);

			private:
				void checkCompileErr();
				void checkLinkingErr();
				void compile();
				void link();
				unsigned int vertexID, fragmentID, ID;
				std::string vertexCode;
				std::string fragmentCode;
			};
		}
	}
}
#endif