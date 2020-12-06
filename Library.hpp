//
// Created by letih on 12/3/2020.
//

#pragma once
#ifndef OOP_LAB1__LIBRARY_HPP_
#define OOP_LAB1__LIBRARY_HPP_
#include "Book.hpp"
#include "LinkedList.hpp"
#include "Reader.hpp"

/**
 * @brief Класс для представления библиотеки
 */
class Library {
  public:
    Library() = default;

    /**
     * @brief Создание библиотеки из списков книг и читателей
     * @param books Список книг
     * @param readers Список читателей
     */
    Library(LinkedList<Book> &books, LinkedList<Reader> &readers);

    ~Library() = default;

    /**
     * @brief Получение количества книг в списке
     * @return Количество книг в списке
     */
    [[nodiscard]] int GetNumberOfBooks() const;

    /**
     * @brief Получение списка книг
     * @return Список книг
     */
    [[nodiscard]] LinkedList<Book> *GetBooks() const;

    /**
     * @brief Удаление одной книги из списка, если книга не находится у читателя
     * @param book Книга, для сравнения с существующими и удаления совпадения
     * @return Истина, если не выдана, ложь, если была выдана
     */
    bool RemoveBook(Book &book);

    /**
     * @brief Удаление всего списка книг, если нет не возвращённых книг
     * @return Истина, если отсутствуют не отданные книги, ложь, если есть не отданные книги
     */
    bool RemoveBooks();

    /**
     * @brief Получение количества читателей в списке
     * @return Количество читателей
     */
    [[nodiscard]] int GetNumberOfReaders() const;

    /**
     * @brief Получение списка читателей
     * @return Список читателей
     */
    [[nodiscard]] LinkedList<Reader> *GetReaders() const;

    /**
     * @brief Удаление одного читателя из списка, если у него нет взятой книги
     * @param reader Читатель, для сравнения с существующими и удаления совпадения
     * @return Истина, если отсутствует взятая книга, ложь, если она у него есть
     */
    bool RemoveReader(Reader &reader);

    /**
     * @brief Удаление всего списка читателей, если ни у кого из них нет взятой книги
     * @return Истина, если нет выданных книг, ложь, если есть выданные книги
     */
    bool RemoveReaders();

    /**
     * @brief Добавление новой книги в список
     * @param book Новая книга
     */
    void AddBook(Book &book);

    /**
     * @brief Добавление нового читателя в список
     * @param reader Новый читатель
     */
    void AddReader(Reader &reader);

    /**
     * @brief Выдача книги читателю
     * @param bid ID книги для выдачи
     * @param rid ID читателя для получения книги
     * @return Истина, если удалось выдать книгу, ложь, если книгу выдать не удалось
     */
    bool IssueBook(int bid, int rid);

    /**
     * @brief Возвращение книги в библиотеку
     * @param bid ID книги для возвращения
     * @param rid ID читателя для возвращения
     * @return Истина, если удалось вернуть книгу, ложь, если книгу вернуть не удалось
     */
    bool ReturnBook(int bid, int rid);

    /**
     * @brief Поиск книги по ID
     * @param bid ID книги для поиска
     * @return Найденная книга или nullptr
     */
    Book *FindBook(int bid);

    /**
     * @brief Поиск книги по её индексу в списке
     * @param index Индекс книги
     * @return Найденная книга или nullptr
     */
    Book *FindBookByIndex(int index);

    /**
     * @brief Поиск читателя по ID
     * @param rid ID читателя для поиска
     * @return Найденный читатель или nullptr
     */
    Reader *FindReader(int rid);

    /**
     * @brief Поиск читателя по его индексу в списке
     * @param index Индекс читателя
     * @return Найденный читатель или nullptr
     */
    Reader *FindReaderByIndex(int index);

    /**
     * @brief Оператор копирования
     * @param library Библиотека для копирования
     * @return Новая библиотека
     */
    Library &operator=(const Library &library);

  private:
    /**
     * @brief Указатель на список книг
     */
    LinkedList<Book> *books_;

    /**
     * @brief Указатель на список читатель
     */
    LinkedList<Reader> *readers_;
};

#endif//OOP_LAB1__LIBRARY_HPP_
