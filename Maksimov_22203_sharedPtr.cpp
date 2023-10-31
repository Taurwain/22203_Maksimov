#include <iostream>
#include <cstdlib>
#include <vector>

template <class T> class shared_ptr {
public:
    shared_ptr(T* p = nullptr) : ptr_(p), counter(new int(1)) { };

    ~shared_ptr() {
        if (counter) {
            if ((*counter) == 1) {
                delete counter;
                delete ptr_;
            } else ptr_ = nullptr;
        }
    };

    shared_ptr(const shared_ptr& other) : ptr_(other.ptr_), counter(other.counter) {
        if (counter && ptr_) {
            (*counter)++;
        }
    };

    shared_ptr(shared_ptr&& other) noexcept : ptr_(std::move(other.ptr_)),
            counter(std::move(other.counter)) {
        other.ptr_ = nullptr;
    };

    shared_ptr& operator = (const shared_ptr& other) {
        if (this != &other) {
            (*counter)--;
            if (!(*counter)) {
                delete ptr_;
                delete counter;
            }

            ptr_ = other.ptr_;
            counter = other.counter;
            (*counter)++;
        }
        return *this;
    };

    shared_ptr& operator = (shared_ptr&& other) noexcept {
        if (this != &other) {
            (*counter)--;
            if (!(*counter)) {
                delete ptr_;
                delete counter;
            }

            ptr_ = std::move(other.ptr_);
            counter = std::move(other.counter);
            other.ptr_ = nullptr;
        }
        return *this;
    };

    T* get() {
        return ptr_;
    };

    T* reset(T * newnew = nullptr) {
        T * tmp = ptr_;
        this = std::move(newnew);
        return tmp;
    };

    T* release() {
        T * tmp = ptr_;
        if (*(counter) == 1) {
            delete ptr_;
            delete counter;
        } else (*counter)--;
        return tmp;
    };

    T* operator -> () {
        return ptr_;
    };

    T & operator * () {
        return * ptr_;
    };

private:
    T * ptr_ = nullptr;
    int * counter = nullptr;

};

struct A { };

int main() {
    shared_ptr<A> p1(new A());
    shared_ptr<A> p2 = p1;
    shared_ptr<A> p3 = std::move(p1);
    shared_ptr<A> p4 = shared_ptr<A>();

    shared_ptr<A> p5(new A());
    shared_ptr<A> p6 = p5;
    shared_ptr<A> p7 = p5;

    shared_ptr<A> p8 = p7.get();
    //shared_ptr<A> p9 = p8.release();
    shared_ptr<A> p10;

    return 0;
}
