#pragma once

#include <iostream>
#include <stdexcept> 
#include "Resource.hpp"

class ResourceManager
{
private:
    Resource* resource;

public:
    ResourceManager() : resource(new Resource()) {}

    ResourceManager(const ResourceManager& other) : resource(new Resource(*other.resource)) {}

    ResourceManager(ResourceManager&& other) noexcept : resource(other.resource)
    {
        other.resource = nullptr;
    }

    ResourceManager& operator=(const ResourceManager& other)
    {
        if (this == &other)
            return *this;

        delete resource;
        resource = new Resource(*other.resource);
        return *this;
    }

    ResourceManager& operator=(ResourceManager&& other) noexcept
    {
        if (this == &other)
            return *this;

        delete resource;
        resource       = other.resource;
        other.resource = nullptr;
        return *this;
    }

    ~ResourceManager() { delete resource; }

    double get() const
    {
        if (!resource)
            throw std::runtime_error("Brak zasobu!");
        return resource->get();
    }
};