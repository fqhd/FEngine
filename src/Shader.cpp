#include "Shader.hpp"
#include <iostream>

std::string readFileToString(const std::string &shaderName)
{
    std::string shaderCode = "";
    std::string line;
    std::ifstream is;
    is.open(shaderName);
    if (is.fail())
    {
        is.close();
        return shaderCode;
    }

    while (std::getline(is, line))
    {
        shaderCode += line + "\n";
    }

    is.close();
    return shaderCode;
}

void Shader::init(const std::string &dirPath)
{
    m_programID = glCreateProgram();

    m_vertexID = glCreateShader(GL_VERTEX_SHADER);
    std::string vsCode = readFileToString(dirPath + "/vertex.glsl");
    const char *vs_pointer = vsCode.c_str();
    glShaderSource(m_vertexID, 1, &vs_pointer, 0);
    GLint vsCompileStatus;
    glCompileShader(m_vertexID);
    glGetShaderiv(m_vertexID, GL_COMPILE_STATUS, &vsCompileStatus);
    if (!vsCompileStatus)
    {
        std::cout << "Failed to compile vertex shader: " << dirPath + "/vertex.glsl" << std::endl;
    }
    glAttachShader(m_programID, m_vertexID);

    m_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fsCode = readFileToString(dirPath + "/fragment.glsl");
    const char *fs_pointer = fsCode.c_str();
    glShaderSource(m_fragmentID, 1, &fs_pointer, 0);
    GLint fsCompileStatus;
    glCompileShader(m_fragmentID);
    glGetShaderiv(m_fragmentID, GL_COMPILE_STATUS, &fsCompileStatus);
    if (!fsCompileStatus)
    {
        std::cout << "Failed to compile fragment shader: " << dirPath + "/fragment.glsl" << std::endl;
    }
    glAttachShader(m_programID, m_fragmentID);

    std::string gsCode = readFileToString(dirPath + "/geometry.glsl");
    if (gsCode != "")
    {
        m_geometryID = glCreateShader(GL_GEOMETRY_SHADER);
        const char *gs_pointer = gsCode.c_str();
        glShaderSource(m_geometryID, 1, &gs_pointer, 0);
        GLint gsCompileStatus;
        glCompileShader(m_geometryID);
        glGetShaderiv(m_geometryID, GL_COMPILE_STATUS, &gsCompileStatus);
        if (!gsCompileStatus)
        {
            std::cout << "Failed to compile geometry shader: " << dirPath + "/geometry.glsl" << std::endl;
        }
        glAttachShader(m_programID, m_geometryID);
    }

    glLinkProgram(m_programID);
    GLint isLinked = 0;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        std::cout << "Failed to link shader: " + dirPath << std::endl;
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