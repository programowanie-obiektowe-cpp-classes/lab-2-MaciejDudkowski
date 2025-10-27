#pragma once

#include "Resource.hpp"
#include <iostream>
#include <stdexcept>

class ResourceManager
{
private:
    Resource* resource;

public:
    ResourceManager() : resource(new Resource()) {}

    ResourceManager(const ResourceManager& other) : resource(new Resource(*other.resource)) {}

    ResourceManager& operator=(const ResourceManager& other)
    {
        if (this == &other)
            return *this;

        delete resource;
        resource = new Resource(*other.resource);
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
