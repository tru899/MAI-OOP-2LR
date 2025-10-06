#include <iostream>
#include "../include/eleven.h"

using namespace std;

void Eleven::rem_zeros() {
    ssize_t not_zero = arrSize - 1;
    while (not_zero > 0 && dataArr[not_zero] == 0) {
        --not_zero;
    }

    size_t new_size = not_zero + 1;
    //if all 0 -> 0
    if (new_size == arrSize) {
        return;
    }
    //sdgiv not_zero to start
    unsigned char* new_arr = new unsigned char[new_size];
    for (size_t i = 0; i < new_size; ++i) {
        new_arr[i] = dataArr[i];
    }
    delete[] dataArr;
    dataArr = new_arr;
    arrSize = new_size;
}

Eleven::Eleven() : arrSize(0), dataArr(nullptr) {}

Eleven::Eleven(const size_t& arrSize, unsigned char defaltValue) {
    if ((defaltValue > 10) && defaltValue != 'A') {
        throw invalid_argument("error: invalid input\n");
    }

    this->arrSize = arrSize;
    this->dataArr = new unsigned char[arrSize];

    for (size_t i = 0; i < arrSize; ++i) {
        this->dataArr[i] = defaltValue;
    }
    rem_zeros();
}

Eleven::Eleven(const initializer_list <unsigned char> &initialValues) {
    arrSize = initialValues.size();
    dataArr = new unsigned char[arrSize];

    int idx = 0;
    for(const auto& value : initialValues) {
        if (value > 10) {
            throw invalid_argument("error: invalid input\n");
            }
        dataArr[idx++] = value;
    }
    rem_zeros();
}

Eleven::Eleven(const string &sourceStr) {
    if (sourceStr.empty()) {
        throw invalid_argument("error: str is empty\n");
    }

    arrSize = sourceStr.size();
    dataArr = new unsigned char[arrSize];
    for (size_t i = 0; i < arrSize; ++i) {
        char c = sourceStr[arrSize - 1 - i];
        if (c >= '0' && c <= '9') {
            dataArr[i] = c - '0';
        } else if (c == 'A') {
            dataArr[i] = 10;
        } else {
            throw invalid_argument("error: invalid input\n");
        }
    }
    rem_zeros();
}

Eleven::Eleven(const Eleven& other) {
    arrSize = other.arrSize;
    dataArr = new unsigned char[arrSize];

    for (size_t i = 0; i < arrSize; ++i) {
        dataArr[i] = other.dataArr[i];
    }
}

Eleven::Eleven(Eleven&& other) noexcept : arrSize(other.arrSize), dataArr(other.dataArr) {
    other.arrSize = 0;
    other.dataArr = nullptr;
}

Eleven::~Eleven() noexcept {
    if (dataArr != nullptr) {
        delete[] dataArr;
        dataArr = nullptr;
    }
    arrSize = 0;
}

Eleven Eleven::add(const Eleven& other) {
    size_t max_arr = max(arrSize, other.arrSize);
    Eleven res;
    res.arrSize = max_arr + 1;
    res.dataArr = new unsigned char[res.arrSize];

    int carry = 0;
    for (size_t i = 0; i < max_arr; ++i) {
        int summa = carry;
        if (i < arrSize) {
            summa += dataArr[i];
        }
        if (i < other.arrSize) {
            summa += other.dataArr[i];
        }
        res.dataArr[i] = summa % 11;
        carry = summa / 11;
    }
    res.rem_zeros();
    return res;
}

Eleven Eleven::minus(const Eleven& other) {
    if (lq(other)) {
        throw logic_error("error: can't diff\n");
    }
    
    size_t max_arr = max(arrSize, other.arrSize);
    Eleven res;
    res.arrSize = max_arr;
    res.dataArr = new unsigned char[res.arrSize];

    int borrow = 0;
    for (size_t i = 0; i < arrSize; ++i) {
        int diff = dataArr[i] - borrow;
        if (i < other.arrSize) {
            diff -= other.dataArr[i];
        }
        if (diff < 0) {
            diff += 11;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.dataArr[i] = diff;
    }
    res.rem_zeros();
    return res;
}

Eleven Eleven::copy() const
{
    return Eleven(*this);
}

bool Eleven::eq (const Eleven& other) const {
    if (arrSize != other.arrSize) {
        return false;
    }
    for (size_t i = 0; i < arrSize; ++i) {
        if (dataArr[i] != other.dataArr[i]) {
            return false;
        }
    }
    return true;
}

bool Eleven::lq(const Eleven& other) const {
    if (arrSize < other.arrSize) {
        return true;
    }
    if (arrSize > other.arrSize) {
        return false;
    }
    for (size_t i = arrSize; i-- > 0;) {
        if (dataArr[i] < other.dataArr[i]) {
            return true;
        }
        if (dataArr[i] > other.dataArr[i]) {
            return false;
        }
    }
    return false;
}

bool Eleven::gq (const Eleven& other) const {
    return (!eq(other) && !lq(other));
}

string Eleven::to_str() const {
    if (arrSize == 0) {
        return "0";
    }
    string res;
    for (size_t i = arrSize; i-- > 0; ) {
        unsigned char digit = dataArr[i];
        if (digit < 10) {
            res += static_cast<char>('0' + digit);
        } else if (digit == 10) {
            res += 'A';
        } else throw runtime_error("error: invalid input\n");
    }
    return res;
}

ostream& Eleven::print(ostream& os) {
    os << to_str();
    return os;
}
