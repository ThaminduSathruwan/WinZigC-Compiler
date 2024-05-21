#include <iostream>
#include <sstream>
#include "winzigcmgr.h"
#include "../../include/options.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <program>" << std::endl;
        return 1;
    }

    if (!Options::OptionsMgr::Instance().setOptions(argc, argv))
        return 1;

    WinZigCC::WinZigCMgr winZigCMgr;

    if (!winZigCMgr.run())
        return 1;

    return 0;
}
