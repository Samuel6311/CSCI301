//Samuel Larson
//Project 6
//10/22/18
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int evaluate(int, int, char);
void invalid();

class stack
{
public:
    typedef char item;
    //member constant
    static const int CAPACITY = 20;
    //constructor
    stack(){used = 0;}
    //modification functions
    void push(item entry);
    item pop();
    //constant member functions
    int size(){return used;}
    bool empty(){return used == 0;}
private:
    //data members
    item data[CAPACITY];
    int used;
};

int main()
{
    stack num;
    stack op;
    ifstream infile;
    infile.open("equation.txt");
    char ch, func, popped;
    string line;
    int result, oper1, oper2, pos;
    while(getline(infile, line))
    {
        cout << "expression: ";
        pos = 0;
        while(line[pos] >= ' ')
        {
            ch = line[pos];
            cout << ch;
            if(ch < '(' || ch > '9' || ch == ',' || ch == '.')
            {
                invalid();
                return 0;
            }
            if(ch == '+' || ch == '-' || ch == '*' || ch == '/')
            {
                if(line[pos - 1] == '(' || line[pos - 1] == '+' || line[pos - 1] == '-'
                   || line[pos - 1] == '*' || line[pos - 1] == '/')
                {//displays that the equation is invalid
                    invalid();
                    return 0;
                }
                op.push(ch);
            }
            if(ch == '(')
                op.push(ch);
            if(ch >= '0' && ch <='9')
                num.push(ch);
            if(ch == ')')
            {
                if(op.empty())
                {//displays that the equation is invalid
                    invalid();
                    return 0;
                }
                popped = op.pop();
                if(popped == '('  || line[pos - 1] == '+' || line[pos - 1] == '-'
                   || line[pos - 1] == '*' || line[pos - 1] == '/')
                {//displays that the equation is invalid
                    invalid();
                    return 0;
                }
                while(popped != '(')
                {
                    oper2 = num.pop() - '0';
                    oper1 = num.pop() - '0';
                    func = popped;
                    num.push(evaluate(oper1,oper2,func));
                    popped = op.pop();
                }
                popped = op.pop();
                if(popped != '(')
                {
                    while(op.size() > 0 && popped != '(')
                    {
                        oper2 = num.pop() - '0';
                        oper1 = num.pop() - '0';
                        func = op.pop();
                        num.push(evaluate(oper1,oper2,func));
                    }
                }
                op.push(popped);
            }
            pos++;
        }
        while(op.size() > 0)
        {
            oper2 = num.pop() - '0';
            oper1 = num.pop() - '0';
            func = op.pop();
            num.push(evaluate(oper1,oper2,func));
        }
        cout << endl << "Value = " << num.pop() << endl;
    }

    return 0;
}
//pre: data is entered post: data is put into a stack
void stack::push(item entry)
{
    data[used] = entry;
    ++used;
}
//post: data is returned from the stack
stack:: item stack::pop()
{
    --used;
    return data[used];
}
//pre: 2 operators and 1 operand are entered post: equation is solved
int evaluate(int oper1, int oper2, char func)
{
    int result;
    switch(func)
    {
        case'+':
            result = oper1 + oper2;
            return('0' + result);
        case'-':
            result = oper1 - oper2;
            return('0' + result);
        case'*':
            result = oper1 * oper2;
            return('0' + result);
        case'/':
            result = oper1 / oper2;
            return('0' + result);
    }
}
//post: message is displayed
void invalid()
{
   cout << endl << "expression not valid" << endl
        << "ending program" << endl;
}
