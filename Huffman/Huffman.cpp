#include "stdafx.h"
#include "Huffman.h"
#include "P_Queue.h"
#include <string>

String all_chars_in_text;

/**
* Goes through the text and puts the every char in the map with its freq.
* @param path the text to be parsed.
* @return the map containing the character and its frequencies.
*/
FrequencyMap getCharacterFrequencies(const String & path) {
	String current_line;
	IfStream myFile;
	myFile.open(path);
	FrequencyMap freq_map;// = new std::unordered_map<char, int>();

	if (myFile.is_open()) {
		while (std::getline(myFile, current_line)) { //get current line
			if (current_line.length() == 0) {
				//std::cout << "empty line" << std::endl;*/
				all_chars_in_text += (int) "\n";
				insert_into_freq_map('\n', freq_map);
			}
			else
				getFrequencies(current_line, freq_map);
		}
		all_chars_in_text += _EOF;
		insert_into_freq_map(_EOF, freq_map);
		myFile.close();
	}
	else
		std::cerr << "unable to open file" << std::endl;

	//for (auto& p: freq_map)
	//std::cout << " " << (char)p.first << " => " << p.second << '\n';

	return freq_map;
}

void insert_into_freq_map(const ext_char & theChar, FrequencyMap &freq_map) {
	//if the element doesnt exist in the map
	if (freq_map.find(theChar) == freq_map.end())
		freq_map.insert({ theChar, 1 });
	else { //it already exist in our map.

		auto freq = freq_map[theChar];
		freq++;
		freq_map.insert_or_assign(theChar, freq);
	}
}

/**
* Gets the frequency of each char in each line and stores it in the map
* @param theLine the line to be checked.
*/
void getFrequencies(const String &current_line, FrequencyMap &freq_map) {
	for (size_t i = 0; i < current_line.size(); i++) {
		all_chars_in_text += (int) current_line[i];
		//insert into map that keeps track of frequency.
		insert_into_freq_map(current_line[i], freq_map);
	}
}

/**
* Build the tree with each. The map containing each character with its binary.
* @param frequencies the map containing the char and its freq.
* @return the maps containing the char and its binary representation.
*/
EncodingMap getEncoding(const FrequencyMap & freq_map) {
	/*for (auto& p : freq_map)
	std::cout << " " << p.first << " => " << p.second << '\n';*/
	//Priority_Queue<Node> my_q;
	//std::priority_queue<Node> my_q; //using the STL's priority queue instead of mine :(
	HuffmanPQueue my_q;
	EncodingMap encodingMap;

	for (auto& p : freq_map) {
		node_ptr n = new Node(p.first, p.second);
		my_q.enqueue(n);
	}

	while (my_q.size() > 1) {
		node_ptr n1 = my_q.peek();
		my_q.dequeueMin(); //current smallest.
		node_ptr n2 = my_q.peek();
		my_q.dequeueMin();
		node_ptr newNode = new Node(NOT_A_CHAR, n1->total + n2->total);

		node_ptr left = new Node(n1->data, n1->total);
		left->left = n1->left; left->right = n1->right;

		node_ptr right = new Node(n2->data, n2->total);
		right->left = n2->left; right->right = n2->right;

		newNode->left = left; newNode->right = right;
		my_q.enqueue(newNode);
	}
	node_ptr n = my_q.peek(); my_q.dequeueMin();
	node_ptr my_root = n;
	String sb;
	getEncoding(my_root, sb, encodingMap);

	std::cout << "Finished Encoding" << std::endl;
	/*for (auto& p : encodingMap)
	std::cout << " " << p.first << " => " << p.second << '\n';*/
	return encodingMap;
}

