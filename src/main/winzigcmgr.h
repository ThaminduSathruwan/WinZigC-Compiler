#ifndef WINZIGCMGR_H

#include <iostream>
#include "../../include/scanmgr.h"
#include "../../include/parsemgr.h"
#include "../../include/compilemgr.h"

namespace WinZigCC
{
    class WinZigCMgr
    {
    public:
        WinZigCMgr(const std::string &program);
        void run();

    private:
        Scanner::ScanMgr scanMgr;
        Parser::ParseMgr parseMgr;
        Compiler::CompileMgr compileMgr;
        const std::string &program;
    };
}

#endif // !WINZIGCMGR_H
