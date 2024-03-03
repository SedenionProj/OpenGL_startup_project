#pragma once
#include <iostream>
#include <glad/glad.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:
	unsigned int ID;
public:
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	Shader() = default;

	~Shader();

	void createShader(const char* vShaderCode, const char* fShaderCode, const char* geometryCode = nullptr);

	void Bind() const;
	void Unind() const;
	inline unsigned int getId() const { return ID; }
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, const glm::vec3 values) const;
	void setVec2(const std::string& name, const glm::vec2 values) const;
	void setMat4(const std::string& name, const glm::mat4& matrix, const float instance = 1) const;
};