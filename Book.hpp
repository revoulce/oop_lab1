//
// Created by letih on 12/3/2020.
//

#pragma once
#ifndef OOP_LAB1__BOOK_HPP_
#define OOP_LAB1__BOOK_HPP_
#include <iostream>
#include <string>

class Book {
  public:
    Book();

    Book(std::string &author,
         std::string &title,
         std::string &publisher,
         int year = 0,
         int bid = 0,
         bool is_issued = false);

    explicit Book(std::string parameters[]);

    Book(const Book &other_book);

    ~Book() = default;

    [[nodiscard]] int GetBid() const;

    [[nodiscard]] bool GetIsIssued() const;

    void SetIsIssued(bool is_issued);

    Book &operator=(const Book &book);

    bool operator==(const Book &book);

    friend std::ostream &operator<<(std::ostream &os, const Book &book);

  private:
    std::string author_;
    std::string title_;
    int year_;
    std::string publisher_;
    int bid_;
    bool is_issued_;
};

#endif//OOP_LAB1__BOOK_HPP_
