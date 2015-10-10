//Author Lea Francher
//Due 10/12/15
//The purpose of this program is to create a simple mechanism to prototype data in a linked list. The program will act as an address book and will later be expanded to do more things.

#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;

class people
{
	private:
		string name;
		int Id;
		people *next;
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
		void setnext(people *n)
		{
			next=n;
		}
		people *getnext()
		{
			return next;
		}
};

class peoples
{
	private:
		int count;
		people *top;
		people *bottom;
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
			string nme;
			int id=1;
			people *temp, *temp2;
			temp2 = top;
			cin.ignore();
			cout << "Enter peoples name: ";
			getline(cin,nme);
			id=id+count;
			temp = new people (nme, id);
			if(count == 0)
			{
				top=bottom=temp;
				temp->setnext(NULL);
				count++;
			}
			else
			{
				bottom->setnext(temp);
				bottom=temp;
				temp->setnext(NULL);
				count++;
			}
		}
		void alphapeople()
		{
			people *now = top;
			people *next = now->getnext();
			string tempnme, tempnme2;
			//tempnme = now->getname();
			//tempnme2 = next->getname();
			//if(next->getname() != NULL)
			{
				//while (now != NULL)
				//{
				//	people *next = now->getnext();
				//	if(tempnme << tempnme2)
				//	{
				//		now->getname() = tempnme2;
				//		next->getname() = tempnme;
				//	}
				//	now = now->getnext();	 
				//}
			}
		}
		void printpeople()
		{
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
		void removepeople(string nme)
		{
			int searched;
			people *now = top;
			people *del = top->getnext();
			people *previous = top;
			people *temp = NULL;


			while (now != NULL)
			{
				if(nme == now->getname())
				{
					if(now==top)
					{
						temp = top;
						top = temp->getnext();
						delete temp;
						cout << "Removal successful: " << nme << endl;
						return;
					}
					previous = now->getnext(); 

					delete now;
					cout << "Removal successful: " << nme << endl;
					return;	
				}
				previous = now;
				now = now->getnext();
			}
			cout << "ERROR: Not found for Removal: " << nme << endl;
		}
};

void initaldisplay(void);

int main()
{
	string command;
	initaldisplay();
	peoples mypeoples;
	string nme;
	int searched;
	do
	{
		cout << "command << ";
		cin >> command;
		if(command == "add")
		{
			mypeoples.addpeople();
			mypeoples.alphapeople();
		}
		else if(command == "search")
		{
			cout << "name of the person you would like to search: ";
			cin.ignore();
			getline(cin,nme);
			mypeoples.searchpeople(nme);
		}
		else if(command == "print")
		{
			mypeoples.printpeople();
		}
		else if(command == "remove")
		{
			cout << "who would you like to remove: ";
			cin.ignore();
			getline(cin,nme);
			mypeoples.removepeople(nme);
		}
		else if(command == "file")
		{
		}
		cout << "-----------------------------------------------" << endl;
	}while(command != "quit");
	cout << "Have a nice day." << endl;
	cout << "-----------------------------------------------" << endl;

}

void initaldisplay(void)
{
	cout << "Computer Sciecne and Engineering, CSCE 2100 - Computing Foundations I\nLea Francher, lrf0055, leafrancher@my.unt.edu\n";
	cout << "-----------------------------------------------" << endl;
	cout << "Welcome to Lea's Address Book" << endl;
}
