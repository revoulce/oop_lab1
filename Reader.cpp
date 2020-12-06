//
// Created by letih on 12/3/2020.
//

#include "Reader.hpp"

Reader::Reader(int rid, int bid) : rid_(rid), bid_(bid) {}

int Reader::GetRid() const {
    return rid_;
}

int Reader::GetBid() const {
    return bid_;
}

void Reader::SetBid(int bid) {
    bid_ = bid;
}

bool Reader::operator==(const Reader& reader) {
    return ((rid_ == reader.rid_) && (bid_ == reader.bid_));
}

std::ostream& operator<<(std::ostream& os, const Reader& reader) {
    os << "RID: " << reader.rid_;
    os << ", BID: " << reader.bid_;
    return os;
}
