#ifndef SETBST_H
#define SETBST_H

#include <iostream>
#include <stack>
#include "binarySearchTree.hpp"

template <typename T = int>
class SetBST{
public:
  class Iterator{
    friend class SetBST<T>;
  private:
    const SetBST<T>* set_;
    typename BinarySearchTree<T>::Node* node_;

    Iterator(const SetBST<T>* set, typename BinarySearchTree<T>::Node* node):set_(set), node_(node){}
  public:
    bool operator==(const Iterator& it) const;
    bool operator!=(const Iterator& it) const;
    Iterator& operator++();
    Iterator operator++(int);
    const T& operator*() const;
    const T* operator->() const;
    operator bool() const{ return this->node_ != nullptr; }

    Iterator& operator=(const Iterator&) = default;
    Iterator& operator=(Iterator&&) = default;

    Iterator() = default;
    Iterator(const Iterator&) = default;
    Iterator(Iterator&&) = default;
    ~Iterator() = default;
  };

private:
  BinarySearchTree<T> bst_;

public:
  std::pair<Iterator, bool> insert(const T& x);
  bool remove(const T& x);
  Iterator find(const T& x);
  const T* find(const T& x) const;
  std::size_t size() const;
  bool empty() const;

  void swapSet(SetBST<T>& first, SetBST<T>& second);

  Iterator begin() const;
  Iterator end() const;

  const SetBST<T>& operator=(const SetBST<T>& set);
  const SetBST<T>& operator=(SetBST<T>&& set);
  friend std::ostream& operator<<(std::ostream& output, const SetBST<T> &set){
    return output << set.bst_;
  }

  SetBST():bst_(){}
  SetBST(const SetBST<T>& set) = default;
  SetBST(SetBST<T>&& set) noexcept = default;
  ~SetBST() = default;
};

template <typename T>
bool SetBST<T>::Iterator::operator==(const Iterator& it) const{
  return (set_->bst_.rootPointer() == it.set_->bst_.rootPointer() && node_ == it.node_);
}

template <typename T>
bool SetBST<T>::Iterator::operator!=(const Iterator& it) const{
  return !(*this == it);
}

template <typename T>
typename SetBST<T>::Iterator& SetBST<T>::Iterator::operator++(){
  if(node_ == nullptr){
    node_ = set_->bst_.rootPointer();
    if(node_ == nullptr){
       throw "Set is empty";
    }

    while(node_->left != nullptr){
      node_ = node_->left;
    }

    return *this;
  }

  if(node_->right != nullptr){
    node_ = node_->right;
    while(node_->left != nullptr){
      node_ = node_->left;
    }
  }else{
    typename BinarySearchTree<T>::Node* temp;
    temp = set_->bst_.findParent(node_->key);
    while(temp != nullptr && node_ == temp->right){
      node_ = temp;
      temp = set_->bst_.findParent(temp->key);
    }
    node_ = temp;
  }

  return *this;
}

template <typename T>
typename SetBST<T>::Iterator SetBST<T>::Iterator::operator++(int){
  Iterator result(*this);
  ++(*this);
  return result;
}

template <typename T>
const T& SetBST<T>::Iterator::operator*() const{
  return node_->key;
}

template <typename T>
const T* SetBST<T>::Iterator::operator->() const{
  return &node_->key;
}

template <typename T>
std::pair<typename SetBST<T>::Iterator, bool> SetBST<T>::insert(const T& x){
  if(bst_.find(x) != nullptr){
    return std::make_pair(Iterator(this, nullptr), false);
  }else{
    bst_.insert(x);
    return std::make_pair(Iterator(this, bst_.search(x)), true);
  }
}

template <typename T>
bool SetBST<T>::remove(const T& x){
  return bst_.remove(x);
}

template <typename T>
typename SetBST<T>::Iterator SetBST<T>::find(const T& x){
  return Iterator(this, bst_.search(x));
}

template <typename T>
const T* SetBST<T>::find(const T& x) const{
  return bst_.findRec(x);
}

template <typename T>
std::size_t SetBST<T>::size() const{
  return bst_.size();
}

template <typename T>
bool SetBST<T>::empty() const{
 return bst_.empty();
}

template <typename T>
void SetBST<T>::swapSet(SetBST<T>& first, SetBST<T>& second){
  std::swap(first.bst_, second.bst_);
  second.bst_ = nullptr;
}

template <typename T>
typename SetBST<T>::Iterator SetBST<T>::begin() const{
  typename BinarySearchTree<T>::Node* root = bst_.rootPointer();
  if(root == nullptr){
    return Iterator(this, nullptr);
  }

  while(true){
    if(root->left != nullptr){
      root = root->left;
    }else if(root->right != nullptr){
      root = root->right;
    }else{
      return typename SetBST<T>::Iterator(this, root);
    }
  }
}

template <typename T>
typename SetBST<T>::Iterator SetBST<T>::end() const{
  return Iterator(this, nullptr);
}

template <typename T>
const SetBST<T>& SetBST<T>::operator=(const SetBST<T>& set){
  if(this != &set){
    bst_.freeMemory(bst_.rootPointer());
    bst_.copyTree(set.bst_.rootPointer());
  }

  return *this;
}

template <typename T>
const SetBST<T>& SetBST<T>::operator=(SetBST<T>&& set){
  swapSet(*this, set);
  return *this;
}

#endif
