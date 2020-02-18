//Samuel Larson
//program 10
//12/3/2018
#include <iostream>
#include <fstream>
using namespace std;
void printmenu();
class BST
{
    public:
        typedef int item;
        //constructors
        BST(){root = NULL;} //creates the start of the list
        //destructor - gives back a list's nodes
        ~BST(){destroy(root);}
        //modification member functions
        bool empty(){return root == NULL;}
        void insert(item entry); //inserts a number to the list
        void remove(item target); //removes a number from the list
        //constant member functions
        void write();
        int length(){return r_length(root);} //returns the length
        bool present(item target); //finds a number in the list
    private:
        //data members
        struct node //structure of a node
        {
            item data;
            node*left;
            node*right;
        };
        node*root;
        //private function
        void destroy(node*);
        int r_length(node*);
        void r_write(node*); //prints the list
        void r_remove(node*&, item);
        void remove_node(node*&);
};
int main()
{
    char funct;
    int num;
    BST numbers;
    printmenu();

    while(funct != 'q')
    {
        cin >> funct;
        switch(funct)//triggers a function based on what the user entered
        {
            case 'e': numbers.~BST();
                      cout << "The tree has been emptied" << endl;
                      break;
            case 'i': cin >> num;
                      numbers.insert(num);
                      cout << num << " has been inserted into the tree" << endl;
                      break;
            case 'r': cin >> num;
                      numbers.remove(num);
                      break;
            case 'l': cout << numbers.length() << " is the length of the tree" << endl;
                      break;
            case 'p':{cin >> num;
                      if(numbers.present(num) == false)
                            cout << num << " was not found in the tree" << endl;
                      else
                            cout << num << " was found in the tree" << endl;
                      break;
                     }
            case 'w': cout << "List:" << endl;
                      numbers.write();
                      break;
            case 'h': printmenu();
        }
    }
void write();
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
         << "w   -- Print the list" << endl
         << "h   -- See this menu" << endl
         << "q   -- Quit" << endl;
}
//post: list is emptied
void BST::destroy(node*p)
{
    if(p!=NULL)
    {
        destroy(p->left);
        destroy(p->right);
        delete p;
    }
}
//pre:user enters a number to be added post: number is added to the list
void BST::insert(item entry)
{
    node *p, *back, *temp;
    p = root;
    back = NULL;
    while(p != NULL)
    {
        back = p;
        if(entry < p->data)
            p = p->left;
        else //entry > p->data
            p = p->right;
    }
    //build a new node
    temp = new node;
    temp->data = entry;
    temp->left = NULL;
    temp->right = NULL;
    if(back == NULL)
        root = temp;
    else if(entry < back->data)
        back->left = temp;
    else //entry > back->data
        back->right = temp;
}
//pre: user enters a number to remove post:a function is called to remove the value
void BST::remove(item target)
{
    r_remove(root,target);
    cout << target << " was removed" << endl;
}
//pre: user enters a number to remove post:function removes the value from the tree
void BST::r_remove(node *&t, item target)
{
    if(t->data == target)
        remove_node(t);
    else if(target < t->data)
        r_remove(t->left, target);
    else//target > t->data
        r_remove(t->right, target);
}
//pre: node to remove post: node is removed
void BST:: remove_node(node *&t)
{
    node *ptr, *back;
    if(t->left == NULL)
    {
        delete t;
        t = NULL;
    }
    else if(t->right == NULL)
    {
        ptr=t;
        t = t->left;
        delete ptr;
    }
    else if(t->left == NULL)
    {
        ptr = t;
        t = t->right;
        delete ptr;
    }
    else
    {
        back = t;
        ptr = t->right;
        while(ptr->left != NULL)
        {
            back = ptr;
            ptr = ptr->left;
        }
        t->data = ptr->data;
        if(back==t)
            remove_node(back->right);
        else
            remove_node(back->left);
    }
}
//post: calls function to print the tree
void BST::write()
{
    r_write(root);
    cout << endl;
}
//post:function prints the tree
void BST::r_write(node*p)
{
    if(p != NULL)
    {
        r_write(p->left);
        cout << p->data << ' ';
        r_write(p->right);
    }
}
//post:function returns the length of the tree
int BST::r_length(node*p)
{
    if(p == NULL)
        return 0;
    else
        return r_length(p->left) + 1 + r_length(p->right);
}
//pre: user enters a number to search for post: function returns true or false if found
bool BST::present(item target)
{
    node*p;
    p=root;
    while(true)
    {
        if(p == NULL)
            return false;
        if(target<p->data)
            p = p->left;
        else if(target==p->data)
            return true;
        else //target>p->data
            p = p->right;
    }
}



