#include <iostream>
#include "../../include/scanmgr.h"
#include "../../include/parsemgr.h"
#include "../../include/compilemgr.h"
#include "winzigcmgr.h"

namespace WinZigCC
{
    WinZigCMgr::WinZigCMgr(const std::string &program)
        : program(program)
    {
        std::cout << "Welcome to the WinZigC compiler!" << std::endl;
    }

    void WinZigCMgr::run()
    {
        // Create an instance of ScanMgr
        Scanner::ScanMgr scanManager;

        // Call the processFile method
        scanManager.processFile();
    }
}
