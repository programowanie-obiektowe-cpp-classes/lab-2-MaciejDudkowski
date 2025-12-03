#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

class Resource
{
private:
    static constexpr size_t   SIZE = 100'000'000;
    std::unique_ptr< char[] > data_;

public:
    Resource() : data_(std::make_unique< char[] >(SIZE))
    {
        std::memset(data_.get(), 0, SIZE);
        std::cout << "Resource constructed (" << SIZE << " bytes)\n";
    }

    Resource(const Resource& other) : data_(std::make_unique< char[] >(SIZE))
    {
        std::memcpy(data_.get(), other.data_.get(), SIZE);
        std::cout << "Resource copied\n";
    }

    Resource(Resource&& other) noexcept : data_(std::move(other.data_))
    {
        std::cout << "Resource moved\n";
    }

    Resource& operator=(const Resource& other)
    {
        if (this != &other) {
            data_ = std::make_unique< char[] >(SIZE);
            std::memcpy(data_.get(), other.data_.get(), SIZE);
        }
        std::cout << "Resource copy-assigned\n";
        return *this;
    }

    Resource& operator=(Resource&& other) noexcept
    {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        std::cout << "Resource move-assigned\n";
        return *this;
    }

    ~Resource() { std::cout << "Resource destroyed\n"; }

    double get() const
    {
        return 42.0;
    }
};


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
