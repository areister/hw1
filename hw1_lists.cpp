#include <iostream>
#include <string> 
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

struct Item 
{
	Item(int v, Item* n)
	{
		val = v;
		next = n;
	}
	int val;
	Item* next;
}; 

Item* copy(Item* head)
{
	if(head == NULL)
	{
		return NULL;
	}
	else
	{
		return new Item(head->val, copy(head->next));
	}
}

Item* travel(Item* head)
{
	if (head -> next== NULL)
	{
		return head;
	}
	else
	{
		travel(head -> next);
	}
}


Item* concatenate(Item* head1, Item* head2) //returns one list
{
	Item* newhead1 = new Item(0, NULL);
	Item* newhead2 = new Item(0, NULL);
	newhead1 = copy(head1);
	newhead2 = copy(head2);

	Item* end = new Item(0, NULL);
	end = travel(newhead1);
	end->next = new Item(newhead2->val, newhead2->next);
	return newhead1;
}
	

void removeEvens(Item*& head)
{
	if (head -> next == NULL)
	{
		//break;
	}
	else 
	{

		int input = head -> next -> val;
		if (input % 2 == 0)
		{
			head -> next = head -> next -> next;
			removeEvens(head);
		}
		else
		{
			removeEvens(head -> next);
		}
	}
}

int counter(Item* head)
{
	if (head == NULL)
	{
		return 0;
	}
	else
	{
		return (counter(head -> next) + 1);
	}
}


double findSum(Item* head)
{
	if (head == NULL)
	{
		return 0;
	}
	else
	{
		return (findSum(head -> next) + head ->val);
	}
}

double findAverage(Item* head)
{
	double total = findSum(head);
	double number = counter(head);
	cout << "Total: " << total << endl;
	cout << "Number: " << number << endl;
	return total/number;

}



void printList(std::ostream& ofile, Item* head)
{
  if(head == NULL)
    ofile << std::endl;
  else {
    ofile << head->val << " ";
    printList(ofile, head->next);    
  }
}

int main (int argc, char *argv[])
{
	//argv[1] is input
	//argv[2] is output
	ifstream file;
	file.open(argv[1]);

	Item* head = NULL;
	Item* head1 = NULL;
	Item* head2 = NULL;
	Item* head3 = NULL;
	Item* current = NULL;

	int counter = 0;
	while (!file.eof())
	{
		string buffer; 
		stringstream ss;
		getline(file, buffer);
		ss << buffer;
		string input; 
		while (!ss.eof()) 
		{
			ss >> input;
			int IntInput = atoi(input.c_str());

			if (counter == 0)
			{
				if (head1 == NULL)
				{
					head1 = new Item(IntInput, NULL);
					current = head1;
					//cout << IntInput << " ";
					//cout << "Head 1 " << head1 -> val << endl;
				}
				else if (head1 != NULL)
				{
					current -> next = new Item(IntInput, NULL);
					current = current -> next;
					//cout << IntInput << " ";
					//cout << "PRINT" << endl;
				}
			}

			if (counter == 1)
			{
				if (head2 == NULL)
				{
					head2 = new Item(IntInput, NULL);
					current = head2;
					//cout << IntInput << " ";
				}
				else if (head2 != NULL)
				{
					current -> next = new Item(IntInput, NULL);
					current = current -> next;
					//cout << IntInput << " ";
				}
			}
		}
		counter++;
	}

	//Item* head1 = NULL;
	//Item* head2 = NULL;
	//Item* head3 = NULL;

	ofstream ofile(argv[2]);

	head3 = concatenate(head1, head2);

	//ofile << "Head 3 List 1st round" << endl;
	//printList(ofile, head3);

	removeEvens(head3);
	cout << findAverage(head3) << endl;
	


	//ofstream ofile(argv[2]);
	ofile << "Head 1 List" << endl;
	printList(ofile, head1);

	ofile << "Head 2 List" << endl;
	printList(ofile, head2);

	ofile << "Head 3 List" << endl;
	printList(ofile, head3);


	return 0;
}