#pragma once
#include <unordered_map>
#include <fstream>
#include "Node.h"
#include "P_Queue.h"


typedef std::string String;
typedef std::ifstream IfStream;
//typedef std::unordered_map<char, int> FrequencyMap;

std::unordered_map<char, int> freq_map;
std::unordered_map<char, String> encodingMap;
String sb;
node_ptr my_root;

//Function declarations----------------
std::unordered_map<char, int> getCharacterFrequencies(const String path);
void insert_into_freq_map(const char & theChar);
void getFrequencies(const String &current_line);
std::unordered_map<char, String> getEncoding(std::unordered_map<char, int> freq);

/**
* Goes through the text and puts the every char in the map with its freq.
* @param path the text to be parsed.
* @return the map containing the character and its frequencies.
*/
std::unordered_map<char, int> getCharacterFrequencies(const String path) { 
	String current_line;
	IfStream myFile;
	myFile.open(path);

	if (myFile.is_open()) {
		while (std::getline(myFile, current_line)) { //get current line
			if (current_line.length() == 0) {
				//std::cout << "empty line" << std::endl;*/
				insert_into_freq_map('\n');
			}else 
				getFrequencies(current_line);
		}
		myFile.close();
	}
	else
		std::cerr << "unable to open file" << std::endl;

	/*for (auto& p: freq_map)
		std::cout << " " << p.first << " => " << p.second << '\n';*/

	return freq_map;
}

void insert_into_freq_map(const char & theChar) {
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
void getFrequencies(const String &current_line) {
	for (size_t i = 0; i < current_line.size(); i++) {
		//insert into map that keeps track of frequency.
		insert_into_freq_map(current_line[i]);
	}
}

/**
* Build the tree with each. The map containing each character with its binary.
* @param frequencies the map containing the char and its freq.
* @return the maps containing the char and its binary representation.
*/
std::unordered_map<char, String> getEncoding(std::unordered_map<char, int> freq) {
	for (auto& p : freq_map)
		std::cout << " " << p.first << " => " << p.second << '\n';
	Priority_Queue<Node> my_q;

	for (auto& p : freq_map) {
		const node_ptr n = new Node();
		n->data = p.first;
		n->total = p.second;

		my_q.push(*n);
	}

	for (size_t i = 0; i < my_q.size(); i++) {
		auto n = my_q.pop();
		std::cout << n.data << "-" << n.total << std::endl;
	}

	return encodingMap;
}

/**
* This method assigns each character a binary representation.
* @param myRoot the root of the tree.
* @param sb the string builder representing
*/
void getEncoding(node_ptr root) {

}

Node buildHuffsTree(Priority_Queue<Node> &myNodes) {

	return Node();
}

double getCompressionRatio(std::unordered_map<char, int> &freq, std::unordered_map<char, String> encoding) {

	return 0.0;
}