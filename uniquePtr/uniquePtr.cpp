/*
* Unique Pointer implementation
* https://www.learncpp.com/cpp-tutorial/move-constructors-and-move-assignment/
*/

#include <iostream>

using namespace std;

class Resource {
public:
    Resource() {cout << "resource acquired" << endl;}
    ~Resource() {cout << "resource destroyed" << endl;}
};

template <typename T>
class UniquePtr {
private:
    T* ptr_;
public:
    UniquePtr(T* ptr) : ptr_(ptr) {
        cout << "ctor" << endl;
    }

    UniquePtr(UniquePtr& uptr) = delete;

    UniquePtr(UniquePtr&& uptr) {
        cout << "move ctor" << endl;
        ptr_ = uptr.ptr_;
        uptr.ptr_ = nullptr;
    }

    ~UniquePtr() {
        cout << "dtor" << endl;
        if(ptr_) {
            delete ptr_;
        }
    }

    UniquePtr& operator= (UniquePtr& uptr) = delete;

    UniquePtr& operator= (UniquePtr&& uptr) {
        cout << "move assignment" << endl;
        if(&uptr == this) {return *this;}

        // release existing ownership
        if(ptr_) {
            delete ptr_;
        }

        // transfer ownership to current object
        ptr_ = uptr.ptr_;

        // release ownership of old object
        uptr.ptr_ = nullptr;

        return *this;
    }

    T& operator*() {
        return *ptr_;
    }

    T* operator->() {
        return *ptr_;
    }

};

UniquePtr<Resource> generateResource() {
    UniquePtr<Resource> up(new Resource());
    cout << "generated resource" << endl;
    return up;
}

int main() {
    cout << "Smart Pointer: UniquePtr" << endl;
    // Resource* res1 = new Resource();
    // UniquePtr<Resource> up1 (res1);
    UniquePtr<Resource> up1 ( generateResource() );
    // UniquePtr<Resource> up2 ( up1 );
    UniquePtr<Resource> up3 (move(up1));
    cout << "Test move assignment" << endl;
    UniquePtr<Resource> up4 ( generateResource() );
    up4 = move(up3);
    return 0;
}