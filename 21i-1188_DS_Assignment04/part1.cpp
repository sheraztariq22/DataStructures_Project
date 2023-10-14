#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <fstream>


class Node
{
public:
	int data;
	Node* right;
	Node* down;
	
	Node() 
	{
		data = 0;
		right = NULL;
		down = NULL;
	}
	
	Node(int data)
	{
		this->data = data;
		right = NULL;
		down = NULL;
	}
};

class QuadTree
{
public:
	Node* root;
	QuadTree* NW;
	QuadTree* NE;
	QuadTree* SW;
	QuadTree* SE;
	
	QuadTree()
	{
		root = NULL;
		NW = NULL;
		NE = NULL;
		SW = NULL;
		SE = NULL;
	}
};


void convertTo2dLL(int** array, int row, int col) {
	Node* head = new Node(-1);
	Node* temp = head;

	//itrating the each row
	for (int i = 0; i < row; i++) {
		Node* rowHead = new Node(-1);
		Node* rowTemp = rowHead;
		//iterating the each column
		for (int j = 0; j < col; j++) {
			Node* newNode = new Node(array[i][j]);
			rowTemp->right = newNode;
			rowTemp = rowTemp->right;
		}
		temp->down = rowHead->right;
		temp = temp->down;
	}

	//inserting end of black pixels indicator
	for (int i = 0; i < col; i++)
	{
		Node* newNode = new Node(-1);
		temp->right = newNode;
		temp = temp->right;
	}

	//again itrating over each coloum in the row again
	for (int i = 0; i < col; i++) {
		Node* colHead = new Node(-1);
		Node* colTemp = colHead;
		//iterating the each row
		for (int j = 0; j < row; j++) {
			Node* newNode = new Node(array[j][i]);
			colTemp->down = newNode;
			colTemp = colTemp->down;
		}
		temp->right = colHead->down;
		temp = temp->right;
	}

	//inserting end of white pixels indicator
	Node* endWhite = new Node(-2);
	temp->right = endWhite;
	temp = temp->right;

	//moving to next row
	temp->down = new Node(-2);
	temp = temp->down;

	//printing the 2D linked list
	Node* rowTemp = head->down;
	while (rowTemp != NULL) {
		Node* colTemp = rowTemp;
		while (colTemp != NULL)
		{
			std::cout << colTemp->data << " ";
			colTemp = colTemp->right;
		}
		std::cout << std::endl;
		rowTemp = rowTemp->down;
	}
	
	//Passing the 2D linked list to the quad tree
	QuadTree* quadTree = new QuadTree();
	quadTree->root = head;
	quadTree->NW = new QuadTree();
	quadTree->NE = new QuadTree();
	quadTree->SW = new QuadTree();
	quadTree->SE = new QuadTree();
	
	//converting the 2D linked list to quad tree
	Node* rowTemp1 = head->down;
	Node* colTemp1 = rowTemp1;
	while (rowTemp1 != NULL) {
		colTemp1 = rowTemp1;
		while (colTemp1 != NULL)
		{
			if (colTemp1->data == -1) {
				quadTree->NW->root = colTemp1;
				quadTree->NW->NW = new QuadTree();
				quadTree->NW->NE = new QuadTree();
				quadTree->NW->SW = new QuadTree();
				quadTree->NW->SE = new QuadTree();
			}
			else if (colTemp1->data == -2) {
				quadTree->NE->root = colTemp1;
				quadTree->NE->NW = new QuadTree();
				quadTree->NE->NE = new QuadTree();
				quadTree->NE->SW = new QuadTree();
				quadTree->NE->SE = new QuadTree();
			}
			
			else if (colTemp1->data == -3) {
				quadTree->SW->root = colTemp1;
				quadTree->SW->NW = new QuadTree();
				quadTree->SW->NE = new QuadTree();
				quadTree->SW->SW = new QuadTree();
				quadTree->SW->SE = new QuadTree();
			}

			else if (colTemp1->data == -4) {
				quadTree->SE->root = colTemp1;
				quadTree->SE->NW = new QuadTree();
				quadTree->SE->NE = new QuadTree();
				quadTree->SE->SW = new QuadTree();
				quadTree->SE->SE = new QuadTree();
			}
			colTemp1 = colTemp1->right;
		}
		rowTemp1 = rowTemp1->down;
	}
	
	//printing the quad tree
	std::cout << "Quad Tree" << std::endl;
	std::cout << "NW" << std::endl;
	Node* rowTemp2 = quadTree->NW->root->down;
	while (rowTemp2 != NULL) {
		Node* colTemp2 = rowTemp2;
		while (colTemp2 != NULL)
		{
			std::cout << colTemp2->data << " ";
			colTemp2 = colTemp2->right;
		}
		std::cout << std::endl;
		rowTemp2 = rowTemp2->down;
	}
	
	std::cout << "NE" << std::endl;
	Node* rowTemp3 = quadTree->NE->root->down;
	while (rowTemp3 != NULL) {
		Node* colTemp3 = rowTemp3;
		while (colTemp3 != NULL)
		{
			std::cout << colTemp3->data << " ";
			colTemp3 = colTemp3->right;
		}
		std::cout << std::endl;
		rowTemp3 = rowTemp3->down;
	}
	
	/*std::cout << "SW" << std::endl;
	Node* rowTemp4 = quadTree->SW->root->down;
	while (rowTemp4 != NULL) {
		Node* colTemp4 = rowTemp4;
		while (colTemp4 != NULL)
		{
			std::cout << colTemp4->data << " ";
			colTemp4 = colTemp4->right;
		}
		std::cout << std::endl;
		rowTemp4 = rowTemp4->down;
	}
	
	std::cout << "SE" << std::endl;
	Node* rowTemp5 = quadTree->SE->root->down;
	while (rowTemp5 != NULL) {
		Node* colTemp5 = rowTemp5;
		while (colTemp5 != NULL)
		{
			std::cout << colTemp5->data << " ";
			colTemp5 = colTemp5->right;
		}
		std::cout << std::endl;
		rowTemp5 = rowTemp5->down;
	}*/
	
	//deleting the quad tree
	delete quadTree->NW->NW;
	delete quadTree->NW->NE;
	delete quadTree->NW->SW;
	delete quadTree->NW->SE;
	delete quadTree->NW;
	delete quadTree->NE->NW;
	delete quadTree->NE->NE;
	delete quadTree->NE->SW;
	delete quadTree->NE->SE;
	delete quadTree->NE;
	delete quadTree->SW->NW;
	delete quadTree->SW->NE;
	delete quadTree->SW->SW;
	delete quadTree->SW->SE;
	delete quadTree->SW;
	delete quadTree->SE->NW;
	delete quadTree->SE->NE;
	delete quadTree->SE->SW;
	delete quadTree->SE->SE;
	delete quadTree->SE;
	delete quadTree;
	
	

	
	//deleting the linked list
	/*rowTemp = head->down;
	while (rowTemp != NULL) {
		Node* colTemp = rowTemp;
		while (colTemp != NULL)
		{
			Node* temp = colTemp;
			colTemp = colTemp->right;
			delete temp;
		}
		Node* temp = rowTemp;
		rowTemp = rowTemp->down;
		delete temp;
	}
	delete head;*/

}

