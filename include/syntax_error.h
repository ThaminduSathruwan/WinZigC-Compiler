#ifndef SYNTACTIC_ERROR_H
#define SYNTACTIC_ERROR_H

#include <iostream>
#include <string>

#include "token.h"

#define ERROR_LINE_NUM_WIDTH 10

namespace Parser
{

    typedef enum
    {
        UNEXPECTED_TOKEN,
        UNEXPECTED_EOF,
        UNMATCHED_TOKEN
    } SyntaxErrorType;

    class SyntaxError
    {
    public:
        SyntaxError(Scanner::Token *token, SyntaxErrorType type = SyntaxErrorType::UNEXPECTED_TOKEN);
        ~SyntaxError();
        Scanner::Token *getToken();
        SyntaxErrorType getType() const;
        bool operator<(const SyntaxError &error) const;
        bool operator==(const SyntaxError &error) const;
        friend std::ostream &operator<<(std::ostream &os, const SyntaxError &error);

    private:
        Scanner::Token *token;
        SyntaxErrorType type;
    };

}

#endif // !SYNTACTIC_ERROR_H
