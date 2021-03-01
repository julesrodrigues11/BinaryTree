#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

//Class for Binary Search Tree
class BinarySearchTree
{
public:
	class TreeNode
	{
		//Contains integer variable for data contained
		//And TreeNode pointers for leftChild, rightChild and parent
	public:
		int data;
		TreeNode* leftChild;
		TreeNode* rightChild;
		TreeNode* parent;

		//Constructor for TreeNode class
		TreeNode(int d)
		{
			data = d;
			leftChild = nullptr;
			rightChild = nullptr;
			parent = nullptr;
		}

		//Setter function for Left Child
		void setLeftChild(TreeNode* n)
		{
			leftChild = n;
			if (n != nullptr)
			{
				n->parent = this;
			}
		}

		//Setter function for Right Child
		void setRightChild(TreeNode* n)
		{
			rightChild = n;
			if (n != nullptr)
			{
				n->parent = this;
			}
		}
	};

	//Find Function
	//Returns a pointer to the TreeNode with the given value
	//Returns a nullptr if nothing found
	TreeNode* find(int findMe)
	{
		TreeNode* n = root;
		while (n != nullptr)
		{
			if (n->data==findMe)
			{
				return n;
			}

			if (n->data < findMe)
			{
				n = n->rightChild;
			}
			else
			{
				n = n->leftChild;
			}
		}
		return nullptr;
	}

	//Function to output subtree for a given node
	//Runs outputSubtree recursively and prints the data of the given node
	void outputSubTree(TreeNode* n)
	{
		if (n != nullptr)
		{
			outputSubTree(n->leftChild);
			std::cout << n->data << " ";
			outputSubTree(n->rightChild);
		}
	}

	//Function to output the data within a Tree
	//If the root is a nullptr, it prints "Empty Tree"
	//Runs outputSubTree function for the root node which then calls it recursively
	void output()
	{
		if (root == nullptr)
		{
			std::cout << "Empty Tree" << std::endl;
		}
		else
		{
			outputSubTree(root);
			std::cout << std::endl;
		}
	}

	//Function to insert a node with value passed as argument
	//If the root is a nullptr, aka the tree is empty
	//It will create a new TreeNode and assign root to this value
	//Else, it runs the insertBelow function recursively
	void insert(int value)
	{
		if (root == nullptr)
		{
			root = new TreeNode(value);
		}
		else
		{
			insertBelow(root, value);
		}
	}

	//Function to insert a node with given value below another node
	//Runs the function recursively to insert it in the right spot
	void insertBelow(TreeNode* node, int value)
	{
		//If the value passed as an argument is greater than the current node,
		//It will seek to insert it on the right hand side of the TreeNode,
		//Else, it will seek to insert it on the left hand side
		if (value > node->data)
		{
			if (node->rightChild == nullptr)
			{
				node->setRightChild(new TreeNode(value));
			}
			else
			{
				insertBelow(node->rightChild, value);
			}
		}
		else
		{
			if (node->leftChild == nullptr)
			{
				node->setLeftChild(new TreeNode(value));
			}
			else
			{
				insertBelow(node->leftChild, value);
			}
		}
	}

	//Function to remove a value from a tree
	//Finds the value within the tree, and if found, seeks to remove it from the tree
	void removeValue(int value)
	{
		TreeNode* n = find(value);
		if (n != nullptr)
		{
			//If the node to be removed has no children, it will replaceNode the given node with a nullptr
			if (n->leftChild == nullptr && n->rightChild == nullptr)
			{
				replaceNode(n, nullptr);
			}
			//If the node to be removed has only one child on right hand side, it will replaceNode with the right child
			else if (n->leftChild == nullptr)
			{
				replaceNode(n, n->rightChild);
			}
			//If the node to be removed has only one child on left hand side, it will replaceNode with the left child
			else if (n->rightChild == nullptr)
			{
				replaceNode(n, n->leftChild);
			}
			//Else, if the node has two children, it will seek out either the greatest value on the left hand side, or the lowest value on the left hand side
			//Seeks the greatest value on the left hand side in this case
			//Reassigns the value of n to value of m
			//Then calls replaceNode to replace m, with its left child
			else
			{
				TreeNode* m = n->leftChild;
				while (m->rightChild != nullptr)
				{
					m = m->rightChild;
				}
				n->data = m->data;
				replaceNode(m, m->leftChild);
			}
		}
	}

	//Function to generate a vector populated with random values
	//Generate random values and then push back to vector
	//Return this vector at the end of the function
	std::vector<int> randomValues(int howMany)
	{
		std::vector<int> random;
		int randomInt;
		for (int i = 0; i < howMany; i++)
		{
			randomInt = rand() % 50;
			random.push_back(randomInt);
		}

		return random;
	}

	//Function to insert all values in the vector to the tree
	//Calls insert function for all values in the vector
	//Outputs values if printResults is set to true
	void insertAll(std::vector<int> values, bool printResults)
	{
		for (int i = 0; i < values.size(); i++)
		{
			insert(values[i]);
			if (printResults)
			{
				output();
			}
		}
	}

	//Function too remove all values in the vector from the tree
	//Calls removeValue function for all values in the vector
	//Outputs values if printResults is set to true
	void removeAll(std::vector<int> values, bool printResults)
	{
		for (int i = 0; i < values.size(); i++)
		{
			removeValue(values[i]);
			if (printResults)
			{
				output();
			}
		}
	}

private:
	//TreeNode pointer variable for root node
	TreeNode* root;

	//Function to replaceNode
	//Replaces given node with the replacement node
	void replaceNode(TreeNode* node, TreeNode* replacement)
	{
		//TreeNode pointer variable for the parent of the node to be replaced
		TreeNode* parent = node->parent;
		//If the parent is a nullptr, it means it's the highest node in the tree
		//Replace root with replacement, and reset the parent of the root to nullptr
		if (parent == nullptr)
		{
			root = replacement;
			if (root != nullptr)
			{
				root->parent = nullptr;
			}
		}
		//Else if the node to be replaced is the leftChild of the parent,
		//setLeftChild to replacement node
		else if (node == parent->leftChild)
		{
			parent->setLeftChild(replacement);
		}
		//Else if the node to be replaced is the rightChild of the parent,
		//setRightChild to replacement node
		else
		{
			parent->setRightChild(replacement);
		}
	}
};

//Main function
int main()
{
	//Random time seed for generating random numbers
	srand((unsigned)time(NULL));

	//Number of values we need for the tree
	int numValues = 10;
	bool printResults = true;

	//Making an object of type BinarySearchTree and making a vector populated with random values
	BinarySearchTree* t = new BinarySearchTree();
	std::vector<int> values = t->randomValues(numValues);

	//Prints values vector out
	if (printResults)
	{
		std::cout << "Input values : ";
		for (int i = 0; i < numValues; i++)
		{
			std::cout << values[i] << " ";
		}
		std::cout << std::endl;
	}

	//Runs insertAll function for the tree
	t->insertAll(values, printResults);

	//Runs removeAll function for the tree
	t->removeAll(values, printResults);

	//Delete t to prevent memory leaks
	delete t;

	return 1;
}