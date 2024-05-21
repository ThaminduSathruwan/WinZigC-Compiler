#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include "singleton.h"

namespace Options
{
    class OptionsMgr : public Singleton<OptionsMgr>
    {
    public:
        bool isPrintAST();
        bool isPrintTokens();
        std::string &getInputFileName();
        bool setOptions(int argc, char *argv[]);
        friend class Singleton<OptionsMgr>;

    private:
        OptionsMgr() = default;
        int argc;
        char **argv;
        std::string inputFileName;
        bool printAST;
        bool printTokens;
        bool parseOptions();
    };
}

#endif // !OPTIONS_H
