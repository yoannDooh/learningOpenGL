#include "../header/shader.h"


/*--SHADER CLASSE--*/
static std::string readGlslFile(std::string filePath)
{
    std::string shader{};
    std::string offStream{};
    std::ifstream shaderFile(filePath);

    while (std::getline(shaderFile, offStream))
    {
        if (offStream != "")
        {
            shader = shader + '\n' + offStream;
        }
    }

    return shader;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexShaderCppStr{ readGlslFile(vertexPath) };
    const char* vertexShaderSrc{ vertexShaderCppStr.c_str() };

    std::string fragmentShaderCppStr{ readGlslFile(fragmentPath) };
    const char* fragmentShaderSrc{ fragmentShaderCppStr.c_str() };

    //fragment shader 
    unsigned int fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    //vertex shader
    unsigned int vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);


    //debug shader and fragment
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
            infoLog << std::endl;

        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
            infoLog << std::endl;
    }

    //link shaders
    Shader::ID = { glCreateProgram() };
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    //debug shader program
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" <<
            infoLog << std::endl;
    }

    //delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set4Float(const std::string& name, float values[4]) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), values[0], values[1], values[2], values[3]);
}

glm::vec3 rgb(float red, float blue, float green)
{
	return glm::vec3(red / 255.0f, blue / 255.0f, green / 255.0f);
}
