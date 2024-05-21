#include <iostream>
#include "../../include/scanner.h"
#include "../../include/scanmgr.h"

namespace Scanner
{

    void ScanMgr::processFile(const std::string &filename)
    {

        std::ifstream file(filename);
        if (!file)
        {
            std::cerr << "Cannot open file: " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }

    bool ScanMgr::runScanner()
    {
        Scanner scanner(lines);

        // Tokenize the input lines
        scanner.tokenize();

        return !printErrors(std::cerr);
    }

    const std::vector<Token *> &
    ScanMgr::getTokens()
    {
        return tokens;
    }

    void ScanMgr::addToken(Token *token)
    {
        tokens.push_back(token);
    }

    std::string ScanMgr::getLineByNum(int lineNumber)
    {
        return lines[lineNumber];
    }

    void ScanMgr::printTokens(std::ostream &os)
    {
        for (Token *token : tokens)
        {
            os << *token << std::endl;
        }
    }

    void ScanMgr::addError(Token *token, Parser::SyntaxErrorType type)
    {
        errors.insert(Parser::SyntaxError(token, type));
    }

    bool ScanMgr::printErrors(std::ostream &os)
    {
        if (errors.size() > 0)
        {
            for (auto it = errors.begin(); it != errors.end(); it++)
            {
                Parser::SyntaxError error = *it;
                os << error << std::endl;
                if (error.getType() != Parser::SyntaxErrorType::UNEXPECTED_EOF && error.getToken() != nullptr)
                {
                    os.width(ERROR_LINE_NUM_WIDTH);
                    os << error.getToken()->getLocation().second + 1;
                    os.width(0);
                    os << " | " << getLineByNum(error.getToken()->getLocation().second) << std::endl;
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

    ScanMgr::~ScanMgr()
    {
        // Destructor - clean up tokens
        for (Token *token : tokens)
        {
            delete token;
        }
    }
}