//function to traverse the quad tree
void traverseQuadTree(QuadTree* root, int rowStart, int rowEnd, int startCol, int endCol, int** image) {
	
	root->root = root->root->right;
	root = NULL;
	
	if (root == NULL || rowStart > rowEnd || startCol > endCol) {
		return;
	}
	
	else if (root->root->data == -1) {
		for (int i = rowStart; i <= rowEnd; i++) {
			for (int j = startCol; j <= endCol; j++) {
				image[i][j] = 0;
			}
		}
	}

	else if (root->root->data == -2) {
		for (int i = rowStart; i <= rowEnd; i++) {
			for (int j = startCol; j <= endCol; j++) {
				image[i][j] = 255;
			}
		}
	}

	else if (root->root->data == -3) {
		for (int i = rowStart; i <= rowEnd; i++) {
			for (int j = startCol; j <= endCol; j++) {
				if (i >= rowStart && i <= (rowStart + rowEnd) / 2 && j >= startCol && j <= (startCol + endCol) / 2) {
					image[i][j] = 0;
				}
				else {
					image[i][j] = 255;
				}
			}
		}
	}

	else if (root->root->data == -4) {
		for (int i = rowStart; i <= rowEnd; i++) {
			for (int j = startCol; j <= endCol; j++) {
				if (i >= rowStart && i <= (rowStart + rowEnd) / 2 && j >= startCol && j <= (startCol + endCol) / 2) {
					image[i][j] = 255;
				}
				else {
					image[i][j] = 0;
				}
			}
		}
	}

	else 
	{
		traverseQuadTree(root->NW, rowStart, (rowStart + rowEnd) / 2, startCol, (startCol + endCol) / 2, image);
		traverseQuadTree(root->NE, rowStart, (rowStart + rowEnd) / 2, (startCol + endCol) / 2 + 1, endCol, image);
		traverseQuadTree(root->SW, (rowStart + rowEnd) / 2 + 1, rowEnd, startCol, (startCol + endCol) / 2, image);
		traverseQuadTree(root->SE, (rowStart + rowEnd) / 2 + 1, rowEnd, (startCol + endCol) / 2 + 1, endCol, image);

	}
	
	//after traversing now we will write the each node in separate file
	std::ofstream file("quadTree.txt", std::ios::app);
	Node* rowTemp = root->root->down;
	if (file.is_open()) {
        
		while (rowTemp != NULL) {
			Node* colTemp = rowTemp;
			while (colTemp != NULL)
			{
				file << colTemp->data << " ";
				colTemp = colTemp->right;
			}
			file << std::endl;
			rowTemp = rowTemp->down;
		}
		file << std::endl;
	}
	
	else 
	{
		std::cout << "File not opened" << std::endl;
	}
	file.close();
	
	
}

