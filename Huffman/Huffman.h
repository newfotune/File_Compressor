#pragma once
#include <unordered_map>
#include <fstream>
#include "Node.h"
//#include "P_Queue.h"
#include <iostream>
#include <queue>


typedef std::string String;
typedef std::ifstream IfStream;
//typedef std::unordered_map<char, int> FrequencyMap;

std::unordered_map<char, int> freq_map;
std::unordered_map<char, String> encodingMap;
String sb;
Node *my_root;

//Function declarations----------------
std::unordered_map<char, int> getCharacterFrequencies(const String & path);
void insert_into_freq_map(const char & theChar);
void getFrequencies(const String &current_line);
std::unordered_map<char, String> getEncoding(const std::unordered_map<char, int> & freq);
void getEncoding(Node * root, String sb);

/**
* Goes through the text and puts the every char in the map with its freq.
* @param path the text to be parsed.
* @return the map containing the character and its frequencies.
*/
std::unordered_map<char, int> getCharacterFrequencies(const String & path) { 
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
std::unordered_map<char, String> getEncoding(const std::unordered_map<char, int> & freq) {
	/*for (auto& p : freq_map)
		std::cout << " " << p.first << " => " << p.second << '\n';*/
	//Priority_Queue<Node> my_q;
	std::priority_queue<Node> my_q; //using the STL's priority queue instead of mine :(

	for (auto& p : freq_map) {
		const node_ptr n = new Node(p.first, p.second);
		my_q.push(*n);
	}

	while (my_q.size() > 1) {
		//my_q.print();
		Node n1 = my_q.top();
		my_q.pop(); //current smallest.
		Node n2 = my_q.top(); 
		my_q.pop();
		Node *newNode = new Node('$', n1.total+n2.total);

		Node * left = new Node(n1.data, n1.total);
		left->left = n1.left; left->right = n1.right;

		Node * right = new Node(n2.data, n2.total);
		right->left = n2.left; right->right = n2.right;
		
		newNode->left = left; newNode->right = right;
		my_q.push(*newNode);
	}
	Node n = my_q.top(); my_q.pop();
	my_root = &n;
	getEncoding(my_root, sb);

	std::cout << "------------------------" <<std::endl;
	/*for (auto& p : encodingMap)
		std::cout << " " << p.first << " => " << p.second << '\n';*/
	return encodingMap;
}

/**
* This method assigns each character a binary representation.
* @param myRoot the root of the tree.
* @param sb the string builder representing
*/
void getEncoding(Node * root, String sb) {
	//std::cout << root.data << "-->>" << root.total << std::endl;
	if (root == NULL)
		return;

	if (root->data != '$') {
		//std::cout << root->data << ": " << sb << "\n";
		encodingMap.insert({ root->data, sb });
		return;
	}
		
	getEncoding(root->left, sb + "0");
	getEncoding(root->right, sb + "1");
}


double getCompressionRatio(std::unordered_map<char, int> &freq, std::unordered_map<char, String> encoding) {
	double myTotal = 0.0;
	for (auto& p : freq_map) {
		myTotal += p.second;
	}
	myTotal *= 8;

	String s;// = new String();
	for (auto& p : encodingMap) {
		//std::cout << p.first << "->" << p.second << std::endl;
		s = s + p.second;
	}
	double s2 = s.length();

	std::cout << "total = " << myTotal << " length = " << s2 << std::endl;
	return myTotal / s2;
}