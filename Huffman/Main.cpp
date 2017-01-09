// Huffman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iomanip>
#include "Huffman.h"


//function declaration
//template <unsigned N, unsigned M> int compare(const char(&p1)[N], const char(&p2)[M]);

int main()
{
	String file_to_be_compressed = String("C:/Users/Fortune/Documents/Visual Studio 2015/Projects/File_Compressor/Huffman/missisipi.txt");
	String out_put_dictionary = String("C:/Users/Fortune/Documents/Visual Studio 2015/Projects/File_Compressor/Huffman/dictionary.txt");
	String coded_file = String("C:/Users/Fortune/Documents/Visual Studio 2015/Projects/File_Compressor/Huffman/coded.txt");

	FrequencyMap freq_map = getCharacterFrequencies(file_to_be_compressed);
	EncodingMap encodingMap = getEncoding(freq_map);
	write_encoded(encodingMap, coded_file, out_put_dictionary);

	std::cout << "The compression ration is : "<< std::setprecision(3) << getCompressionRatio(freq_map, encodingMap) <<"%" << std::endl;
	
	String decoded_file = String("C:/Users/Fortune/Documents/Visual Studio 2015/Projects/File_Compressor/Huffman/decoded_file.txt");
	decode_and_write(coded_file, out_put_dictionary, decoded_file);

	system("pause");
    return 0;
}