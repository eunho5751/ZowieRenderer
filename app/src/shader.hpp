#pragma once

#include <string>
#include <string_view>

class Shader
{
public:
    Shader();
    ~Shader();

    Shader(const Shader&) = delete;
    Shader(Shader&&) = delete;
    Shader operator=(const Shader&) = delete;
    Shader operator=(Shader&&) = delete;

    void set_vertex_shader(std::string vs);
    void set_fragment_shader(std::string fs);
    bool is_compiled() const;

    void Compile();
    void Use();

    void SetBool(std::string_view name, bool value);
    void SetInt(std::string_view name, int value);
    void SetFloat(std::string_view name, float value);

private:
    unsigned int id_;
    std::string vs_;
    std::string fs_;
    bool is_compiled_;
};