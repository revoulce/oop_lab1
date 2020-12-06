//
// Created by letih on 12/3/2020.
//

#pragma once
#ifndef OOP_LAB1__READER_HPP_
#define OOP_LAB1__READER_HPP_
#include <iostream>

class Reader {
  public:
    explicit Reader(int rid = 0, int bid = 0);

    ~Reader() = default;

    /**
     * @brief Получение ID читателя
     * @return ID читателя
     */
    [[nodiscard]] int GetRid() const;

    /**
     * @brief Получение ID выданной книги
     * @return ID книги
     */
    [[nodiscard]] int GetBid() const;

    /**
     * @brief Установка ID выданной книги
     * @param bid ID книги
     */
    void SetBid(int bid);

    /**
     * @brief Оператор равенства
     * @param reader Читатель для сравнения
     * @return Истина, если равны, ложь, если не равны
     */
    bool operator==(const Reader &reader);

    /**
     * @brief Оператор вывода на экран
     * @param os Поток для вывода
     * @param reader Книга для вывода
     * @return Поток с выводом
     */
    friend std::ostream &operator<<(std::ostream &os, const Reader &reader);

  private:
    /**
     * @brief ID читателя
     */
    int rid_;

    /**
     * @brief ID выданной книги
     */
    int bid_;
};

#endif//OOP_LAB1__READER_HPP_
