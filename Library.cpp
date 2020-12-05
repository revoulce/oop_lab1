//
// Created by letih on 12/3/2020.
//

#include "Library.hpp"

Library::Library(LinkedList<Book> &books, LinkedList<Reader> &readers) {
    books_ = new LinkedList<Book>(books);
    readers_ = new LinkedList<Reader>(readers);
}

LinkedList<Book> *Library::GetBooks() const {
    return books_;
}

int Library::GetNumberOfBooks() const {
    return books_->Size();
}

bool Library::RemoveBook(Book &book) {
    return books_->DeleteNodeByContent(book);
}

void Library::RemoveBooks() {
    books_->DeleteList();
}

int Library::GetNumberOfReaders() const {
    return readers_->Size();
}

LinkedList<Reader> *Library::GetReaders() const {
    return readers_;
}

bool Library::RemoveReader(Reader &reader) {
    return readers_->DeleteNodeByContent(reader);
}

void Library::RemoveReaders() {
    readers_->DeleteList();
}

void Library::AddBook(Book &book) {
    books_->PushBack(book);
}

void Library::AddReader(Reader &reader) {
    readers_->PushBack(reader);
}

bool Library::IssueBook(int bid, int rid) {
    auto *book = FindBook(bid);
    auto *reader = FindReader(rid);

    if (book == nullptr || reader == nullptr) {
        return false;
    }

    if (reader->GetBid() != 0) {
        return false;
    }

    book->SetIsIssued(true);
    reader->SetBid(bid);

    return true;
}

bool Library::ReturnBook(int bid, int rid) {
    auto *book = FindBook(bid);
    auto *reader = FindReader(rid);

    if (book == nullptr || reader == nullptr) {
        return false;
    }

    if (reader->GetBid() != bid || !book->GetIsIssued()) {
        return false;
    }

    book->SetIsIssued(false);
    reader->SetBid(0);

    return true;
}

Book *Library::FindBook(int bid) {
    auto *books = books_->GetIteratorAtHead();
    auto *book = books->StepForward();

    while (book != nullptr) {
        if (book->data.GetBid() == bid) {
            break;
        }

        book = books->StepForward();
    }

    if (book == nullptr) {
        return nullptr;
    }

    return &book->data;
}

Book *Library::FindBookByIndex(int index) {
    return books_->GetNodeDataByIndex(index);
}

Reader *Library::FindReader(int rid) {
    auto *readers = readers_->GetIteratorAtHead();
    auto *reader = readers->StepForward();

    while (reader != nullptr) {
        if (reader->data.GetRid() == rid) {
            break;
        }

        reader = readers->StepForward();
    }

    if (reader == nullptr) {
        return nullptr;
    }

    return &reader->data;
}

Reader *Library::FindReaderByIndex(int index) {
    return readers_->GetNodeDataByIndex(index);
}

Library &Library::operator=(const Library &library) {
    if (this == &library) {
        return *this;
    }

    delete books_;
    delete readers_;

    books_ = new LinkedList<Book>(*(library.books_));
    readers_ = new LinkedList<Reader>(*(library.readers_));

    return *this;
}
