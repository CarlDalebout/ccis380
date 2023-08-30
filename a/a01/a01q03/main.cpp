#include <iostream>
#include <string>

void printarray(int x[], int n)
{
    std::string dir = "";
    for(int i = 0; i < n; ++i)
    {
        std::cout << dir << x[i];
        dir = ", ";
    }
    std::cout << std::endl;
}

bool iscliming(int x[], int n)
{
    n -= 1;
    if(n <= 1)
    {
        return true;
    }
    else
    {
        
        std::cout << x[n]-1 << ' ' << x[n-1] << std::endl;
        if(x[n] != x[n-1] || x[n] - 1 != x[n-1])
        {
            std::cout << x[n] << " is not equal to " << x[n-1] << " or one number less\n";
            iscliming(x, n-1);
        }
        return false;
    }
}

int main()
{
    int n = 0;
    std::cin >> n; 
    int x[n];
    for(int i = 0; i < n; ++i)
    {
        std::cin >> x[i];
    }

    printarray(x, n);

    std::cout << iscliming(x, n) << std::endl;

    return 0;
}