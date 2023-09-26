#include <iostream>

int GLOBAL = 1;

void uvw()
{
    std::cout << GLOBAL++ << std::endl;
    return;
}

int main()
{
    int n = 5;
    for (int k = 0; k < n - 1; k++)
    {
        for (int j = 0; j < 2 * k; j++)
        {
            uvw();
        }
    }

    return 0;
}
