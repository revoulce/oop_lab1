//
// Created by letih on 12/3/2020.
//

#include "Console.hpp"

void Console::Run() {
    ReadFiles();

    try {
        UserInteraction();
    } catch (std::exception &e) {
        std::cerr << "Ошибка: " << e.what();
        WaitForAnyKey();
    }
}

void Console::ReadFiles() {
    try {
        std::string books_filename = "books.txt";
        std::string readers_filename = "readers.txt";

        std::ifstream books_file(books_filename);
        std::ifstream readers_file(readers_filename);

        books_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        readers_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        std::string line, token;
        char delimiter = ',';
        int rid;
        const int parameters_count = 5;
        std::string parameters[parameters_count];

        auto *books = new LinkedList<Book>();
        auto *readers = new LinkedList<Reader>();

        std::getline(books_file, line);
        int books_count = std::stoi(line);

        std::getline(readers_file, line);
        int readers_count = std::stoi(line);

        for (int i = 0; i < books_count; ++i) {
            std::getline(books_file, line);
            std::stringstream ss(line);

            for (auto &parameter : parameters) {
                std::getline(ss, token, delimiter);
                parameter = token;
            }

            auto *book = new Book(parameters);
            books->PushBack(*book);
        }

        for (int i = 0; i < readers_count; ++i) {
            std::getline(readers_file, line);
            rid = std::stoi(line);
            auto *reader = new Reader(rid);
            readers->PushBack(*reader);
        }

        library_ = new Library(*books, *readers);

        books_file.close();
        readers_file.close();
    } catch (std::ifstream::failure &e) {
        std::cerr << "Произошла ошибка при открытии/чтении/закрытии файла" << std::endl;
        std::cerr << "Error message: " << e.what() << std::endl;
        WaitForAnyKey();
    } catch (std::invalid_argument &e) {
        std::cerr
            << "Были обнаружены буквы вместо цифр. Пожалуйста проверьте данные в файлах и повторно запустите программу."
            << std::endl;
        std::cerr << "Сообщение об ошибке: " << e.what() << std::endl;
        WaitForAnyKey();
    }

}

void Console::UserInteraction() {
    int user_answer;
    std::string temp_user_answer;
    std::string string_to_ensure_exit = "Вы уверены, что хотите выйти? Y/n";

    while (true) {
        ClearScreen();
        PrintMenu();

        std::cout << "Введите ваш выбор: ";
        std::getline(std::cin, temp_user_answer);

        try {
            if (!temp_user_answer.empty() && CheckIsNumeric(temp_user_answer)) {
                user_answer = std::stoi(temp_user_answer);
            } else {
                std::cerr << "Введённые данные пусты или содержат символы отличные от цифр." << std::endl;
                WaitForAnyKey();
                continue;
            }
        } catch (std::out_of_range &e) {
            std::cerr << "Введено слишком большое число." << std::endl;
            WaitForAnyKey();
            continue;
        }

        switch (user_answer) {
            case 0:
                if (CheckUserWish(string_to_ensure_exit)) {
                    return;
                }
                break;
            case 1:
                ClearScreen();
                PrintBooks();
                WaitForAnyKey();
                break;
            case 2:
                ClearScreen();
                PrintReaders();
                WaitForAnyKey();
                break;
            case 3:
                ClearScreen();
                AddBooks();
                break;
            case 4:
                ClearScreen();
                AddReaders();
                break;
            case 5:
                ClearScreen();
                DeleteBooks();
                break;
            case 6:
                ClearScreen();
                DeleteReaders();
                break;
            case 7:
                ClearScreen();
                IssueBook();
                break;
            case 8:
                ClearScreen();
                ReturnABook();
                break;
            default:
                std::cerr << "Был введён неверный номер." << std::endl;
                WaitForAnyKey();
        }
    }
}

bool Console::CheckIsNumeric(std::string &string_to_check) {
    return std::ranges::all_of(string_to_check, [](char ch) { return std::isdigit(ch) != 0; });
}

bool Console::CheckUserWish(std::string &string_to_output) {
    std::string user_input;

    std::cout << string_to_output << std::endl << "> ";
    std::getline(std::cin, user_input);
    std::cout << std::endl;

    if (user_input == "N" || user_input == "n") {
        return false;
    } else if (user_input != "Y" && user_input != "y") {
        return CheckUserWish(string_to_output);
    }

    return true;
}

