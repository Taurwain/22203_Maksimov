#include <iostream>
#include <string.h>

using namespace std;

class String {
    
private:

    size_t capacity;
    size_t size;
    char *memory;

public:
    
    String() {
        memory = nullptr;
        capacity = 0;
        size = 0;
    }
    
    String(size_t initial_capacity) {
        capacity = initial_capacity;
        memory = (char *)malloc(capacity);
        size = 0;
    }
    
    String(const char *str) {
        capacity = strlen(str);
        size = capacity;
        memory = (char *)malloc(capacity);
        strcpy(memory, str);
    }
    
    String(const String& other_string) {
        capacity = other_string.capacity;
        size_t size = other_string.size;
        memory = (char *)malloc(capacity);
        strcpy(memory, other_string.memory);
    }
    
    String& operator = (const String& new_string) {
        while (new_string.size > capacity) {
            capacity *= 1.75;
            memory = (char*)realloc(memory, capacity);
        }
        size = new_string.size;
        strcpy(memory, new_string.memory);
        return *this;
    }
    
    char& operator [] (int index) {
        return memory[index];
    }
    
    void append(char symbol) {
        if (size + 1 > capacity) {
            capacity += 1;
            memory = (char*)realloc(memory, capacity);
        }
        memory[size] = symbol;
        size++;
    }
    
    void insert(char symbol, size_t index) {
        if (size + 1 > capacity) {
            capacity += 1;
            memory = (char*)realloc(memory, capacity);
        }
        memcpy(memory + index + 1, memory + index, size - index);
        memory[index] = symbol;
        size++;
    }
    void print() {
        cout << memory << endl;
    }
    
    ~String() {
        free(memory);
        capacity = 0;
        size_t size = 0;
    }
};

int main() {
    String str("Hello");
    str.print();
    char comma = ',';
    str.append(comma);
    str.print();
    str = "world!";
    str.print();
    cout << str[2] << endl;
    str.insert('5',6);
    str.print();
    return 0;
}