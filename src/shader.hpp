#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "texture.hpp"
#include "common.hpp"

#define SHADER_UNDERCOMPILED -1

class Shader {
private:
    std::string vertCode;
    std::string fragCode;

    /// Chached uniforms
    std::unordered_map<std::string, i32> uniforms;

    i32 getUniformLoc(const std::string &name);
public:
    /// Program ID
    /// -1 indicates the shader being uncompiled.
    u32 programID = SHADER_UNDERCOMPILED;

    // Constructor reads and builds the shader
    Shader(const char vertexPath[], const char fragmentPath[]);

    ~Shader();

    // Compile shader
    void compile();

    // Use/activate the shader
    void use();

    // Utility uniform function
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setMat2(const std::string &name, glm::mat2 value);
    void setMat3(const std::string &name, glm::mat3 value);
    void setMat4(const std::string &name, glm::mat4 value);
    void setVec1(const std::string &name, glm::vec1 value);
    void setVec2(const std::string &name, glm::vec2 value);
    void setVec3(const std::string &name, glm::vec3 value);
    void setVec1(const std::string &name, float x);
    void setVec2(const std::string &name, float x, float y);
    void setVec3(const std::string &name, float x, float y, float z);
};

