#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <unordered_map>
#include <fstream>
#include "Types.h"
#include <iostream>
#include <queue>
#include "bstream.h"

typedef std::string String;
typedef std::ifstream IfStream;
typedef std::ofstream Ofstream;
typedef std::unordered_map<ext_char, int> FrequencyMap;
typedef std::unordered_map<ext_char, String> EncodingMap;

//Node *my_root;

//Function declarations----------------
FrequencyMap getCharacterFrequencies(const String & path);
void insert_into_freq_map(const ext_char & theChar, FrequencyMap&);

void getFrequencies(const String &current_line, FrequencyMap&);
std::unordered_map<char, String> getEncoding(const std::unordered_map<char, int> &);

EncodingMap getEncoding(const FrequencyMap & freq_map);
void getEncoding(Node * root, String sb, EncodingMap&);
void write_encoded(EncodingMap&, const String&, const String&);

void decode_and_write(const String&, const String&, const String&);
unordered_map<String, ext_char> create_decode_dictionary(const String& dict);
void split(String &line, String &key, ext_char &value);

double getCompressionRatio(FrequencyMap &freq_map, EncodingMap encoding_map);

#endif // !HUFFMAN_H