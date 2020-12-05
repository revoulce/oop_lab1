//
// Created by letih on 12/3/2020.
//

#pragma once
#ifndef OOP_LAB1__LIBRARY_HPP_
#define OOP_LAB1__LIBRARY_HPP_
#include "Book.hpp"
#include "LinkedList.hpp"
#include "Reader.hpp"

class Library {
  public:
    Library() = default;

    Library(LinkedList<Book> &books, LinkedList<Reader> &readers);

    ~Library() = default;

    [[nodiscard]] int GetNumberOfBooks() const;

    [[nodiscard]] LinkedList<Book> *GetBooks() const;

    bool RemoveBook(Book &book);

    void RemoveBooks();

    [[nodiscard]] int GetNumberOfReaders() const;

    [[nodiscard]] LinkedList<Reader> *GetReaders() const;

    bool RemoveReader(Reader &reader);

    void RemoveReaders();

    void AddBook(Book &book);

    void AddReader(Reader &reader);

    bool IssueBook(int bid, int rid);

    bool ReturnBook(int bid, int rid);

    Book *FindBook(int bid);

    Book *FindBookByIndex(int index);

    Reader *FindReader(int rid);

    Reader *FindReaderByIndex(int index);

    Library &operator=(const Library &library);

  private:
    LinkedList<Book> *books_;
    LinkedList<Reader> *readers_;
};

#endif//OOP_LAB1__LIBRARY_HPP_
