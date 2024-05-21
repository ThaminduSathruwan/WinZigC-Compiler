#include <iostream>
#include <utility>

#include "../../include/token.h"
#include "../../include/syntax_error.h"

namespace Parser
{

    SyntaxError::SyntaxError(Scanner::Token *token, SyntaxErrorType type) : token(token), type(type)
    {
    }

    SyntaxError::~SyntaxError()
    {
    }

    std::ostream &operator<<(std::ostream &os, const SyntaxError &error)
    {
        Scanner::Location loc = error.token->getLocation();
        os << "Syntax Error: ";
        switch (error.type)
        {
        case SyntaxErrorType::UNEXPECTED_EOF:
            os << "Unexpected end of file";
            return os;
        case SyntaxErrorType::UNEXPECTED_TOKEN:
            os << "Unexpected token at line " << loc.second + 1 << " column " << loc.first + 1;
            return os;
        case SyntaxErrorType::UNMATCHED_TOKEN:
            os << "Unmatched token at line " << loc.second + 1 << " column " << loc.first + 1;
            return os;
        default:
            os << "Unknown error";
            return os;
        }
    }

    Scanner::Token *SyntaxError::getToken()
    {
        return token;
    }

    SyntaxErrorType SyntaxError::getType() const
    {
        return type;
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