bool Console::DoesLibraryExist() {
    if (library_ == nullptr) {
        std::cerr
            << "Библиотека не была создана. Проверьте наличие файлов в той же папке, что и программа, а так же их правильность."
            << std::endl;
        WaitForAnyKey();
        return true;
    }

    return false;
}

void Console::PrintMenu() {
    std::cout << "Меню:" << std::endl;
    std::cout << "0. Выход из программы." << std::endl;
    std::cout << "1. Вывод списка книг." << std::endl;
    std::cout << "2. Вывод списка читателей." << std::endl;
    std::cout << "3. Добавить книгу/книги." << std::endl;
    std::cout << "4. Добавить читателя/читателей." << std::endl;
    std::cout << "5. Удалить книгу/книги." << std::endl;
    std::cout << "6. Удалить читателя/читателей." << std::endl;
    std::cout << "7. Выдать книгу/книги." << std::endl;
    std::cout << "8. Вернуть книгу/книги." << std::endl;
}

void Console::PrintBooks() {
    if (DoesLibraryExist()) {
        return;
    }

    auto *books = library_->GetBooks()->GetIteratorAtHead();
    auto *book = books->StepForward();
    int i = 1;

    if (book == nullptr) {
        std::cout << "Список книг пуст." << std::endl;
        return;
    }

    while (book != nullptr) {
        std::cout << i << "." << std::endl << book->data << std::endl << std::endl;
        book = books->StepForward();
        ++i;
    }
}

void Console::PrintReaders() {
    if (DoesLibraryExist()) {
        return;
    }

    auto *readers = library_->GetReaders()->GetIteratorAtHead();
    auto *reader = readers->StepForward();
    auto i = 1;

    if (reader == nullptr) {
        std::cout << "Список читателей пуст." << std::endl;
        return;
    }

    while (reader != nullptr) {
        std::cout << i << ". " << reader->data << std::endl;
        reader = readers->StepForward();
        ++i;
    }
}

Book *Console::InputBook() {
    const auto parameters_count = 5;
    std::string parameters[parameters_count];
    std::string author, title, year, publisher, bid;
    bool all_is_set[parameters_count] = {false, false, false, false, false};
    int i;

    while (true) {
        i = 0;
        if (!all_is_set[i]) {
            std::cout << "Введите автора: ";
            std::getline(std::cin, author);

            if (!author.empty()) {
                all_is_set[i] = true;
                parameters[i] = author;
            }
        }

        i = 1;
        if (!all_is_set[i]) {
            std::cout << "Введите название: ";
            std::getline(std::cin, title);

            if (!title.empty()) {
                all_is_set[i] = true;
                parameters[i] = title;
            }
        }

        i = 2;
        if (!all_is_set[i]) {
            std::cout << "Введите год издания: ";
            std::getline(std::cin, year);

            if (!year.empty() && CheckIsNumeric(year)) {
                all_is_set[i] = true;
                parameters[i] = year;
            }
        }

        i = 3;
        if (!all_is_set[i]) {
            std::cout << "Введите издателя: ";
            std::getline(std::cin, publisher);

            if (!publisher.empty()) {
                all_is_set[i] = true;
                parameters[i] = publisher;
            }
        }

        i = 4;
        if (!all_is_set[i]) {
            std::cout << "Введите ID книги: ";
            std::getline(std::cin, bid);

            if (!bid.empty() && CheckIsNumeric(bid)) {
                all_is_set[i] = true;
                parameters[i] = bid;
            }
        }

        if (std::ranges::all_of(all_is_set, [](bool is_set) { return is_set; })) {
            break;
        }

        std::cout << "Попробуйте снова -- в вводе были ошибки." << std::endl;
    }

    Book *book = new Book(parameters);

    return book;
}

Reader *Console::InputReader() {
    std::string rid;

    while (true) {
        std::cout << "Введите ID читателя: ";
        std::getline(std::cin, rid);

        if (!rid.empty() && CheckIsNumeric(rid)) {
            break;
        }

        std::cout << "Попробуйте снова -- в вводе были ошибки." << std::endl;
    }

    auto *reader = new Reader(std::stoi(rid));

    return reader;
}

void Console::AddBooks() {
    if (DoesLibraryExist()) {
        return;
    }

    std::string string_to_check_a_wish = "Вы уверены что хотите добавить новую книгу? Y/n";

    while (CheckUserWish(string_to_check_a_wish)) {
        auto *book = InputBook();
        library_->AddBook(*book);
        ClearScreen();
        std::cout << "Успех! Книга была добавлена в список." << std::endl << std::endl;
    }
}

