/**
 * SharedPtr
 *  
 */

#include <iostream>

using namespace std;

class CtrlBlk {
private:
    int refCount_;
public:
    CtrlBlk() : refCount_(0) {
        cout << "CtrlBlk Ctor" << endl;
    }
    ~CtrlBlk() {
        cout << "CtrlBlk Dtor" << endl;
    }
    void incRefCount() {
        refCount_++;
        cout << "refCount: " << refCount_ << endl;
    }
    void decRefCount() {
        refCount_--;
        cout << "refCount: " << refCount_ << endl;
    }
    int getRefCount() {
        return refCount_;
    }
};

template <typename T>
class SharedPtr {
private:
    T* ptr_;
    CtrlBlk* ctrl_blk;

public:
    SharedPtr(T* ptr) : ptr_(ptr) {
        cout << "SharedPtr Ctor" << endl;
        ctrl_blk = new CtrlBlk();
        ctrl_blk->incRefCount();
    }

    SharedPtr(SharedPtr& s_ptr) {
        cout << "SharedPtr Copy Ctor" << endl;
        ptr_ = s_ptr.ptr_;
        ctrl_blk = s_ptr.ctrl_blk;
        ctrl_blk->incRefCount();
    }

    SharedPtr(SharedPtr&& s_ptr) {
        cout << "SharedPtr Move Ctor" << endl;
        ptr_ = s_ptr.ptr_;
        ctrl_blk = s_ptr.ctrl_blk;
        s_ptr.ptr_ = nullptr;
        s_ptr.ctrl_blk = nullptr;
    };

    ~SharedPtr() {
        cout << "SharedPtr Dtor" << endl;
        if(!ctrl_blk) {return;}
        ctrl_blk->decRefCount();
        if(ctrl_blk->getRefCount() > 0) {return;}
        delete ctrl_blk;
        if(ptr_) {
            delete ptr_;
        }
    }

    SharedPtr& operator=(SharedPtr& s_ptr) {
        if(this == &s_ptr) {return *this;}
        cout << "SharedPtr Copy Assignment" << endl;
        ctrl_blk->decRefCount();
        if(ctrl_blk->getRefCount() == 0) {
            delete ptr_;
            delete ctrl_blk;
        }
        ptr_ = s_ptr.ptr_;
        ctrl_blk = s_ptr.ctrl_blk;
        ctrl_blk->incRefCount();
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& s_ptr) {
        if(this == &s_ptr) {return *this;}
        cout << "SharedPtr Move Assignment" << endl;
        if(ctrl_blk) {
            ctrl_blk->decRefCount();
            if(ctrl_blk->getRefCount() == 0) {
                delete ptr_;
                delete ctrl_blk;
            }
        }
        ptr_ = s_ptr.ptr_;
        ctrl_blk = s_ptr.ctrl_blk;
        s_ptr.ptr_ = nullptr;
        s_ptr.ctrl_blk = nullptr;
        return *this;
    }

    T* operator->() {
        return ptr_;
    }

    T& operator*() {
        return *ptr_;
    }
};

class Resource {
public:
    int x = 42;
    Resource() {cout << "resource acquired x: " << x << endl;}
    Resource(int x_) : x(x_) {cout << "resource acquired x: " << x << endl;}
    ~Resource() {cout << "resource destroyed x: " << x << endl;}
};

int main() {
    cout << "SharedPtr!" << endl;
    SharedPtr<Resource> ptr1 (new Resource(42));
    cout << "ptr1->x: " << ptr1->x << endl;
    cout << "*ptr1.x " << (*ptr1).x << endl;
    {
        SharedPtr<Resource> ptr2 = ptr1;
        cout << "ptr2->x: " << ptr2->x << endl;
    }
    cout << "creating ptr3" << endl;
    SharedPtr<Resource> ptr3 (new Resource(25));
    ptr3 = ptr1;
    cout << "creating ptr4" << endl;
    SharedPtr<Resource> ptr4 (std::move(ptr3));
    cout << "move ownership from ptr4 to ptr3" << endl;
    ptr3 = move(ptr4);
    return 0;
}