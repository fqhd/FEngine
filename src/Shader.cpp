#include <FEngine/Shader.hpp>
#include <iostream>


void Shader::init(const char* vsCode, const char* fsCode, const char* gsCode)
{
    m_programID = glCreateProgram();

    m_vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexID, 1, &vsCode, 0);
    GLint vsCompileStatus;
    glCompileShader(m_vertexID);
    glGetShaderiv(m_vertexID, GL_COMPILE_STATUS, &vsCompileStatus);
    if (!vsCompileStatus)
    {
        std::cout << "Failed to compile vertex shader" << std::endl;
    }
    glAttachShader(m_programID, m_vertexID);

    m_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentID, 1, &fsCode, 0);
    GLint fsCompileStatus;
    glCompileShader(m_fragmentID);
    glGetShaderiv(m_fragmentID, GL_COMPILE_STATUS, &fsCompileStatus);
    if (!fsCompileStatus)
    {
        std::cout << "Failed to compile fragment shader" << std::endl;
    }
    glAttachShader(m_programID, m_fragmentID);

    if (gsCode != nullptr)
    {
        m_geometryID = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(m_geometryID, 1, &gsCode, 0);
        GLint gsCompileStatus;
        glCompileShader(m_geometryID);
        glGetShaderiv(m_geometryID, GL_COMPILE_STATUS, &gsCompileStatus);
        if (!gsCompileStatus)
        {
            std::cout << "Failed to compile geometry" << std::endl;
        }
        glAttachShader(m_programID, m_geometryID);
    }

    glLinkProgram(m_programID);
    GLint isLinked = 0;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        std::cout << "Failed to link shader" << std::endl;
    }
    glValidateProgram(m_programID);
}

void Shader::bind()
{
    glUseProgram(m_programID);
}

void Shader::unbind()
{
    glUseProgram(0);
}

void Shader::destroy()
{
    glDetachShader(m_programID, m_vertexID);
    glDetachShader(m_programID, m_fragmentID);
    glDetachShader(m_programID, m_geometryID);
    glDeleteShader(m_vertexID);
    glDeleteShader(m_fragmentID);
    glDeleteProgram(m_programID);
}

GLint Shader::getUniformLocation(const std::string &name)
{
    auto it = m_uniformLocations.find(name);
    if (it == m_uniformLocations.end())
    {
        GLint location = glGetUniformLocation(m_programID, name.c_str());
        m_uniformLocations[name] = location;
        return location;
    }
    return it->second;
}

void Shader::set(const std::string &name, const glm::vec3 &vec)
{
    glUniform3fv(getUniformLocation(name), 1, &vec.x);
}

void Shader::set(const std::string &name, const glm::ivec2 &vec)
{
    glUniform2iv(getUniformLocation(name), 1, &vec.x);
}

void Shader::set(const std::string &name, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::set(const std::string &name, float f)
{
    glUniform1f(getUniformLocation(name), f);
}

void Shader::set(const std::string &name, int i)
{
    glUniform1i(getUniformLocation(name), i);
}

void Shader::set(const std::string &name, bool b)
{
    int value = (int)b;
    glUniform1i(getUniformLocation(name), value);
}