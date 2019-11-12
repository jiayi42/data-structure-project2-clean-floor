#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <stdio.h>
using namespace std;
int m,n,limit;

template<class T>
class QNode
{
	public:
	T data;
	QNode<T> *link;
	//~QNode(){
	//delete link;
	//link=NULL;
	//};
};
template<class T>
class Queue {
	public:
		Queue() {front = rear = 0;}
		~Queue();
		int IsEmpty()
		{return ((front) ? 0 : 1);}
		T Front();
		Queue<T>& push( T& x);
		void pop();
	private:
		QNode<T> *front;
		QNode<T> *rear;
};

	template<class T>
Queue<T>::~Queue()
{
	QNode<T> *next;
	while (front) {
		next = front->link;
		delete front;
		front=NULL;
		front = next;
	}
	delete next;
	next=NULL;
}
template<class T>
T Queue<T>::Front()
{
	if (IsEmpty())return NULL;
	return front->data;
}

template<class T>
Queue<T>& Queue<T>::push( T& x)
{
	QNode<T> *p = new QNode<T>;
	p->data = x;
	p->link = 0;
	if (front) rear->link = p;  // queue not empty
	else front = p;             // queue empty
	rear = p;
	return *this;
}
	template<class T>
void Queue<T>::pop()
{
	if (IsEmpty()) { return ; };
	QNode<T> *p = front;
	front = front->link;
	delete p;
}


class Node
{
    int x, y;
	Node* parent;
  public:
        Node(int x_,int y_):x(x_),y(y_),parent(NULL){}

        void setx(int x){this->x=x;}
        void sety(int y){this->y=y;}
        void setp(Node* p){this->parent=p;}

        int getx(){return this->x;}
        int gety(){return this->y;}
        Node* getp(){return this->parent;}

        bool const operator==(const Node* ob) const
        {return x == ob->x && y == ob->y;}
        bool operator<(const Node* ob) const
        {return x < ob->x || (x == ob->x && y < ob->y);}
};