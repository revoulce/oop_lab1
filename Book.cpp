//
// Created by letih on 12/3/2020.
//

#include "Book.hpp"

Book::Book() {
    year_ = 0;
    bid_ = 0;
    is_issued_ = false;
}

Book::Book(std::string& author, std::string& title, std::string& publisher, int year, int bid, bool is_issued)
    : author_(author), title_(title), publisher_(publisher), year_(year), bid_(bid), is_issued_(is_issued) {}

Book::Book(std::string* parameters) {
    author_ = parameters[0];
    title_ = parameters[1];
    year_ = std::stoi(parameters[2]);
    publisher_ = parameters[3];
    bid_ = std::stoi(parameters[4]);
    is_issued_ = false;
}

Book::Book(const Book& other_book) {
    author_ = other_book.author_;
    title_ = other_book.title_;
    year_ = other_book.year_;
    publisher_ = other_book.publisher_;
    bid_ = other_book.bid_;
    is_issued_ = other_book.is_issued_;
}

int Book::GetBid() const {
    return bid_;
}

bool Book::GetIsIssued() const {
    return is_issued_;
}

void Book::SetIsIssued(bool is_issued) {
    is_issued_ = is_issued;
}

Book& Book::operator=(const Book& book) {
    if (this == &book) {
        return *this;
    }

    author_ = book.author_;
    title_ = book.title_;
    year_ = book.year_;
    publisher_ = book.publisher_;
    bid_ = book.bid_;
    is_issued_ = book.is_issued_;

    return *this;
}

bool Book::operator==(const Book& book) {
    bool expression = title_ == book.title_;
    expression = expression && (title_ == book.title_);
    expression = expression && (year_ == book.year_);
    expression = expression && (publisher_ == book.publisher_);
    expression = expression && (bid_ == book.bid_);
    expression = expression && (is_issued_ == book.is_issued_);

    return expression;
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << "Автор: " << book.author_ << std::endl;
    os << "Название: " << book.title_ << std::endl;
    os << "Год: " << book.year_ << std::endl;
    os << "Издатель: " << book.publisher_ << std::endl;
    os << "BID: " << book.bid_ << std::endl;

    if (book.is_issued_) {
        os << "Выдана: да";
    } else {
        os << "Выдана: нет";
    }

    return os;
}
