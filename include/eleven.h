#pragma once

#include <iostream>
#include <string>
#include <initializer_list>
using namespace std;

class Eleven {
public:
    Eleven();
    Eleven(const size_t& arrSize, unsigned char defaltValue = 0);
    Eleven(const initializer_list <unsigned char> &initialValues);
    Eleven(const string &sourceStr);
    Eleven(const Eleven& other);
    Eleven(Eleven&& other) noexcept;
    virtual ~Eleven() noexcept;

    Eleven add(const Eleven& other);
    Eleven minus(const Eleven& other);
    Eleven copy() const;
    
    bool eq(const Eleven& other) const;
    bool lq(const Eleven& other) const;
    bool gq(const Eleven& other) const;


    string to_str() const;
    ostream& print(ostream& outputStream);

private:
    size_t arrSize;
    unsigned char* dataArr;

    void rem_zeros();
};