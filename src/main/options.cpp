#include <iostream>
#include "../../include/options.h"

namespace Options
{

    bool OptionsMgr::parseOptions()
    {
        for (int i = 1; i < argc; i++)
        {
            std::string arg = std::string(argv[i]);
            if (arg == std::string("-ast"))
            {
                printAST = true;
            }
            else if (arg.length() > 0 && arg[0] != '-')
            {
                inputFileName = arg;
            }
            else if (arg.length() > 0)
            {
                std::cerr << "Unknown option: " << arg << std::endl;
                return false;
            }
        }

        if (inputFileName.length() == 0)
        {
            std::cerr << "No input file specified" << std::endl;
            return false;
        }

        return true;
    }

    bool OptionsMgr::isPrintAST()
    {
        return printAST;
    }

    std::string &OptionsMgr::getInputFileName()
    {
        return inputFileName;
    }

    bool OptionsMgr::setOptions(int argc, char *argv[])
    {
        this->argc = argc;
        this->argv = argv;
        return parseOptions();
    }

}
