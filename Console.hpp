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

class Console {
  public:
    Console() = default;

    ~Console() = default;

    void Run();

  private:
    Library *library_;

    void ReadFiles();

    void UserInteraction();

    bool CheckIsNumeric(std::string &string_to_check);

    bool CheckUserWish(std::string &string_to_output = (std::string &) "Are you sure?");

    bool IsLibraryEmpty();

    void PrintMenu();

    void PrintBooks();

    void PrintReaders();

    Book *InputBook();

    Reader *InputReader();

    void AddBooks();

    void AddReaders();

    void DeleteBooks();

    void DeleteReaders();

    Book *ChooseBook();

    Reader *ChooseReader();

    void IssueABook();

    void ReturnABook();

    void ClearScreen();

    void WaitForAnyKey(const TCHAR *prompt = nullptr);
};

#endif//OOP_LAB1__CONSOLE_HPP_
