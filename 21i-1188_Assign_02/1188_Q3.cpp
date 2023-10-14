/*
FAST university has hired you to make an operating system for their lifts. Below are specifications of the lifts OS.
The lift will be place in a building with 6 floors including a basement.
From basement to top floors are labeled as -1,0,1,2,3,4 respectively.
In the morning, the lift goes operation from the basement. The lift can go up and down.
If maintained is required, the lift can be halted. If the lift is halted, the lift not usable during that period.
Once unhalted, the lift can be used again.
With the help of above information, make a lift operating system
*/

#include<iostream>


using namespace std;

class lift_floors {
public:
	int  floor;
	char floor_status; //A for active N for not active
	lift_floors* next;
	lift_floors* prev;
	lift_floors(int data) {
		this->floor = data;
		this->next = NULL;
		this->prev = NULL;
		this->floor_status = 'A';
	}
};

void add_floor(lift_floors* new_floor, lift_floors* head, lift_floors* tail);
int liftup(lift_floors* current, lift_floors* head, lift_floors* tail, int requested_floor);
int liftdown(lift_floors* current, lift_floors* head, lift_floors* tail, int requested_floor);
char halt_lift(char& status);
char un_halt_lift(char& status);
void skip_floor(lift_floors* head, lift_floors* tail, int requested_floor);
void make_floor_operational(lift_floors* head, lift_floors* tail, int requested_floor);



int main()
{
	lift_floors* head;
	lift_floors* tail;
	lift_floors* current;
	int total_floors = 6; // total number of floors
	int current_floor = -1; // starts with basement
	int requested_service; //choice of user
	int requested_floor; //floor the lift goes on
	char status = 'W'; //W for working , H for halted

	//initialize everything and poplate the link list based on above data.
	//use add floor to add all the floors in the list
	head = new lift_floors(-1);
	tail = head;
	for (int i = 0; i < total_floors; i++)
	{
		lift_floors* new_floor = new lift_floors(i);
		tail->next = new_floor;
		new_floor->prev = tail;
		tail = new_floor;
		add_floor(new_floor, head, tail);
	}


	while (1)
	{
		cout << endl << "1. Go to a floor";
		cout << endl << "2. Halt Lift";
		cout << endl << "3. Unhalt Lift";
		cout << endl << "4. Add floor";
		;		cout << endl << "5. Skip floor";
		cout << endl << "6. Make a floor operational";
		cout << endl << "7. Exit";
		cout << endl;
		cout << "Please select a funcation of your choice:";
		cin >> requested_service;
		//input validation
		while (requested_service < 1 || requested_service > 7)
		{
			cout << "Invalid choice" << endl;
			cout << "Please select a funcation of your choice:";
			cin >> requested_service;
		}
		switch (requested_service)
		{
		case 1:
			cout << endl << "Enter Floor of choice ";
			cin >> requested_floor;
			//input validation
			while (requested_floor < -1 || requested_floor > 4)
			{
				cout << "Invalid choice" << endl;
				cout << "Please select a correct floor number:";
				cin >> requested_floor;
			}
			if (current_floor == -1)
			{
				current_floor = liftup(head, head, tail, requested_floor);
			}
			else if (current_floor < requested_floor)
			{
				current_floor = liftup(head, head, tail, requested_floor);
			}
			else if (current_floor > requested_floor)
			{
				current_floor = liftdown(head, head, tail, requested_floor);
			}
			else
			{
				cout << "You are already on the floor" << endl;
			}
			break;
		case 2:
			status = halt_lift(status);
			break;
		case 3:
			status = un_halt_lift(status);
			break;
		case 4:
			cout << endl << "Enter Floor of choice ";
			cin >> requested_floor;
			//input validation
			while (requested_floor < -1 || requested_floor > 4)
			{
				cout << "Invalid choice" << endl;
				cout << "Please select a correct floor number:";
				cin >> requested_floor;
			}
			//intilization of new floor is skip by case label 4
			for (int i = 0; i < total_floors; i++)
			{
				lift_floors* new_floor = new lift_floors(i);
				tail->next = new_floor;
				new_floor->prev = tail;
				tail = new_floor;
				add_floor(new_floor, head, tail);
			}
			break;
		case 5:
			cout << endl << "Enter Floor of choice ";
			cin >> requested_floor;
			//input validation
			while (requested_floor < -1 || requested_floor > 4)
			{
				cout << "Invalid choice" << endl;
				cout << "Please select a correct floor number:";
				cin >> requested_floor;
			}
			skip_floor(head, tail, requested_floor);
			break;

		case 6:
			cout << endl << "Enter Floor of choice ";
			cin >> requested_floor;
			//input validation
			while (requested_floor < -1 || requested_floor > 4)
			{
				cout << "Invalid choice" << endl;
				cout << "Please select a correct floor number:";
				cin >> requested_floor;
			}
			make_floor_operational(head, tail, requested_floor);
			break;
		case 7:
			exit(0);
			break;
		default:

			cout << "Invalid choice" << endl;
			break;
		}

	}
}

