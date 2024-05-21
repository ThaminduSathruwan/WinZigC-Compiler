#ifndef WINZIGCMGR_H
#define WINZIGCMGR_H

#include <iostream>
#include "../../include/scanmgr.h"
#include "../../include/parsemgr.h"
#include "../../include/compilemgr.h"

namespace WinZigCC
{
    class WinZigCMgr
    {
    public:
        WinZigCMgr();
        bool run();

    private:
        Compiler::CompileMgr compileMgr;
        const std::string &program;
    };
}

#endif // !WINZIGCMGR_H