void Console::AddReaders() {
    if (DoesLibraryExist()) {
        return;
    }

    std::string string_to_check_a_wish = "Вы уверены что хотите добавить нового читателя? Y/n";

    while (CheckUserWish(string_to_check_a_wish)) {
        auto *reader = InputReader();
        library_->AddReader(*reader);
        ClearScreen();
        std::cout << "Успех! Читатель был добавлен в список." << std::endl << std::endl;
    }
}

void Console::DeleteBooks() {
    if (DoesLibraryExist()) {
        return;
    }

    std::string string_to_check_a_wish = "Вы уверены что хотите удалить книгу? Y/n";
    std::string string_to_ensure_delete_all = "Вы уверены что хотите удалить всех читателей? Y/n";

    if (CheckUserWish(string_to_ensure_delete_all)) {
        if (library_->RemoveBooks()) {
            return;
        }

        std::cout
            << "Не удалось удалить книги из-за того что некоторые из них не возвращены. Верните книги и попытайтесь снова.";
        return;
    }

    while (CheckUserWish(string_to_check_a_wish)) {
        auto *find_book = ChooseBook();

        if (find_book != nullptr) {
            ClearScreen();

            if (library_->RemoveBook(*find_book)) {
                std::cout << "Успех! Книга была удалена." << std::endl;
            } else {
                std::cout
                    << "Провал! Книга не была удалена по причине: её не существует уже или она была выдана кому-то. Верните книгу или выберите другую."
                    << std::endl;
            }
        }
    }
}

void Console::DeleteReaders() {
    if (DoesLibraryExist()) {
        return;
    }

    std::string string_to_check_a_wish = "Вы уверены что хотите удалить читателя? Y/n";
    std::string string_to_ensure_delete_all = "Вы уверены что хотите удалить всех читателей? Y/n";

    if (CheckUserWish(string_to_ensure_delete_all)) {
        if (library_->RemoveReaders()) {
            return;
        }

        std::cout
            << "Не удалось удалить читателей из-за того что некоторые из них не вернули книги. Помогите им вернуть книги и тогда Вы сможете удалить их всех.";
        return;
    }

    while (CheckUserWish(string_to_check_a_wish)) {
        auto *find_reader = ChooseReader();

        if (find_reader != nullptr) {
            ClearScreen();

            if (library_->RemoveReader(*find_reader)) {
                std::cout << "Успех! Читатель был удалён." << std::endl;
            } else {
                std::cout
                    << "Провал! Читатель не был удалён по причине: его не существует или он владеет книгой. Верните книгу или выберите другого."
                    << std::endl;
            }
        }
    }
}

Book *Console::ChooseBook() {
    std::string string_to_choose_a_method =
        "Вы хотите ввести ID книги? Если нет, то Вам будет предложено выбрать из списка. Y/n";
    std::string user_input;
    int user_input_int;

    if (CheckUserWish(string_to_choose_a_method)) {
        std::cout << "Введите ID книги: ";
        std::getline(std::cin, user_input);

        if (user_input.empty() || !CheckIsNumeric(user_input)) {
            std::cerr << "Введённые данные пусты или содержат символы отличные от цифр." << std::endl;
            WaitForAnyKey();
            return nullptr;
        }

        auto *find_book = library_->FindBook(std::stoi(user_input));

        if (find_book == nullptr) {
            std::cerr << "Книга не была найдена -- попробуйте снова с другими данными." << std::endl;
            WaitForAnyKey();
            return nullptr;
        }

        return find_book;
    } else {
        PrintBooks();

        std::cout << "Введите номер книги: ";
        std::getline(std::cin, user_input);

        if (user_input.empty() || !CheckIsNumeric(user_input)) {
            std::cerr << "Введённые данные пусты или содержат символы отличные от цифр." << std::endl;
            WaitForAnyKey();
            return nullptr;
        }

        user_input_int = std::stoi(user_input);

        if ((user_input_int < 0) || (user_input_int >= library_->GetNumberOfBooks())) {
            std::cerr << "Введённые данные меньше ноля или больше количества книг." << std::endl;
            WaitForAnyKey();
            return nullptr;
        }

        auto *find_book_by_index = library_->FindBookByIndex(user_input_int - 1);

        if (find_book_by_index == nullptr) {
            std::cerr << "Книга не была найдена -- попробуйте снова с другими данными." << std::endl;
            WaitForAnyKey();
            return nullptr;
        }

        return find_book_by_index;
    }
}

