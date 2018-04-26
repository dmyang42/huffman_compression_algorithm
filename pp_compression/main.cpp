#include <iostream>
#include "pp_encode.h"
#include "pp_decode.h"

int compress_mode()
{
    std::string FileName;
    std::cout << "Enter file name :";
    std::cout << ">>";
    std::cin >> FileName;
    pp_encode pp(FileName);
    pp.encode();
    return 0;
}

int decompress_mode()
{
    std::string FileName;
    std::cout << "Enter file name :";
    std::cout << ">>";
    std::cin >> FileName;
    pp_decode pp(FileName);
    pp.decode();
    return 0;
}

int main()
{
    int mode;
    std::cout << "Enter mode : (0 for encode, 1 for decode)" << std::endl;
    std::cout << ">>";
    std::cin >> mode;
    if (mode == 0)
        compress_mode();
    else if (mode == 1)
        decompress_mode();
    else
        std::cout << "Error!";
    return 0;
}
