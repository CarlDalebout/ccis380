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
    if(n == 0)
    {
        return true;
    }
    else
    {
        //std::cout << x[n] << ' ' << x[n-1] << std::endl;
        if(x[n] == x[n-1])
        {
            iscliming(x, n-1);
        }
        else if(x[n]-1 == x[n-1])
        {
            iscliming(x, n-1);
        }
        else
        {
            //std::cout << "returning false\n";
            return false;
        }
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

    // printarray(x, n);

    std::cout << iscliming(x, n-1) << std::endl;

    return 0;
}