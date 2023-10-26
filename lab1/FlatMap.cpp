#include "FlatMap.h"

#include <iostream>
#include <algorithm>
#include <cassert>

FlatMap::FlatMap() = default;

FlatMap::~FlatMap() {
    delete [] values;
    delete [] keys;
}

FlatMap::FlatMap(const FlatMap& b) : map_capacity(b.map_capacity), map_size(b.map_size) {
    values = new Value[b.map_capacity];
    keys = new Key[b.map_capacity];
    std::copy(b.keys, b.keys + b.map_size, keys);
    std::copy(b.values, b.values + b.map_size, values);
    //std::cout << "Copy constructor" << std::endl;
}

FlatMap::FlatMap(FlatMap&& b) noexcept : map_capacity(b.map_capacity), map_size(b.map_size),
                                                                keys(b.keys), values(b.values) {
    b.keys = nullptr;
    b.values = nullptr;
    b.map_size = b.map_capacity = 0;
    //std::cout << "Move constructor" << std::endl;
}

void FlatMap::swap(FlatMap& b) {
    std::swap(keys, b.keys);
    std::swap(values, b.values);
    std::swap(map_capacity, b.map_capacity);
    std::swap(map_size, b.map_size);
}

FlatMap& FlatMap::operator = (const FlatMap& b) {
    if (this != &b) {
        FlatMap(b).swap(*this);
    }
    //std::cout << "Copied" << std::endl;
    return *this;
}

FlatMap& FlatMap::operator = (FlatMap&& b) noexcept {
    if (this != &b) {
        FlatMap(std::move(b)).swap(*this);
    }
    //std::cout << "Moved" << std::endl;
    return *this;
}

void FlatMap::clear() {
    for (; map_size > 0; map_size--) {
        values[map_size - 1] = Value();
        keys[map_size - 1] = "";
    }
}

void FlatMap::resize(size_t newCapacity) {
    assert(newCapacity > map_size);
    Key* tmp_keys = new Key[newCapacity];
    auto* tmp_values = new Value[newCapacity];
    std::copy(keys, keys + map_size, tmp_keys);
    std::copy(values, values + map_size, tmp_values);
    delete [] keys;
    delete [] values;
    keys = tmp_keys;
    values = tmp_values;
    map_capacity = newCapacity;
}

int64_t FlatMap::binarySearch(const Key& k) const {
    int64_t left = 0;
    int64_t right = (int64_t)map_size - 1;
    int64_t middle;
    while (left <= right) {
        middle = left + ((right - left) / 2);
        if (keys[middle] < k) {
            left = middle + 1;
        } else if (keys[middle] > k) {
            right = middle - 1;
        } else {
            return (middle);
        }
    }
    return (-1)*(left+1);
}

bool FlatMap::erase(const Key& k) {
    if (map_size == 0) {
        return false;
    }
    int64_t placeToErase = binarySearch(k);
    if (placeToErase >= 0) {
        std::move(keys + placeToErase + 1, keys + map_size,
                 keys + placeToErase);
        std::move(values + placeToErase + 1, values + map_size,
                  values + placeToErase);
        keys[map_size - 1] = "";

        values[map_size - 1] = {0, 0};
        map_size--;
        return true;
    }
    return false;
}

bool FlatMap::insert(const Key& k, const Value& v) {
    if (map_size == map_capacity) {
        resize(map_size*ResizeMultiplier + 1);
    }
    int64_t placeToInsert = binarySearch(k);
    if (placeToInsert >= 0) {
        return false;
    } else placeToInsert = (-1)*placeToInsert - 1;

    Key* keysTmp = new Key[map_size+1];
    auto* valuesTmp = new Value[map_size+1];


    std::copy(keys, keys + placeToInsert, keysTmp);
    std::copy(values, values + placeToInsert, valuesTmp);
    std::copy(keys + placeToInsert, keys + map_size,
                                        keysTmp + placeToInsert + 1);
    std::copy(values + placeToInsert, values + map_size,
                                        valuesTmp + placeToInsert + 1);

    keysTmp[placeToInsert] = k;
    valuesTmp[placeToInsert] = v;

    std::move(keysTmp, keysTmp + map_size + 1, keys);
    std::move(valuesTmp, valuesTmp + map_size + 1, values);
    delete [] keysTmp;
    delete [] valuesTmp;
    map_size++;
    return true;
}

bool FlatMap::contains(const Key& k) const {
    if (map_size == 0) {
        return false;
    }
    return (binarySearch(k) >= 0);
}

Value& FlatMap::operator [] (const Key& k) {
    int64_t placeToCheck = binarySearch(k);
    if (placeToCheck >= 0) {
        return values[placeToCheck];
    }
    insert(k, Value());
    return values[(-1)*placeToCheck - 1];
}

// Возвращает значение по ключу. Бросает исключение при неудаче.
Value& FlatMap::at(const Key& k) {
    int64_t placeToCheck = binarySearch(k);
    if (placeToCheck >= 0) {
        return values[placeToCheck];
    }
    throw std::out_of_range("The value you asked for doesn't exist!");

}

const Value& FlatMap::at(const Key& k) const {
    return const_cast<FlatMap*>(this)->at(k);
}

size_t FlatMap::size() const {
    return map_size;
}

bool FlatMap::empty() const {
    return (map_size == 0);
}

bool operator == (const FlatMap& a, const FlatMap& b) {
    if (a.map_size != b.map_size) {
        return false;
    }
    for (unsigned long i = 0; i < a.map_size; i++) {
        if (a.keys[i] != b.keys[i]) {
            return false;
        }
        if (a.values[i].weight != b.values[i].weight ||
            a.values[i].age != b.values[i].age) {
            return false;
        }
    }
    return true;
}

bool operator != (const FlatMap& a, const FlatMap& b) {
    return !(a == b);
}

Key FlatMap::firstKey() const {
    return keys[0];
}

Key FlatMap::lastKey() const {
    return keys[map_size-1];
}

