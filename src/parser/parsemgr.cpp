#include <iostream>
#include "../../include/parser.h"
#include "../../include/parsemgr.h"

namespace Parser
{

    void ParseMgr::runParser(std::vector<Scanner::Token *> &tokens)
    {
        Parser parser(tokens);
        parser.parse();
    }

}
