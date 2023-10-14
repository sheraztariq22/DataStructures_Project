#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>

using namespace std;

class Node
{
public:
	int data;
	Node* right;
	Node* down;
	Node* NE;
	Node* NW;
	Node* SE;
	Node* SW;

	Node()
	{
		data = 0;
		right = NULL;
		down = NULL;
		NE = NULL;
		NW = NULL;
		SE = NULL;
		SW = NULL;
	}

	Node(int data)
	{
		this->data = data;
		right = NULL;
		down = NULL;
		NE = NULL;
		NW = NULL;
		SE = NULL;
		SW = NULL;
	}
};

class QuadTree
{
public:
	Node* root;
	int color;
	int x, y;
	QuadTree* NW;
	QuadTree* NE;
	QuadTree* SW;
	QuadTree* SE;

	QuadTree()
	{
		color = 0;
		x = 0;
		y = 0;
		root = NULL;
		NW = NULL;
		NE = NULL;
		SW = NULL;
		SE = NULL;
	}
};

void reconstructImage(QuadTree* root, int** image, int x, int y, int size)
{
	QuadTree* NW = new QuadTree();
	QuadTree* NE = new QuadTree();
	QuadTree* SW = new QuadTree();
	QuadTree* SE = new QuadTree();
	
	if (root->color == 0)
	{
		for (int i = x; i < x + size; i++)
		{
			for (int j = y; j < y + size; j++)
			{
				image[i][j] = 0;
			}
		}
	}
	else if (root->color == 1)
	{
		for (int i = x; i < x + size; i++)
		{
			for (int j = y; j < y + size; j++)
			{
				image[i][j] = 255;
			}
		}
	}
	else
	{
		reconstructImage(root->NW, image, x, y, size / 2);
		reconstructImage(root->NE, image, x, y + size / 2, size / 2);
		reconstructImage(root->SW, image, x + size / 2, y, size / 2);
		reconstructImage(root->SE, image, x + size / 2, y + size / 2, size / 2);
	}
}

void assignColors(Node* node, cv::Mat& img)
{
	if (node->data == 0)
	{
		for (int i = node->right->data; i < node->right->data + node->down->data; i++)
		{
			for (int j = node->down->data; j < node->down->data + node->right->data; j++)
			{
				img.at<uchar>(i, j) = 0;
			}
		}
	}
	else if (node->data == 1)
	{
		for (int i = node->right->data; i < node->right->data + node->down->data; i++)
		{
			for (int j = node->down->data; j < node->down->data + node->right->data; j++)
			{
				img.at<uchar>(i, j) = 255;
			}
		}
	}
	else
	{
		assignColors(node->NW, img);
		assignColors(node->NE, img);
		assignColors(node->SW, img);
		assignColors(node->SE, img);
	}
}

void printTree(Node* node)
{
	if (node->data == 0)
	{
		cout << "0" << endl;
	}
	else if (node->data == 1)
	{
		cout << "1" << endl;
	}
	else
	{
		cout << "2" << endl;
		printTree(node->NW);
		printTree(node->NE);
		printTree(node->SW);
		printTree(node->SE);
	}
}

int main() {
	//read quadtree from file
	ifstream file("quadtree.txt");
	if (!file.is_open())
	{
		cout << "File not found" << endl;
		return 1;
	}
	
	int x=0, y=0, size=0;
	QuadTree* root = NULL;
	string line;
	while (getline(file, line))
	{
		QuadTree* node = new QuadTree();
		if (line == "0")
		{
			node->color = 0;
		}
		else if (line == "1")
		{
			node->color = 1;
		}
		else
		{
			node->color = 2;
		}
		if (root == NULL)
		{
			root = node;
		}
		else
		{
			QuadTree* temp = root;
			while (temp->NW != NULL)
			{
				temp = temp->NW;
			}
			temp->NW = node;
		}
	}
	
	//reconstruct image from quadtree
	int** image = new int* [512];
	for (int i = 0; i < 512; i++)
	{
		image[i] = new int[512];
	}
	reconstructImage(root, image, 0, 0, 512);
	
	//write image to file using imwrite function
	Node* head = NULL;
	cv::Mat img(512, 512, CV_8UC1);
	assignColors(head, img);
	cv::imwrite("image.png", img);
	
	//writing the Quadtree to a file using recursion
	ofstream file2("quadtree2.txt");
	if (!file2.is_open())
	{
		cout << "File not found" << endl;
		return 1;
	}
	
	printTree(head);
	
	return 0;
}