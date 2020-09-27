#include <iostream>
#include "handler.h"
#include <string>

int main()
{
    
    setlocale(LC_ALL, "Russian");
    Handler handler;
    char filename []= "./Debug/testBase2.dat";
    handler.GetDataFromFile(filename);
    system("PAUSE");
}

