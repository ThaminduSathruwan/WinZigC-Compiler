#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

template <typename T>
class Singleton
{
public:
    static T &Instance()
    {
        if (!instance)
        {
            instance = new T();
        }
        return instance;
    }

private:
    static T instance;
};

#endif // !SINGLETON_H
