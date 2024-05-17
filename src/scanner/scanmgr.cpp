#include <iostream>
#include "../../include/scanner.h"
#include "../../include/scanmgr.h"

namespace Scanner
{

    ScanMgr::ScanMgr()
    {
    }

    // void ScanMgr::processFile(const std::string &filename)
    // {

    void ScanMgr::processFile()
    {
        // Hardcoded file path
        std::string filename = "/home/thamindu/CSE/WinZigC-Compiler/tests/frontend/programs/winzig_02";

        std::ifstream file(filename);
        if (!file)
        {
            std::cerr << "Cannot open file: " << filename << std::endl;
            return;
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();

        // for (const auto &line : lines)
        // {
        //     std::cout << "Line: " << line << std::endl;
        // }

        // Create an instance of Scanner with input lines
        Scanner scanner(lines);

        // Tokenize the input lines
        std::vector<Token *> tokens = scanner.tokenize();

        for (Token *token : tokens)
        {
            std::cout << "Token Type: " << token->getType() << ", Data: " << token->getData() << std::endl;
        }

        // Cleanup memory
        for (Token *token : tokens)
        {
            delete token;
        }
    }

    ScanMgr::~ScanMgr()
    {
        // Additional cleanup can be done here if needed
    }
}
