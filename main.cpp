#include <iostream>
#include <cstdlib>
#include <cstring>
#include "include/gtest/gtest.h"

typedef std::string Key;

struct Value {
    unsigned age;
    unsigned weight;
};

class FlatMap
{
private:
    struct Value* values;
    Key* keys;
    size_t map_size;
    size_t map_capacity;

    [[nodiscard]] long binarySearch(const Key& k) const {
        long left = 0;
        long right = (long)(map_size - 1);
        long middle;
        while (left <= right) {
            middle = (left + right) / 2;
            if (keys[middle] < k) {
                left = middle + 1;
            } else if (keys[middle] > k) {
                right = middle - 1;
            } else {
                return (long int)(middle);
            }
        }
        return (-1)*(long int)(left+1); //самое точное место вставки
    }                                   //проверка на нулевое место

public:

    FlatMap() {
        values = nullptr;
        keys = nullptr;                                // i |-> i - биекция
        map_size = map_capacity = 0;
    };

    ~FlatMap() {
        if (values && keys) {
            delete [] values;
            delete [] keys;
        }
        map_capacity = 0;
        map_size = 0;
    };

    FlatMap(const FlatMap& b) {
        map_capacity = b.map_capacity;
        values = new Value[b.map_capacity];
        keys = new Key[b.map_capacity];
        map_size = 0;
        for (; map_size < b.map_size; map_size++) {
            values[map_size] = b.values[map_size];
            keys[map_size] = b.keys[map_size];
        }
    };

    FlatMap(FlatMap&& b) noexcept {
        keys = std::exchange(keys, b.keys);
        values = std::exchange(values, b.values);
        map_size = std::exchange(map_size, b.map_size);
        map_capacity = std::exchange(map_capacity, b.map_capacity);

        /*map_capacity = b.map_capacity;
        map_size = b.map_size;
        keys = b.keys;
        values = b.values;
        b.map_size = b.map_capacity = 0;*/
    };

    // Обменивает значения двух флетмап.
    // Подумайте, зачем нужен этот метод, при наличии стандартной функции
    // std::swap.
    void swap(FlatMap& b) {
        struct Value* p_v = b.values;
        Key* p_k = b.keys;
        b.values = values;
        b.keys = keys;
        values = p_v;
        keys = p_k;
        std::swap(map_size, b.map_size);
        std::swap(map_capacity, b.map_capacity);
    };

    FlatMap& operator = (const FlatMap& b) {
        if (this != &b) {
            delete [] keys;
            delete [] values;
            keys = new Key[b.map_capacity];
            values = new Value[b.map_capacity];
            map_capacity = b.map_capacity;
            map_size = 0;
            for (; map_size < b.map_size; map_size++) {
                values[map_size] = b.values[map_size];
                keys[map_size] = b.keys[map_size];
            }
        }
        return *this;
    };

    FlatMap&& operator=(FlatMap&& b) noexcept {
        if (this != &b) {
            values = b.values;
            keys = b.keys;
            map_size = b.map_size;
            map_capacity = b.map_capacity;
            b.values = nullptr;
            b.keys = nullptr;
            b.map_size = b.map_capacity = 0;
        }
        return std::move(*this);
    };


    // Очищает контейнер.
    void clear() {
        for (; map_size > 0; map_size--) {
            values[map_size - 1] = {0, 0};
            keys[map_size - 1] = "";
        }
    };

    void recreate(size_t newCapacity) {
        Key* tmp_keys = new Key[newCapacity];
        auto* tmp_values = new Value[newCapacity];
        for (unsigned long i = 0; i < map_size; i++) {
            tmp_keys[i] = keys[i];
            tmp_values[i] = values[i];
        }
        delete [] keys;
        delete [] values;
        keys = tmp_keys;
        values = tmp_values;
        map_capacity = newCapacity;
    }

