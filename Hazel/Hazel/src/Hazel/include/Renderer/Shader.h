#pragma once

#include <string>
#include <unordered_map>
namespace Hazel
{
    class HAZEL_API Shader
    {
    public:
        ~Shader() = default;
        virtual void bind() = 0;
        virtual void unBind() = 0;
        virtual const std::string &getName() const = 0;

        static Ref<Shader> create(const std::string &filepath);
        static Ref<Shader> create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
    };

    class HAZEL_API ShaderLibrary
    {
    public:
        void add(const std::string &name, const Ref<Shader> &shader);
        void add(const Ref<Shader> &shader);

        Ref<Shader> load(const std::string &filepath);
        Ref<Shader> load(const std::string &name, const std::string &filepath);

        Ref<Shader> get(const std::string &name);

        bool isExist(const std::string &name);

    private:
        std::unordered_map<std::string, Ref<Shader>> mShaders;
    };
}