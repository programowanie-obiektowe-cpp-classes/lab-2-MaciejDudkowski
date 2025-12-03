#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

class ResourceManager
{
private:
    std::unique_ptr< Resource > resource_;

public:
    ResourceManager() : resource_(std::make_unique< Resource >())
    {
        std::cout << "ResourceManager constructed\n";
    }

    ResourceManager(const ResourceManager& other)
        : resource_(other.resource_ ? std::make_unique< Resource >(*other.resource_) : nullptr)
    {
        std::cout << "ResourceManager copied\n";
    }

    ResourceManager(ResourceManager&& other) noexcept = default;

    ResourceManager& operator=(const ResourceManager& other)
    {
        std::cout << "ResourceManager copy-assigned\n";
        if (this != &other) {
            resource_ = other.resource_ ? std::make_unique< Resource >(*other.resource_) : nullptr;
        }
        return *this;
    }

    ResourceManager& operator=(ResourceManager&& other) noexcept = default;

    ~ResourceManager() { std::cout << "ResourceManager destroyed\n"; }

    double get() const { return resource_->get(); }
};

int main()
{
    std::cout << "sizeof(Resource): " << sizeof(Resource) << " bytes\n";
    std::cout << "sizeof(ResourceManager): " << sizeof(ResourceManager) << " bytes\n\n";

    ResourceManager manager;
    std::cout << "manager.get() = " << manager.get() << "\n\n";

    ResourceManager copy  = manager;
    ResourceManager moved = std::move(manager);

    std::cout << "\nKoniec programu.\n";
}
