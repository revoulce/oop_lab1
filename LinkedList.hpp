//
// Created by letih on 12/3/2020.
//

#pragma once
#ifndef OOP_LAB1__LINKEDLIST_HPP_
#define OOP_LAB1__LINKEDLIST_HPP_
#include "Iterator.hpp"
#include "Node.hpp"

template<class T>
class LinkedList {
  public:
    LinkedList() {
        head_ = new Node<T>();
        tail_ = new Node<T>();
    }

    /**
     * @brief Конструктор копирования
     * @param other_list Список для копирования
     */
    LinkedList(const LinkedList<T>& other_list) {
        if (other_list.IsEmpty()) {
            head_ = new Node<T>();
            tail_ = new Node<T>();
            return;
        }

        auto* list = other_list.GetIteratorAtHead();
        auto* node = list->StepForward();

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

    /**
     * @brief Проверка списка на пустоту
     * @return Истина, если список не пуст, ложь, если список пуст
     */
    [[nodiscard]] bool IsEmpty() const {
        return head_->next == nullptr;
    }

    /**
     * @brief Получение размера списка
     * @return Размер списка
     */
    [[nodiscard]] int Size() const {
        if (IsEmpty()) {
            return 0;
        }

        Node<T>* node = tail_;
        auto count = 0;

        while (node != nullptr) {
            node = node->prev;
            ++count;
        }

        return count;
    }

    /**
     * @brief Добавление элемента в конец списка
     * @param data Данные для добавления
     */
    void PushFront(T& data) {
        if (IsEmpty()) {
            Node<T>* node = new Node<T>(data);
            head_->next = node;
            tail_->prev = node;
            return;
        }

        Node<T>* first = head_->next;
        Node<T>* node = new Node<T>(data, first);
        first->prev = node;
        head_->prev = node;
    }

    /**
     * @brief Добавление элемента в начало списка
     * @param data Данные для добавления
     */
    void PushBack(T& data) {
        if (IsEmpty()) {
            auto* node = new Node<T>(data);
            head_->next = node;
            tail_->prev = node;
            return;
        }

        Node<T>* last = tail_->prev;
        auto* node = new Node<T>(data, nullptr, last);
        last->next = node;
        tail_->prev = node;
    }

    /**
     * @brief Вставка перед определённым элементом
     * @param reference Указатель на элемент, перед которого необходимо вставить новый элемент
     * @param data Данные для добавления
     * @return Истина, если удалось добавить элемент, ложь, если не удалось
     */
    bool InsertBefore(Node<T>* reference, T& data) {
        if (IsEmpty()) {
            return false;
        }

        Node<T>* search_reference = head_->next;

        while (search_reference != nullptr) {
            if (search_reference == reference) {
                break;
            }

            search_reference = search_reference->next;
        }

        if (search_reference == nullptr) {
            return false;
        }

        Node<T>* before_preference = search_reference->prev;
        auto* node = new Node<T>(data, search_reference, before_preference);

        if (before_preference == nullptr) {
            head_->next = node;
        } else {
            before_preference->next = node;
        }

        search_reference->prev = node;

        return true;
    }

    /**
     * @brief Вставка после определённого элемента
     * @param reference Указатель на элемент, после которого необходимо вставить новый элемент
     * @param data Данные для добавления
     * @return Истина, если удалось добавить элемент, ложь, если не удалось
     */
    bool InsertAfter(Node<T>* reference, T& data) {
        if (IsEmpty()) {
            return false;
        }

        Node<T>* search_reference = head_->next;

        while (search_reference != nullptr) {
            if (search_reference == reference) {
                break;
            }

            search_reference = search_reference->next;
        }

        if (search_reference == nullptr) {
            return false;
        }

        Node<T>* after_preference = search_reference->next;
        auto* node = new Node<T>(data, after_preference, search_reference);

        if (after_preference == nullptr) {
            tail_->prev = node;
        } else {
            after_preference->prev = node;
        }

        search_reference->next = node;

        return true;
    }

    /**
     * @brief Удаление элемента с определёнными данными
     * @param data Данные для проверки
     * @return Истина, если удалось удалить элемент, ложь, если не удалось
     */
    bool DeleteNodeByContent(T& data) {
        if (IsEmpty()) {
            return false;
        }

        auto* node = head_->next;

        while (node != nullptr) {
            if (node->data == data) {
                break;
            }

            node = node->next;
        }

        return DeleteNode(node);
    }

    /**
     * @brief Удаление определённого элемента
     * @param reference Указатель на удаляемый элемент
     * @return Истина, если удалось удалить элемент, ложь, если не удалось
     */
    bool DeleteNode(Node<T>* reference) {
        if (IsEmpty()) {
            return false;
        }

        Node<T>* node_to_delete = tail_->prev;

        while (node_to_delete != nullptr) {
            if (node_to_delete == reference) {
                break;
            }

            node_to_delete = node_to_delete->prev;
        }

        if (node_to_delete == nullptr) {
            return false;
        }

        Node<T>* after_delete = node_to_delete->next;
        Node<T>* before_delete = node_to_delete->prev;

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

    /**
     * @brief Удаление всего списка
     */
    void DeleteList() {
        while (tail_->prev != nullptr) {
            Node<T>* node_to_delete = tail_->prev;
            DeleteNode(node_to_delete);
        }
    }

    /**
     * @brief Получение элемента по его индексу в списке
     * @param index Индекс элемента
     * @return Истина, если удалось найти элемент, ложь, если не удалось
     */
    T* GetNodeDataByIndex(int index) const {
        auto* list = GetIteratorAtHead();
        auto* node = list->StepForward();
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

    /**
     * @brief Получение указателя на итератор с начала списка
     * @return Указатель на итератор с начала списка
     */
    Iterator<T>* GetIteratorAtHead() const {
        auto* iterator = new Iterator<T>(head_);
        return iterator;
    }

    /**
     * @brief Получение указателя на итератор с конца списка
     * @return Указатель на итератор с конца списка
     */
    Iterator<T>* GetIteratorAtTail() const {
        auto* iterator = new Iterator<T>(tail_);
        return iterator;
    }

    /**
     * @brief Оператор копирования
     * @param linked_list Список для копирования
     * @return Новый список
     */
    LinkedList<T>& operator=(const LinkedList<T>& linked_list) {
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
    /**
     * @brief Указатель на указатель на первый элемент в списке
     */
    Node<T>* head_;

    /**
     * @brief Указатель на указатель на последний элемент в списке
     */
    Node<T>* tail_;
};

#endif//OOP_LAB1__LINKEDLIST_HPP_
