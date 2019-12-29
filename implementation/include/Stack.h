/**
 * \file Stack.h
 * \author Zayed Sheet, MacID: sheetz
 * \brief Provides an ADT for a generic stack.
 * \date March 26, 2019
 */
#ifndef A3_STACK_H_
#define A3_STACK_H_

#include <vector>
#include <stdexcept>

/**
 * \brief ADT for a generic stack
 */
template <class T>
class Stack{
    private:
        std::vector<T> s;

    public:
        /**
         * \brief constructor for a generic stack.
         * @param s parameter for a sequence of T elements.
         */
        Stack(std::vector<T> s);

        /**
         * \brief pushes an element to the top of the stack.
         * @param e  element T thats being pushed.
         * @return returns a stack with param e pushed to the top.
         */
        Stack<T> push(T e);

        /**
         * \brief pops an element from the top of the stack.
         * @return returns a stack with top element popped off.
         */
        Stack<T> pop();

        /**
         * \brief retreives the value of the top element of the stack.
         * @return returns the top element of a stack.
         */
        T top();

        /**
         * \brief retrieves the number of elements in the stack
         * @return number of elements in the stack
         */
        unsigned int size();

        /**
         * \brief retreives all the elements in the stack as a vector
         * @return vector of the elements in the stuck
         */
        std::vector<T> toSeq();

};

#endif