    // Удаляет элемент по заданному ключу.
    bool erase(const Key& k) {
        if (map_size == 0) {
            return false;
        }
        long placeToErase = binarySearch(k);
        if (placeToErase >= 0) {
            for (unsigned long i = placeToErase; i < map_size - 1; i++) {
                values[i] = values[i+1];
                keys[i] = keys[i+1];
            }
            //если искомый ключ расположен в конце Flatmap,
            //нам не нужно будет делать сдвиг, лишь занулить последний элемент,
            //мы даже не зайдем в цикл и тут же перейдём сюда.
            keys[map_size - 1] = "";
            values[map_size - 1] = {0, 0};
            map_size--;
            return true;
        }
        return false;
    };

    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, const Value& v) {
        if (map_capacity == 0) {
            values = new Value[1];
            keys = new Key[1];
            map_size++;
            map_capacity++;
            values[0] = v;
            keys[0] = k;
            return true;
        }
        if (map_size == map_capacity) {
            recreate(map_size*2);
        }
        long placeToInsert = binarySearch(k);
        if (placeToInsert >= 0) {                //вставка элемента с таким же ключом не несёт смысла:
            return false;                       //мы к нему не сможем обратиться по ключу
        }
        placeToInsert = abs(placeToInsert) - 1;
        if (placeToInsert <= map_size) {
            for (unsigned long i = map_size; i > placeToInsert; i--) {
                keys[i] = keys[i - 1];
                values[i] = values[i - 1];
            }
            keys[placeToInsert] = k;
            values[placeToInsert] = v;
            map_size++;
            return true;
        }
        return false;
    };

    // Проверка наличия значения по заданному ключу.
    [[nodiscard]] bool contains(const Key& k) const {
        if (map_size == 0) {
            return false;
        }
        long placeToCheck = binarySearch(k);
        if (placeToCheck >= 0) {
            return true;
        }
        return false;
    };

    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнере, следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него.
    Value& operator[](const Key& k) {
        long placeToCheck = binarySearch(k);
        if (placeToCheck >= 0) {
            return values[placeToCheck];
        }
        this->insert(k, Value());
        return values[(-1)*placeToCheck - 1];
    };

    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value& at(const Key& k) {
        long placeToCheck = binarySearch(k);
        if (placeToCheck >= 0) {
            return values[placeToCheck];
        }
        throw std::out_of_range("The value you asked for doesn't exist!");

    };

    [[nodiscard]] const Value& at(const Key& k) const {
        long placeToCheck = binarySearch(k);
        if (placeToCheck >= 0) {
            return values[placeToCheck];
        }
        throw std::out_of_range("The value you asked for doesn't exist!");
    };

    [[nodiscard]] size_t size() const {
        return map_size;
    };

    [[nodiscard]] bool empty() const {
        return (map_size == 0);
    };

    friend bool operator==(const FlatMap& a, const FlatMap& b) {
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
    };

    friend bool operator!=(const FlatMap& a, const FlatMap& b) {
        return !(a == b);
    };

    Key firstKey() {
        return keys[0];
    }

    Key lastKey() {
        return keys[map_size-1];
    }

    void print() {
        for (unsigned i = 0; i < map_size; i++) {
            std::cout << keys[i] << std::endl;
            std::cout << values[i].age << " " << values[i].weight << std::endl;
        }
        std::cout << std::endl;
    }
};

TEST(FlatMapTest, constructors) {
    FlatMap m1;
    ASSERT_TRUE(m1.empty());

    FlatMap m2;
    m2.insert("Stanley", {19, 74});
    FlatMap m3(m2);
    ASSERT_EQ(m3.size(), 1);
    ASSERT_TRUE(m3.contains("Stanley"));

    //FlatMap m4(std::move(m3));
    //ASSERT_EQ(m4.size(), 1);
    //ASSERT_TRUE(m4.contains("Stanley"));
    //ASSERT_TRUE(m3.empty());
}

TEST(FlatMaptest, swap) {
    FlatMap m1;
    FlatMap m2;
    m2.insert("Bob", {12, 29});
    ASSERT_FALSE(m1 == m2);
    ASSERT_TRUE(m1.empty());
    ASSERT_FALSE(m2.empty());
    ASSERT_TRUE(m2.contains("Bob"));
    m1.swap(m2);
    ASSERT_FALSE(m1 == m2);
    ASSERT_TRUE(m2.empty());
    ASSERT_FALSE(m1.empty());
    ASSERT_FALSE(m2.contains("Bob"));
}

TEST(FlatMaptest, equation) {
    FlatMap m1;
    m1.insert("Shrek", {35, 160});
    FlatMap m2;
    m2.insert("Fiona", {27, 100});
    ASSERT_TRUE(m1.contains("Shrek"));
    ASSERT_TRUE(m2.contains("Fiona"));
    ASSERT_FALSE(m1.contains("Fiona"));
    m1 = m2;
    ASSERT_FALSE(m1.contains("Shrek"));
    ASSERT_TRUE(m2.contains("Fiona"));
    ASSERT_TRUE(m1.contains("Fiona"));
}

TEST(FlatMaptest, cleanse) {
    FlatMap m1;
    m1.insert("Alex", {38, 59});
    m1.insert("Sarah", {64, 82});
    m1.insert("Ginny", {20, 46});
    ASSERT_EQ(m1.size(), 3);
    m1.clear();
    ASSERT_TRUE(m1.empty());
}

