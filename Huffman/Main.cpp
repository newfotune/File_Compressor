// Huffman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "P_Queue.h"
//#include "Node.h"
#include "Huffman.h"

//function declaration
//template <unsigned N, unsigned M> int compare(const char(&p1)[N], const char(&p2)[M]);
//void testQueue();
void testNode();

int main()
{
	std::cout << "hello world\n" << std::endl;
	//testQueue();
	//testNode();
	getCharacterFrequencies(String("C:/Users/Fortune/Documents/Visual Studio 2015/Projects/File_Compressor/Huffman/missisipi.txt"));
	getEncoding(freq_map);
	std::cout << "The compression ration is : " << getCompressionRatio(freq_map, encodingMap) << std::endl;

	system("pause");
    return 0;
}

/*Function to test my Priority queue.*/
/*void testQueue() {
	std::cout << "----------------------testting Priotity Queue------------- " << std::endl;
	std::vector<int> b{ 1 , 1, 5, 4, 1, 2, 2, 2, 1, 2, 2 };

	Priority_Queue<int> myQueue;
	//myQueue.pop();
	for (int i = 0; i < b.size(); i++)
		myQueue.push(b[i]);

	//myQueue.print(std::cout);
	std::cout << myQueue.size() << std::endl;

	for (int i = myQueue.size(); i > 0; i--)
		std::cout << myQueue.pop() << " ";
	std::cout << std::endl;
}*/

/*Function to test my Node.*/
void testNode() {
	std::cout << "----------------------testting Node------------- " << std::endl;
	node_ptr node1 = new Node('f', 10);

	node_ptr node2 = new Node('m', 5);

	bool isTrue = true, isFalse = false;
	std::cout << "True is " << isTrue << " ||  false is " << isFalse << std::endl;

	bool a = *node1 == *node2;
	std::cout << "should be false: " << a << std::endl;

	a = *node1 == *node1;
	std::cout << "should be true: " << a << std::endl;

	a = *node1 != *node2;
	std::cout << "should be true: " << a << std::endl;

	a = *node1 > *node2;
	std::cout << "should be true: " << a << std::endl;

	a = *node1 < *node2;
	std::cout << "should be false: " << a << std::endl;


}


//function definition
/*template <unsigned N, unsigned M>
int compare(const char(&p1)[N], const char(&p2)[M]) {
	return strcmp(p1, p2);
}*/