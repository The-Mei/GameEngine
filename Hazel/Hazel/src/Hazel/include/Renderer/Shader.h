#pragma once

#include <string>
#include <unordered_map>

class Shader
{
public:
    Shader(const std::string vertexPath, const std::string fragmentPath);
    ~Shader();
    void bind();
    void unBind();
    unsigned int getProgramId() { return mProgramId; }
    void setUniform1f(const std::string &name, float value);
    void setUniformMatrix4fv(const std::string &name, float *value);
    void setUniform1i(const std::string &name, int value);

private:
    std::string readShaderSource(const std::string &filepath);
    unsigned int compileShader(unsigned int type, const std::string &source);
    unsigned int createShaderProgram(const std::string &vertexSource, const std::string &fragmentSource);
    unsigned int getUniformId(const std::string name);

private:
    unsigned int mProgramId;
    std::unordered_map<std::string, unsigned int> mUniform;
};