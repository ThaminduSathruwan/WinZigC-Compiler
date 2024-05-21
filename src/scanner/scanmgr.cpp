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

    void ScanMgr::runScanner()
    {
        Scanner scanner(lines);

        // Tokenize the input lines
        scanner.tokenize();
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

    ScanMgr::~ScanMgr()
    {
        // Destructor - clean up tokens
        for (Token *token : tokens)
        {
            delete token;
        }
    }
}
