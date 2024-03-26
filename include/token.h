#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <utility>

namespace Scanner
{

    typedef enum
    {
        IDENTIFIER,
        INTEGER,
        WHITE_SPACE,
        CHAR,
        STRING,
        COMMENT,
        PUNCTUATION
    } TokenType;

    typedef std::pair<unsigned int, unsigned int> Location;

    class Token
    {
    public:
        Token(TokenType type, std::string data, unsigned int hPos, unsigned int vPos);
        TokenType getType();
        std::string getData();
        Location getLocation();

    private:
        TokenType type;
        std::string data;
        unsigned int hPos;
        unsigned int vPos;
    };

}

#endif // !TOKEN_H
