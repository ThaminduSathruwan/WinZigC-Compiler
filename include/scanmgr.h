#ifndef SCANMGR_H
#define SCANMGR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include "scanner.h"
#include "singleton.h"
#include "syntax_error.h"

namespace Scanner
{
    class ScanMgr : public Singleton<ScanMgr>
    {
    public:
        void processFile(const std::string &filename);
        bool runScanner();
        const std::vector<Token *> &getTokens();
        void addToken(Token *token);
        std::string getLineByNum(int lineNumber);
        void printTokens(std::ostream &os);
        void addError(Token *token, bool end = false);
        ~ScanMgr();
        friend class Singleton<ScanMgr>;

    private:
        ScanMgr() = default;
        std::vector<Token *> tokens;
        std::vector<std::string> lines;
        std::set<Parser::SyntaxError> errors;
        bool printErrors();
    };
}

#endif // !SCANMGR_H