TEST(FlatMaptest, erasing) {
    FlatMap m;
    m.insert("Braxton", {38, 59});
    m.insert("Jackson", {38, 59});
    m.insert("Milo", {38, 59});
    m.insert("Philip", {23, 78});
    m.insert("Remington", {38, 59});

    FlatMap m2 = m;

    ASSERT_EQ(m.size(), 5);

    ASSERT_TRUE(m.erase("Braxton"));                //удалим первого
    ASSERT_EQ(m.size(), 4);
    ASSERT_FALSE(m.contains("Braxton"));
    ASSERT_EQ(m.firstKey(), "Jackson");
    ASSERT_EQ(m.lastKey(), "Remington");

    ASSERT_TRUE(m.erase("Remington"));              //удалим последнего
    ASSERT_EQ(m.size(), 3);
    ASSERT_FALSE(m.contains("Remington"));
    ASSERT_EQ(m.firstKey(), "Jackson");
    ASSERT_EQ(m.lastKey(), "Philip");

    ASSERT_TRUE(m.erase("Milo"));                   //удалим некрайнего
    ASSERT_EQ(m.size(), 2);
    ASSERT_FALSE(m.contains("Milo"));
    ASSERT_EQ(m.firstKey(), "Jackson");
    ASSERT_EQ(m.lastKey(), "Philip");

    ASSERT_FALSE(m.erase("Marigold"));
    ASSERT_FALSE(m.contains("Marigold"));
    ASSERT_EQ(m.size(), 2);

    ASSERT_TRUE(m2.erase("Remington"));
    ASSERT_TRUE(m2.erase("Braxton"));
    ASSERT_TRUE(m2.erase("Milo"));

    ASSERT_TRUE(m == m2);                               //не зависит от порядка удаления
}

TEST(FlatMaptest, inserting) {
    FlatMap m;
    ASSERT_TRUE(m.insert("Ember", {27, 73}));
    ASSERT_EQ(m.firstKey(), "Ember");
    ASSERT_EQ(m.lastKey(), "Ember");
    ASSERT_EQ(m.size(), 1);

    ASSERT_TRUE(m.insert("Dolores", {82, 60}));
    ASSERT_EQ(m.firstKey(), "Dolores");
    ASSERT_EQ(m.lastKey(), "Ember");
    ASSERT_EQ(m.size(), 2);

    ASSERT_TRUE(m.insert("Aredhel Ar-Feiniel", {538, 40}));
    ASSERT_EQ(m.firstKey(), "Aredhel Ar-Feiniel");
    ASSERT_EQ(m.lastKey(), "Ember");
    ASSERT_EQ(m.size(), 3);

    ASSERT_TRUE(m.insert("Temperance", {40, 71}));
    ASSERT_EQ(m.firstKey(), "Aredhel Ar-Feiniel");
    ASSERT_EQ(m.lastKey(), "Temperance");
    ASSERT_EQ(m.size(), 4);

    ASSERT_FALSE(m.insert("Ember", {29, 80}));
    ASSERT_EQ(m.size(), 4);

    FlatMap m2;
    ASSERT_TRUE(m2.insert("Aredhel Ar-Feiniel", {538, 40}));
    ASSERT_TRUE(m2.insert("Temperance", {40, 71}));
    ASSERT_TRUE(m2.insert("Ember", {27, 73}));
    ASSERT_TRUE(m2.insert("Dolores", {82, 60}));

    ASSERT_TRUE(m == m2);
}

TEST(FlatMaptests, access) {
    FlatMap m1;

    m1.insert("Willow", {52, 80});
    m1.insert("Harrison", {34, 92});
    m1.insert("Edward", {3, 14});
    m1.insert("Jemma", {14, 38});
    m1.insert("Archie", {71, 102});

    FlatMap m2 = m1;
    const FlatMap m3 = m1;

    ASSERT_EQ(m1["Willow"].age, 52);
    ASSERT_EQ(m1["Willow"].weight, 80);
    ASSERT_EQ(m1["Archie"].age, 71);
    ASSERT_EQ(m1["Archie"].weight, 102);

    ASSERT_TRUE(m1.erase("Jemma"));
    ASSERT_FALSE(m1.contains("Jemma"));
    ASSERT_EQ(m1["Jemma"].age, Value().age);
    ASSERT_EQ(m1["Jemma"].weight, Value().weight);
    ASSERT_TRUE(m1.contains("Jemma"));
    ASSERT_FALSE(m1.insert("Jemma", {14, 38}));

    ASSERT_EQ(m2.at("Willow").age, 52);
    ASSERT_EQ(m2.at("Willow").weight, 80);
    ASSERT_EQ(m2.at("Archie").age, 71);
    ASSERT_EQ(m2.at("Archie").weight, 102);

    m2.erase("Jemma");
    ASSERT_THROW(m2.at("Jemma"), std::out_of_range);

    ASSERT_EQ(m3.at("Willow").age, 52);
    ASSERT_EQ(m3.at("Willow").weight, 80);
    ASSERT_EQ(m3.at("Archie").age, 71);
    ASSERT_EQ(m3.at("Archie").weight, 102);

    ASSERT_THROW(m3.at("Andrew"), std::out_of_range);
}

TEST(FlatMaptest, comparison) {
    FlatMap m1;

    m1.insert("Willow", {52, 80});
    m1.insert("Harrison", {34, 92});
    m1.insert("Edward", {3, 14});
    m1.insert("Jemma", {14, 38});
    m1.insert("Archie", {71, 102});

    ASSERT_TRUE(m1 == m1);
    ASSERT_FALSE(m1 != m1);

    FlatMap m2 = m1;
    m2.erase("Archie");

    ASSERT_TRUE(m1 != m2);
    ASSERT_FALSE(m1 == m2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}