#ifndef SCANMGR_H
#define SCANMGR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "scanner.h"

namespace Scanner
{
    class ScanMgr
    {
    public:
        ScanMgr();
        // void processFile(const std::string &filename);
        void processFile();
        ~ScanMgr();

    private:
        Scanner scanner(const std::vector<std::string> &inputLines);
    };
}

#endif // !SCANMGR_H
