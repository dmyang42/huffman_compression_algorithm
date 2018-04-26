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
    int id; // ʹ��int���ͣ���ΪҪ����ֵΪ256��pseudo-EOF
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
        };// ���ڱȽ����ȶ�����Ԫ�ؼ��˳��
        std::priority_queue< Node_ptr, std::vector<Node_ptr>, Compare > pq;

        /*����������ѹ���ĺ���*/
        int create_pq();//�����������ͳ���ļ��и���byte��Ƶ�ʣ����������ȶ���

        int get_byte_frequency();//��creat_pq�е��õ�����ͳ��Ƶ�ʵ�

        int build_huffman_tree();//����pq����huffman tree

        int create_map_table(const Node_ptr node, bool left);//��calculate_huffman_codes�б�����

        int calculate_huffman_codes();//���ݽ�����huffman tree����huffman code

        int do_compress();
};

#endif // PP_ENCODE_H
