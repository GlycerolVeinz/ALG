#include <iostream>

int GLOBAL = 1;

void uvw()
{
    std::cout << GLOBAL++ << std::endl;
    return;
}

int main()
{
    int i = 0;
    while (i < 10)
    {
        for (int j = i; j < 13; j++)
        {
            uvw();
        }
        i++;
    }

    return 0;
}
