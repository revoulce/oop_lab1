//
// Created by letih on 12/3/2020.
//

#pragma once
#ifndef OOP_LAB1__CONSOLE_HPP_
#define OOP_LAB1__CONSOLE_HPP_
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>

#include "Library.hpp"
#include "LinkedList.hpp"

/**
 * @brief Класс для работы с библиотекой и пользователем
 */
class Console {
  public:
    Console() = default;

    ~Console() = default;

    void Run();

  private:
    /**
     * @brief Указатель на библиотеку
     */
    Library *library_;

    /**
     * @brief Читает данные из фалов и создаёт на их основе библиотеку
     */
    void ReadFiles();

    /**
     * @brief Предлагает меню пользователю и работает с ним
     */
    void UserInteraction();

    /**
     * @brief Проверяет строку на наличие только цифр
     * @param string_to_check Строка для проверки
     * @return Истина, если только цифры, ложь, если присутствуют и буквы
     */
    bool CheckIsNumeric(std::string &string_to_check);

    /**
     * @brief Запрашивает у пользователя подтверждение его действий и обрабатывает его ответ
     * @param string_to_output Строка запроса
     * @return Истина, если пользователь согласился, ложь, если отказался
     */
    bool CheckUserWish(std::string &string_to_output = (std::string &) "Are you sure?");

    /**
     * @brief Проверяет библиотеку на существование
     * @return Истина, если существует, ложь, если не существует
     */
    bool DoesLibraryExist();

    void PrintMenu();

    void PrintBooks();

    void PrintReaders();

    /**
     * @brief Запрашивает у пользователя ввод книги
     * @return Указатель на созданную книгу
     */
    Book *InputBook();

    /**
     * @brief Запрашивает у пользователя ввод читателя
     * @return Указатель на созданного читателя
     */
    Reader *InputReader();

    void AddBooks();

    void AddReaders();

    void DeleteBooks();

    void DeleteReaders();

    /**
     * @brief Позволяет пользователю выбрать книгу из списка или вручную ввести ID книги
     * @return Выбранную книгу
     */
    Book *ChooseBook();

    /**
     * @brief Позволяет пользователю выбрать читателя из списка или вручную ввести ID читателя
     * @return
     */
    Reader *ChooseReader();

    /**
     * @brief Выдаёт книгу читателю
     */
    void IssueBook();

    /**
     * @brief Возвращает книгу обратно в библиотеку
     */
    void ReturnABook();

    /**
     * @brief Очищает консоль от символов
     */
    void ClearScreen();

    /**
     * @brief Ожидания нажатия от пользователя
     * @param prompt Строка для вывода для пользователя
     */
    void WaitForAnyKey(const TCHAR *prompt = nullptr);
};

#endif//OOP_LAB1__CONSOLE_HPP_
