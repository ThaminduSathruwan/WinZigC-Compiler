#ifndef PARSEMGR_H
#define PARSEMGR_H

#include <iostream>
#include "parser.h"

namespace Parser
{
    class ParseMgr
    {
    public:
        ParseMgr();

    private:
        Parser parser;
    };
}

#endif // !PARSEMGR_H
