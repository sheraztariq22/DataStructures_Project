#include<iostream>
#include<string>
#include<fstream>

using namespace std;
//Recursive function

class StringList {
public:
	char alphabet;
	StringList* next;
	StringList(char data)
	{
		this->alphabet = data;
		this->next = NULL;

	}
};

int find_Length(StringList*& s, int counter) //counter will start from zero initially
{
	if (s == NULL) 
	{
		return counter;
	}
	else 
	{
		counter += find_Length(s->next, counter++);
	}

	return counter;
}

class String_Manipulation 
{
public:
	void createList(StringList*& head)
	{
		//read text from file and make the list here
		ifstream file;
		file.open("Q4- String Paragraph.txt");
		if (!file.is_open()) 
		{
			cout << "File not found" << endl;
		}
		else
		{
			string str;
			while (getline(file, str))
			{
				for (int i = 0; i < str.length(); i++)
				{
					StringList* temp = new StringList(str[i]);
					if (head == NULL)
					{
						head = temp;
					}
					else 
					{
						StringList* p = head;
						while (p->next != NULL) 
						{
							p = p->next;
						}
						p->next = temp;
					}
				}
			}
		}
		file.close();
	}
	int Calculate_length(StringList*& head)
	{
		int length;
		if (head == NULL)
		{
			return 0;
		}
		else
		{
			length = find_Length(head, 0);
		}
		return length;
	}
	bool substring(StringList*& head, string str)
	{
		bool status = false;
		StringList* p = head;
		int i = 0;
		while (p != NULL) 
		{
			if (p->alphabet == str[i]) 
			{
				i++;
				if (i == str.length()) 
				{
					status = true;
					break;
				}
			}
			else 
			{
				i = 0;
			}
			p = p->next;
		}
		return status;
	}
	int substring_position(StringList*& head, string str)
	{
		int index = -1;
		StringList* p = head;
		int ind = 0;
		if (head == NULL) 
		{
			return -1;
		}
		bool found = false;
		while (p != NULL) 
		{
			StringList* temp = p;
			for (int i = 0; i < str.length(); i++) 
			{
				if (temp->alphabet == str[i]) 
				{
					found = true;
					temp = temp->next;
				}
				else 
				{
					found = false;
					p = p->next;
					ind++;
					break;
				}
			}
			if (found)
			{
				break;
			}
		}
		if (found)
		{
			index = ind;
		}

		return index;
	}
	void replaceString(StringList*& head, string find, string replace)
	{
		////add your code
		int index = substring_position(head, find);
		if (index != -1) {
			StringList* p = head;
			int i = 0;
			while (p != NULL) 
			{
				if (p->alphabet == find[i]) 
				{
					i++;
					if (i == find.length()) 
					{
						StringList* temp = p;
						for (int j = 0; j < replace.length(); j++)
						{
							StringList* temp2 = new StringList(replace[j]);
							temp2->next = temp->next;
							temp->next = temp2;
							temp = temp->next;
						}
						break;
					}
				}
				else
				{
					i = 0;
				}
				p = p->next;
			}
		}
	}
	void appendText(StringList*& head, string appends, int index)
	{
		////add your code
		StringList* p = head;
		int i = 0;
		if (head == NULL) 
		{
			return;
		}
		while (p != NULL)
		{
			if (i == index) 
			{
				StringList* temp = p;
				for (int j = 0; j < appends.length(); j++)
				{
					StringList* temp2 = new StringList(appends[j]);
					temp2->next = temp->next;
					temp->next = temp2;
					temp = temp->next;
				}
				break;
			}
			i++;
			p = p->next;
		}
	}
	void deleteText(StringList*& head, string delText)
	{
		////add your code
		if (head == NULL)
		{
			return;
		}
		int index = substring_position(head, delText);
		if (index == -1)
		{
			return;
		}
		StringList* from = head;
		for (int i = 0; i < index - 1; i++)
		{
			from = from->next;
		}
		StringList* to = from;
		for (int i = 0; i < delText.length(); i++)
		{
			to = to->next;
		}
		StringList* deletefrom = from->next->next;
		if (index == 0)
		{
			head = to->next;
		}
		else
		{
			from->next = to->next;
		}
		while (deletefrom != to) {
			StringList* delhelp = deletefrom;
			deletefrom = deletefrom->next;
			delete delhelp;
		}
	}

};

int main()
{
	StringList* head = NULL;
	String_Manipulation obj;
	obj.createList(head);

	//calling the file reading function
	StringList* current = head;
	if (current == NULL) 
	{
		cout << "The list is empty" << endl;
	}
	else {
		cout << "The list is: ";
		while (current != NULL) {
			cout << current->alphabet;
			current = current->next;
		}
		cout << endl;
	}
	cout << endl << endl;

	//Find its length.
	int length = obj.Calculate_length(head);
	cout << "The length of the list is: " << length << endl;

	//Find a substring in the list.
	string str;
	cout << "Enter the substring to be found: ";
	getline(cin, str);
	bool status = obj.substring(head, str);

	if (status == true)
	{
		cout << "The substring is found in the list" << endl;
	}
	else
	{
		cout << "The substring is not found in the list" << endl;
	}

	//function returns the index of the main string where the sub string starts.
	cout << "Enter the substring to find the index: ";
	cin.get();
	getline(cin, str);
	int index = obj.substring_position(head, str);
	cout << "The index of the substring is: " << index << endl;

	//Replace a substring in the list.
	string find, replace;
	cout << "Enter the substring to be replaced: ";
	getline(cin, find);
	cout << "Enter the substring to replace: ";
	getline(cin, replace);
	obj.replaceString(head, find, replace);
	//print the list after replacing the substring.
	current = head;
	if (current == NULL)
	{
		cout << "The list is empty" << endl;
	}
	else
	{
		cout << "The list is after replacing: ";
		while (current != NULL) 
		{
			cout << current->alphabet;
			current = current->next;
		}
		cout << endl;
	}

	//Append a text to the list.
	string appends;
	cout << "Enter the text to be appended: ";
	getline(cin, appends);
	cout << "Enter the index to append the text: ";
	cin >> index;
	obj.appendText(head, appends, index);

	//print the list after appending the text.
	current = head;
	if (current == NULL)
	{
		cout << "The list is empty" << endl;
	}
	else
	{
		cout << "The list is after appending: ";
		while (current != NULL)
		{
			cout << current->alphabet;
			current = current->next;
		}
		cout << endl;
	}


	//delete string in array
	obj.deleteText(head, "people");
	current = head;
	if (current == NULL) {
		cout << "The list is empty" << endl;
	}
	else 
	{
		cout << "The list is: ";
		while (current != NULL) 
		{
			cout << current->alphabet;
			current = current->next;
		}
		cout << endl;
	}
	return 0;
}
