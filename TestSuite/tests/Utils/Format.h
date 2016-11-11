//
// Created by Llikdowk on 11-Nov-16.
//

#pragma once
#include <iostream>

class Hex {
public:
    explicit Hex(int n) : number(n) {}
    operator int() const { return number; }
    bool operator==(const Hex& x) const { return number == x; }
    bool operator!=(const Hex& x) const { return number != x; }
private:
    int number;
};

class Col : public Hex {
public:
    explicit Col(int n) : Hex(n) {}
};

std::ostream& operator<<(std::ostream& os, const Hex& hex);
std::ostream& operator<<(std::ostream& os, const Col& col);
