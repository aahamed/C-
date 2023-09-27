/**
 * Move semantics 
 */
#include <iostream>

using namespace std;

class MyObj {
public:
    int* ptr_; 
    MyObj(int* ptr) : ptr_(ptr) {
        cout << "ctor" << endl;
    }

    MyObj(MyObj&& obj) {
        cout << "move ctor" << endl;
        ptr_ = obj.ptr_;
        obj.ptr_ = nullptr;
    }

    ~MyObj() {
        cout << "dtor" << endl;
        if(ptr_) {
            delete ptr_;
        }
    }
    int* get() {return ptr_;}
};

int main() {
    cout << "Move Semantics" << endl;
    cout << "sizeof int = " << sizeof(int) << endl;
    auto arr = new int[5];
    cout << "sizeof arr = " << sizeof(arr) << endl;
    MyObj obj1 (arr);
    cout << "obj1 size = " << sizeof(obj1) << endl;
    cout << "obj1.ptr size = " << sizeof(obj1.get()) << endl;
    cout << "obj1.ptr = " << obj1.get() << endl;
    MyObj obj2( obj1 );
    cout << "obj1.ptr = " << obj1.get() << endl;
    cout << "obj2.ptr = " << obj2.get() << endl;
    return 0;
}