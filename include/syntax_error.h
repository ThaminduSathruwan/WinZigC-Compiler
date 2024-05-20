#ifndef SYNTACTIC_ERROR_H
#define SYNTACTIC_ERROR_H

#include <iostream>
#include <string>

#include "token.h"

namespace Parser
{
    class SyntaxError
    {
    public:
        SyntaxError(Scanner::Token *token, std::string message, bool end = false);
        ~SyntaxError();
        friend std::ostream &operator<<(std::ostream &os, const SyntaxError &error);

    private:
        Scanner::Token *token;
        std::string message;
        bool end;
    };
}

#endif // !SYNTACTIC_ERROR_H
