#include <iostream>
#include <ctime>
#include <cstdlib>
const int SIZE = 20;
const char C[] = {'1', '2', '3', '4', '5'};
//=============================================================================
// Fill 2D array m with characters chosen randomly from C.
//=============================================================================
void randarray(char m[SIZE][SIZE])
{
for (int i = 0; i < SIZE; i++)
{
for (int j = 0; j < SIZE; j++)
{
m[i][j] = C[rand() % 5];
}
}
}
//=============================================================================
// Print 2D array.
//=============================================================================
void printarray(char m[SIZE][SIZE])
{
for (int i = 0; i < SIZE; i++)
{
for (int j = 0; j < SIZE; j++)
{
std::cout << m[i][j];
}
std::cout << '\n';
}
}
//=============================================================================
// Compute the first (row, col) position such that this is the center of a
// cross of 5 index positions where the characters in array m at these have
// distinct characters. For instance this is a cross
//  d
// abc
//  e
// of distinct chracters. If the b is at row 5, column 2 then the function
// should set parameter row to 5 and col to 2.
// (Don't forget that we start counting row and column index values at 0.)
//=============================================================================
void f(char m[SIZE][SIZE], int & row, int & col)
{

}
int main()
{
int seed;
std::cin >> seed;
srand(seed);
char m[SIZE][SIZE];
randarray(m);
printarray(m);
int row, col;
f(m, row, col);
std::cout << row << ' ' << col << std::endl;
return 0;
}
