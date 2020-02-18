//Samuel Larson
//program 3
//10/4/2018
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

const int MAX = 8;

int length();

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
        void insert(item entry); //calls the private insert function
        //constant member functions
        ofstream& operator<<(ofstream&);//calls the private print function
        int length(); //calls the private length function
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
        void insert(item entry, node*&); //inserts a number to the list
        void make_empty(node*); //empties the list
        int length(node*); //prints the length
        void print(ofstream&, node*); //prints the list
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

ofstream& operator<<(ofstream& out_f)//calls the private print function
{
    wordlist.print(out_f, wordlist.first);
    return out_f;
}

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
    list::ofstream(wordlist);
    cout << "There is " << wordlist.length() << " unique word(s)" << endl;
    wordlist.~list();

    return 0;
}

//post:list is deconstructed
list::~list()
{
  make_empty(first);
}
//post: list is emptied
void list::make_empty(node*p)
{
    if(p != NULL)
    {
        make_empty(p->next);
        delete p;
    }
}
void list::insert(item entry)
{
    insert(entry, first);
}
//pre:user enters a number to be added post: number is added to the list
void list::insert(item entry, node*&p)
{
    if(p == NULL || strcmpi(entry,p->word) > 0){
        p =  get_node(entry, p);
        return;
    }
    if(strcmpi(entry,p->word) == 0)//checks if the words are the same
        p->amount = p->amount + 1;//increments the counter of that word
    else
        insert(entry, p->next);
}
//post:function prints the list
void list::print(ofstream& out_f, node*p)
{
    if(p != NULL){
        cout << p->word << " " << p->amount << endl;
        print(p->next);
    }
}
//post:returns the length of the list
int list::length()
{
    return length(first);
}
//post:function returns the length of the list
int list::length(node*p)
{
    if(p == NULL)
        return 0;
    else
        return length(p->next)+1;
}



