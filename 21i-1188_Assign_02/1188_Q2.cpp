#include <iostream>
using namespace std;

class Node
{
public:
	const int data; //do not change this
	Node* next;
	Node* prev;

	Node(int d) : data(d)
	{
		this->next = NULL;
		this->prev = NULL;
	}
};

void insertionSort(Node*& head, Node*& tail) {
	// function only called if the list is unsorted
	Node* temp1, * temp2, * temp3;
	for (temp1 = head->next; temp1 != NULL; temp1 = temp1->next) {
		temp2 = temp1->prev;
		temp3 = temp1;
		while (temp2 != NULL && temp2->data > temp3->data) {
			temp2->next = temp3->next;
			temp3->next = temp2;
			temp3->prev = temp2->prev;
			temp2->prev = temp3;
			if (temp3->prev == NULL) {
				head = temp3;
			}
			else {
				temp3->prev->next = temp3;
			}
			if (temp2->next == NULL) {
				tail = temp2;
			}
			else {
				temp2->next->prev = temp2;
			}
			temp2 = temp3->prev;
		}
	}

	//printed the sorted list
	Node* current = head;
	while (current != NULL)
	{
		cout << current->data << "->";
		current = current->next;
	}
	cout << "NULL" << endl;
}
int input(Node* head, Node* tail, int no_of_elements)
{
	//ask user for providing the number of items in the list. Then create n number of nodes
	cout << "Enter the number of elements in the list: ";
	cin >> no_of_elements;
	while (no_of_elements < 0)
	{
		cout << "Enter a positive number: ";
		cin >> no_of_elements;
	}
	//ask user for providing the data for each node
	cout << "Enter the elements of the list: ";
	for (int i = 0; i < no_of_elements; i++)
	{
		int data;
		//entering number in the list until the user presses -1
		while (true)
		{
			cin >> data;
			if (data == -1)
			{
				break;
			}
			else
			{
				break;
			}
		}
		Node* temp = new Node(data);
		if (head == NULL)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
	}

	//returns the number of elements in the list
	insertionSort(head, tail);

	return no_of_elements;
}

bool isSorted(Node* head, Node* tail)
{
	bool flag = true;
	Node* current = head;
	while (current != tail)
	{
		if (current->data > current->next->data)
		{
			flag = false;
			break;
		}
		current = current->next;
	}
	return flag;
}
bool binarySearch(Node*& head, Node*& tail, Node*& mid, int search_number)
{
	bool found = false;
	Node* temp = head;
	Node* temp1 = tail;
	
	while (temp != temp1)
	{
		mid = temp;
		for (int i = 0; i < (temp1->data - temp->data) / 2; i++)
		{
			mid = mid->next;
		}
		if (mid->data == search_number)
		{
			found = true;
			break;
		}
		else if (mid->data > search_number)
		{
			temp1 = mid->prev;
		}
		else
		{
			temp = mid->next;
		}
	}
	return found;

}


int main()
{
	Node* head = NULL;
	Node* tail = NULL;
	Node* mid = NULL;
	int no_of_elements = 0;
	int search_number;

	no_of_elements = input(head, tail, no_of_elements);

	if (isSorted(head, tail))
	{
		cout << endl << "The listed is sorted!" << endl;
	}
	else
	{
		cout << "The list is not sorted!" << endl;
	}


	cout << "Enter the number to be searched: ";
	cin >> search_number;

	if (binarySearch(head, tail, mid, search_number))
	{
		cout << "The number is present in the list.\n";
	}
	else
	{
		cout << "The number is not present in the list!" << endl;
	}

	return  0;
}