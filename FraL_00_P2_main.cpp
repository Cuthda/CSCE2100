//Author Lea Francher
//Due 10/12/15
//The purpose of this program is to create a simple mechanism to prototype data in a linked list. The program will act as an address book and will later be expanded to do more things.

#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <list>
using namespace std;


//create a base class people
class people
{
	//declare private variables for name, id and pointer to get next node
	private:
		string name;
		int Id;
		people *next;

	//create functions to get/set the id, name, and pointer to next node.
	public:
		people(string nm, int id)
		{
			name = nm;
			Id = id;
			cout << "ADDED: id" << setfill('0') << setw(3) << id << " " << nm << endl;
		}
		int getid()
		{
			return Id;
		}
		string getname()
		{
			return name;
		}
		void setname(string nme)
		{
			name=nme;
		}
		void setId(int id)
		{
			Id = id;
		}
		void setnext(people *n)
		{
			next=n;
		}
		people *getnext()
		{
			return next;
		}
};

//this class acts as the link list of people
class peoples
{
	//declare private vairables, top, bottom and a counter
	private:
		int count;
		people *top;
		people *bottom;
	//set up constructor and functions for adding, removing, searching, alphabetizing, and printing people
	public:
		peoples()
		{
			count=0;
			top = bottom = NULL;
		}
		~peoples()
		{
			people * now = top;
			while (now != bottom)
			{
				people * next = now->getnext();
				delete now;
				now = next;
			}
		}
		void addpeople()
		{
			//declare variables nme to hold the name, id to give each an id
			string nme;
			int id=1;
			//temporary variables to hold pointers 
			people *temp, *temp2;
			temp2 = top;
			//carriage return
			cin.ignore();
			//take in the name
			getline(cin,nme);
			//create the correct id
			id=id+count;
			//add the new person
			temp = new people (nme, id);
			//set up the link list if there is nothing
			if(count == 0)
			{
				top=bottom=temp;
				temp->setnext(NULL);
				count++;
			}
			//update the linked list if it is already created
			else
			{
				bottom->setnext(temp);
				bottom=temp;
				temp->setnext(NULL);
				count++;
			}
		}
		void alphapeople(int counter)
		{
			int i;
			//set up a for loop to only loop as many of nodes in the list minus one so we can keep going through the list the exact amount of times to make it alphabetized
			for(i=0;i<(counter-1);i++)
			{
				//declare pointer vairables and temp holders not names
				people *now = top;
				people *next = top->getnext();
				string tempnme, tempnme2;
				//if the next node is nothing then we dont need to alphabetize anything
				if(now->getnext() == NULL)
				{
					return;
				}
				else
				{
					//while there is a node
					while (now != NULL)
						{
							//take in the name of the node we are on and the one after it
							tempnme = now->getname();
							tempnme2 = next->getname();
							//compare the two and switch them if needed
							if(tempnme > tempnme2)
							{
								now->setname(tempnme2);
								next->setname(tempnme);
							}
							//if the next is not null then we can get the next node's pointer
							if(next->getnext() != NULL)
							{
								next = next->getnext();
							}
							//get the next pointer
							now = now->getnext();					 	
						}
				}
			}	
		}
		void printpeople()
		{
			//starting at the top, we print all of the names and ids in the list
			people *now = top;
			while (now != NULL)
			{
				cout << "id" << setfill('0') << setw(3) << now->getid();
				cout << " " << now->getname() << endl;
				now = now->getnext();
			}
		}
		void searchpeople(string nme)
		{
			//startug at the top we will look at each node to see if there is the name the user asked for
			people *now = top;
			while (now != NULL)
			{
				if(nme == now->getname())
				{	
					cout << "TRUE: " << now->getname() << endl;
					return;
				}
				now = now->getnext();
			}
			cout << "FALSE: " << nme << endl;
		}
		int removepeople(string nme, int counter)
		{
			//if there is no one in the list then we send an error to avoid a seg fault and return the original counter
			if(counter == 0)
			{
				cout << "ERROR: There is no one in your address book." << endl;
				return counter;
			}
			//declare temp vairables to hold the name and id at the top 
			string tnme = top->getname();
			int id = top->getid();
			//start at the top
			people *now = top;
			people *temp = NULL;
			//while there is something in the list
			while (now != NULL)
			{
				//if the name the user wants matches one of the nodes
				if(nme == now->getname())
				{
					//if that node is the top one, make the next node the 'head' and delete the old head
					if(now==top)
					{
						temp = top;
						top = temp->getnext();
						delete temp;
						cout << "Removal successful: " << nme << endl;
						//decrease the counter by 1 since we removed a node
						counter = counter-1;
						alphapeople(counter);
						return counter;
					}
					//if the node is not at the top, put it at the top and remove the top after setting the next one to be the new head
					now->setname(tnme);
					now->setId(id);
					temp = top;
					top = temp->getnext();
					delete temp;
					cout << "Removal successful: " << nme << endl;
					//successful removal, minus the counter by one and return it
					counter = counter-1;
					//since we altered the list we need to realphabetize it
					alphapeople(counter);
					return counter;	
				}
				//get the next pointer
				now = now->getnext();
			}
			//if the while loop goes all the way through we know the requested person does not exist, send an error
			cout << "ERROR: Not found for Removal: " << nme << endl;
			return counter;
		}
};

void initaldisplay(void);

int main()
{
	//declare a variable counter to count how many nodes we have
	int counter=0;
	//variable to hold the command
	string command;
	//print the welcome message
	initaldisplay();
	//introduce the classes to main
	peoples mypeoples;
	//temp name holder nme
	string nme;
	//do while the command isnt quit
	do
	{
		cout << "command << ";
		//take in user comman
		cin >> command;
		//if they said 'add' then add the person and alphabetize, increase counter by 1
		if(command == "add")
		{
			mypeoples.addpeople();
			counter++;
			mypeoples.alphapeople(counter);
		}
		//if 'search', call function search to make sure they exist
		else if(command == "search")
		{
			cin.ignore();
			getline(cin,nme);
			mypeoples.searchpeople(nme);
		}
		//if 'print', call function to print all the people
		else if(command == "print")
		{
			mypeoples.printpeople();
		}
		//if 'remove', call function to remove the person if they exist
		else if(command == "remove")
		{
			cin.ignore();
			getline(cin,nme);
			counter = mypeoples.removepeople(nme, counter);
		}
		//if 'file' I, have no idea what to dp
		else if(command == "file")
		{
		}
		cout << "-----------------------------------------------" << endl;
	}while(command != "quit");
	//say bye 
	cout << "Have a nice day." << endl;
	cout << "-----------------------------------------------" << endl;

}

//void function to just display a welcome message
void initaldisplay(void)
{
	cout << "Computer Sciecne and Engineering, CSCE 2100 - Computing Foundations I\nLea Francher, lrf0055, leafrancher@my.unt.edu\n";
	cout << "-----------------------------------------------" << endl;
	cout << "Welcome to Lea's Address Book" << endl;
}
