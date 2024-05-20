#include <iostream>
#include <utility>

#include "../../include/token.h"
#include "../../include/syntax_error.h"

namespace Parser
{

    SyntaxError::SyntaxError(Scanner::Token *token, bool end) : token(token), end(end)
    {
    }

    SyntaxError::~SyntaxError()
    {
    }

    std::ostream &operator<<(std::ostream &os, const SyntaxError &error)
    {
        Scanner::Location loc = error.token->getLocation();
        if (error.end)
        {
            os << "Syntax Error: " << "Unexpected end of file";
            return os;
        }
        os << "Syntax Error: " << "Unexpected token at line " << loc.second + 1 << " column " << loc.first + 1;
        return os;
    }

    Scanner::Token *SyntaxError::getToken()
    {
        return token;
    }

    bool SyntaxError::isEnd() const
    {
        return end;
    }

    bool SyntaxError::operator<(const SyntaxError &error) const
    {
        Scanner::Location loc1 = token->getLocation();
        Scanner::Location loc2 = error.token->getLocation();
        if (loc1.second < loc2.second)
            return true;
        else if (loc1.second == loc2.second)
            return loc1.first < loc2.first;
        return false;
    }

    bool SyntaxError::operator==(const SyntaxError &error) const
    {
        return token == error.token;
    }

}
