#pragma once
#ifndef TYPES_H
#define TYPES_H

#include <string>
/* A type representing a character, pseudo-eof or nothing */
typedef int ext_char;
/*A character that serves to signify the end of file character.*/
const ext_char _EOF = 256;

/*A constant representing an extended character with no value.
* This will be used for the internal nodes whose characters are
* not in use.
*/
const ext_char NOT_A_CHAR = 257;

/*Node object.
* The node object holds ann ext_char, an int total and pointers
* to the left and right nodes.
*/
typedef struct Node {
	ext_char data;
	unsigned int total = 0;
	Node * left;
	Node * right;

	Node(ext_char data, unsigned int total)
	{
		left = right = NULL;
		this->data = data;
		this->total = total;
	}

	/* Comparator functor class for comparing nodes. */
	struct NodeComparator {
		bool operator() (Node* lhs, Node* rhs);
	};
}*node_ptr;

#endif // !TYPES_H
