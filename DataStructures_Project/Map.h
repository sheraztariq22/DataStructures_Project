#include <iostream>
#include <random>
#include <ctime>
using namespace std;

struct Node {
	int x;
	int y;
	char value;

	Node(int x_, int y_, char value_) : x(x_), y(y_), value(value_) {}
};

class Map {
private:
	const int size = 20;
	char matrix[20][20];
	int crystal_x;
	int crystal_y;
	int reward_x;
	int reward_y;
	int death_x;
	int death_y;
	int obstacle_x;
	int obstacle_y;
	int monster_x;
	int monster_y;
	int weight;
	int score;
	int current_location;
public:
	char Monsters[3] = { '&', '$', '@' };
	char rewards[3] = { 'J', 'P','W' };
	Map()
	{
		crystal_x = 0;
		crystal_y = 0;
		reward_x = 0;
		reward_y = 0;
		death_x = 0;
		death_y = 0;
		obstacle_x = 0;
		obstacle_y = 0;
		monster_x = 0;
		monster_y = 0;
		weight = 0;
		score = 0;
		current_location = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				matrix[i][j] = 'C';
		}

		for (int i = 0; i < 3; i++)
		{
			rewards[i];
		}
		for (int i = 0; i < 3; i++)
		{
			Monsters[i];
		}
	}

	Map(int x, int y)
	{
		crystal_x = x;
		crystal_y = y;
		reward_x = x;
		reward_y = y;
		death_x = x;
		death_y = y;
		obstacle_x = x;
		obstacle_y = y;
		monster_x = x;
		monster_y = y;
		weight = 0;
		score = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				matrix[i][j] = 'C';
		}

		for (int i = 0; i < 3; i++)
		{
			rewards[i];
		}

		for (int i = 0; i < 3; i++)
		{
			Monsters[i];
		}


	}
	
	void setCurrentLocation(int x, int y)
	{
		current_location = x * 20 + y;
	}
	
	int getCurrentLocation()
	{
		return current_location;
	}
	
	void set_score()
	{
		//On collecting a jewel, weapon, or a potion, you will get +50, +30, and +70 points respectively.

		
		if (Monsters[0] == 'J')
		{
			this->score += 50;
		}
		else if (rewards[2] == 'W')
		{
			this->score += 30;
		}
		else if (rewards[1] == 'P')
		{
			this->score += 70;
		}
		
		else
		{
			this->score += 100;
		}

	}

	void update_score()
	{
		//update score
		for (int i = 0; i < 20; i++)
		{
			if (Monsters[i] == 'J')
			{
				this->score += 50;
			}
			else if (rewards[i] == 'W')
			{
				this->score += 30;
			}
			else if (rewards[i] == 'P')
			{
				this->score += 70;
			}
			else
			{
				this->score += 100;
			}
		}
		//cout << "The updates score is:" << score << endl;
		//this->score += score;
	}

	int get_score()
	{
		return score;
	}

	void removeScore(int value)
	{
		//loose score
		if (Monsters[2] == '@')
		{
			this->score -= 30;
		}
		else if (Monsters[1] == '$')
		{
			this->score -= 70;
		}
		else if (Monsters[0] == '&')
		{
			this->score -= 50;
		}
		else
		{
			this->score = 0;
		}

	}


	void setCrystal()
	{
		crystal_x = rand() % 20;
		crystal_y = rand() % 20;
		//add crystals to random location in the map
		matrix[crystal_x][crystal_y] = '*';

	}

	void setReward()
	{

		//adding rewards to random location in the map
		for (int i = 0; i < 25; i++)
		{
			reward_x = rand() % 20;
			reward_y = rand() % 20;
			while (matrix[reward_x][reward_y] != 'C') {
				reward_x = rand() % 20;
				reward_y = rand() % 20;
			}
			matrix[reward_x][reward_y] = rewards[rand() % 3];

		}
	}

	void setDeath()
	{
		//add death points to random location in the map
		for (int i = 0; i < 15; i++) {
			death_x = rand() % 20;
			death_y = rand() % 20;
			while (matrix[death_x][death_y] != 'C') {
				death_x = rand() % 20;
				death_y = rand() % 20;
			}
			matrix[death_x][death_y] = '%';

		}
	}

	void setObstacle()
	{
		//adding obstacles to random location in the map
		for (int i = 0; i < 50; i++) {
			obstacle_x = rand() % 20;
			obstacle_y = rand() % 20;
			while (matrix[obstacle_x][obstacle_y] != 'C') {
				obstacle_x = rand() % 20;
				obstacle_y = rand() % 20;
			}
			matrix[obstacle_x][obstacle_y] = '#';
		}
	}

	//Note: You can specify the weights of the edges towards the obstacles as 100, all other edges have a weight of 1.
	void setWeight()
	{
		//adding weights to the edges
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (matrix[i][j] == '#')
				{
					weight = 100;
				}
				else
				{
					weight = 1;
				}
			}
		}
	}

	void setMonster()
	{
		//adding monsters to random location in the map
		for (int i = 0; i < 20; i++)
		{
			monster_x = rand() % 20;
			monster_y = rand() % 20;
			while (matrix[monster_x][monster_y] != 'C')
			{
				monster_x = rand() % 20;
				monster_y = rand() % 20;
			}
			matrix[monster_x][monster_y] = Monsters[rand() % 3];
		}
	}

	void printMap()
	{
		//printing the map
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	void creategraph()
	{
		/* Node nodes[20][20];
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				nodes[i][j] = new Node(i, j, matrix[i][j]);
			}
		}*/

			// Create an adjacency matrix for the graph
			int adjacency_matrix[20][20];
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				adjacency_matrix[i][j] = 1;
			}
		}

		// Connect neighboring nodes with corresponding weights in the adjacency matrix
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++)
			{
				if (matrix[i][j] == '#') {
					continue;  // Skip connecting obstacles
				}

				// Connect with the node above
				if (matrix[i - 1][j] == '#')
				{
					adjacency_matrix[i][j] = 100;
				}
				else
				{
					adjacency_matrix[i][j] = 1;
				}


				// Connect with the node below
				if (matrix[i + 1][j] == '#') {
					adjacency_matrix[i][j] = 100;
				}
				else
				{
					adjacency_matrix[i][j] = 1;
				}


				// Connect with the node on the left
				if (matrix[i][j - 1] == '#') {
					adjacency_matrix[i][j] = 100;
				}
				else {
					adjacency_matrix[i][j] = 1;
				}


				// Connect with the node on the right
				if (matrix[i][j + 1] == '#') 
				{
					adjacency_matrix[i][j] = 100;
				}
				else 
				{
					adjacency_matrix[i][j] = 1;
				}


			}
		}


		// Print the adjacency matrix representation of the graph
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				cout << adjacency_matrix[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
};