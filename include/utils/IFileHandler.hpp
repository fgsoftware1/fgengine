#pragma once

#include "pch.hpp"

/**
 * @class IFileHandler
 * @brief Interface for handling file operations on data of type T.
 *
 * This interface provides a common interface for loading and saving data of
 * type T from and to files. It is templated on the type of data being handled.
 */
template <typename T>
class IFileHandler
{
public:
    /**
     * @brief Virtual destructor for the interface.
     */
    virtual ~IFileHandler() = default;

    /**
     * @brief Load data from a file.
     *
     * @param filename The name of the file to load data from.
     * @return The loaded data.
     */
    virtual Ref<T> Load(const std::string &filename) = 0;

    /**
     * @brief Save data to a file.
     *
     * @param path The path of the file to save data to.
     * @param data The data to save.
     */
    virtual void Save(const std::string &path, const T& data) = 0;
};
