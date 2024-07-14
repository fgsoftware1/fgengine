#pragma once

#include "chaiscript/chaiscript.hpp"
#include <yaml-cpp/yaml.h>

#include "pch.hpp"

class ChaiBinder
{
public:
    ChaiBinder() : chai(new chaiscript::ChaiScript()) {}

    template<typename T>
    ChaiBinder& klass(const std::string& name) {
        chai->add(chaiscript::user_type<T>(), name);
        bindings[name] = { "class" };
        return *this;
    }

    template<typename T>
    ChaiBinder& ctor() {
        chai->add(chaiscript::constructor<T>(), "Vector2");
        bindings[typeid(T).name()].push_back("ctor");
        return *this;
    }

    template<typename Func>
    ChaiBinder& method(const std::string& name, const Func& f) {
        chai->add(chaiscript::fun(f), name);
        bindings[name].push_back("method");
        return *this;
    }

    template<typename T>
    ChaiBinder& var(const std::string& name, const T& t) {
        chai->add(chaiscript::var(t), name);
        return *this;
    }

    void runFromSource(const std::string& str) {
        chai->eval(str);
    }

    void runFromFile(const std::string& file) {
        chai->eval_file(file);
    }

    const std::map<std::string, std::vector<std::string>>& getBindings() const {
        return bindings;
    }

    void generateYAML(const ChaiBinder& binder, const std::string& filename) {
        const auto& bindings = binder.getBindings();

        YAML::Emitter out;
        out << YAML::BeginMap;

        for (const auto& kv : bindings) {
            out << YAML::Key << kv.first;
            out << YAML::Value << YAML::BeginSeq;
            for (const auto& type : kv.second) {
                out << type;
            }
            out << YAML::EndSeq;
        }

        out << YAML::EndMap;

        std::ofstream fout(filename);
        fout << out.c_str();
    }

private:
    Scope<chaiscript::ChaiScript> chai;
    std::map<std::string, std::vector<std::string>> bindings;
};
