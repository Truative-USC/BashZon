#include "splaytree.h"
#include "bst.h"
#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
	
	splayTree<int,int> myTree;
	for(int i =0 ; i < 50;i++) {
		myTree.insert(make_pair(i,i));
	}
	myTree.print();


	return 0;
}