/**
 * \file Stack.cpp
 * \author Zayed Sheet <sheetz@mcmaster.ca>
 */
#include "../include/Stack.h"
#include "../include/CardTypes.h"

template <class T>
Stack<T>::Stack(std::vector<T> s){
    this->s = s;
}

template <class T>
Stack<T> Stack<T>::push(T e){
    this->s.push_back(e);
    return Stack(this->s);
}

template <class T>
Stack<T> Stack<T>::pop(){
    if(size() == 0){
        throw std::out_of_range("Pop Error");
    }
    this->s.pop_back();
    return Stack(this->s);
}

template <class T>
T Stack<T>::top(){
    if(size() == 0){
        throw std::out_of_range("Top Error");
    }
    return this->s.back();
}

template <class T>
unsigned int Stack<T>::size(){
    return this->s.size();
}

template <class T>
std::vector<T> Stack<T>::toSeq(){
    return this->s;
}

// Keep this at bottom
template class Stack<CardT>;
