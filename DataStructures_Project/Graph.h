
#include <iostream>

using namespace std;

class Graph {

public:
	int num_nodes;
	int matrix_size;
	char** matrix;
	Graph(int num_nodes)
	{
		this->num_nodes = num_nodes;
		matrix_size = num_nodes * 2;
		matrix = new char* [matrix_size];
		for (int i = 0; i < matrix_size; i++)
		{
			matrix[i] = new char[matrix_size];
		}
		for (int i = 0; i < matrix_size; i++)
		{
			for (int j = 0; j < matrix_size; j++)
			{
				matrix[i][j] = ' ';
			}
		}
	}

	~Graph()
	{
		for (int i = 0; i < matrix_size; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	void add_nodes(int location)
	{
		int crystal_x = rand() % matrix_size;
		int crystal_y = rand() % matrix_size;
		matrix[crystal_x][crystal_y] = '*';
	}

	void add_edges(int location1, int location2, int weight)
	{
		matrix[location1][location2] = weight;
		matrix[location2][location1] = weight;
	}

	void remove_node(int location)
	{
		for (int i = 0; i < matrix_size; i++)
		{
			matrix[location][i] = 0;
			matrix[i][location] = 0;
		}
	}

	void remove_edge(int location1, int location2)
	{
		matrix[location1][location2] = 0;
		matrix[location2][location1] = 0;
	}

	//floyd's algorithm to find the shortest path between two nodes
	int get_shortest_path_floyds(int start_loc, int end_loc) {
		int** dist = new int* [matrix_size];
		for (int i = 0; i < matrix_size; i++)
		{
			dist[i] = new int[matrix_size];
		}
		for (int i = 0; i < matrix_size; i++)
		{
			for (int j = 0; j < matrix_size; j++)
			{
				dist[i][j] = matrix[i][j];
			}
		}
		for (int k = 0; k < matrix_size; k++)
		{
			for (int i = 0; i < matrix_size; i++)
			{
				for (int j = 0; j < matrix_size; j++)
				{
					if (dist[i][k] + dist[k][j] < dist[i][j])
					{
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}
		int shortest_path = dist[start_loc][end_loc];
		for (int i = 0; i < matrix_size; i++)
		{
			delete[] dist[i];
		}
		delete[] dist;
		return shortest_path;
	}

	//prims algorithm to find the minimum spanning tree
	int get_min_spanning_tree_prims() {
		int** dist = new int* [matrix_size];
		for (int i = 0; i < matrix_size; i++)
		{
			dist[i] = new int[matrix_size];
		}
		for (int i = 0; i < matrix_size; i++)
		{
			for (int j = 0; j < matrix_size; j++)
			{
				dist[i][j] = matrix[i][j];
			}
		}
		int* visited = new int[matrix_size];
		for (int i = 0; i < matrix_size; i++)
		{
			visited[i] = 0;
		}
		int min_spanning_tree = 0;
		visited[0] = 1;
		int num_visited = 1;
		while (num_visited < matrix_size)
		{
			int min_dist = 999999;
			int min_i = 0;
			int min_j = 0;
			for (int i = 0; i < matrix_size; i++)
			{
				if (visited[i] == 1)
				{
					for (int j = 0; j < matrix_size; j++)
					{
						if (visited[j] == 0)
						{
							if (dist[i][j] < min_dist)
							{
								min_dist = dist[i][j];
								min_i = i;
								min_j = j;
							}
						}
					}
				}
			}
			min_spanning_tree += min_dist;
			visited[min_j] = 1;
			num_visited++;
		}
		for (int i = 0; i < matrix_size; i++)
		{
			delete[] dist[i];
		}
		delete[] dist;
		delete[] visited;
		return min_spanning_tree;
	}

	//kruskals algorithm to find the minimum spanning tree
	int get_min_spanning_kruskals() {
		int** dist = new int* [matrix_size];
		for (int i = 0; i < matrix_size; i++)
		{
			dist[i] = new int[matrix_size];
		}
		for (int i = 0; i < matrix_size; i++)
		{
			for (int j = 0; j < matrix_size; j++)
			{
				dist[i][j] = matrix[i][j];
			}
		}
		int* visited = new int[matrix_size];
		for (int i = 0; i < matrix_size; i++)
		{
			visited[i] = 0;
		}
		int min_spanning_tree = 0;
		int num_visited = 0;
		while (num_visited < matrix_size - 1)
		{
			int min_dist = 999999;
			int min_i = 0;
			int min_j = 0;
			for (int i = 0; i < matrix_size; i++)
			{
				for (int j = 0; j < matrix_size; j++)
				{
					if (dist[i][j] < min_dist)
					{
						min_dist = dist[i][j];
						min_i = i;
						min_j = j;
					}
				}
			}
			if (visited[min_i] == 0 || visited[min_j] == 0)
			{
				min_spanning_tree += min_dist;
				visited[min_i] = 1;
				visited[min_j] = 1;
				num_visited++;
			}
			dist[min_i][min_j] = 999999;
			dist[min_j][min_i] = 999999;
		}
		for (int i = 0; i < matrix_size; i++)
		{
			delete[] dist[i];
		}
		delete[] dist;
		delete[] visited;
		return min_spanning_tree;
	}

	//dijkstras algorithm to find the shortest path
	int get_shortest_path_dijkstras(int start_loc, int end_loc) {
		int* dist = new int[matrix_size];
		int* visited = new int[matrix_size];
		for (int i = 0; i < matrix_size; i++)
		{
			dist[i] = 999999;
			visited[i] = 0;
		}
		dist[start_loc] = 0;
		int num_visited = 0;
		while (num_visited < matrix_size)
		{
			int min_dist = 999999;
			int min_i = 0;
			for (int i = 0; i < matrix_size; i++)
			{
				if (visited[i] == 0)
				{
					if (dist[i] < min_dist)
					{
						min_dist = dist[i];
						min_i = i;
					}
				}
			}
			visited[min_i] = 1;
			num_visited++;
			for (int i = 0; i < matrix_size; i++)
			{
				if (visited[i] == 0)
				{
					if (dist[min_i] + matrix[min_i][i] < dist[i])
					{
						dist[i] = dist[min_i] + matrix[min_i][i];
					}
				}
			}
		}
		int shortest_path = dist[end_loc];
		delete[] dist;
		delete[] visited;
		return shortest_path;
	}

	int get_matrix_size()
	{
		return matrix_size;
	}

	int getWeight(int i, int j)
	{
		return matrix[i][j];
	}

	//determine shortest path using floyd warshall
	int get_shortest_path_floyd_warshall(int start_loc, int end_loc) {
		int** dist = new int* [matrix_size];
		for (int i = 0; i < matrix_size; i++)
		{
			dist[i] = new int[matrix_size];
		}
		for (int i = 0; i < matrix_size; i++)
		{
			for (int j = 0; j < matrix_size; j++)
			{
				dist[i][j] = matrix[i][j];
			}
		}
		for (int k = 0; k < matrix_size; k++)
		{
			for (int i = 0; i < matrix_size; i++)
			{
				for (int j = 0; j < matrix_size; j++)
				{
					if (dist[i][k] + dist[k][j] < dist[i][j])
					{
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}
	    int shortest_path=dist[start_loc][end_loc];
		for (int i = 0; i < matrix_size; i++)
		{
			delete[] dist[i];
		}
		delete[] dist;
		
		return shortest_path;
	}
	
	
	


};