int lift_operating_system(int requested_floor, lift_floors* current, lift_floors* head, lift_floors* tail, char lift_status)
{
	//add logic to make lift go to a specific floor
	if (lift_status == 'H') {
		cout << "Lift is halted. Unhalt the lift before using it " << endl;
		return current->floor;
	}
	else if (requested_floor > current->floor)
	{
		return liftup(current, head, tail, requested_floor);
	}
	else if (requested_floor < current->floor)
	{
		return liftdown(current, head, tail, requested_floor);
	}
	
	else if (requested_floor == current->floor)
	{
		cout << "You are already on the floor" << endl;
		return current->floor;
	}
	else
	{
		cout << "Invalid floor number" << endl;
		return current->floor;
	}
}
int liftup(lift_floors* current, lift_floors* head, lift_floors* tail, int requested_floor)
{
	//recurrsive funcation to take lift up
	if (current->next == NULL)
	{
		cout << "You are on the top floor. Please enter a lower floor " << endl;
		return current->floor;
	}
    if (current->next->floor == requested_floor && current->next->floor_status == 'A')
	{
		cout << "The list is operating up towards flooor " << endl;
		return current->next->floor;
	}
	if (current->next->floor_status == 'H')
	{
		cout << "THe floor is halt make it unhalt to operate "<< endl;
		return current->floor;
	}
	 if (current->next->floor_status == 'N')
	{
		cout << "The lift is not active " << current->next->floor << endl;
		 return liftup(current->next, head, tail, requested_floor);
	}
	else
	{
		cout << "The list is operating up towards flooor " << current->next->floor << endl;
		return liftup(current->next, head, tail, requested_floor);
	}

	 
}
int liftdown(lift_floors* current, lift_floors* head, lift_floors* tail, int requested_floor)
{
	//recurrsive funcation to bring the lift down
	if (current->prev == NULL)
	{
		cout << "You are already on the basement floor" << endl;
		return current->floor;
	}
	else if (current->prev->floor == requested_floor && current->prev->floor_status == 'A')
	{
		cout << "the lift is operating downward to the floor " << endl;
		return current->prev->floor;
	}
	
	else if (current->prev->floor_status == 'N')
	{
		cout << "The lift is not active." << current->prev->floor << endl;
		return liftdown(current->prev, head, tail, requested_floor);
	}
	else
	{
		cout << "The list is operating up towards flooor " << current->prev->floor << endl;
		 return liftdown(current->prev, head, tail, requested_floor);
	}
	
	
}
char halt_lift(char& status)
{
	//halts the lift, no up and down operation can be performed. Stored H for halting

	if (status == 'W')
	{
		status = 'H';
		cout << "The lift is halted now!" << endl;
	}
	else
	{
		cout << "The lift is already halted" << endl;
	}

	return status;
}
char un_halt_lift(char& status)
{
	//Unhatls the lift. Store W which represents that the lift is working
	if (status == 'H')
	{
		status = 'W';
		cout << "The lift starts working" << endl;
	}
	else
	{
		cout << "The lift is already working" << endl;
	}

	return status;
}
void add_floor(lift_floors* new_floor, lift_floors* head, lift_floors* tail)
{
	//add a lift floor;
	if (head == NULL)
	{
		head = new_floor;
		tail = new_floor;
	}
	else
	{
		tail->next = new_floor;
		new_floor->prev = tail;
		tail = new_floor;
	}
}
void skip_floor(lift_floors* head, lift_floors* tail, int floorNo)
{
	//add logic to make lift skip a certian floor
	lift_floors* current = head;

	if (current == NULL)
	{
		cout << "No floors to skip" << endl;
		return;
	}

	while (current != NULL)
	{
		if (current->floor == floorNo)
		{
			current->floor_status = 'N';
			cout << "Floor " << floorNo << " is skipped" << endl;
			return;
		}
		current = current->next;
	}
	cout << "Floor " << floorNo << " is not found" << endl;

}
void make_floor_operational(lift_floors* head, lift_floors* tail, int floorNo)
{
	//add logic to make lift operational on a certain floor
	lift_floors* current = head;
	while (current != NULL)
	{
		if (current->floor == floorNo)
		{
			current->floor_status = 'A';
			cout << "Floor " << floorNo << " is operational" << endl;
			return;
		}
		current = current->next;
	}
	cout << "Floor " << floorNo << " is not found" << endl;

}