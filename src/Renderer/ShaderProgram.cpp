#include "ShaderProgram.h"
#include <iostream>

using namespace std;

namespace Renderer {

ShaderProgram::ShaderProgram(const string& vertexShader, const string& fragmentShader) {
    GLuint vertexShaderID;
    if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) {
        cerr << "VERTEX SHADER compile time error" << endl;
        return;
    }

    GLuint fragmentShaderID;
    if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {
        cerr << "FRAGMENT SHADER compile time error" << endl;
        glDeleteShader(vertexShaderID);
        return;
    }

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShaderID);
    glAttachShader(m_ID, fragmentShaderID);
    glLinkProgram(m_ID);

    GLuint success;
    glGetProgramiv(m_ID, GL_LINK_STATUS, reinterpret_cast<GLint*>(&success));
    if (!success) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(m_ID, 1024, nullptr, infoLog);
        cerr << "Error: Shader link time error: " << infoLog << endl;
        return;
    } else {
        m_isComplete = true;
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

bool ShaderProgram::createShader(const string& source, const GLenum shaderType, GLuint& shaderID) {
    shaderID = glCreateShader(shaderType);
    const char* code = source.c_str();
    glShaderSource(shaderID, 1, &code, nullptr);
    glCompileShader(shaderID);

    GLuint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, reinterpret_cast<GLint*>(&success));
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
        cerr << "Error: Shader compile time error: " << infoLog << endl;
        return false;
    }
    return true;
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_ID);
}

void ShaderProgram::use() const {
    glUseProgram(m_ID);
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept {
    if (this != &other) {
        glDeleteProgram(m_ID);
        m_ID = other.m_ID;
        m_isComplete = other.m_isComplete;

        other.m_ID = 0;
        other.m_isComplete = false;
    }
    return *this;
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept {
    m_ID = other.m_ID;
    m_isComplete = other.m_isComplete;

    other.m_ID = 0;
    other.m_isComplete = false;
}

}