/**
* This method assigns each character a binary representation.
* @param myRoot the root of the tree.
* @param sb the string builder representing
*/
void getEncoding(Node * root, String sb, EncodingMap & encodingMap) {
	//std::cout << root.data << "-->>" << root.total << std::endl;
	if (root == NULL)
		return;

	if (root->data != NOT_A_CHAR) { //if we are at a root node
									//std::cout << root->data << ": " << sb << "\n";
		encodingMap.insert({ root->data, sb });
		return;
	}

	getEncoding(root->left, sb + "0", encodingMap);
	getEncoding(root->right, sb + "1", encodingMap);
}

void write_encoded(EncodingMap& encoding_map, const String& path, const String& dictionary) {
	ofbstream my_file_bits; //bits written to compressed file.
	Ofstream my_file_chars; //dictionary written to another file. 

	my_file_chars.open(dictionary);
	if (my_file_chars.is_open()) {
		for (auto &p : encoding_map)
			my_file_chars << (ext_char) p.first << '=' << p.second << "\n";
		my_file_chars.close();
	}
	else std::cout << "Unable to write dictionary to dictionary file" << std::endl;
	//finised writing dictionary to file.

	if (my_file_bits.is_open()) {
		my_file_bits.open(path);
		for (int i = 0; i < all_chars_in_text.length(); i++) {
			String s = encoding_map[(int)all_chars_in_text[i]];
			for (int j = 0; j < s.length(); j++) {
				char a = s[j];
				int ia = a - '0';
				my_file_bits.writeBit(ia);
			}
			s.clear();
		}
		std::cout << "finished writing to file" << std::endl;
		all_chars_in_text.clear();
		my_file_bits.close();
	}
	else std::cout << "Unable to write codes to Output file" << std::endl;
}

void decode_and_write(const String& encoded, const String& dict, const String& output) {
	unordered_map<String, ext_char> dictionary;
	dictionary = create_decode_dictionary(dict);
	//my_input.open(input);
	
	std::cout << "Printing Map from file" << std::endl;
	for (auto& p : dictionary)
		std::cout << p.first << "-" << (char)p.second <<"\n";

	ifbstream in_file;
	Ofstream out_file;
	in_file.open(encoded);
	out_file.open(output);

	if (in_file.is_open()) {
		if (out_file.is_open()) {
			String binary = "";
			while (1) {
				binary += (char)(in_file.readBit() + 48);
				auto ele = dictionary.find(binary);
				if (ele != dictionary.end()) {
					binary.clear();
					if (ele->second == _EOF)
						break;
					else {
						std::cout << (char)ele->second;
						out_file << (char)ele->second;
					}
						
				}
			}

			out_file.close();
		}
		else { std::cout << "unable to open output file"; }
		in_file.close();
	}
	else { std::cout << "Unable to open codes" << std::endl; }

}

unordered_map<String, ext_char> create_decode_dictionary(const String& dict) {
	IfStream dict_file;
	dict_file.open(dict);
	String current_line;

	unordered_map <String, ext_char> map;
	if (dict_file.is_open()) {
		String key; ext_char value;
		while (getline(dict_file, current_line)) {
			split(current_line, key, value);
			map.insert({ key, value });
		}
	}
	else
		std::cout << "unable to open file" << std::endl;

	return map;
}

void split(String &line, String &key, ext_char &value) {
	String theValue = "";
	size_t i = 0;
	for (; i < line.length(); i++) {
		if (line[i] == '=')
			break;
		theValue += line[i];
	}

	key = line.substr(i+1, line.length());
	value = stoi(theValue);
}

/*Calculates the ratio of our compressed file to our original file.*/
double getCompressionRatio(FrequencyMap &freq_map, EncodingMap encoding_map) {
	double myTotal = 0.0;
	for (auto& p : freq_map) {
		myTotal += p.second;
	}
	myTotal *= 8;

	int stringLength = 0;
	for (auto &c : freq_map) {
		auto ch = c.first;
		auto count = c.second;
		//std::cout << encoding
		stringLength += count * (encoding_map[ch].length());
	}
	std::cout << "total = " << myTotal << " length = " << stringLength << std::endl;
	return (stringLength / myTotal) * 100;
}