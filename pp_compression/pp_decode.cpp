#include "pp_decode.h"

pp_decode::pp_decode(std::string FileName)
{
    InputFileName = FileName;

    int i = 0;
    while (FileName[i] != '.')
        ++i;
    FileName = FileName.substr(0, i);
    OutputFileName = FileName + ".out";
}

/*以下是解压部分*/
/*the decompress part is as below*/

int pp_decode::rebuild_huffman_tree()
{
    std::ifstream input_file(InputFileName.c_str(), std::ifstream::binary);
    if (!input_file.is_open())
	{
		std::cout << "Fail to open the file!";
		std::exit(1);
	}
    int id, length;
    std::string code;
    Node_ptr_2 node, tmp, new_node;

    root = new Huffman_node_2();
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;

    input_file >> size_rd;
    if (size_rd > MAX_SIZE)
    {
        printf("The number of nodes is not valid, maybe the compressed file has been broken.\n");
        exit(1);
    }

    for (int i = 0; i < size_rd; ++i)
    {
        input_file >> id;
        input_file >> code;
        length = code.length();
        node = root;
        for (int j = 0; j < length; ++j)
        {
            if('0' == code[j])
                tmp = node->left;
            else if('1' == code[j])
                tmp = node->right;
            else
            {
                printf("Error!\n");
                exit(1);
            }

            // 如果到了空，则新建一个节点
            if (tmp == NULL)
            {
                new_node = new Huffman_node_2();
                new_node->left = NULL;
                new_node->right = NULL;
                new_node->parent = node;

                // 如果是最后一个0或1,说明到了叶子节点，给叶子节点赋相关的值
                if (j == length - 1)
                {
                    new_node->id = id;
                    new_node->code = code;
                }

                if ('0' == code[j])
                    node->left = new_node;
                else
                    node->right = new_node;

                tmp = new_node;
            }
            // 如果不为空，且到了该huffman编码的最后一位，这里却已经存在了一个节点，就说明
            // 原来的huffmaninman是有问题的
            else if (j == length -1)
            {
                printf("Huffman code is not valid, maybe the compressed file has been broken.\n");
                exit(1);
            }
            // 如果不为空，但该节点却已经是叶子节点，说明寻路到了其他字符的编码处，huffman编码也不对
            else if (tmp->left == NULL && tmp->right == NULL)
            {
                printf("Huffman code is not valid, maybe the compressed file has been broken.\n");
                exit(1);
            }
            node = tmp;
        }

    }
    input_file.close();
    return 0;
}

int pp_decode::do_decompress()
{
    std::ifstream input_file(InputFileName.c_str(), std::ifstream::binary);
	std::ofstream output_file(OutputFileName.c_str(), std::ios::out | std::ios::trunc);
    bool pseudo_eof;
    int i, id;
    char in_char;
    unsigned char u_char, flag;
    Node_ptr_2 node;
    std::string buffer, out_string;

    for (int l = 0; l < size_rd + 1; ++l)
    {
        std::getline(input_file, buffer);
    }
    node = root;
    pseudo_eof = false;
    while (!input_file.eof())
    {
        std::getline(input_file, buffer);
        for (int i = 0; i != buffer.size(); ++i)
        {
            unsigned char l = buffer[i];
            flag = 0x80;
            for (int j = 0; j < 8; ++j)
            {

                if (l & flag)
                    node = node->right;
                else
                    node = node->left;
                if (node->left == NULL && node->right == NULL)
                {
                    id = node->id;
                    if (id == PSEUDO_EOF)
                    {
                        pseudo_eof = true;
                        break;
                    }
                    else
                    {
                        out_string += (unsigned char)node->id;
                        node = root;
                    }
                }
                if (pseudo_eof)
                    break;
                flag = flag >> 1;
            }
        }
        if (pseudo_eof)
            break;
    }
    if (!out_string.empty())
        output_file << out_string;

    input_file.close();
    output_file.close();
    return 0;
}

int pp_decode::decode()
{
    rebuild_huffman_tree();
    do_decompress();
    return 0;
}

pp_decode::~pp_decode()
{
    //dtor
}
