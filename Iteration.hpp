//
// Created by letih on 12/3/2020.
//

#pragma once
#ifndef OOP_LAB1__ITERATION_HPP_
#define OOP_LAB1__ITERATION_HPP_
#include <ostream>
#include "Node.hpp"

template<class T>
class Iterator {
  public:
    Iterator(Node<T> *nodes = nullptr) : nodes_(nodes) {}

    ~Iterator() {
        if (nodes_ == nullptr) {
            nodes_ = nullptr;
        }
    }

    Node<T> *StepForward() {
        if (nodes_ == nullptr) {
            return nullptr;
        }

        nodes_ = nodes_->next;
        return nodes_;
    }

    Node<T> StepBackward() {
        if (nodes_ == nullptr) {
            return nullptr;
        }

        nodes_ = nodes_->prev;
        return nodes_;
    }

  private:
    Node<T> *nodes_;
};

#endif//OOP_LAB1__ITERATION_HPP_
