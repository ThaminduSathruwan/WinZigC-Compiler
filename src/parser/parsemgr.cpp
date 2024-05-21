#include <iostream>
#include "../../include/parser.h"
#include "../../include/parsemgr.h"
#include "../../include/scanmgr.h"

namespace Parser
{

    bool ParseMgr::runParser()
    {
        auto tokens = Scanner::ScanMgr::Instance().getTokens();
        Parser parser(tokens);
        parser.parse();

        return !printErrors(std::cerr);
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

    void ParseMgr::addError(Scanner::Token *token, SyntaxErrorType type)
    {
        errors.insert(SyntaxError(token, type));
    }

    bool ParseMgr::printErrors(std::ostream &os)
    {
        if (errors.size() > 0)
        {
            for (auto it = errors.begin(); it != errors.end(); it++)
            {
                SyntaxError error = *it;
                os << error << std::endl;
                if (error.getType() != SyntaxErrorType::UNEXPECTED_EOF && error.getToken() != nullptr)
                {
                    os.width(ERROR_LINE_NUM_WIDTH);
                    os << error.getToken()->getLocation().second + 1;
                    os.width(0);
                    os << " | " << Scanner::ScanMgr::Instance().getLineByNum(error.getToken()->getLocation().second) << std::endl;
                    os.width(ERROR_LINE_NUM_WIDTH);
                    os << " ";
                    os.width(0);
                    os << " | ";
                    for (int i = 0; i < (int)error.getToken()->getLocation().first; ++i)
                    {
                        os << " ";
                    }
                    os << "^";
                    for (int i = 1; i < (int)error.getToken()->getData().size(); ++i)
                    {
                        os << "~";
                    }
                    os << std::endl;
                }
            }
            return true;
        }
        return false;
    }

}
