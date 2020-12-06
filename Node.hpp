//
// Created by letih on 12/3/2020.
//

#pragma once
#ifndef OOP_LAB1__NODE_HPP_
#define OOP_LAB1__NODE_HPP_

template<class T> class Node {
  public:
    /**
     * @brief Данные элемента
     */
    T data;

    /**
     * @brief Указатель на следующий элемент
     */
    Node* next;

    /**
     * @brief Указатель на предыдущий элемент
     */
    Node* prev;

    Node(const T& data = T(), Node* next = nullptr, Node* prev = nullptr) : data(data), next(next), prev(prev) {}

    Node(const Node& other_node) : data(other_node.data), next(other_node.next), prev(other_node.prev) {}

    ~Node() = default;
};

#endif//OOP_LAB1__NODE_HPP_
