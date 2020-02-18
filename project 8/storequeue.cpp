//Samuel Larson
//Project 8
//11/08/18
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class queue
{
public:
    typedef int item;
	static const int CAPACITY = 20;
	//constructor
	queue();
	//modification member functions
	void enqueue(item entry);
	item dequeue();
	//constant member functions
	int size(){return count;}
	bool empty(){return count == 0;}
	void print();
private:
    //data members
	item data[CAPACITY];
	int front;
	int rear;
	int count;
	//private function
	int next_index(int i){return (i+1)%CAPACITY;}
};

int main()
{
    int seed, sumtime, customers, avgtime, prob, tickmax, toticks, queues,
        ticks, shortline, longest, shortest, custinqueue, transtime, wait;
    cout << "Enter these parameters of the situation: " << endl;
    cout << "   The number of queue/server pairs: ";
    cin >> queues;
    cout << "   The probability that a customer arrives in one tick (%): ";
    cin >> prob;
    cout << "   The maximum duration of a transaction in ticks: ";
    cin >> tickmax;
    cout << "   The duration of the simulation in ticks: ";
    cin >> toticks;
    cout << "Enter a random number seed: ";
    cin >> seed;
    srand(seed);
    sumtime = 0;
    customers = 0;
    longest = 0;
    custinqueue = 0;
    queue lines[queues];//an array of queues
    queue times[queues];//an array of times entered into a queue
    int servers[queues];//an array of servers for each queue
    for(int i=0; i<queues; i++)
        servers[i]=0;
    for(ticks = 1; ticks<=toticks; ticks++)
    {
        if(rand()%100 <= prob)//random chance a customer enters a queue
        {
            transtime = rand()%tickmax;
            shortest = 0;//customer defaults to the first queue
            for(int i=0; i<queues; i++)//finds shortest queue
            {
               if(lines[i].size() < lines[shortest].size())
                    shortest = i;
            }
            lines[shortest].enqueue(transtime);
            times[shortest].enqueue(ticks);
            custinqueue++;
        }
        for(int i=0; i<queues; i++)
        {//finds servers that are done with their customer
            if(servers[i]==0 && lines[i].size()>0)
            {
                customers++;
                servers[i]=lines[i].dequeue();
                wait=ticks-times[i].dequeue();
                if(wait>longest)
                    longest=wait;
                sumtime=sumtime+wait;
                custinqueue--;
            }
        }

        cout << ticks << endl;
        for(int j=0; j<queues; j++)//prints current state of queues
        {
            cout << "  " << servers[j] << "  ";
            lines[j].print();
            cout << endl;
        }
        for(int g=0; g<queues; g++)//decrements the amount of time left in a transaction
        {
            if(servers[g]>0)
                servers[g]--;
        }
    }
    if(customers != 0)
        avgtime = sumtime/customers;
    else
        avgtime = 0;
    cout << customers << " customers waited an average of "
         << avgtime << " ticks." << endl;
    cout << "The longest time a customer waited was " << longest << " ticks." << endl;
    cout << custinqueue << " customers remain in the lines." << endl;
    return 0;
}
//constructor
queue::queue()
{
    front = 0;
    rear = CAPACITY-1;
    count = 0;
}
//pre: entry is entered post: entry is added to a queue
void queue::enqueue(item entry)
{
	rear = next_index(rear);
	data[rear] = entry;
	++count;

	return;
}
//pre: non empty queue post::returned value from the queue
queue::item queue::dequeue()
{
    item it;
    it = data[front];
    front = next_index(front);
    --count;
    return it;
}
//post: printed values of the queue
void queue::print()
{
    for(int i=0; i<size(); i++)
        cout << data[i] << " ";
}
