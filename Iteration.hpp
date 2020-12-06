//
// Created by letih on 12/3/2020.
//

#pragma once
#ifndef OOP_LAB1__ITERATION_HPP_
#define OOP_LAB1__ITERATION_HPP_
#include <ostream>
#include "Node.hpp"

/**
 * @brief Класс для прохождения по списку
 * @tparam T Класс для которого создавался список
 */
template<class T>
class Iterator {
  public:
    /**
     * @brief Создаёт итератор для прохождения по списку
     * @param nodes Указатель на один из элементов списка, который будет итерироваться
     */
    explicit Iterator(Node<T> *nodes = nullptr) : nodes_(nodes) {}

    ~Iterator() {
        if (nodes_ == nullptr) {
            nodes_ = nullptr;
        }
    }

    /**
     * @brief Сделать шаг вперед в списке
     * @return Указатель на следующий элемент списка или nullptr, если список пуст
     */
    Node<T> *StepForward() {
        if (nodes_ == nullptr) {
            return nullptr;
        }

        nodes_ = nodes_->next;
        return nodes_;
    }

    /**
     * @brief Сделать шаг назад в списке
     * @return Указатель на следующий элемент списка или nullptr, если список пуст
     */
    Node<T> StepBackward() {
        if (nodes_ == nullptr) {
            return nullptr;
        }

        nodes_ = nodes_->prev;
        return nodes_;
    }

  private:
    /**
     * @brief Указатель на текущий элемент в списке
     */
    Node<T> *nodes_;
};

#endif//OOP_LAB1__ITERATION_HPP_
