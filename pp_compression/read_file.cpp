#include <iostream>
#include <fstream> 
#include <string>

#define uint unsigned int

long long t = 0;

int scan_bit(char i, char k)
{
	if(i & k)
		return 1;
	else
		return 0;
}

int count_each_byte(std::string line, float stat[])
{		
    for (int i = 0; i != line.size(); ++i)
    {
    	int byte_num = 0;
    	t++;
    	unsigned char k = 0x80;
    	unsigned char l = line[i];
		/*
		for (int j = 7; j >= 0; --j, k >>= 1)//manipulate each bit in each character, j for bit & i for char 
		{   //k : scan all bits 
			std::cout << sizeof(line[i]) << " " << (int)l << std::endl;
			byte_num = (byte_num << 1) | scan_bit(line[i], k);
	    }*/
	    std::cout << (int)l << std::endl;
		stat[(int)l] += 0.01;
	}
	return 0;
}

/*int string_to_binary(std::string line, std::ofstream &out_binary, int stat[])
{	
	int byte_num = 0;
	
    for(int i = 0; i != line.size(); ++i)
    {
    	t++;
    	unsigned char k = 0x80;
		for (int j = 0; j < 8; ++j, k >>= 1)
		{   
	        if (line[i] & k)
			{  
				out_binary << "1";  
				byte_num += std::pow(2, 8 - j - 1);
	        }
			else
			{  
				out_binary << "0";  
	        }
	    }
	    out_binary << " ";
		if(t % 100 == 0)
		{
			out_binary << std::endl;
		}
		stat[byte_num]++;
		byte_num = 0;
	}
	return 0;
}*/

int main()
{
	std::string file_name;
	std::string buffer, word;
	float stat[255] = {0.};
	int i = 0; 
	std::cout << "Input the file name:";
	std::cin >> file_name;
	std::ifstream input_file(file_name.c_str(), std::ifstream::binary);
	//std::ofstream output_file("out_binary.txt", std::ios::out | std::ios::trunc);
	if (!input_file.is_open())
	{
		std::cout << "Error!";
		return -1;
	} 
	while (!input_file.eof())
	{
		i++;
		std::getline(input_file, buffer);
		//string_to_binary(buffer, output_file, stat);
		count_each_byte(buffer, stat);
	}
	std::cout << i << " lines";
	//output_file << std::endl; 
	/*for(int i = 0; i < 255; ++i)
	{
		output_file << i << " : " << stat[i] << std::endl;
		//std::cout << i << " : " << stat[i] << std::endl;
	}*/
	input_file.close();
	//output_file.close();
	return 0; 
}
