#include <iostream>
#include <string>


void printchar(int n, char c)
{
    for(int i = 0; i < n; ++i)
    {
        std::cout << c;
    }
}

int main()
{
    int n = 0;
    std::cin >> n;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            printchar(i-j+1, '*');
            printchar(n-i, ' ');
        }
        std::cout << '*' << std::endl;
    }
}

/*
+
++  +
+++ ++ +
*/