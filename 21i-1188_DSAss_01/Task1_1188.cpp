#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<sstream>
#include<cmath>


using namespace std;

double euclidean_distance(double x1, double y1, double x2, double y2)
{
	double d = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	return d;
}

//function to randomly initialize the k markers

void random_initialize(int** driver_arr, int k) {
	srand(time(NULL));
	for (int i = 0; i < k; i++) {
		int random = rand() % 4000;
		for (int j = 0; j < 2; j++) {
			driver_arr[i][j] = driver_arr[random][j];
		}
	}
}

//assigns each datapoint to its nearest marker
void assign_cluster(int** driver_arr, double x1, double y1, double x2, double y2)
{	double mini_distance = INFINITY;
	int closest_cluster = -1;
	
	for (int i = 0; i < 3999; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			x1 = driver_arr[i][j];
			y1 = driver_arr[i][j];
			x2 = driver_arr[i + 1][j];
			y2 = driver_arr[i][j + 1];
			double d = euclidean_distance(x1, y1, x2, y2);
			if (d < mini_distance)
			{
				mini_distance = d;
				closest_cluster = i;
			}
		}
	}
}

//reassing centoriod of each cluster
void reassign_centroid(int** driver_arr, double mini_distance)
{
	double x1, y1, x2, y2;
	double d;
	double sum_x = 0;
	double sum_y = 0;
	int count = 0;
	
	for (int i = 0; i < 3999; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			x1 = driver_arr[i][j];
			y1 = driver_arr[i][j];
			x2 = driver_arr[i + 1][j];
			y2 = driver_arr[i][j + 1];
			d = euclidean_distance(x1, y1, x2, y2);
			if (d == mini_distance)
			{
				sum_x += x1;
				sum_y += y1;
				count++;
			}
		}
	}
	
	double new_x = sum_x / count;
	double new_y = sum_y / count;
	
}


int main() {
	
	const int rows = 4000;
	const int cols = 2;
	int** driver_arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		driver_arr[i] = new int[cols];
	}
	string line;
	
	int i = 0;
	ifstream driver_file;
	driver_file.open("driver-data.csv");
	
	if (!driver_file.is_open())
	{
		cout << "Error opening file" << endl;
	}
	
	else
	{
		cout << "File is open" << endl;
		getline(driver_file, line);
		while (getline(driver_file, line))
		{
			stringstream ss(line);
			string token;
			int j = 0;
			getline(ss, token, ',');
			while (getline(ss, token, ','))
			{
				if (i == 0 && j == 0) {
					cout << "The first element is " << token << endl;
				}
				else if (i == 0 && j == 1) {
					cout << "The second element is " << token << endl;
				}
				else if (i == 0 && j == 2)
				{
					cout << "The third element is " << token << endl; 
				}
				
				else
				{
				   driver_arr[i][j] = stoi(token);
				   cout << token << " ";
				}
				j++;
			}
			cout << endl;
			i++;
		}
	}
    driver_file.close();
	
	
	//Now applying the clustering algorithm
	//First we need to find the distance between the drivers
	//We will use the Euclidean distance formula
	//d = sqrt((x2-x1)^2 + (y2-y1)^2)
	
	//We will use the distance formula to find the distance between the drivers
	
	double x1, y1, x2, y2;
	double d;
	
	for (int i = 0; i < 3999; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			x1 = driver_arr[i][j];
			y1 = driver_arr[i][j];
			x2 = driver_arr[i + 1][j];
			y2 = driver_arr[i][j + 1];
			d = euclidean_distance(x1, y1, x2, y2);
			cout << d << endl;
		}
	}
	
	//Initialize the clusters by randomly selecting k points as markers and assigning each datapoint to its nearest marker.
	
	random_initialize(driver_arr,5);
	assign_cluster(driver_arr,x1, y1, x2, y2);
	
	//Reassign the markers to the centroid of the new clusters.
	reassign_centroid(driver_arr, d);

	
	////Write the output to a .csv file
	ofstream myfile;
	myfile.open("output.csv");
	for (int i = 0; i < 4000; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			myfile << driver_arr[i][j]<< ",";
		}
		myfile << endl;
	}
	myfile.close();
		
	//delete the array
	for(int i = 0; i < rows; i++)
	{
	    delete[] driver_arr[i];
	}
	delete[] driver_arr;
	
	
	return 0;
}




