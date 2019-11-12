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

// Below arrays details all 4 possible movements from a cell


// The function returns false if pt is not a valid position
bool isValid(int x, int y)
{return (x >= 0 && x < m) && (y >= 0 && y < n);}
int count_Path(Node* path)
{
	if (path==NULL)
		return 0;
	int len = count_Path(path->getp()) + 1;
	return len;
}
int Count_Path(Node* path)
{
	if (path==NULL)
		return -1;
	int len = count_Path(path->getp());
	return len;
}

void show_Path(Node* path, ofstream& f)
{
	if (path==NULL)
		return;
	show_Path(path->getp(),f);
	if(path->getp()!=NULL){
        cout << "(" << path->getx() << ", " << path->gety() << ") ";
        f<< path->getx() << " " << path->gety()<<endl;
	}


}


int n_unclear_Path(Node* path,int** unclear_matrix)
{

	if (path==NULL)
		return 0;
	int len=n_unclear_Path(path->getp(),unclear_matrix);
	if(unclear_matrix[path->getx()][path->gety()]==0)
        return ++len;
	else
	    return len;
}
int N_unclear_Path(Node* path,int** unclear_matrix)
{

	if (path==NULL)
		return 0;
	return n_unclear_Path(path->getp(),unclear_matrix);

}

Node* find_shortest_Path(int** matrix, int x, int y,int x_ ,int y_ )
{
	// create a queue and enqueue first node

	Queue<Node*> q;
	Node* src;
	src=new Node(x,y);

	q.push(src);

	// set to check if matrix cell is visited before or not
	//int visited;
	//visited.insert(src);
    bool visited[m][n];

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++){
                visited[i][j] = false;
                if (matrix[i][j] == 1)
                visited[i][j] = true;
        }

    visited[x][y] = true;

	// run till queue is not empty
	while (!q.IsEmpty())
	{
		// pop front node from the queue and process it
		Node* curr = q.Front();
		q.pop();

		int i = curr->getx();
		int j = curr->gety();

		if (i == x_ && j == y_)
		{

			return curr;
		}

		int n = matrix[i][j];

        int row[] = { -1, 0, 0, 1 };
        int col[] = { 0, -1, 1, 0 };
		for (int k = 0; k < 4; k++)
		{

			int x = i + row[k] ;
			int y = j + col[k] ;


			if (isValid(x, y))
			{

				Node *next;
				next=new Node(x,y);
				next->setp(curr);


				if (!visited[x][y])
				{
					q.push(next);
					visited[x][y]=true;
				}
			}
		}
	}
    return NULL;

}
bool Isclear(int** unclear_matrix,int m, int n){
    for(int i=0;i<m;i++)
      for(int j=0;j<n;j++){
        if(unclear_matrix[i][j]==0 )
            return false;
      }
    return true;
}
void run_Path(Node* path,int** unclear_matrix)
{

	if (path==NULL)
		return;
	run_Path(path->getp(),unclear_matrix);
	unclear_matrix[path->getx()][path->gety()]=2;
	//return;
}