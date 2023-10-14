
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define MAX_FILE_SIZE 100000

class Node {
public:
	char data;
	Node* next;
};

class Stack {
private:
	Node* top; 
public:
	Stack() 
	{
		top = NULL; 
	};
	
	void push(char data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		newNode->next = top;
		top = newNode;
	}
	
	char pop()
	{
		if (top == NULL)
		{
			return NULL;
		}
		else
		{
			Node* temp = top;
			top = top->next;
			char data = temp->data;
			delete temp;
			return data;
		}
	}
	
	char peek()
	{
		if (top == NULL)
		{
			return NULL;
		}
		else
		{
			return top->data;
		}
	}
	
	bool isEmpty()
	{
		return top == NULL;
	}
	
	void clear()
	{
		while (top != NULL)
		{
			Node* temp = top;
			top = top->next;
			delete temp;
		}
	}
};

class Queue {
private:
	char* arr;
	int front;
	int rear;
	int size;
public:
	Queue()
	{
		size = 100;
		arr = new char[size];
		front = -1;
		rear = -1;
	}
	Queue(int size)
	{
		this->size = size;
		arr = new char[size];
		front = -1;
		rear = -1;
	}

	void enqueue(char data)
	{
		if (rear == size - 1)
		{
			cout << "Queue is full" << endl;
		}
		else
		{
			if (front == -1)
			{
				front = 0;
			}
			rear++;
			arr[rear] = data;
		}
	}

	char dequeue()
	{
		if (front == -1 || front > rear)
		{
			cout << "Queue is empty" << endl;
			return NULL;
		}
		else
		{
			char data = arr[front];
			front++;
			return data;
		}
	}

	char peek()
	{
		if (front == -1 || front > rear)
		{
			cout << "Queue is empty" << endl;
			return NULL;
		}
		else
		{
			return arr[front];
		}
	}

	bool isEmpty()
	{
		return front == -1 || front > rear;
	} 
	
	void clear()
	{
		front = -1;
		rear = -1;
	}
	int getSize()
	{
		return rear - front + 1;
	}
	
};

class TPS {
private:
	Stack redoStack;
	Stack undoStack;
	Queue megaUndoQueue;
	Queue megaRedoQueue;
	string documentName;
	string fileContent;
	
	
public:
	TPS()
	{
		documentName = "";
		fileContent = "";
	}
	TPS(string fileName)
	{
		this->documentName = fileName;
		fileContent = "";
	}
	
	void loadfromfile()
	{
		ifstream file(documentName);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				fileContent += line;
			}
			file.close();
		}
		else
		{
			cout << "Unable to open file" << endl;
		}
	}
	
	void addUndoMegaState()
	{
		if (undoStack.isEmpty())
		{
			cout << "Nothing to undo" << endl;
		}
		else
		{
			Queue tempQueue;
			while (!undoStack.isEmpty())
			{
				tempQueue.enqueue(undoStack.pop());
			}
			megaUndoQueue.enqueue(tempQueue.getSize());
			while (!tempQueue.isEmpty())
			{
				undoStack.push(tempQueue.dequeue());
			}
		}
	}
	
	void addRedoMegaState()
	{
		if (redoStack.isEmpty())
		{
			cout << "Nothing to redo" << endl;
		}
		else
		{
			Queue tempQueue;
			while (!redoStack.isEmpty())
			{
				tempQueue.enqueue(redoStack.pop());
			}
			megaRedoQueue.enqueue(tempQueue.getSize());
			while (!tempQueue.isEmpty())
			{
				redoStack.push(tempQueue.dequeue());
			}
		}
	}

	void restoreUndoMegaState()
	{
		if (megaUndoQueue.isEmpty())
		{
			cout << "Nothing to undo" << endl;
		}
		else
		{
			int size = megaUndoQueue.dequeue();
			for (int i = 0; i < size; i++)
			{
				undoStack.push(redoStack.pop());
			}
		}
	}
	
	void restoreMegaRedoState()
	{
		if (megaRedoQueue.isEmpty())
		{
			cout << "Nothing to redo" << endl;
		}
		else
		{
			int size = megaRedoQueue.dequeue();
			for (int i = 0; i < size; i++)
			{
				redoStack.push(undoStack.pop());
			}
		}
	}
	
	void createNewDocument(string fileName)
	{
		documentName = fileName;
		fileContent = "";
	}
	
	void undo()
	{
		if (undoStack.isEmpty())
		{
			cout << "Nothing to undo" << endl;
		}
		else
		{
			char action = undoStack.pop();
			if (action == 'a')
			{
				fileContent = fileContent.substr(0, fileContent.length() - 1);
			}
			else if (action == 'd')
			{
				fileContent += redoStack.pop();
			}
			redoStack.push(action);
		}
	}

	void redo()
	{
		if (redoStack.isEmpty())
		{
			cout << "Nothing to redo" << endl;
		}
		else
		{
			char action = redoStack.pop();
			if (action == 'a')
			{
				fileContent += undoStack.pop();
			}
			else if (action == 'd')
			{
				fileContent = fileContent.substr(0, fileContent.length() - 1);
			}
			undoStack.push(action);
		}
	}

	string getDocumentText(string fileName)
	{
		if (fileName == documentName)
		{
			return fileContent;
		}
		ifstream file;
		string content = "";
		file.open(fileName);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				content += line;
			}
			file.close();
		}
		else
		{
			cout << "Unable to open file" << endl;
		}
		return content;
	}

	void readDocument(string fileName)
	{
		ifstream file;
		file.open(fileName);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				cout << line<<endl;
			}
			file.close();
		}
		else
		{
			cout << "Unable to open file" << endl;
		}
	}
	
	void saveFile()
	{
		ofstream file;
		file.open(documentName);
		file << fileContent;
		file.close();
		
	}
	
	void addText(string text)
	{
		while (!redoStack.isEmpty())
		{
			redoStack.pop();
		}
		for (int i = 0; i < text.length(); i++)
		{
			undoStack.push(text[i]);
			fileContent += text[i];
			
		}
		addUndoMegaState();
		saveFile();
	}
	
	void closeFile()
	{
		saveFile();
	}
	
	bool documentExists(string fileName)
	{
		ifstream file;
		file.open(fileName);
		if (file.is_open())
		{
			file.close();
			return true;
		}
		else
		{
			return false;
		}
	}
	
	
	void handleInput(string& text) {
		string input;
		getline(cin, input);
		if (input == "@")
		{
			undo();
		}
		else if (input == "#")
		{
			redo();
		}
		else if (input == "!")
		{
			saveFile();
		}
		else if (input == "*") {
			//closes the file
			
		}
		else if (input == "read")
		{
			readDocument(documentName);
		}
		else if (input == "new")
		{
			cout << "Enter file name: ";
			string fileName;
			getline(cin, fileName);
			createNewDocument(fileName);
		}
		else if (input == "open")
		{
			cout << "Enter file name: ";
			string fileName;
			getline(cin, fileName);
			fileContent = getDocumentText(fileName);
			documentName = fileName;
		}
		else if (input == "exit")
		{
			exit(0);
		}
		else
		{
			addText(input);
		}
	}
};