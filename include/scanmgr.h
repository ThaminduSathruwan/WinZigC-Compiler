#ifndef SCANMGR_H
#define SCANMGR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "scanner.h"
#include "singleton.h"

namespace Scanner
{
    class ScanMgr : public Singleton<ScanMgr>
    {
    public:
        void processFile(const std::string &filename);
        void runScanner();
        const std::vector<Token *> &getTokens();
        void addToken(Token *token);
        std::string getLineByNum(int lineNumber);
        void printTokens(std::ostream &os);
        ~ScanMgr();
        friend class Singleton<ScanMgr>;

    private:
        ScanMgr() = default;
        std::vector<Token *> tokens;
        std::vector<std::string> lines;
    };
}

#endif // !SCANMGR_H
