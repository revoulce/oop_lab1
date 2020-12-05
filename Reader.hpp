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

    [[nodiscard]] int GetRid() const;

    [[nodiscard]] int GetBid() const;

    void SetBid(int bid);

    bool operator==(const Reader &reader);

    friend std::ostream &operator<<(std::ostream &os, const Reader &reader);

  private:
    int rid_;
    int bid_;
};

#endif//OOP_LAB1__READER_HPP_
