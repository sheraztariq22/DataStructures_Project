
#include <iostream>
#include "Map.h"

using namespace std;

class AVLTree
{
public:
	struct Node
	{
		int data;
		Node* left;
		Node* right;
		int height;
		int count;
		int ID;
	};
	Node* root;
	int height(Node* node)
	{
		if (node == NULL)
			return 0;
		return node->height;
	}
	int max(int a, int b)
	{
		return (a > b) ? a : b;
	}
	Node* newNode(int data)
	{
		Node* node = new Node();
		node->data = data;
		node->left = NULL;
		node->right = NULL;
		node->height = 1;
		return node;
	}
	Node* rightRotate(Node* node)
	{
		Node* left = node->left;
		Node* right = left->right;
		left->right = node;
		node->left = right;
		node->height = max(height(node->left), height(node->right)) + 1;
		left->height = max(height(left->left), height(left->right)) + 1;
		return left;
	}
	Node* leftRotate(Node* node)
	{
		Node* right = node->right;
		Node* left = right->left;
		right->left = node;
		node->right = left;
		node->height = max(height(node->left), height(node->right)) + 1;
		right->height = max(height(right->left), height(right->right)) + 1;
		return right;
	}
	int getBalance(Node* node)
	{
		if (node == NULL)
			return 0;
		return height(node->left) - height(node->right);
	}
	Node* insert(Node* node, int data)
	{
		if (node == NULL)
			return newNode(data);
		if (data < node->data)
			node->left = insert(node->left, data);
		else if (data > node->data)
			node->right = insert(node->right, data);
		else
			return node;
		node->height = 1 + max(height(node->left), height(node->right));
		int balance = getBalance(node);
		if (balance > 1 && data < node->left->data)
			return rightRotate(node);
		if (balance < -1 && data > node->right->data)
			return leftRotate(node);
		if (balance > 1 && data > node->left->data)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
		if (balance < -1 && data < node->right->data)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
		return node;
	}
	Node* minValueNode(Node* node)
	{
		Node* current = node;
		while (current->left != NULL)
			current = current->left;
		return current;
	}

	Node* deleteNode(Node* node, int data)
	{
		if (node == NULL)
			return node;
		if (data < node->data)
			node->left = deleteNode(node->left, data);
		else if (data > node->data)
			node->right = deleteNode(node->right, data);
		else
		{
			if ((node->left == NULL) || (node->right == NULL))
			{
				Node* temp = node->left ? node->left : node->right;
				if (temp == NULL)
				{
					temp = node;
					node = NULL;
				}
				else
					*node = *temp;
				free(temp);
			}
			else
			{
				Node* temp = minValueNode(node->right);
				node->data = temp->data;
				node->right = deleteNode(node->right, temp->data);
			}
		}
		if (node == NULL)
			return node;
		node->height = 1 + max(height(node->left), height(node->right));
		int balance = getBalance(node);
		if (balance > 1 && getBalance(node->left) >= 0)
			return rightRotate(node);
		if (balance > 1 && getBalance(node->left) < 0)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
		if (balance < -1 && getBalance(node->right) <= 0)
			return leftRotate(node);
		if (balance < -1 && getBalance(node->right) > 0)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
		return node;
	}

	void setID(Node* node, int id)
	{
		if (node != NULL)
		{
			node->ID = id;
			setID(node->left, id * 2);
			setID(node->right, id * 2 + 1);
		}
	}

	void setCount(Node* node)
	{
		if (node != NULL)
		{
			node->count = 1;
			if (node->left != NULL)
				node->count += node->left->count;
			if (node->right != NULL)
				node->count += node->right->count;
			setCount(node->left);
			setCount(node->right);
		}
	}

	int getID(Node* node, int data)
	{
		if (node == NULL)
			return -1;
		if (node->data == data)
			return node->ID;
		if (data < node->data)
			return getID(node->left, data);
		else
			return getID(node->right, data);
	}

	int getCount(Node* node, int data)
	{
		if (node == NULL)
			return 0;
		if (node->data == data)
			return node->count;
		if (data < node->data)
			return getCount(node->left, data);
		else
			return getCount(node->right, data);
	}

	void preOrder(Node* node)
	{
		if (node != NULL)
		{
			cout << node->data << " ";
			preOrder(node->left);
			preOrder(node->right);
		}
	}

	void inOrder(Node* node)
	{
		if (node != NULL)
		{
			inOrder(node->left);
			cout << node->data << " ";
			inOrder(node->right);
		}
	}

	void postOrder(Node* node)
	{
		if (node != NULL)
		{
			postOrder(node->left);
			postOrder(node->right);
			cout << node->data << " ";
		}
	}


	//create a graph from the tree
	void createGraph(Node* node, int** graph)
	{
		int dx[] = { -1, 1, 0, 0 }; // Directions for neighboring cells
		int dy[] = { 0, 0, -1, 1 };
		if (node != NULL)
		{
			for (int i = 0; i < 4; i++)
			{
				int x = node->ID / 2 / 2;
				int y = node->ID / 2 % 2;
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (nx >= 0 && nx < 2 && ny >= 0 && ny < 2)
				{
					int neighborID = nx * 2 + ny;
					int neighborData = getData(root, neighborID);
					if (neighborData != -1)
					{
						graph[node->data][neighborData] = 1;
						graph[neighborData][node->data] = 1;
					}
				}
			}
			createGraph(node->left, graph);
			createGraph(node->right, graph);
		}


	}

	//getData calling
	int getData(Node* node, int ID)
	{
		if (node == NULL)
			return -1;
		if (node->ID == ID)
			return node->data;
		if (ID < node->ID)
			return getData(node->left, ID);
		else
			return getData(node->right, ID);
	}

	//print the graph
	void printGraph(int** graph)
	{
		for (int i = 0; i < 16; i++)
		{
			cout << i << ": ";
			for (int j = 0; j < 16; j++)
				cout << graph[i][j] << " ";
			cout << endl;
		}
	}
	//INF
	const int INF = 100;
	//Implement Floyd's algorithm to calculate the shortest path between a custom locationand the crystal
	void floyd(int** graph, int** dist, int** path)
	{
		for (int i = 0; i < 16; i++)
			for (int j = 0; j < 16; j++)
			{
				dist[i][j] = graph[i][j];
				if (i == j)
					path[i][j] = -1;
				else if (dist[i][j] != INF)
					path[i][j] = i;
				else
					path[i][j] = -1;
			}
		for (int k = 0; k < 16; k++)
			for (int i = 0; i < 16; i++)
				for (int j = 0; j < 16; j++)
					if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
					{
						dist[i][j] = dist[i][k] + dist[k][j];
						path[i][j] = path[k][j];
					}
	}


	//print the path
	void printPathfloyds(char** path, int start, int end)
	{
		if (path[start][end] == -1)
			cout << end << " ";
		else
		{
			printPathfloyds(path, start, path[start][end]);
			printPathfloyds(path, path[start][end], end);
		}
	}



};

class Player {
private:
	int current_location;
public:
	Player()
	{
		this->current_location = 0;
	}

	Player(int current_location) {
		this->current_location = current_location;

	}

	~Player()
	{
	}

	void set_currentLocation(int current_location)
	{
		this->current_location = current_location;
	}

	int get_next_move()
	{
		//the player will automatically move to the next location
		for (int i = 0; i < 10; i++)
		{
			return current_location + 1;
		}
		//return current_location + 1;
	}

	int get_location()
	{
		return current_location;
	}
};