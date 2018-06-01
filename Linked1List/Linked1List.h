#include <iostream>
#include <string>
#include <functional>

using namespace std;

template <class T>
class List {
public:
    virtual void    clean() = 0;
    virtual void    clone(void*) = 0;
    virtual bool    isEmpty() = 0;
    virtual size_t  getSize() = 0;
    virtual T&      at(int i) = 0;
    virtual T&      operator[](int i) = 0;

    virtual bool    find(T& a, int& idx) = 0;
    virtual T*      find(T& a) = 0;
    virtual T*      find(T& a, std::function<bool (T&, T&)> eqCmp) = 0;
    virtual int     insert(int i, T& a) = 0;
    virtual int     insert(int i, T&& a) = 0;
    virtual int     remove(int i) = 0;
    virtual int     remove(T& a, std::function<bool (T&, T&)> eqCmp) = 0;

    virtual int     push_back(T& a) = 0;
    virtual int     push_back(T&& a) = 0;
    virtual int     insertHead(T& a) = 0;
    virtual int     insertHead(T&& a) = 0;
    virtual int     removeHead() = 0;
    virtual int     removeLast() = 0;

    virtual void    traverse(std::function<void (T&)> op) = 0;
    virtual void    traverse(std::function<void (T&, void*)> op, void* pParam) = 0;

    //virtual void    reverse() = 0;
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;

    L1Item(T &a) : data(a), pNext(NULL) {}
    L1Item(T &a, void* next) : data(a), pNext(next) {}
    L1Item(T &&a) : data(std::move(a)), pNext(NULL) {}
    L1Item(T &&a, void* next) : data(std::move(a)), pNext(next) {}
};

template <class T>
class L1List : public List<T> {
    L1Item<T>   *_pHead;
    size_t      _size;
public:
    L1List() : _pHead(NULL), _size(0) {}
    ~L1List();

    void    clean();
    void    clone(void*);
    bool    isEmpty() { return _pHead == NULL; }
    size_t  getSize() { return _size; }

    T&      at(int i);
    T&      operator[](int i);

    bool    find(T& a, int& idx);
    T*      find(T& a);
    T*      find(T& a, std::function<bool (T&, T&)> eqCmp);//bool (*eqCmp)(T&, T&));
    int     insert(int i, T& a);
    int     insert(int i, T&& a);
    int     remove(int i);
    int     remove(T& a, std::function<bool (T&, T&)> eqCmp);

    int     push_back(T& a);
    int     push_back(T&& a);
    int     insertHead(T& a);
    int     insertHead(T&& a);
    int     removeHead();
    int     removeLast();

    void    reverse(){
        L1Item<T> * current = this->_pHead;
        L1Item<T> * next = current->pNext;
        while(next){
            L1Item<T> * pre = current;
            current = next;
            next = current->pNext;
            current->pNext = pre;
        }
        this->_pHead->pNext = NULL;
        this->_pHead = current;
    }

    void    traverse(std::function<void (T&)> op) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data);
            p = p->pNext;
        }
    }
    //void    traverse(void (*op)(T&, void*), void* pParam) {
    void    traverse(std::function<void (T&, void*)> op, void* pParam) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data, pParam);
            p = p->pNext;
        }
    }
};

template <class T>
void L1List<T>::clean(){
    L1Item<T> * current = this->_pHead;
    while(this->_pHead){
        this->_pHead = this->_pHead->pNext;
        delete current;
        current = this->_pHead;
        this->_size--;
    }
    
}

template <class T>
void L1List<T>::clone(void * pRet){
    L1List<T> * pClone = (L1List<T>*)pRet;
    L1Item<T> * current = this->_pHead;
    while(current){
        pClone->push_back(current->data);
        current = current->pNext;
    }

}

template <class T>
bool L1List<T>::find(T& a,int &idx){
    L1Item<T> * current = this->_pHead;
    while(current){
        if(a == current->data){
            return true;
        }
        idx++;
        current = current->pNext;
    }
    return false;
}



