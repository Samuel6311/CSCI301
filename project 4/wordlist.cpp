//Samuel Larson
//program 3
//10/4/2018
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

const int MAX = 8;

class list
{
    public:
        typedef char item[MAX+1];
        typedef int num;
        //constructors
        list(){first = NULL;} //creates the start of the list
        list(const list&);
        //destructor - gives back a list's nodes
        ~list();
        //modification member functions
        void make_empty(); //empties the list
        void insert(item entry); //inserts a number to the list
        //constant member functions
        void print(); //prints the list
        int length(); //prints the length
    private:
        //data members
        struct node //structure of a node
        {
            item word;
            num amount;
            node*next;
        };
        node*first;
        //private function
        node*get_node(item entry, node*link) //creates a node
        {
            node*temp;
            temp = new node;
            strcpy(temp->word,entry);
            temp->amount = 1;
            temp->next = link;
            return temp;
        };
};

int main()
{
    list wordlist;
    string filename;
    char word[MAX+1];
    ifstream infile;
    cout << "Please enter a file name" << endl;
    cin >> filename;
	infile.open(filename);	//opens the file m1.dat to take in information
	while(infile.good() == false)
	{
	    cout << "file does not exist" << endl
	         << "Please enter a file name" << endl;
        cin >> filename;
        infile.open(filename);	//opens the file m1.dat to take in information
	}
	while(!infile.eof())//inserts more words while it isn't the end of the file
    {
        infile >> word;
        wordlist.insert(word);
	}
	cout << "Word & Count" << endl;//start of the display of all words
    wordlist.print();
    cout << "There is " << wordlist.length() << " unique word(s)" << endl;
    wordlist.~list();

    return 0;
}

//post:list is deconstructed
list::~list()
{
    node*temp;
    while(first != NULL)
    {
        temp = first;
        first = first->next;
        delete temp;
    }
}
//post: list is emptied
void list::make_empty()
{
    node*temp;
    while(first != NULL)
    {
        temp = first;
        first = first->next;
        delete temp;
    }
}
//pre:user enters a number to be added post: number is added to the list
void list::insert(item entry)
{
    node*p;

    if(first == NULL)
        first =  get_node(entry, first);
    else
    {
        p = first;
        //scans the list for a match or the end
        while(p->next != NULL && strcmpi(entry,p->word) != 0)
        {
            p = p->next;
        }
        if(p->next == NULL)//checks if the next node exists
            p->next = get_node(entry, p->next);//creates a new node
        if(strcmpi(entry,p->word) == 0)//checks if the words are the same
            p->amount = p->amount + 1;//increments the counter of that word
    }
}
//post:function prints the list
void list::print()
{
    node*p;
    p = first;
    while(p != NULL){
        cout << p->word << " " << p->amount << endl;
        p = p->next;
    }
    return;
}
//post:function returns the length of the list
int list::length()
{
    node*p;
    int length = 0;
    p = first;
    while(p != NULL){
        length++;
        p = p->next;
        }
    return length;
}



