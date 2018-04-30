#ifndef PP_DECODE_H
#define PP_DECODE_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#define MAX_SIZE 270
#define WRITE_BUFF_SIZE 20
#define PSEUDO_EOF 256 //伪结束符eof，用于判断是否是尾部补齐

struct Huffman_node_2
{
    int id;
    float freq;
    std::string code;
    Huffman_node_2  *left,
                  *right,
                  *parent;
};
typedef Huffman_node_2* Node_ptr_2;

class pp_decode
{
    public:
        pp_decode(std::string);
        std::string InputFileName;
        std::string OutputFileName;
        int decode();
        virtual ~pp_decode();

    private:
        Node_ptr_2 root;

        int size_rd;

        long long total_byte;

        int rebuild_huffman_tree();

        int do_decompress();
};

#endif // PP_DECODE_H
