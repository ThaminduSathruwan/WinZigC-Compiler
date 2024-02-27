#ifndef SCANMGR_H
#define SCANMGR_H

#include <iostream>
#include "scanner.h"

namespace Scanner
{
    class ScanMgr
    {
    public:
        ScanMgr();

    private:
        Scanner scanner;
    };
}

#endif // !SCANMGR_H