//the function to decode the image and recursively constructing the quad tree
void reconstructImageFromQuadTree(const std::string& rootFilePath, const std::string& imagePath) {
	//reading the file
	std::ifstream file(rootFilePath);
	int data;
	int row = 0;
	int col = 0;
	int** array = new int* [row];
	while (file >> data) {
		if (data == -5) {
			row++;
			col = 0;
			array = new int* [row];
		}
		else if (data == -6) {
			break;
		}
		else {
			array[row - 1][col] = data;
			col++;
		}
	}
	file.close();

	//constructing the quad tree
	QuadTree* quadTree = new QuadTree();
	quadTree->root = new Node();
	quadTree->root->data = array[0][0];
	quadTree->root->right = NULL;
	quadTree->root->down = NULL;
	
	

	//reconstructing the linked list
	Node* rowTemp = quadTree->root;
	for (int i = 0; i < row; i++) {
		Node* colTemp = rowTemp;
		for (int j = 0; j < col; j++) {
			Node* temp = new Node();
			temp->data = array[i][j];
			temp->right = NULL;
			temp->down = NULL;
			colTemp->right = temp;
			colTemp = colTemp->right;
		}
		Node* temp = new Node();
		temp->data = -5;
		temp->right = NULL;
		temp->down = NULL;
		colTemp->right = temp;
		rowTemp->down = temp;
		rowTemp = rowTemp->down;
	}

	//reconstructing the quad tree

	//traversing the quad tree
	cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
	int** imageArray = new int* [image.rows];
	for (int i = 0; i < image.rows; i++) {
		imageArray[i] = new int[image.cols];
	}
	traverseQuadTree(quadTree, 0, image.rows - 1, 0, image.cols - 1, imageArray);
}

	
int main()
{
	cv::Mat image = cv::imread("C:\\Users\\Hp EliteBook\\source\\repos\\OpenCV_DS_Assignment04\\OpenCV_DS_Assignment04\\t1.bmp", cv::IMREAD_GRAYSCALE);
	cv::imshow("Original Image ", image);
	cv::waitKey(0);

	int row = image.rows;
	int col = image.cols;

	int** array = new int* [row];
	for (int i = 0; i < row; i++)
	{
		array[i] = new int[col];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			array[i][j] = image.at<uchar>(i, j);
		}
	}

	convertTo2dLL(array, row, col);
	Node* head = NULL;
	//traversing the quad tree
	QuadTree* quadTree = new QuadTree();
	quadTree->root = NULL;
	
	traverseQuadTree(quadTree, 0, row - 1, 0, col - 1, array);
	
	//reconstructing the image from quad tree
	reconstructImageFromQuadTree("quadTree.txt", "C:\\Users\\Hp EliteBook\\source\\repos\\OpenCV_DS_Assignment04\\OpenCV_DS_Assignment04\\t1.bmp");

	for (int i = 0; i < row; i++)
	{
		delete[] array[i];
	}
	delete[] array;
	

	
	return 0;
}
