#ifndef PARSEMGR_H
#define PARSEMGR_H

#include <iostream>
#include "parser.h"

namespace Parser
{
    class ParseMgr
    {
    public:
        void runParser(std::vector<Scanner::Token *> &tokens);
    };
}

#endif // !PARSEMGR_H
