#include <iostream>
#include "../../include/parser.h"
#include "../../include/parsemgr.h"
#include "../../include/scanmgr.h"

namespace Parser
{

    void ParseMgr::runParser()
    {
        auto tokens = Scanner::ScanMgr::Instance().getTokens();
        Parser parser(tokens);
        parser.parse();
    }

    void ParseMgr::printAST(std::ostream &os)
    {
        os << ast;
    }

    void ParseMgr::build_tree(ASTNodeType type, int childrenCnt)
    {
        ast.build_tree(type, childrenCnt);
    }

    void ParseMgr::build_tree(std::string str, bool identifier)
    {
        ast.build_tree(str, identifier);
    }

    void ParseMgr::build_tree(int32_t integer)
    {
        ast.build_tree(integer);
    }

    void ParseMgr::build_tree(char character)
    {
        ast.build_tree(character);
    }

    void ParseMgr::finalizeAST()
    {
        ast.finalize();
    }

}
