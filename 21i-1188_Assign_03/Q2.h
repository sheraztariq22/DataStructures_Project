#include <iostream>
#include <string>

using namespace std;

class DoubleLinkedList {
private:
	struct Node 
	{
		string data;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
public:
	DoubleLinkedList() {
		head = NULL;
		tail = NULL;
	}
	void push(string data) {
		Node* temp = new Node;
		temp->data = data;
		temp->next = NULL;
		temp->prev = NULL;
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
	string pop() {
		if (head == NULL) {
			return "";
		}
		else {
			Node* temp = tail;
			tail = tail->prev;
			if (tail != NULL) {
				tail->next = NULL;
			}
			else {
				head = NULL;
			}
			string data = temp->data;
			delete temp;
			return data;
		}
	}
	string top() {
		if (head == NULL) {
			return "";
		}
		else {
			return tail->data;
		}
	}
	bool is_empty() {
		return head == NULL;
	}

	
};

bool is_operator(char c) 
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%' || c == '(' || c == ')';
}




// Function to get the precedence of an operator
int precedence(char c)
{
	if (c == '+' || c == '-')
	{
		return 1;
	}
	//2. Precedence of % is higher than ^ but less than *
	else if (c == '^' || c == '*')
	{
		return 4;
	}
	else if (c == '%')
	{
		return 5;
	}
	else if (c == '*' || c == '/' || c == '%')
	{
		return 2;
	}
	else if (c == '^' || c=='*')
	{
		return 3;
	}
	else
	{
		return 0;
	}
}
int infix_to_postfix_A(string infix, char* output_stack, DoubleLinkedList& operator_stack)
{
	int pos = 0;
	for (int i = 0; i < infix.length(); i++)
	{
		if (infix[i] == ' ')
		{
			continue;
		}
		else if (is_operator(infix[i]))
		{
			if (infix[i] == '(')
			{
				string temp = "";
				temp += infix[i];
				operator_stack.push(temp);
			}
			else if (infix[i] == ')')
			{
				while (operator_stack.top() != "(")
				{
					string temp = operator_stack.pop();
					output_stack[pos++] = temp[0];
				}
				operator_stack.pop();
			}
			else
			{
				while (!operator_stack.is_empty() && precedence(operator_stack.top()[0]) >= precedence(infix[i]))
				{
					string temp = operator_stack.pop();
					output_stack[pos++] = temp[0];
				}
				string temp = "";
				temp += infix[i];
				operator_stack.push(temp);
			}
		}
		else
		{
			output_stack[pos++] = infix[i];
		}
	}
	
	while (!operator_stack.is_empty())
	{
		string temp = operator_stack.pop();
		output_stack[pos++] = temp[0];
	}
	output_stack[pos] = '\0';
	
	return pos;
}

//--------------Q2 part B Starts here----------------

int precedence1(char c)
{
	//normAL PRECEDENCE
	if (c == '+' || c == '-')
	{
		return 1;
	}
	else if (c == '*' || c == '/' || c == '%')
	{
		return 2;
	}
	else if (c == '^')
	{
		return 3;
	}
	else
	{
		return 0;
	}
}


//implementing the infix to postfix conversion using the Queue
class Queue {	
private:
	struct Node 
	{
		string data;
		Node* next;
	};
	Node* head;
	Node* tail;
public:
	Queue() {
		head = NULL;
		tail = NULL;
	}
	void enqueue(string data) {
		Node* temp = new Node;
		temp->data = data;
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}
	string peek() {
		if (head == NULL) {
			return "";
		}
		else {
			return head->data;
		}
	}
	
	bool is_full() 
	{
		return false;
	}
	
	char dequeue()
	{
		if (head == NULL) {
			return '\0';
		}
		else {
			Node* temp = head;
			head = head->next;
			if (head == NULL) {
				tail = NULL;
			}
			char data = temp->data[0];
			delete temp;
			return data;
		}
	}
	
	char front() {
		if (head == NULL) {
			return '\0';
		}
		else {
			return head->data[0];
		}
	}
	
	bool is_empty() 
	{
		return head == NULL;
	}
	
	
};

//void infix_to_postfix_B(string infix, string postfix, Queue& queue_operator_stack, Queue& second_queue)
void infix_to_postfix_B(string infix, string& postfix, Queue& operator_queue, Queue& second_queue) 
{
	for (int i = 0; i < infix.length(); i++)
	{
		if (infix[i] == ' ')
		{
			continue;
		}
		else if (is_operator(infix[i]))
		{
			if (infix[i] == '(')
			{
				string temp = "";
				temp += infix[i];
				operator_queue.enqueue(temp);
				
			}
			
			else if (infix[i] == ')')
			{
				while (operator_queue.front() != '(')
				{
					char temp = operator_queue.dequeue();
					postfix += temp;
				}
				operator_queue.dequeue();
			}
			
			else
			{
				while (!operator_queue.is_empty() && precedence1(operator_queue.front()) >= precedence1(infix[i]))
				{
					char temp = operator_queue.dequeue();
					postfix += temp;
				}
				string temp = "";
				temp += infix[i];
				operator_queue.enqueue(temp);
			}
		}
		else if (is_operator(infix[i]))
		{
			string temp = "";
			temp += infix[i];
			second_queue.enqueue(temp);
		}
		
		else
		{
			postfix += infix[i];
		}
		
	}

	while (!operator_queue.is_empty())
	{
		char temp = operator_queue.dequeue();
		postfix += temp;
	}
	
	while (!second_queue.is_empty())
	{
		char temp = second_queue.dequeue();
		postfix += temp;
	}
	
}