Reader *Console::ChooseReader() {
    std::string string_to_choose_a_method =
        "Вы хотите ввести ID читателя? Если нет, то Вам будет предложено выбрать из списка. Y/n";
    std::string user_input;
    int user_input_int;

    if (CheckUserWish(string_to_choose_a_method)) {
        std::cout << "Введите ID пользователя: ";
        std::getline(std::cin, user_input);

        if (user_input.empty() || !CheckIsNumeric(user_input)) {
            std::cerr << "Введённые данные пусты или содержат символы отличные от цифр." << std::endl;
            WaitForAnyKey();
            return nullptr;
        }

        auto *find_reader = library_->FindReader(std::stoi(user_input));

        if (find_reader == nullptr) {
            std::cerr << "Читатель не был найден -- попробуйте снова с другими данными." << std::endl;
            WaitForAnyKey();
            return nullptr;
        }

        return find_reader;
    } else {
        PrintReaders();

        std::cout << "Введите номер читателя: ";
        std::getline(std::cin, user_input);

        if (user_input.empty() || !CheckIsNumeric(user_input)) {
            std::cerr << "Введённые данные пусты или содержат символы отличные от цифр." << std::endl;
            WaitForAnyKey();
            return nullptr;
        }

        user_input_int = std::stoi(user_input);

        if ((user_input_int < 0) || (user_input_int >= library_->GetNumberOfReaders())) {
            std::cerr << "Введённые данные меньше ноля или больше количества читателей." << std::endl;
            WaitForAnyKey();
            return nullptr;
        }

        auto *find_reader_by_index = library_->FindReaderByIndex(user_input_int - 1);

        if (find_reader_by_index == nullptr) {
            std::cerr << "Читатель не был найден -- попробуйте снова с другими данными." << std::endl;
            WaitForAnyKey();
            return nullptr;
        }

        return find_reader_by_index;
    }
}

void Console::IssueBook() {
    if (DoesLibraryExist()) {
        return;
    }

    std::string string_to_check_a_wish = "Вы уверены что хотите выдать книгу? Y/n";

    while (CheckUserWish(string_to_check_a_wish)) {
        auto *book = ChooseBook();
        auto *reader = ChooseReader();

        ClearScreen();

        if (library_->IssueBook(book->GetBid(), reader->GetRid())) {
            std::cout << "Успех!" << std::endl;
        } else {
            std::cout << "Провал!" << std::endl;
        }
    }
}

void Console::ReturnABook() {
    if (DoesLibraryExist()) {
        return;
    }

    std::string string_to_check_a_wish = "Вы уверены что хотите вернуть книгу? Y/n";

    while (CheckUserWish(string_to_check_a_wish)) {
        auto *book = ChooseBook();
        auto *reader = ChooseReader();

        ClearScreen();

        if (library_->ReturnBook(book->GetBid(), reader->GetRid())) {
            std::cout << "Успех!" << std::endl;
        } else {
            std::cout << "Провал!" << std::endl;
        }
    }
}

void Console::ClearScreen() {
    CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;
    DWORD count;
    COORD home_coords = {0, 0};
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (handle == INVALID_HANDLE_VALUE) {
        return;
    }

    if (GetConsoleScreenBufferInfo(handle, &console_screen_buffer_info) == 0) {
        return;
    }

    DWORD cell_count = console_screen_buffer_info.dwSize.X * console_screen_buffer_info.dwSize.Y;

    if (FillConsoleOutputCharacter(handle, static_cast<TCHAR>(' '), cell_count, home_coords, &count) == 0) {
        return;
    }

    if (FillConsoleOutputAttribute(handle, console_screen_buffer_info.wAttributes, cell_count, home_coords, &count)
        == 0) {
        return;
    }

    SetConsoleCursorPosition(handle, home_coords);
}

void Console::WaitForAnyKey(const TCHAR *prompt) {
    TCHAR tchar;
    DWORD mode;
    DWORD count;
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);

    if (prompt == nullptr) {
        prompt = TEXT("Нажмите любую клавишу для продолжения...\n");
    }

    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), prompt, lstrlen(prompt), &count, nullptr);

    GetConsoleMode(handle, &mode);
    SetConsoleMode(handle, 0);

    WaitForSingleObject(handle, INFINITE);

    ReadConsole(handle, &tchar, 1, &count, nullptr);

    SetConsoleMode(handle, mode);
}
