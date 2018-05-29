#include <iostream>
#ifndef AVLTree
template <class T>
struct AVLNode {
    T           _data;
    AVLNode<T>   *_pLeft, *_pRight;
#ifdef AVL_USE_HEIGHT
    int         _height;
    AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _height(1) {}
#else
    int         _bFactor;
    AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _bFactor(0) {}
    //bFactor -1 = lefthigh, 0 = balance, 1 = righthight
#endif
};

template <class T>
class AVLTree {
    AVLNode<T> *_pRoot;
public:
    AVLTree() : _pRoot(NULL) {}
    ~AVLTree() { destroy(_pRoot); }

    bool find(T& key, T* &ret) { return find(_pRoot, key, ret); }
    bool insert(T& key) { return insert(_pRoot, key); }
    bool remove(T& key) { return remove(_pRoot, key); }
    void traverseNLR(void (*op)(T&)) { traverseNLR(_pRoot, op); }
    void traverseLNR(void (*op)(T&)) { traverseLNR(_pRoot, op); }
    void traverseLRN(void (*op)(T&)) { traverseLRN(_pRoot, op); }
protected:
    void destroy(AVLNode<T>* &pR);
    bool find(AVLNode<T> *pR, T& key, T* &ret);
    bool insert(AVLNode<T>* &pR, T& a);
    bool remove(AVLNode<T>* &pR, T& a);
    void traverseNLR(AVLNode<T> *pR, void (*op)(T&));
    void traverseLNR(AVLNode<T> *pR, void (*op)(T&));
    void traverseLRN(AVLNode<T> *pR, void (*op)(T&));

    void rotLeft(AVLNode<T>* &pR);
    void rotRight(AVLNode<T>* &pR);
    void rotLR(AVLNode<T>* &pR);
    void rotRL(AVLNode<T>* &pR);

    bool balanceLeft(AVLNode<T>* &pR);
    bool balanceRight(AVLNode<T>* &pR);

    //additional
    bool _replacingRootRightMost(AVLNode<T>* &pR, AVLNode<T>* &pRet);
};

template <class T>
void AVLTree<T>::rotLeft(AVLNode<T>* &pR){
    AVLNode<T> * pTemp = pR;
    pR = pR->_pRight;
    pTemp->_pRight = pR->_pLeft;
    pR->_pLeft = pTemp;
}

template <class T>
void AVLTree<T>::rotRight(AVLNode<T>* &pR){
    AVLNode<T> * pTemp = pR;
    pR = pR->_pLeft;
    pTemp->_pLeft = pR->_pRight;
    pR->_pRight = pTemp;
}

template <class T>
void AVLTree<T>::rotLR(AVLNode<T>* &pR){
    rotLeft(pR->_pLeft);
    rotRight(pR);
}

template <class T>
void AVLTree<T>::rotRL(AVLNode<T>* &pR){
    rotRight(pR->_pRight);
    rotLeft(pR);
}
template <class T>
bool AVLTree<T>::balanceLeft(AVLNode<T>* &pR){
    AVLNode<T> * leftTree = pR->_pLeft;
    bool taller;
    if(leftTree->_bFactor == -1){
        rotRight(pR);
        pR->_bFactor = 0;
        pR->_pRight->_bFactor = 0;
        taller = false;
    }else if(leftTree->_bFactor == 1){
        AVLNode<T> * rightTree = leftTree->_pRight;
        //?if(rightTree == NULL) return;
        if(rightTree->_bFactor == -1){
            pR->_bFactor = 1;
            leftTree->_bFactor = 0;
        }else if(rightTree->_bFactor == 0){
            pR->_bFactor = 0;
            leftTree->_bFactor = 0;
        }else{
            pR->_bFactor = 0;
            leftTree->_bFactor = -1;
        }
        rightTree->_bFactor = 0;
        /*rotateLeft(leftTree);
        pR->pLeft = leftTree;
        rotateRight(pR);*/
        rotLR(pR);
        taller = false;
    }else{
        int bFactor = 0;
        if(pR->_pLeft->_bFactor == -1)bFactor = 0;
        else bFactor = 1;
        rotRight(pR);
        pR->_bFactor = bFactor;
        taller = true; // for remove, so reuse balance of insert which is remove taller = !insert taller
    }
    return taller;
}

template <class T>
bool AVLTree<T>::balanceRight(AVLNode<T>* &pR){
    AVLNode<T> * rightTree = pR->_pRight;
    bool taller;
    if(rightTree->_bFactor == 1){
        rotLeft(pR);
        pR->_bFactor = 0;
        pR->_pLeft->_bFactor = 0;
        //Tree->balanceF = balanced;
        taller = false;
    }else if(rightTree->_bFactor == -1){
        AVLNode<T> * leftTree = rightTree->_pLeft;
        //?if(leftTree == NULL) return;
        if(leftTree->_bFactor == 1){
            pR->_bFactor = -1;
            rightTree->_bFactor = 0;
        }else if(leftTree->_bFactor == 0){
            rightTree->_bFactor = 0;
            pR->_bFactor = 0;
        }else{
            pR->_bFactor = 0;
            rightTree->_bFactor = 1;
        }
        leftTree->_bFactor = 0;
        /*rotateRight(rightTree);
        pR->pRight = rightTree;
        rotateLeft(pR);*/
        rotRL(pR);
        taller = false;
    }else{
        int bFactor = 0;
        if(pR->_pRight->_bFactor == 1)bFactor = 0;
        else bFactor = -1;
        rotLeft(pR);
        pR->_bFactor = bFactor;
        taller = true;
    }
    return taller;
}