template <class T>
T* L1List<T>::find(T&a){
    L1Item<T> * current = this->_pHead;
    while(current){
        if(a == current->data){
            return &current->data;
        }
        current = current->pNext;
    }
}

template <class T>
T* L1List<T>::find(T& a, std::function<bool (T&, T&)> eqCmp){
    L1Item<T> * current = this->_pHead;
    while(current){
        if(eqCmp(a,current->data)){
            return &current->data;
        }
        current = current->pNext;
    }
}

template <class T>
int L1List<T>::insert(int i,T&a){
    L1Item<T> * current = this->_pHead;
    int idx = 0;
    while(current){
        if(i == idx){
            break;
        }
        current = current->pNext;
        idx++;
    }
    L1Item<T> * pNew = new L1Item<T>(a);
    pNew->pNext = current->pNext;
    current->pNext = pNew;
    this->_size++;
    return idx;
}

template <class T>
int L1List<T>::insert(int i,T&&a){
    L1Item<T> * current = this->_pHead;
    int idx = 0;
    while(current){
        if(i == idx){
            break;
        }
        current = current->pNext;
        idx++;
    }
    L1Item<T> * pNew = new L1Item<T>(std::move(a));
    pNew->pNext = current->pNext;
    current->pNext = pNew;
    this->_size++;
    return idx;
}

template <class T>
int L1List<T>::remove(int i){
    L1Item<T> * current = this->_pHead;
    L1Item<T> * preCurrent;
    int idx = 0;
    while(current){
        if(i == idx){
            break;
        }
        current = current->pNext;
        preCurrent = current;
        idx++;
    }
    if(current){
        preCurrent->pNext = current->pNext;
        current = NULL;
    }
    return i;
}

template <class T>
int L1List<T>::remove(T& a, std::function<bool (T&, T&)> eqCmp){
    L1Item<T> * current = this->_pHead;
    L1Item<T> * preCurrent;
    while(current){
        if(eqCmp(a, current->data)){
            break;
        }
        current = current->pNext;
        preCurrent = current;
    }
    if(current){
        preCurrent->pNext = current->pNext;
        current = NULL;
    }
    return 0;
}

template <class T>
T& L1List<T>::at(int i){
    if(this->_pHead != NULL){
        L1Item<T> * pRet = this->_pHead;
        int idx = 0;
        while(pRet){
            if(i != idx){
                pRet = pRet->pNext;
                idx++;
            }else  return (pRet->data);
        }
    }
    T ret;
    return ret;
}


template <class T>
T& L1List<T>::operator[](int i){
    return at(i);
}


/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
    if (_pHead == NULL) {
        _pHead = new L1Item<T>(a);
    }
    else {
        L1Item<T>   *p = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext = new L1Item<T>(a);
    }

    _size++;
    return 0;
}

template <class T>
int L1List<T>::push_back(T &&a) {
    if (_pHead == NULL) {
        _pHead = new L1Item<T>(std::move(a));
    }
    else {
        L1Item<T>   *p = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext = new L1Item<T>(std::move(a));
    }

    _size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
    L1Item<T>   *p = new L1Item<T>(a);
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

template <class T>
int L1List<T>::insertHead(T&& a) {
    L1Item<T>   *p = new L1Item<T>(std::move(a));
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
    if(_pHead) {
        L1Item<T>* p = _pHead;
        _pHead = p->pNext;
        delete p;
        _size--;
        return 0;
    }
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
    if(_pHead) {
        if(_pHead->pNext) {
            L1Item<T>* prev = _pHead;
            L1Item<T>* pcur = prev->pNext;
            while(pcur->pNext) {
                prev = pcur;
                pcur = pcur->pNext;
            }
            delete pcur;
            prev->pNext = NULL;
        }
        else {
            delete _pHead;
            _pHead = NULL;
        }
        _size--;
        return 0;
    }
    return -1;
}
