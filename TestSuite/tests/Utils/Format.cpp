//
// Created by Llikdowk on 11-Nov-16.
//

#include "Format.h"
#include <Color.h>

std::ostream& operator<<(std::ostream& os, const Hex& hex) {
    os << "0x" << std::hex << (int)hex;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Col& col) {
    Color c = Color::decode(static_cast<uint32_t>(col));
    os << "(r,g,b,a) = "
       << "(" << static_cast<int>(c.r)
       << ", " << static_cast<int>(c.g)
       << ", " << static_cast<int>(c.b)
       << ", " << static_cast<int>(c.a)
       << ")" << " ";
    return os;
}