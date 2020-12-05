//
// Created by letih on 12/3/2020.
//

#pragma once
#ifndef OOP_LAB1__LINKEDLIST_HPP_
#define OOP_LAB1__LINKEDLIST_HPP_
#include "Iteration.hpp"
#include "Node.hpp"

template<class T>
class LinkedList {
  public:
    LinkedList() {
        head_ = new Node<T>();
        tail_ = new Node<T>();
    }

    LinkedList(const LinkedList<T> &other_list) {
        if (other_list.IsEmpty()) {
            head_ = new Node<T>();
            tail_ = new Node<T>();
            return;
        }

        auto *list = other_list.GetIteratorAtHead();
        auto *node = list->StepForward();

        head_ = new Node<T>();
        tail_ = new Node<T>();

        PushBack(node->data);

        node = list->StepForward();

        while (node != nullptr) {
            PushBack(node->data);
            node = list->StepForward();
        }
    }

    ~LinkedList() {
        DeleteList();
        delete head_;
        delete tail_;
    }

    [[nodiscard]] bool IsEmpty() const {
        return head_->next == nullptr;
    }

    [[nodiscard]] int Size() const {
        if (IsEmpty()) {
            return 0;
        }

        Node<T> *node = tail_;
        auto count = 0;

        while (node != nullptr) {
            node = node->prev;
            ++count;
        }

        return count;
    }

    void PushFront(T &data) {
        if (IsEmpty()) {
            Node<T> *node = new Node<T>(data);
            head_->next = node;
            tail_->prev = node;
            return;
        }

        Node<T> *first = head_->next;
        Node<T> *node = new Node<T>(data, first);
        first->prev = node;
        head_->prev = node;
    }

    void PushBack(T &data) {
        if (IsEmpty()) {
            auto *node = new Node<T>(data);
            head_->next = node;
            tail_->prev = node;
            return;
        }

        Node<T> *last = tail_->prev;
        auto *node = new Node<T>(data, nullptr, last);
        last->next = node;
        tail_->prev = node;
    }

    bool InsertBefore(Node<T> *reference, T &data) {
        if (IsEmpty()) {
            return false;
        }

        Node<T> *search_reference = head_->next;

        while (search_reference != nullptr) {
            if (search_reference == reference) {
                break;
            }

            search_reference = search_reference->next;
        }

        if (search_reference == nullptr) {
            return false;
        }

        Node<T> *before_preference = search_reference->prev;
        auto *node = new Node<T>(data, search_reference, before_preference);

        if (before_preference == nullptr) {
            head_->next = node;
        } else {
            before_preference->next = node;
        }

        search_reference->prev = node;

        return true;
    }

    bool InsertAfter(Node<T> *reference, T &data) {
        if (IsEmpty()) {
            return false;
        }

        Node<T> *search_reference = head_->next;

        while (search_reference != nullptr) {
            if (search_reference == reference) {
                break;
            }

            search_reference = search_reference->next;
        }

        if (search_reference == nullptr) {
            return false;
        }

        Node<T> *after_preference = search_reference->next;
        auto *node = new Node<T>(data, after_preference, search_reference);

        if (after_preference == nullptr) {
            tail_->prev = node;
        } else {
            after_preference->prev = node;
        }

        search_reference->next = node;

        return true;
    }

    bool DeleteNodeByContent(T &data) {
        if (IsEmpty()) {
            return false;
        }

        auto *node = head_->next;

        while (node != nullptr) {
            if (node->data == data) {
                break;
            }

            node = node->next;
        }

        return DeleteNode(node);
    }

    bool DeleteNode(Node<T> *reference) {
        if (IsEmpty()) {
            return false;
        }

        Node<T> *node_to_delete = tail_->prev;

        while (node_to_delete != nullptr) {
            if (node_to_delete == reference) {
                break;
            }

            node_to_delete = node_to_delete->prev;
        }

        if (node_to_delete == nullptr) {
            return false;
        }

        Node<T> *after_delete = node_to_delete->next;
        Node<T> *before_delete = node_to_delete->prev;

        if (after_delete == nullptr) {
            tail_->prev = before_delete;
        } else {
            after_delete->prev = before_delete;
        }

        if (before_delete == nullptr) {
            head_->next = after_delete;
        } else {
            before_delete->next = after_delete;
        }

        delete node_to_delete;

        return true;
    }

    void DeleteList() {
        while (tail_->prev != nullptr) {
            Node<T> *node_to_delete = tail_->prev;
            DeleteNode(node_to_delete);
        }
    }

    T *GetNodeDataByIndex(int index) const {
        auto *list = GetIteratorAtHead();
        auto *node = list->StepForward();
        int count = 0;

        while (node != nullptr) {
            if (count == index) {
                break;
            }

            node = node->next;
            ++count;
        }

        if (node == nullptr) {
            return nullptr;
        }

        return &node->data;
    }

    Iterator<T> *GetIteratorAtHead() const {
        auto *iterator = new Iterator<T>(head_);
        return iterator;
    }

    Iterator<T> *GetIteratorAtTail() const {
        auto *iterator = new Iterator<T>(tail_);
        return iterator;
    }

    LinkedList<T> &operator=(const LinkedList<T> &linked_list) {
        if (this == &linked_list) {
            return *this;
        }

        delete head_;
        delete tail_;

        head_ = new Node<T>(*linked_list.head_);
        tail_ = new Node<T>(*linked_list.tail_);

        return *this;
    }

  private:
    Node<T> *head_;
    Node<T> *tail_;
};

#endif//OOP_LAB1__LINKEDLIST_HPP_
