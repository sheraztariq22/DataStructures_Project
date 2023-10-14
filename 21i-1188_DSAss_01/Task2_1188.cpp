#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<sstream>
#include<cmath>
#include<cstdlib>

using namespace std;

//calculating the clusters
void SuperCluster(int* customers,int numCustomers, int numClusters, int max_iterations) 
{
	//finding the centoriods 
	
	int* centroid_indices = new int[numClusters];
	for (int i = 0; i < numClusters; i++)
	{
		centroid_indices[i] = rand() % numCustomers;
	}
	int iteration = 0;
	bool converged = false;
	
	while (!converged && iteration < max_iterations)
	{
		//assigning the clusters
		int* clusters = new int[numCustomers];
		for (int i = 0; i < numCustomers; i++)
		{
			int min_distance = INT_MAX;
			int cluster = 0;
			for (int j = 0; j < numClusters; j++)
			{
				int distance = 0;
				for (int k = 0; k < 4; k++)
				{
					distance += pow(customers[i * 4 + k] - customers[centroid_indices[j] * 4 + k], 2);
				}
				if (distance < min_distance)
				{
					min_distance = distance;
					cluster = j;
				}
			}
			clusters[i] = cluster;
		}
		//finding the new centroids
		int* new_centroid_indices = new int[numClusters];
		for (int i = 0; i < numClusters; i++)
		{
			int* sum = new int[4];
			int count = 0;
			for (int j = 0; j < numCustomers; j++)
			{
				if (clusters[j] == i)
				{
					for (int k = 0; k < 4; k++)
					{
						sum[k] += customers[j * 4 + k];
					}
					count++;
				}
			}
			int min_distance = INT_MAX;
			int centroid = 0;
			for (int j = 0; j < numCustomers; j++)
			{
				if (clusters[j] == i)
				{
					int distance = 0;
					for (int k = 0; k < 4; k++)
					{
						distance += pow(customers[j * 4 + k] - sum[k] / count, 2);
					}
					if (distance < min_distance)
					{
						min_distance = distance;
						centroid = j;
					}
				}
			}
			new_centroid_indices[i] = centroid;
		}
		//checking if the centroids have changed
		converged = true;
		for (int i = 0; i < numClusters; i++)
		{
			if (centroid_indices[i] != new_centroid_indices[i])
			{
				converged = false;
				break;
			}
		}
		centroid_indices = new_centroid_indices;
		iteration++;
		//printing the clusters
		for (int i = 0; i < numClusters; i++)
		{
			cout << "Cluster " << i << ": ";
			for (int j = 0; j < numCustomers; j++)
			{
				if (clusters[j] == i)
				{
					cout << j << " ";
				}
			}
			cout << endl;
		}
	
	}
}



	
int main() {
	const int rows = 200;
	const int cols = 4;
	int** customers_Arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		customers_Arr[i] = new int[cols];
	}
	ifstream customers;
	customers.open("segmented_customers-1.csv");
	if (!customers.is_open())
	{
		cout << "Error opening file" << endl;
		exit(1);
	}
	string line;
	
	int i = 0;
	while (getline(customers, line))
	{
		stringstream ss(line);
		string token;
		int j = 0;
		while (getline(ss, token, ','))
		{
			customers_Arr[i][j] = stoi(token);
			cout << token << " ";
			j++;
			
		}
		cout << endl;
		i++;
	}
	
	//calling the function Super clusters
	SuperCluster(customers_Arr[0], rows, 3, 5);
	

	//storing the data in the file
	ofstream myfile;
	myfile.open("output1.csv");
	if (!myfile.is_open())
	{
		cout << "Error opening file" << endl;
		exit(1);
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			myfile << customers_Arr[i][j] << ",";
		
		}
		myfile << endl;
	}
	myfile.close();
	
	//delete the array
	for (int i = 0; i < rows; i++)
	{
		delete[] customers_Arr[i];
	}
	delete[] customers_Arr;
	
	return 0;
	
	
}