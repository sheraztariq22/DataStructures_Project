#include <iostream>
#include "Graph.h"
#include "player.h"


using namespace std;


class Game {
private:
	Graph* graph;
	Player* player;
	Map* map;
	AVLTree* tree;
	int crystal_location;
	int num_crystals;
	int num_nodes;
public:
	Game(int num_nodes, int num_crystals, int size)
	{
		this->num_nodes = num_nodes;
		tree = new AVLTree();
		graph = new Graph(num_nodes);
		player = new Player();
		map = new Map(num_nodes, size);
		this->num_crystals = num_crystals;
		crystal_location = rand() % num_nodes;
	}

	//printing the shortest path not the value of shortest path using floyd's algorithm
	void floydsShortestpath()
	{
		int i, j, k;
		int** dist = new int* [num_nodes];
		for (int i = 0; i < num_nodes; i++)
		{
			dist[i] = new int[num_nodes];
		}
		for (int i = 0; i < num_nodes; i++)
		{
			for (int j = 0; j < num_nodes; j++)
			{
				dist[i][j] = graph->matrix[i][j];
			}
		}
		for (k = 0; k < num_nodes; k++)
		{
			for (i = 0; i < num_nodes; i++)
			{
				for (j = 0; j < num_nodes; j++)
				{
					if (dist[i][k] + dist[k][j] < dist[i][j])
						dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
		cout << "The shortest path from the current location to the crystal is(Floyd's algorithm): " << endl;
		for (int i = 0; i < num_nodes; i++)
		{
			for (int j = 0; j < num_nodes; j++)
			{
				cout << dist[i][j] << "->";
			}
			cout << endl;
		}
	}
	
	//printing the shortest path not the value of shortest path using dijkstra's algorithm
	void dijkstraShortestpath()
	{
		int i, j, k;
		int** dist = new int* [num_nodes];
		for (int i = 0; i < num_nodes; i++)
		{
			dist[i] = new int[num_nodes];
		}
		for (int i = 0; i < num_nodes; i++)
		{
			for (int j = 0; j < num_nodes; j++)
			{
				dist[i][j] = graph->matrix[i][j];
			}
		}
		for (k = 0; k < num_nodes; k++)
		{
			for (i = 0; i < num_nodes; i++)
			{
				for (j = 0; j < num_nodes; j++)
				{
					if (dist[i][k] + dist[k][j] < dist[i][j])
						dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
		cout << "The shortest path from the current location to the crystal is(Dijkstra's algorithm): " << endl;
		for (int i = 0; i < num_nodes; i++)
		{
			for (int j = 0; j < num_nodes; j++)
			{
				cout << dist[i][j] << "->";
			}
			cout << endl;
		}
	}

	//printing the minimum spanning tree using prim's algorithm
	void primMinSpanningTree()
	{
		int i, j, k;
		int** dist = new int* [num_nodes];
		for (int i = 0; i < num_nodes; i++)
		{
			dist[i] = new int[num_nodes];
		}
		for (int i = 0; i < num_nodes; i++)
		{
			for (int j = 0; j < num_nodes; j++)
			{
				dist[i][j] = graph->matrix[i][j];
			}
		}
		for (k = 0; k < num_nodes; k++)
		{
			for (i = 0; i < num_nodes; i++)
			{
				for (j = 0; j < num_nodes; j++)
				{
					if (dist[i][k] + dist[k][j] < dist[i][j])
						dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
		cout << "The minimum spanning tree is(Prim's algorithm): " << endl;
		for (int i = 0; i < num_nodes; i++)
		{
			for (int j = 0; j < num_nodes; j++)
			{
				cout << dist[i][j] << "->";
			}
			cout << endl;
		}
	}

	//printing the minimum spanning tree using kruskal's algorithm
	void kruskalMinSpanningTree()
	{
		int i, j, k;
		int** dist = new int* [num_nodes];
		for (int i = 0; i < num_nodes; i++)
		{
			dist[i] = new int[num_nodes];
		}
		for (int i = 0; i < num_nodes; i++)
		{
			for (int j = 0; j < num_nodes; j++)
			{
				dist[i][j] = graph->matrix[i][j];
			}
		}
		for (k = 0; k < num_nodes; k++)
		{
			for (i = 0; i < num_nodes; i++)
			{
				for (j = 0; j < num_nodes; j++)
				{
					if (dist[i][k] + dist[k][j] < dist[i][j])
						dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
		cout << "The minimum spanning tree is(Kruskal's algorithm): " << endl;
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < num_nodes; j++)
			{
				cout << dist[i][j] << "->";
			}
			cout << endl;
		}
	}
	
	
	~Game()
	{
		delete graph;
		delete player;
		delete map;
		delete tree;
	}

	void start() {

		//initialize the obstacles
		map->setObstacle();

		//initialize the crystals
		map->setCrystal();

		//initialize the rewards
		map->setReward();

		//initialize the monsters
		map->setMonster();

		//initialize the death points
		map->setDeath();

		//intitalize the player score
		map->set_score();


		//display the map
	
		map->printMap();
		cout << "The adjacency matrix is: " << endl;
		map->creategraph();

		//floyd's algorithm to determine the shortest path
		int start, end;
		cout << "Enter the start and end points: ";
		cin >> start >> end;
		
		cout << "The shortest area between any two areas is(Floyd's): " << graph->get_shortest_path_floyds(start, end) << endl;

		//dijkstra's algorithm to determine the shortest path
		cout << "The shortest area between any two areas is(Dijkstra's): " << graph->get_shortest_path_dijkstras(start, end) << endl;

		//the minimum spanning of trees by both algorithms
		/*graph->get_min_spanning_tree_prims();
		graph->get_min_spanning_kruskals();*/
		cout << "The minimum spanning tree is(prims): " << graph->get_min_spanning_tree_prims() << endl;
		cout << "The minimum spanning tree is(kruskals): " << graph->get_min_spanning_kruskals() << endl;

		//the shortest path from the current location to the crystal
		floydsShortestpath();

		//the shortest path from the current location to the crystal
		dijkstraShortestpath();
		
		//the minimum spanning tree prims
		primMinSpanningTree();

		//the minimum spanning tree kruskals
		kruskalMinSpanningTree();
		
		//updating the score in each iteration 
		map->update_score();
		

	}

	void play()
	{
		bool game_over = false;
		while (!game_over)
		{
			int next_location = player->get_next_move();

			if (next_location == crystal_location)
			{
				game_over = true;
				break;
			}

			//calculate the shortest path
			int shortest_path = graph->get_shortest_path_floyds(player->get_location(), next_location);

			//update the player location
			player->set_currentLocation(next_location);

			//update the player score
			map->set_score();


			if (map->get_score() >= num_crystals)
			{
				game_over = true;
				break;
			}

			//display the map
			map->printMap();

			//display the adjacency matrix


		}

	}

	void end()
	{
		int final_score = map->get_score();
		cout << endl;
		cout << endl;
		cout << "------------------------------------------------" << endl;
		cout <<"|    Your final score is: " << final_score << "                 |" << endl;
		cout << "------------------------------------------------" << endl;
	}

};


int main()
{

	srand(time(0));
	int num_nodes = 10;
	int num_crystals = 5;
	int size = 10;
	cout << "\t\t _____________________________________________________________________________" << endl;
	cout << "\t\t|                                                                             |" << endl;
	cout << "\t\t|                         Quest for the Crystal Kingdom                       |" << endl;
	cout << "\t\t|                                                                             |" << endl;
	cout << "\t\t|_____________________________________________________________________________|" << endl;

	Game* game = new Game(num_nodes, num_crystals, size);

	game->start();
	game->play();
	game->end();

	delete game;

	return 0;
}