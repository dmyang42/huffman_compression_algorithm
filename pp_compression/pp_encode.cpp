#include "pp_encode.h"

pp_encode::pp_encode(std::string FileName)
{
    InputFileName = FileName;
    OutputFileName = FileName + ".pp";
}

int pp_encode::count_each_byte(std::string line, float stat[])
{
    for (int i = 0; i != line.size(); ++i)
    {
    	int byte_num = 0;
    	unsigned char k = 0x80;
    	unsigned char l = line[i];
		stat[(int)l] += 0.01;
	}
	return 0;
}

int pp_encode::get_byte_frequency()
{
    std::string buffer, word;

    std::ifstream input_file(InputFileName.c_str(), std::ifstream::binary);
    if (!input_file.is_open())
	{
		std::cout << "Fail to open the file!";
		std::exit(1);
	}
	while (!input_file.eof())
	{
		std::getline(input_file, buffer);
		count_each_byte(buffer, byte_freq);
	}
	input_file.close();
	for (int i = 0; i < 256; ++i)
    {
        Node_ptr node = new Huffman_node();
        node->id = i;
        node->freq = byte_freq[i];
        node->code = "";
        node->left = NULL;
        node->parent = NULL;
        node->right = NULL;
        node_array[i] = node;
    }//有一些组合可能不会出现，不需要存，这里可以改，数组大小可能要大于255
	return 0;
}

int pp_encode::create_pq()
{
    get_byte_frequency();
    for (int i = 0; i < 256; ++i)
        pq.push(node_array[i]);
    return 0;
}

int pp_encode::build_huffman_tree()
{
    root = NULL;

    while (!pq.empty())
    {
        Node_ptr first = pq.top();
        pq.pop();
        if (pq.empty())
        {
            root = first;
            break;
        }
        Node_ptr second = pq.top();
        pq.pop();
        Node_ptr new_node = new Huffman_node();
        new_node->freq = first->freq + second->freq;

        if (first->freq <= second->freq)
        {
            new_node->left = first;
            new_node->right = second;
        }
        else
        {
            new_node->left = second;
            new_node->right = first;
        }
        first->parent = new_node;
        second->parent = new_node;

        pq.push(new_node);
    }
    return 0;
}

int pp_encode::create_map_table(const Node_ptr node, bool left)
{
    if (left)
        node->code = node->parent->code + "0";
    else
        node->code = node->parent->code + "1";

    // 如果是叶子节点，则是一个“有效”节点，加入编码表
    if (node->left == NULL && node->right == NULL)
        table[node->id] = node->code;
    else
    {
        if (node->left != NULL)
            create_map_table(node->left, true);
        if (node->right != NULL)
            create_map_table(node->right, false);
    }
    return 0;
}

int pp_encode::calculate_huffman_codes()
{
    if (root == NULL)
    {
        std::cout << "No huffman tree exists!";
        std::exit(1);
    }

    if (root->left != NULL)
        create_map_table(root->left, true);
    if (root->right != NULL)
        create_map_table(root->right, false);
    return 0;
}

int pp_encode::do_compress()
{
    std::ifstream input_file(InputFileName.c_str(), std::ifstream::binary);
	std::ofstream output_file(OutputFileName.c_str(), std::ios::out | std::ios::trunc);
    std::map<int, std::string>::iterator table_it;
    std::string code, buffer, out_string;
    char in_char;
    unsigned char out_c, tmp_c;

    for (table_it = table.begin(); table_it != table.end(); ++table_it)
    {
        output_file << table_it->first << " " << table_it->second << std::endl;
    }
    // 第2~(size+1)行写入huffman树，即每行写入字符+huffman编码，如"43 00100"

    // 第size+2行写入huffman编码
    if (!input_file.is_open())
	{
		std::cout << "Error!";
		exit(1);
	}
    while (!input_file.eof())
    {
        code = "";
        out_string.clear();
        std::getline(input_file, buffer);
        for (int i = 0; i != buffer.size(); ++i)
        {
            unsigned char l = buffer[i];
            table_it = table.find((int)l);
            //std::cout << (int)l << std::endl;
            if (table_it != table.end())
                code += table_it->second;
            else
            {
                printf("Can't find the huffman code of character %X\n", l);
                //exit(1);
            }
        }
        //huffman code以二进制流写入到输出文件
        for (int i = 0; i + 7 < code.size(); i += 8)
        {
            out_c = 0;
            for (int j = 0; j < 8; ++j)
            {
                if ('0' == code[i + j])
                    tmp_c = 0;
                else if ('1' == code[i + j])
                    tmp_c = 1;
                out_c += tmp_c << (7 - j);
            }
            out_string += out_c;
        }
        output_file << out_string;
    }
    input_file.close();
    output_file.close();
    return 0;
}

int pp_encode::encode()
{
    create_pq();
    build_huffman_tree();
    calculate_huffman_codes();
    do_compress();

}

pp_encode::~pp_encode()
{
    //dtor
}
