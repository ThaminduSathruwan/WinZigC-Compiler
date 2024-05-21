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

        if (printErrors())

            return false;

        return true;
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

    void ScanMgr::addError(Token *token, bool end)
    {
        errors.insert(Parser::SyntaxError(token, end));
    }

    bool ScanMgr::printErrors()
    {
        if (errors.size() > 0)
        {
            std::cerr << "Token errors " << std::endl;
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
