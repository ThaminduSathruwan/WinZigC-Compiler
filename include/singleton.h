#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

template <typename T>
class Singleton
{
public:
    static T &Instance()
    {
        return instance;
    }

private:
    static T instance;
};

#endif // !SINGLETON_H
