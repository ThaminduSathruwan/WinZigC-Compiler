#include <iostream>
#include "../include/scanner.h"
#include "../include/token.h"

namespace Scanner
{
    Token::Token(TokenType type, std::string data, unsigned int hPos, unsigned int vPos)
        : type(type), data(std::move(data)), hPos(hPos), vPos(vPos) {}

    // Get the type of the token
    TokenType Token::getType()
    {
        return type;
    }

    // Get the data associated with the token
    std::string Token::getData()
    {
        return data;
    }

    // Get the location of the token
    Location Token::getLocation()
    {
        return {hPos, vPos};
    }
}
