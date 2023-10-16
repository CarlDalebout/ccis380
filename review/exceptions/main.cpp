#include <iostream>
#include <exception>

void f()
{
        std::cout << "f ... 1\n";
    throw std::exception();
    std::cout << "f ... 2\n"; 
}   

void g() 
{
    try
    {
        std::cout << "g ... 1\n";
        f();
        std::cout << "g ... 2\n";
    }
    catch (std::exception & e)        
    {        
        std::cout << "g ... caught\n";        
        throw;    
    } 
}    

int main() 
{       
    try    
    {        
        std::cout << "main ... 1\n";        
        g();        
        std::cout << "main ... 2\n";    
    }    
    catch (std::exception & e)    
    {        
        std::cout << "main ... caught \n";    
    }    
    std::cout << "end\n";    
    
    return 0; 
}