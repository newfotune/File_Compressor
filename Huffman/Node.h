#pragma once
#include <string>


typedef struct Node {
	std::string data;
	unsigned int total = 0;
	Node * left;
	Node * right;

	Node operator+(const Node&);
	bool operator>(const Node&);
	bool operator<(const Node&);
	bool operator>=(const Node&);
	bool operator<=(const Node&);
	bool operator==(const Node&);
	bool operator!=(const Node&);

	//std::ostream& operator<<(const Node&);
}* node_ptr;

/*std::ostream& Node::operator<<(const Node& n)
{
	os << dt.mo << '/' << dt.da << '/' << dt.yr;
	return os;
}*/

Node Node::operator+ (const Node &rhs) {
	node_ptr newNode = new Node();
	newNode->total = this->total + rhs.total;
	newNode->data = this->data + rhs.data;
	return *newNode;
}

bool Node::operator>(const Node &rhs) {
	return (this->total - rhs.total) > 0;
}

bool Node::operator<(const Node &rhs) {
	return (this->total - rhs.total) < 0;
}

//trying out different comparison
/*Compares the total of both Nodes. */
bool Node::operator>=(const Node &rhs) {
	return (this->total >= rhs.total);
}
/*Compares the total of both Nodes. */
bool Node::operator<=(const Node &rhs) {
	return (this->total <= rhs.total);
}

//trying out different comparison
/*Compares the string of both Nodes. */
bool Node::operator==(const Node &rhs) {
	return (this->data.compare(rhs.data) == 0 && this->total == rhs.total);
}
/*Compares the string of both Nodes. */
bool Node::operator!=(const Node &rhs) {
	return !operator==(rhs);
}