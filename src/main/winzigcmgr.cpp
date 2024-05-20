#include <iostream>
#include "../../include/scanmgr.h"
#include "../../include/parsemgr.h"
#include "../../include/compilemgr.h"
#include "../../include/options.h"
#include "winzigcmgr.h"

template <typename T>
T Singleton<T>::instance;
template class Singleton<Options::OptionsMgr>;

namespace WinZigCC
{
    WinZigCMgr::WinZigCMgr() : program(Options::OptionsMgr::Instance().getInputFileName())
    {
    }

    void WinZigCMgr::run()
    {
        // Call the processFile method
        Scanner::ScanMgr::Instance().processFile(program);
        Scanner::ScanMgr::Instance().runScanner();
        Parser::ParseMgr::Instance().runParser();
        if (Options::OptionsMgr::Instance().isPrintAST())
        {
            Parser::ParseMgr::Instance().printAST(std::cout);
        }
    }
}
