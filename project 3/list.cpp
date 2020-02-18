//Samuel Larson
//program 3
//9/24/2018
#include <iostream>
#include <fstream>
using namespace std;

void printmenu();

class list
{
    public:
        typedef int item;
        //constructors
        list(){first = NULL;} //creates the start of the list
        list(const list&);
        //destructor - gives back a list's nodes
        ~list();
        //modification member functions
        void make_empty(); //empties the list
        void insert(item entry); //inserts a number to the list
        void remove(item target); //removes a number from the list
        //constant member functions
        void print(); //prints the list
        int length(); //prints the length
        bool present(item target); //finds a number in the list
        void kth(int k); //finds the kth number in the list
    private:
        //data members
        struct node //structure of a node
        {
            item data;
            node*next;
        };
        node*first;
        //private function
        node*get_node(item entry, node*link) //creates a node
        {
            node*temp;
            temp = new node;
            temp->data = entry ;
            temp->next = link;
            return temp;
        };
};

int main()
{
    char funct;
    int num;
    list numbers;
    printmenu();

    while(funct != 'q')
    {
        cin >> funct;
        //triggers a function based on what the user entered
        switch(funct)
        {
            case 'e': numbers.make_empty();
                      cout << "The list has been emptied" << endl;
                      break;
            case 'i': cin >> num;
                      numbers.insert(num);
                      cout << num << " has been inserted into the list" << endl;
                      break;
            case 'r': cin >> num;
                      numbers.remove(num);
                      break;
            case 'l': cout << numbers.length() << " is the length of the array" << endl;
                      break;
            case 'p':{cin >> num;
                      if(numbers.present(num) == false)
                            cout << num << " was not found in the list" << endl;
                      else
                            cout << num << " was found in the list" << endl;
                      break;
                     }
            case 'k':{cin >> num;
                      cout << "the kth number in the array is ";
                      numbers.kth(num);
                      cout << endl;
                      break;
                     }
            case 'w': cout << "List:" << endl;
                      numbers.print();
                      break;
            case 'h': printmenu();
        }


    }

    return 0;
}
//post: function prints the menu
void printmenu()
{
    cout << "Commands" << endl
         << "e   -- Empty the list" << endl
         << "i v -- Insert an integer (v) into the list" << endl
         << "r v -- Remove an integer (v) from the list" << endl
         << "l   -- Print the length of the list" << endl
         << "p v -- Searches the list for an integer (v)" << endl
         << "k v -- Print the kth value of the list" << endl
         << "w   -- Print the list" << endl
         << "h   -- See this menu" << endl
         << "q   -- Quit" << endl;
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
    node*prev;
    if(first == NULL || entry < first->data)
        first =  get_node(entry, first);
    else
    {
        prev = first;
        while(prev->next != NULL && prev->next->data < entry)
            prev = prev->next;
        prev->next = get_node(entry, prev->next);
    }
}
//pre: user enters a number to remove post:function removes the value from the list
void list::remove(item target)
{
    node*prev;
    node*temp;
    prev=first;
    if(first == NULL){
        cout << target << " was not in the list" << endl;
        return;
    }
    if(first -> data == target)
    {
        first = first ->next;
        delete prev;
    }
    else
    {
        while(prev->next != NULL && prev->next->data != target)
            prev = prev->next;
        if(prev->next == NULL){
            cout << target << " was not in the list" << endl;
            return;
        }
        temp = prev->next;
        prev->next = temp->next;
        delete temp;
    }
    cout << target << " was removed from the list" << endl;
}
//post:function prints the list
void list::print()
{
    node*p;
    p = first;
    while(p != NULL){
        cout << p->data << endl;
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
//pre: user enters a number to search for post: function returns true or false if found
bool list::present(item target)
{
    node*p;
    p = first;
    while(p != NULL){
        if(p->data == target)
            return true;
        p = p->next;
    }
    return false;
}
//pre: user enters a number post: function returns a number in the position of the list
void list::kth(int k)
{
    int count = 0;
    node*p;
    p = first;
    if(k > length()){
        cout << "non existing" << endl;
        return;
    }
    while(count != k - 1){
        p = p->next;
        count++;
    }
    cout << p->data;
}


