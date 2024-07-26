#pragma once

#include "yaml-cpp/yaml.h"
#include "glm/glm.hpp"

#include "pch.hpp"

namespace YAML {
    /**
     * @brief Converts a glm::vec2 to a YAML node and vice versa
     *
     * This struct implements the convert functions for glm::vec2 to work with
     * the YAML library. The conversion is done by mapping the x and y components
     * of the vector to the elements of a YAML sequence.
     */
    template<>
    struct convert<glm::vec2> {
        /**
         * @brief Converts a glm::vec2 to a YAML node
         *
         * @param rhs The glm::vec2 to convert
         * @return A YAML node representing the vector
         */
        static Node encode(const glm::vec2& rhs) {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            return node;
        }

        /**
         * @brief Converts a YAML node to a glm::vec2
         *
         * @param node The YAML node to convert
         * @param rhs The glm::vec2 to store the result in
         * @return true if the conversion was successful, false otherwise
         */
        static bool decode(const Node& node, glm::vec2& rhs) {
            if(!node.IsSequence() || node.size() != 2) {
                return false;
            }

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };

     
    /**
     * @brief Converts a glm::vec4 to a YAML node and vice versa
     *
     * This struct implements the convert functions for glm::vec4 to work with
     * the YAML library. The conversion is done by mapping the x, y, z, and w
     * components of the vector to the elements of a YAML sequence.
     */
    template<>
    struct convert<glm::vec4> {
        /**
         * @brief Converts a glm::vec4 to a YAML node
         *
         * @param rhs The glm::vec4 to convert
         * @return A YAML node representing the vector
         */
        static Node encode(const glm::vec4& rhs) {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            return node;
        }

        /**
         * @brief Converts a YAML node to a glm::vec4
         *
         * @param node The YAML node to convert
         * @param rhs The glm::vec4 to store the result in
         * @return true if the conversion was successful, false otherwise
         */
        static bool decode(const Node& node, glm::vec4& rhs) {
            if(!node.IsSequence() || node.size() != 4) {
                return false;
            }

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };
}
