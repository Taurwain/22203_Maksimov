#ifndef FLATMAP_H
#define FLATMAP_H

#include <string>

typedef std::string Key;

struct Value {
    unsigned age = 0;
    unsigned weight = 0;
};

class FlatMap
{
public:
    FlatMap();
    ~FlatMap();
    FlatMap(const FlatMap& b);
    FlatMap(FlatMap&& b) noexcept;
    void swap(FlatMap& b);
    FlatMap& operator=(const FlatMap& b);
    FlatMap& operator=(FlatMap&& b) noexcept;
    void clear();
    int64_t binarySearch(const Key& k) const;
    bool erase(const Key& k);
    bool insert(const Key& k, const Value& v);
    bool contains(const Key& k) const;
    Value& operator[](const Key& k);
    Value& at(const Key& k);
    const Value& at(const Key& k) const;
    size_t size() const;
    bool empty() const;
    friend bool operator==(const FlatMap& a, const FlatMap& b);
    friend bool operator!=(const FlatMap& a, const FlatMap& b);
    Key firstKey() const;
    Key lastKey() const;

private:
    struct Value* values = nullptr;
    Key* keys = nullptr;
    size_t map_size = 0;
    size_t map_capacity = 0;
    static const int ResizeMultiplier = 2;
    void resize(size_t newCapacity);
};

#endif //FLATMAP_H