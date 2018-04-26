#ifndef PP_ENCODE_H
#define PP_ENCODE_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#define MAX_SIZE 270
#define WRITE_BUFF_SIZE 10

struct Huffman_node
{
    int id; // 使用int类型，因为要插入值为256的pseudo-EOF
    float freq;
    std::string code;
    Huffman_node  *left,
                  *right,
                  *parent;
};
typedef Huffman_node* Node_ptr;

class pp_encode
{
    public:
        pp_encode(std::string);
        std::string InputFileName;
        std::string OutputFileName;
        int encode();
        int decode();
        float restore_examine();
        virtual ~pp_encode();

    private:
        int count_each_byte(std::string, float*);
        float byte_freq[256] = {0.};
        Node_ptr node_array[256];
        Node_ptr root;
        std::map<int, std::string> table;

        class Compare
        {
            public:
                bool operator()(const Node_ptr& c1, const Node_ptr& c2) const
                {

                    return (*c1).freq > (*c2).freq;
                }
        };// 用于比较优先队列中元素间的顺序
        std::priority_queue< Node_ptr, std::vector<Node_ptr>, Compare > pq;

        /*以下是用于压缩的函数*/
        int create_pq();//调用这个函数统计文件中各种byte的频率，并建立优先队列

        int get_byte_frequency();//在creat_pq中调用的用于统计频率的

        int build_huffman_tree();//根据pq建立huffman tree

        int create_map_table(const Node_ptr node, bool left);//在calculate_huffman_codes中被调用

        int calculate_huffman_codes();//根据建立的huffman tree计算huffman code

        int do_compress();
};

#endif // PP_ENCODE_H
