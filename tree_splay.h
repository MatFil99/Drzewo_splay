#pragma once

#include <cstdlib>
#include "node_tree.h"
#include <random>

template <typename KeyType, typename ValueType>
class TreeSplay{
    private:
    NodeTree<KeyType, ValueType>* root;
    int size;

    public:
    TreeSplay():    root(nullptr), size(0){}
    ~TreeSplay(){
        if(root!=nullptr){
            deallocating(root);
            size = 0;
        }
    }

    void splay(NodeTree<KeyType, ValueType>* x_node){
        if(x_node == root ) {root = x_node; return ;}
        if(x_node->getParent() == root){
            if(x_node->isLeftChild()){
                rightRotate(x_node);
                root = x_node;
                return ;
            }else{
                root = x_node;
                return ;
            }
        }else
        if(x_node->isLeftChild() && x_node->getParent()->isLeftChild()){
            rightRotate(x_node->getParent());
            rightRotate(x_node);
        }else
        if(x_node->isRightChild() && x_node->getParent()->isRightChild()){
            leftRotate(x_node->getParent());
            leftRotate(x_node);
        }else
        if(x_node->isLeftChild()){
            rightRotate(x_node);
            leftRotate(x_node);
        }else
        {
            leftRotate(x_node);
            rightRotate(x_node);
        }
        if(x_node->getParent() == nullptr) root = x_node;
        splay(x_node);
    }

    void eraseEl(KeyType key){
        static short flag;
        NodeTree<KeyType, ValueType>* eraseEl = doSearching(root, key_search);
        ++flag;
        if(flag%2){
            
        }
    }

    NodeTree<KeyType, ValueType>* search(KeyType key_search){
        NodeTree<KeyType, ValueType>* findEl = doSearching(root, key_search);
        splay(findEl);
        return findEl;
    }

    NodeTree<KeyType, ValueType>* doSearching(NodeTree<KeyType, ValueType>* el, KeyType key){
        if(el == nullptr) return nullptr;
        if(el->getKey() == key) return el;
        else{
            if(el->getKey()>key) doSearching(el->getLeftChild(), key);
            else doSearching(el->getRightChild(), key);
        }
    }

    void rightRotate(NodeTree<KeyType, ValueType>* el){
        NodeTree<KeyType, ValueType>* x_Parent = el->getParent();
        x_Parent->attachLeft(el->getRightChild());
        if(x_Parent->isLeftChild()){
            x_Parent->getParent()->attachLeft(el);
        }else if(x_Parent->isRightChild())
        {
            x_Parent->getParent()->attachRight(el);
        }else{
            el->attachParent(nullptr);
        }
        el->attachRight(x_Parent);
    }

    void leftRotate(NodeTree<KeyType, ValueType>* el){
        NodeTree<KeyType, ValueType>* x_Parent = el->getParent();
        x_Parent->attachRight(el->getLeftChild());
        if(x_Parent->isLeftChild()){
            x_Parent->getParent()->attachLeft(el);
        }else if(x_Parent->isRightChild())
        {
            x_Parent->getParent()->attachRight(el);
        }else{
            el->attachParent(nullptr);
        }
        el->attachLeft(x_Parent);
    }

    void insert(KeyType k, ValueType v){
        NodeTree<KeyType, ValueType>* new_el = createNode(k, v);
        if( root == nullptr ){
            if(root = new_el){
                ++size;
            }else std::cout<<"Operacja dodawnia wezla do drzewa nie powiodla sie!\n";
        }else{
            doInsertion(root, new_el);
            splay(new_el);
        }

    }

    void writeOut(){
        doWriting(root);
    }


    void doWriting(NodeTree<KeyType, ValueType>* el){
        if(el->haveLeftChild()){
            doWriting(el->getLeftChild());
        }
        if(el->haveRightChild()){
            doWriting(el->getRightChild());
        }
        el->writeOut();
        std::cout<<"\n";
    }

//private:
    void doInsertion(NodeTree<KeyType, ValueType>* node_a, NodeTree<KeyType, ValueType>* new_el){
        //if(node_a == nullptr) return 
        if(node_a->getKey()>new_el->getKey()){
            if(node_a->haveLeftChild()){
                doInsertion(node_a->getLeftChild(), new_el);
            }else
            node_a->attachLeft(new_el);
        }else{
            if(node_a->haveRightChild()){
                doInsertion(node_a->getRightChild(), new_el);
            }else
            node_a->attachRight(new_el);
        }
    }

//private:
    NodeTree<KeyType, ValueType>* createNode(KeyType key, ValueType value){
        return new NodeTree<KeyType, ValueType>(key, value);
    }

//private:
    void deallocating(NodeTree<KeyType, ValueType>* node_del){
        if(node_del->getLeftChild() != nullptr ){
            deallocating(node_del->getLeftChild());
        }
        if(node_del->getRightChild() != nullptr ){
            deallocating(node_del->getRightChild());
        }
        delete node_del;
        node_del = nullptr;
    }
    
};