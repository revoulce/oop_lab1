//
// Created by letih on 12/3/2020.
//

#pragma once
#ifndef OOP_LAB1__BOOK_HPP_
#define OOP_LAB1__BOOK_HPP_
#include <iostream>
#include <string>

/**
 * @brief Класс для представления книги
 */
class Book {
  public:
    Book();

    /**
     * @brief Создание книги с указанием каждого параметра отдельно
     * @param author Имя автора
     * @param title Название
     * @param publisher Издатель
     * @param year Год издания
     * @param bid ID книги
     * @param is_issued Книга выдана?
     */
    Book(std::string &author,
         std::string &title,
         std::string &publisher,
         int year = 0,
         int bid = 0,
         bool is_issued = false);

    /**
     * @brief Создание книги из массива строк
     * @param parameters Массив строк, где находятся все параметры кроме выдачи
     */
    explicit Book(std::string parameters[]);

    /**
     * @brief Создание копии книги
     * @param other_book Книга, копия которой создаётся
     */
    Book(const Book &other_book);

    ~Book() = default;

    /**
     * @brief Получение ID книги
     * @return ID книги
     */
    [[nodiscard]] int GetBid() const;

    /**
     * @brief Получения статуса выдачи книги
     * @return Истина, если выдана, ложь, если нет
     */
    [[nodiscard]] bool GetIsIssued() const;

    /**
     * @brief Установка статуса выдачи книги
     * @param is_issued Новый статус выдачи
     */
    void SetIsIssued(bool is_issued);

    /**
     * @brief Оператор копирования
     * @param book Книга, которая копируется
     * @return Копия объекта
     */
    Book &operator=(const Book &book);

    /**
     * @brief Оператор равенства
     * @param book Книга для сравнения
     * @return Истина, если равны, ложь, если нет
     */
    bool operator==(const Book &book);

    /**
     * @brief Оператор вывода на экран
     * @param os Поток для вывода
     * @param book Книга для вывода
     * @return Поток с выводом
     */
    friend std::ostream &operator<<(std::ostream &os, const Book &book);

  private:
    /**
     * @brief Имя автора книги
     */
    std::string author_;

    /**
     * @brief Название книги
     */
    std::string title_;

    /**
     * @brief Год издания книги
     */
    int year_;

    /**
     * @brief Издательство книги
     */
    std::string publisher_;

    /**
     * @brief ID книги
     */
    int bid_;

    /**
     * @brief Выдана ли книга?
     */
    bool is_issued_;
};

#endif//OOP_LAB1__BOOK_HPP_