template <class T>
void AVLTree<T>::destroy(AVLNode<T>* &pR){
    if(pR != NULL){
        destroy(pR->_pLeft);
        destroy(pR->_pRight);
        delete pR;
    }
    pR = NULL;
}

template <class T>
bool AVLTree<T>::find(AVLNode<T> *pR, T& key, T* &ret){
    if(pR == NULL){
        return false;
    }
    AVLNode<T> * ptr = pR;
    while(ptr){
        if(key < ptr->_data){
            ptr = ptr->_pLeft;
        }else if(key > ptr->_data){
            ptr = ptr->_pRight;
        }else{
            ret = ptr->_data;
            return true;
        }
    }
    return false;
}

template <class T>
bool AVLTree<T>::insert(AVLNode<T>* &pR, T& key){
    if(pR == NULL){
        pR = new AVLNode<T>(key);
        return true;
    }
    bool taller;
    if(key < pR->_data){
        taller = insert(pR->_pLeft, key);
        if(taller){
            if(pR->_bFactor == -1){
                taller = balanceLeft(pR);
            }else if(pR->_bFactor == 0){
                pR->_bFactor = -1;
            }else{
                pR->_bFactor = 0;
                taller = false;
            }

        }
    }else{
        taller = insert(pR->_pRight, key);
        if(taller){
            if(pR->_bFactor == -1){
                pR->_bFactor = 0;
                taller = false;
            }else if(pR->_bFactor == 0){
                pR->_bFactor = 1;
            }else{
                taller = balanceRight(pR);
            }
        }
    }
    return taller;
}

template <class T>
bool AVLTree<T>::_replacingRootRightMost(AVLNode<T> *& pR, AVLNode<T>* &pRet){
    if(pR->_pRight == NULL){
            pRet = pR;
            pR = pR->_pLeft;
            return true;
    }
    bool taller = _replacingRootRightMost(pR->_pRight, pRet);
    
    if(taller){
        if(pR->_bFactor== 0) {
            taller = false;
            pR->_bFactor = -1;
        }else if(pR->_bFactor == 1){
            pR->_bFactor = 0;
        }else pR->_bFactor = 0;
    }    
    return taller;
}

template <class T>
bool AVLTree<T>::remove(AVLNode<T>* &pR, T& key){
    if(pR == NULL){
        return false;
    }
    bool taller;
    if(key < pR->_data){
        taller = remove(pR->_pLeft, key);
        if(taller){
            if(pR->_bFactor == 1){
                taller = !balanceRight(pR);
            }else if(pR->_bFactor == 0){
                pR->_bFactor = 1;
                taller = false;
            }else pR->_bFactor = 0;
        }
    }else if(key > pR->_data){
        taller = remove(pR->_pRight, key);
        if(taller){
            if(pR->_bFactor == -1){
                taller = !balanceLeft(pR);
            }else if(pR->_bFactor == 0){
                pR->_bFactor = -1;
                taller = false;
            }else pR->_bFactor = 0;
        }
    }else{
        if(pR->_pLeft == NULL && pR->_pRight == NULL){
            pR = NULL;
            return true;
        }
        //
        AVLNode<T> * pRep = pR->_pRight;//preplacing
        AVLNode<T> * leftTree = pR->_pLeft;
        taller = true;
        if(leftTree){
            pRep = pR->_pLeft;
            if(leftTree->_pRight){
                taller = _replacingRootRightMost(leftTree, pRep);
                pRep->_pLeft = pR->_pLeft;
                pRep->_pRight = pR->_pRight;
                pRep->_bFactor = pR->_bFactor;
            }else{
                pRep->_pRight = pR->_pRight;                
                pRep->_bFactor = 1;
                if(pR->_bFactor == -1){
                    pRep->_bFactor = 0;
                }else if(pR->_bFactor == 0){
                    taller = false;
                }else{
                   taller = !balanceRight(pRep);                    
                }
            }
        }
        pR = pRep;
    }
    return taller;
}

template <class T>
void AVLTree<T>::traverseNLR(AVLNode<T> *pR, void (*op)(T&)){
    if(pR != NULL){
        op(pR->_data);
        traverseNLR(pR->_pLeft, op);
        traverseNLR(pR->_pRight, op);
    }
}

template <class T>
void AVLTree<T>::traverseLNR(AVLNode<T> *pR, void (*op)(T&)){
    if(pR != NULL){
        traverseLNR(pR->_pLeft, op);
        op(pR->_data);
        traverseLNR(pR->_pRight, op);
    }
}

template <class T>
void AVLTree<T>::traverseLRN(AVLNode<T> *pR, void (*op)(T&)){
    if(pR != NULL){
        traverseLRN(pR->_pLeft, op);
        traverseLRN(pR->_pRight, op);
        op(pR->_data);
    }
}
#endif //A02_DSALIB_H
