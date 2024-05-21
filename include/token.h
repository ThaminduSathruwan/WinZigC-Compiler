#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <utility>

namespace Scanner
{

    typedef enum
    {
        NEW_LINE,
        PROGRAM,
        VAR,
        CONST,
        TYPE,
        FUNCTION,
        RETURN,
        BEGIN,
        END,
        SWAP,
        ASSIGN,
        OUTPUT,
        IF,
        THEN,
        ELSE,
        WHILE,
        DO,
        CASE,
        OF,
        CASE_DOTS,
        OTHERWISE,
        REPEAT,
        UNTIL,
        FOR,
        LOOP,
        POOL,
        EXIT,
        LESS_THAN,
        LESS_THAN_EQUAL,
        GREATER_THAN,
        GREATER_THAN_EQUAL,
        EQUAL,
        NOT_EQUAL,
        MOD,
        AND,
        OR,
        NOT,
        READ,
        SUCC,
        PRED,
        CHR,
        ORD,
        EOF_TOKEN,
        COLON,
        SEMICOLON,
        COMMA,
        PERIOD,
        LEFT_PAREN,
        RIGHT_PAREN,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        IDENTIFIER,
        INTEGER,
        WHITE_SPACE,
        CHAR,
        STRING,
        SINGLE_LINE_COMMENT,
        MULTI_LINE_COMMENT,
        ERROR
    } TokenType;

    typedef std::pair<unsigned int, unsigned int> Location;

    class Token
    {
    public:
        Token(TokenType type, std::string data, unsigned int hPos, unsigned int vPos);
        TokenType getType();
        std::string getData();
        Location getLocation();
        friend std::ostream &operator<<(std::ostream &os, const Token &token);

    private:
        TokenType type;
        std::string data;
        unsigned int hPos;
        unsigned int vPos;
    };

    std::string tokenTypeToString(TokenType type);

}

#endif // !TOKEN_H
