#pragma once
#include <string>


typedef struct Node {
	char data;// = new String();
	unsigned int total = 0;
	Node * left;
	Node * right;

	Node operator+(const Node&);
	friend bool operator>(const Node&, const Node&);
	friend bool operator<(const Node&, const Node&);
	friend bool operator>=(const Node&, const Node&);
	friend bool operator<=(const Node&, const Node&);
	friend bool operator==(const Node&, const Node&);
	friend bool operator!=(const Node&, const Node&);

	Node(char data, unsigned int total)
	{
		left = right = NULL;
		this->data = data;
		this->total = total;
	}
	/*~Node() {
		free(left);
		free(right);
	}*/
	//std::ostream& operator<<(const Node&);
}* node_ptr;

/*std::ostream& Node::operator<<(const Node& n)
{
	os << dt.mo << '/' << dt.da << '/' << dt.yr;
	return os;
}*/

Node Node::operator+ (const Node &rhs) {
	node_ptr newNode = new Node(rhs.data, rhs.total);
	newNode->total = this->total + rhs.total;

	//const char * s = strcat(this->data.c_str(), (rhs.data.c_str));
	newNode->data = '$';//this->data + rhs.data;
	return *newNode;
}

bool operator>(const Node &lhs, const Node &rhs) {
	return lhs.total > rhs.total;
}
//operator currently in use
bool operator<(const Node &lhs, const Node &rhs) {
	return rhs.total < lhs.total;
	//return this->total < rhs.total;
}

//trying out different comparison
/*Compares the total of both Nodes. */
bool operator>=(const Node &lhs, const Node &rhs) {
	return (lhs.total >= rhs.total);
}
/*Compares the total of both Nodes. */
bool operator<=(const Node &lhs, const Node &rhs) {
	return (lhs.total <= rhs.total);
}

//trying out different comparison
/*Compares the string of both Nodes. */
bool operator==(const Node &lhs, const Node &rhs) {
	return (lhs.data ==rhs.data && lhs.total == rhs.total);
}
/*Compares the string of both Nodes. */
bool operator!=(const Node &lhs, const Node &rhs) {
	return !operator==(lhs, rhs);
}