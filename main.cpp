#include <iostream>
#include "pp_encode.h"

int compress_mode()
{
    std::string FileName;
    std::cout << "Enter file name : ";
    std::cin >> FileName;
    pp_encode pp(FileName);
    pp.encode();
    return 0;
}

int decode_mode()
{
    return 0;
}

int main()
{
    compress_mode();

    return 0;
}
