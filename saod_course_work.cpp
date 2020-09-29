#include <iostream>
#include "handler.h"
#include <string>

int main()
{
    setlocale(LC_ALL, "ru_RU.CP1251");
    Handler handler;
    char filename []= "./Debug/testBase2.dat";
    handler.GetDataFromFile(filename);
    handler.PrintStruct();
}

