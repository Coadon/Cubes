#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

#include "shader.hpp"

using namespace std;

i32 Shader::getUniformLoc(const string &name) {
    if (auto srch = uniforms.find(name); srch != uniforms.end())
        return srch->second;
    return uniforms.insert(
            {name, glGetUniformLocation(programID, name.c_str())}).first->second;
}

Shader::Shader(const char vertexPath[], const char fragmentPath[]) {
    ifstream vshFile;
    ifstream fshFile;

    // ensure ifstream objects can throw exceptions
    vshFile.exceptions(ifstream::failbit | ifstream::badbit);
    fshFile.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        // Open files
        vshFile.open(vertexPath);
        fshFile.open(fragmentPath);
        // read file's buffer contents into string streams
        stringstream vshStr, fshStr;
        vshStr << vshFile.rdbuf();
        fshStr << fshFile.rdbuf();
        // close file handlers
        vshFile.close();
        fshFile.close();
        // convert stream into string
        vertCode = vshStr.str();
        fragCode = fshStr.str();
    } catch (ifstream::failure e) {
        LOGGER.error("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: {0}\n{1}", e.what(), e.code().message());
    }
}

Shader::~Shader() { glDeleteProgram(programID); }

void Shader::compile() {
    u32 vshId, fshId;
    int success;
    char infoLog[512];

    const char *vertRawCode = vertCode.c_str();
    const char *fragRawCode = fragCode.c_str();

    // Vertex Shader

    vshId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshId, 1, &vertRawCode, NULL);
    glCompileShader(vshId);

    glGetShaderiv(vshId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vshId, 512, NULL, infoLog);
        LOGGER.error("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{}", infoLog);
    };

    // Fragment SHader

    fshId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshId, 1, &fragRawCode, NULL);
    glCompileShader(fshId);

    glGetShaderiv(fshId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fshId, 512, NULL, infoLog);
        LOGGER.error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{}", infoLog);
    };

    // Shader Program

    programID = glCreateProgram();
    glAttachShader(programID, vshId);
    glAttachShader(programID, fshId);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        LOGGER.error("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{}", infoLog);
    }

    glDeleteShader(vshId);
    glDeleteShader(fshId);

}

void Shader::use() { glUseProgram(programID); }

void Shader::setBool(const string &name, bool value) {
    glUniform1i(getUniformLoc(name), (int) value);
}

void Shader::setInt(const string &name, int value) {
    glUniform1i(getUniformLoc(name), value);
}

void Shader::setFloat(const string &name, float value) {
    glUniform1f(getUniformLoc(name), value);
}

void Shader::setMat2(const string &name, glm::mat2 value) {
    glUniformMatrix2fv(getUniformLoc(name), 1, GL_FALSE,
                       glm::value_ptr(value));
}

void Shader::setMat3(const string &name, glm::mat3 value) {
    glUniformMatrix3fv(getUniformLoc(name), 1, GL_FALSE,
                       glm::value_ptr(value));
}

void Shader::setMat4(const string &name, glm::mat4 value) {
    glUniformMatrix4fv(getUniformLoc(name), 1, GL_FALSE,
                       glm::value_ptr(value));
}

void Shader::setVec1(const string &name, glm::vec1 value) {
    glUniform1f(getUniformLoc(name), value.x);
}

void Shader::setVec2(const string &name, glm::vec2 value) {
    glUniform2f(getUniformLoc(name), value.x, value.y);
}

void Shader::setVec3(const string &name, glm::vec3 value) {
    glUniform3f(getUniformLoc(name), value.x, value.y, value.z);
}

void Shader::setVec1(const string &name, float x) {
    glUniform1f(getUniformLoc(name), x);
}

void Shader::setVec2(const string &name, float x, float y) {
    glUniform2f(getUniformLoc(name), x, y);
}

void Shader::setVec3(const string &name, float x, float y, float z) {
    glUniform3f(getUniformLoc(name), x, y, z);
}

