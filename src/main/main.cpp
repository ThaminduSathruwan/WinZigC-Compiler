#include <iostream>
#include <sstream>
#include "winzigcmgr.h"

int main()
{
    std::stringstream progStream;
    progStream << "Welcome to the WinZigC compiler!" << std::endl;
    std::string program = progStream.str();

    WinZigCC::WinZigCMgr winZigCMgr(program);
    winZigCMgr.run();

    return 0;
}
