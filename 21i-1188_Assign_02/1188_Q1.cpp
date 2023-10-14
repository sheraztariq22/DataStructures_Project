#include <iostream>
#include <string>

//21i-1188
//Sheraz Tariq
using namespace std;

class student_Node {
public:
	string data;
	student_Node* next;
	student_Node(string data) {
		this->data = data;
		this->next = NULL;
	}
};
//The above portion cannot be changed

string* list_of_all_students(student_Node* head1, student_Node* head2, student_Node* head3)
{
	string* result;
	int count = 0;
	student_Node* temp;
    
	temp = head1;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	temp = head2;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	temp = head3;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}

	//allcoate array to list all students
	result = new string[count];
	int index = 0;

	//traversing all list and add strings to array
	temp = head1;
	while (temp != NULL) {
		bool flag = false;
		for (int i = 0; i < index; i++)
		{
			if (result[i] == temp->data)
			{
				flag = true;
				break;
			}
			
		}
		if (!flag)
		{
			result[index] = temp->data;
			index++;
		}
		temp = temp->next;
		
	}
	
	temp = head2;
	while (temp != NULL) {
		bool flag = false;
		for (int i = 0; i < index; i++)
		{
			if (result[i] == temp->data)
			{
				flag = true;
				break;
			}

		}
		if (!flag)
		{
			result[index] = temp->data;
			index++;
		}
		temp = temp->next;

	}
	temp = head3;
	while (temp != NULL) {
		bool flag = false;
		for (int i = 0; i < index; i++)
		{
			if (result[i] == temp->data)
			{
				flag = true;
				break;
			}

		}
		if (!flag)
		{
			result[index] = temp->data;
			index++;
		}
		temp = temp->next;

	}
	
	//printing the array
	for (int i = 0; i < index; i++)
	{
		cout << result[i] << endl;
	}
	
	return result;
}
string* list_common_student_society(student_Node* head1, student_Node* head2, student_Node* head3)
{

	string* result = NULL;
	int count = 0;
	student_Node* temp1 = head1;
	student_Node* temp2 = head2;
	student_Node* temp3 = head3;
	
	while (temp1 != NULL) {
		temp2 = head2;
		while (temp2 != NULL)
		{
			if (temp1->data == temp2->data)
			{
				temp3 = head3;
				while (temp3 != NULL)
				{
					if (temp1->data == temp3->data)
					{
						if (result == NULL)
						{
							//fisrt duplicate found
							result = new string[1];
							result[0] = temp1->data;
							count++;
						}
						else
						{
							//new duplicate found
							string* temp = new string[count + 1];
							for (int i = 0; i < count; i++)
							{
								temp[i] = result[i];
							}
							temp[count] = temp1->data;
							delete[] result;
							result = temp;
							count++;
						}
						break;
					}
					temp3 = temp3->next;
				}
				break;
			}
			temp2 = temp2->next;
		}
		temp1 = temp1->next;	
	}
	
	//checking the array is empty or not
	if (result == NULL)
	{
		cout << "There are no Common Students in all three societies" << endl;
	}
	//printing the array
	for (int i = 0; i < count; i++)
	{
		cout << result[i] << endl;
	}
	
	return result;
}

//you can make fuctions for input and output, Core logic will be in above two funcation. Main should only work as a runner.
int main()
{
	//TC1
	student_Node* FGC_List = new student_Node("Ali");
	FGC_List->next = new student_Node("Usman");
	FGC_List->next->next = new student_Node("Haider");
	FGC_List->next->next->next = new student_Node("Maryam");
	FGC_List->next->next->next->next = new student_Node("Masooma");
	FGC_List->next->next->next->next->next = new student_Node("Urooj");

	student_Node* FAS_List = new student_Node("Ashiq");
	FAS_List->next = new student_Node("Manika");
	FAS_List->next->next = new student_Node("Ali");
	FAS_List->next->next->next = new student_Node("Masooma");
	FAS_List->next->next->next->next = new student_Node("Akbar");
	FAS_List->next->next->next->next->next = new student_Node("Urooj");

	student_Node* FDS_List = new student_Node("Masooma");
	FDS_List->next = new student_Node("Bilal");
	FDS_List->next->next = new student_Node("Amna");
	FDS_List->next->next->next = new student_Node("Madiha");
	FDS_List->next->next->next->next = new student_Node("Rohail");
	FDS_List->next->next->next->next->next = new student_Node("Urooj");
	
	//TC2
	/*student_Node* FGC_List = new student_Node("Ali");
	FGC_List->next = new student_Node("Usman");
	FGC_List->next->next = new student_Node("Haider");
	
	student_Node* FAS_List = new student_Node("Ashiq");
	FAS_List->next = new student_Node("Manika");
	FAS_List->next->next = new student_Node("Ali");
	FAS_List->next->next->next = new student_Node("Masooma");
	
	student_Node* FDS_List = new student_Node("Masooma");
	FDS_List->next = new student_Node("Bilal");
	FDS_List->next->next = new student_Node("Amna");
	FDS_List->next->next->next = new student_Node("Madiha");
	FDS_List->next->next->next->next = new student_Node("Rohail");
	FDS_List->next->next->next->next->next = new student_Node("Urooj");*/
	
	//TC3
	/*student_Node* FGC_List = new student_Node("Ali");
	FGC_List->next = new student_Node("Usman");
	FGC_List->next->next = new student_Node("Haider");
	
	student_Node* FAS_List = NULL;
	
	student_Node* FDS_List = NULL;*/

	//TC4
	/*student_Node* FGC_List = new student_Node("Ali");
	FGC_List->next = new student_Node("Usman");
	FGC_List->next->next = new student_Node("Haider");

	student_Node* FAS_List = new student_Node("Masooma");
	
	student_Node* FDS_List = NULL;*/

	//call list_of_all_students
	cout << "The list of all students in different societies are: " << endl;
	string* result = list_of_all_students(FGC_List, FAS_List, FDS_List);

	//call list_common_student_society
	cout << "The list of common students in societies are: " << endl;
	string* result2 = list_common_student_society(FGC_List, FAS_List, FDS_List);

	return 0;
}