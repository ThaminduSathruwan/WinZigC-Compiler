#ifndef COMPILEMGR_H
#define COMPILEMGR_H

#include <iostream>
#include "compiler.h"

namespace Compiler
{
    class CompileMgr
    {
    public:
        CompileMgr();

    private:
        Compiler compiler;
    };
}

#endif // !COMPILEMGR_H
