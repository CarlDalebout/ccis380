#include <iostream>
#include <string>
#include "complex.h"

std::string removeSpaces(std::string input)
{
    int c = 0;
    for(int i = 0; i <= input.length(); ++i)
    {
        if(input[i] != ' ')
        {
            //std::cout << "found " << input[i] << "c++\n";
            c++;
        }
        else
        {
            int j = i+1;
            while(input[j] == ' ')
            {
                if(j >= input.length())
                {
                    //std::cout << "Resizing input from " << input.length() << " to " << input.length() - c << std::endl;
                    input.resize(c);
                    return input;            
                }
                ++j;
            }
            //std::cout << "found " << input[j] << "c++\n";
            c++;
            char temp = input[i];
            input[i] = input[j];
            input[j] = temp;
        }
    }
    //std::cout << "Resizing input from " << input.length() << " to " << input.length() - c << std::endl;
    input.resize(c);
    return input;
}

int main()
{
    std::string input;
    std::getline(std::cin, input);
    input = removeSpaces(input);

    std::cout << '"' << input << '"' << std::endl;
    std::cout << "recived " << int(input[0])-48 << std::endl;

    complex z0(int(input[1])-48, int(input[2])-48);
    complex x1(int(input[3])-48, int(input[4])-48);
    
    std::cout << "z0: " << z0 << "\nz1: " << x1 << std::endl; 

    switch(int(input[0])-48)
    {
        case 0:
            std::cout << "case 0\n";
            std::cout << (z0 += x1) << std::endl;
            break;
        case 1:
            std::cout << "case 1\n";
            std::cout << (z0 -= x1) << std::endl;
            break;
        case 2:
            std::cout << "case 2\n";
            std::cout << (z0 *= x1) << std::endl;
            break;
        case 3:
            std::cout << "case 3\n";
            std::cout << (z0 /= x1) << std::endl;
            break;
        case 4:
            std::cout << "case 4\n";
            std::cout << (z0 + x1) << std::endl;
            break;
        case 5:
            std::cout << "case 5\n";
            std::cout << (z0 - x1) << std::endl;
            break;
        case 6:
            std::cout << "case 6\n";
            std::cout << (z0 * x1) << std::endl; 
            break;
        case 7:
            std::cout << "case 7\n";
            std::cout << (z0 / x1) << std::endl;
            break;
        case 8:
            std::cout << "case 8\n";
            std::cout << (z0.abs()) <<std::endl;
            break;
    }

    return 0;
}