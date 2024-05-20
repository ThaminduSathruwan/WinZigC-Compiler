#include <iostream>
#include <utility>

#include "../../include/token.h"
#include "../../include/syntax_error.h"

namespace Parser
{

    SyntaxError::SyntaxError(Scanner::Token *token, std::string message, bool end) : token(token), message(message), end(end)
    {
    }

    SyntaxError::~SyntaxError()
    {
    }

    std::ostream &operator<<(std::ostream &os, const SyntaxError &error)
    {
        Scanner::Location loc = error.token->getLocation();
        os << "Syntax Error: " << error.message << " at line " << loc.first << " column " << loc.second << std::endl;
        return os;
    }

}
