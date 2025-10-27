#pragma once

#include "Resource.hpp"
#include <iostream>
#include <utility>
#include <stdexcept>

class Resource
{
public:
    Resource() {}
    Resource(const Resource&) {}
    Resource(Resource&&) noexcept {}
    Resource& operator=(const Resource&)
    {
        return *this;
    }
    Resource& operator=(Resource&&) noexcept
    {
        return *this;
    }
    ~Resource() {}

    double get() const { return 42.0; }
};

class ResourceManager
{
private:
    Resource* resource;

public:
    ResourceManager() : resource(new Resource())
    {
    }

    ResourceManager(const ResourceManager& other) : resource(new Resource(*other.resource))
    {
    }

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

    ~ResourceManager()
    {
        delete resource;
    }

    double get() const
    {
        if (!resource)
            throw std::runtime_error("Brak zasobu!");
        return resource->get();
    }
};
int main()
{
    std::cout << "Tworzenie r1\n";
    ResourceManager r1;
    std::cout << "Wynik r1.get(): " << r1.get() << "\n\n";

    std::cout << "Kopiowanie r2 = r1\n";
    ResourceManager r2 = r1;
    std::cout << "Wynik r2.get(): " << r2.get() << "\n\n";

    std::cout << "Przenoszenie r3 = std::move(r1)\n";
    ResourceManager r3 = std::move(r1);
    std::cout << "Wynik r3.get(): " << r3.get() << "\n\n";

    std::cout << "Przypisanie kopiuj¹ce r2 = r3\n";
    r2 = r3;

    std::cout << "Przypisanie przenosz¹ce r3 = std::move(r2)\n";
    r3 = std::move(r2);

    return 0;
}
