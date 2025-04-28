#pragma once

#include <glad/glad.h>
#include <string>

using namespace std;

namespace Renderer {

class ShaderProgram {
public:
    ShaderProgram(const string& vertexShader, const string& fragmentShader);
    ~ShaderProgram();

    bool isComplete() const { return m_isComplete; }
    void use() const;

    ShaderProgram() = delete;
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    ShaderProgram(ShaderProgram&& other) noexcept;
    ShaderProgram& operator=(ShaderProgram&& other) noexcept;

private:
    bool createShader(const string& source, GLenum shaderType, GLuint& shaderID);

    bool m_isComplete = false;
    GLuint m_ID = 0;
};

}
