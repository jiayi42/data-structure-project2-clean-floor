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
        //cout << "(" << path->getx() << ", " << path->gety() << ") ";
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
int main()
{



    ifstream myfile("floor.data");
      int mmm;
      int nnn;
      int _limit;
int start_x,start_y;

      myfile>>mmm>>nnn>>_limit;
      m=mmm;
      n=nnn;
      //int probe;
      //int kk=max(100/n,1);
      //probe=min(100/m,kk);
      //cout<<"probe:"<<probe<<endl;
      limit=_limit;
       //cout<<m<<n<<limit<<endl;
      ///////////////////////////////////////////////////////////////////////
      char** f_matrix = new char*[m];//double pointer record pointer(for each row)
      for(int i = 0; i < m; ++i)
        f_matrix[i] = new char[n];//allocate elements space of each row

      for(int i = 0; i < m; ++i)
        myfile>>f_matrix[i];

    myfile.close();
    int space_go=0;
    /////////////////////////////////////////////////////////////////////////
      int** matrix = new int*[m];//double pointer record pointer(for each row)
      for(int i = 0; i < m; ++i)
        matrix[i] = new int[n];//allocate elements space of each row
      for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            if(f_matrix[i][j]=='0'){
                 matrix[i][j]=0;
                 space_go++;
            }

            if(f_matrix[i][j]=='1')
                matrix[i][j]=1;
            if(f_matrix[i][j]=='R'){
                    start_x=i;
                    start_y=j;
                matrix[i][j]=3;
            }
        }
      }
     //cout<<space_go<<endl;
      int**  dist_to_R_matrix = new int*[m];//double pointer record pointer(for each row)
      for(int i = 0; i < m; ++i)
         dist_to_R_matrix[i] = new int[n];//allocate elements space of each row
      for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j)
            dist_to_R_matrix[i][j] =0;







    //Node* cur;


    int Bat=0;
    int BBat=0;

Node* temp_cur;
    for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
        if(matrix[i][j]!=1){

                temp_cur=find_shortest_Path(matrix,start_x,start_y,i,j);
                dist_to_R_matrix[i][j]=Count_Path(temp_cur);
                if(dist_to_R_matrix[i][j]>BBat)
                    BBat=dist_to_R_matrix[i][j];

                delete temp_cur;

            }
        else{
            dist_to_R_matrix[i][j]=-1;

        }
        //cout<<dist_to_R_matrix[i][j]<<endl;
      }
       // cout<<endl;
     }


    Bat=BBat;

    int temp_x;
    int temp_y;
    Node* cur;
    Node* potential;

    int** unclear_matrix = new int*[m];//double pointer record pointer(for each row)
    for(int j = 0; j < m; ++j)
        unclear_matrix[j] = new int[n];//allocate elements space of each row
//cout<<"mom"<<endl;

    int total = 0;
    int smallest_total = 2147483647;//INT_MAX do not mutiply and add

    Bat*=2;
    int bat;
    int Battery_self=Bat;
    //cout<<Bat<<endl;
int factor=1;
while( Bat<= limit && Bat<=smallest_total){
    bat=Bat;
    total = 0;
    temp_x=start_x;
    temp_y=start_y;
   for(int i=0;i<m;i++)
      for(int j=0;j<n;j++)
        unclear_matrix[i][j]=matrix[i][j];

  //ofstream outfile ("project2_temp.final");
 // outfile<<start_x<<" "<<start_y<<endl;

  int step, step_uc, big_step;
  float benefits = 0;
  int potential_steps=0;
  while (!Isclear(unclear_matrix, m, n)) {
    int big = 0;
    big_step = 0;
    float Benefits = 0;
    cur = find_shortest_Path(matrix, temp_x, temp_y, start_x, start_y);
    // cout<<Count_Path(cur)<<endl;
    int loop=0;
    int tiny_loop=0;
    for (int i = 0; i <m; i++)
      for (int j = 0; j < n; j++) {
        if (unclear_matrix[i][j] == 0) {
          potential = find_shortest_Path(matrix, temp_x, temp_y, i, j);
          step = Count_Path(potential);
          step_uc = N_unclear_Path(potential, unclear_matrix);
          //loop=step+pow(pow(abs( temp_y-j),2)+pow(abs(temp_x- i),2),0.5);
          loop=dist_to_R_matrix[i][j];
          benefits = (float)step_uc / (float)(step);//+pow(pow(abs( temp_y-j),2)+pow(abs(temp_x- i),2),0.5));  // float
          // if((dist_to_R_matrix[i][j]+step)<=bat && step_uc>=big){
          if ((dist_to_R_matrix[i][j] + step) <= bat && benefits > Benefits) {
            delete cur;
            cur = potential;
            // big=step_uc;
            tiny_loop=loop;
            Benefits = benefits;
            big_step = step;
          }
          else if ((dist_to_R_matrix[i][j] + step) <= bat && benefits == Benefits  && loop>tiny_loop){// && (real_dis+big_step<(step+abs( temp_y-j)+abs(temp_x- i)))) {
            delete cur;
            cur = potential;
            tiny_loop=loop;
            Benefits = benefits;
            big_step = step;

            //cout<<temp_x<<","<< temp_y<<","<< i<<","<< j<<endl;
//cout<<real_dis<<endl;
          }
        }
      }
    temp_x = cur->getx();
    temp_y = cur->gety();
    if (temp_x == start_x && temp_y == start_y) {
      bat = Bat;
      run_Path(cur, unclear_matrix);
      //show_Path(cur,outfile);
      total +=Count_Path(cur);
    } else {
      run_Path(cur, unclear_matrix);
      //show_Path(cur,outfile);
      bat -= big_step;
      total += big_step;
    }
  }
  if (!(temp_x == start_x && temp_y == start_y)) {
    cur = find_shortest_Path(matrix, temp_x, temp_y, start_x, start_y);
    run_Path(cur, unclear_matrix);
    //show_Path(cur,outfile);
    total += Count_Path(cur);
  }


    if(total<smallest_total){
            Battery_self=Bat;
    smallest_total=total;
//cout<< Battery_self<<endl;
//cout<<":"<<smallest_total<<endl;
    }

    factor++;
    //Bat+=2;
    if(factor<5){
        if(space_go<100)
            Bat+=2;
        else if(space_go<200 &&space_go>=100)
            Bat+=4;
        else if(space_go<400 &&space_go>=200)
            Bat+=8;
        else
            Bat+=20;
    }

    else if(factor<10 &&factor>=5){
        if(space_go<100)
            Bat+=2;
        else if(space_go<200 &&space_go>=100)
            Bat+=8;
        else if(space_go<400 &&space_go>=200)
            Bat+=20;
        else
            Bat+=30;
    }

    else if((factor)<15 &&(factor)>=10){
        if(space_go<100)
            Bat+=2;
        else if(space_go<200 &&space_go>=100)
            Bat+=12;
        else if(space_go<400 &&space_go>=200)
            Bat+=40;
        else
            Bat+=60;
    }
    else if((factor)<30 &&(factor)>=15 &&space_go<100){
            Bat+=2;
    }
    else
         break;
    if(space_go>1000){
            Bat+=100;
            if(factor>5)
                break;
    }



    //cout<<Bat<<endl;
    delete cur;
    delete potential;

}

ofstream Toutfile ("final.path");
Toutfile<< smallest_total<<endl;
///////////////////
Bat=Battery_self;
bat=Bat;
total = 0;
    temp_x=start_x;
    temp_y=start_y;
   for(int i=0;i<m;i++)
      for(int j=0;j<n;j++)
        unclear_matrix[i][j]=matrix[i][j];

  //ofstream outfile ("project2_temp.final");
  Toutfile<<start_x<<" "<<start_y<<endl;
//Toutfile<< std::flush;
  int step, step_uc, big_step;
  float benefits = 0;
  int potential_steps=0;
  while (!Isclear(unclear_matrix, m, n)) {
    int big = 0;
    big_step = 0;
    float Benefits = 0;
    cur = find_shortest_Path(matrix, temp_x, temp_y, start_x, start_y);
    // cout<<Count_Path(cur)<<endl;
    int loop=0;
    int tiny_loop=0;
    for (int i = 0; i <m; i++)
      for (int j = 0; j < n; j++) {
        if (unclear_matrix[i][j] == 0) {
                //delete potential;
          potential = find_shortest_Path(matrix, temp_x, temp_y, i, j);
          step = Count_Path(potential);
          step_uc = N_unclear_Path(potential, unclear_matrix);
          //loop=step+pow(pow(abs( temp_y-j),2)+pow(abs(temp_x- i),2),0.5);
          loop=dist_to_R_matrix[i][j];
          benefits = (float)step_uc / (float)(step);//+pow(pow(abs( temp_y-j),2)+pow(abs(temp_x- i),2),0.5));  // float
          // if((dist_to_R_matrix[i][j]+step)<=bat && step_uc>=big){
          if ((dist_to_R_matrix[i][j] + step) <= bat && benefits > Benefits) {
            delete cur;
            //cur=NULL;
            cur = potential;
            // big=step_uc;
            tiny_loop=loop;
            Benefits = benefits;
            big_step = step;
          }
          else if ((dist_to_R_matrix[i][j] + step) <= bat && benefits == Benefits  && loop>tiny_loop){// && (real_dis+big_step<(step+abs( temp_y-j)+abs(temp_x- i)))) {
            delete cur;
            //cur=NULL;
            cur = potential;
            tiny_loop=loop;
            Benefits = benefits;
            big_step = step;
          }
        }
      }
    temp_x = cur->getx();
    temp_y = cur->gety();
    if (temp_x == start_x && temp_y == start_y) {
      bat = Bat;
      run_Path(cur, unclear_matrix);
      show_Path(cur,Toutfile);
          total += Count_Path(cur);
    int aaa= Count_Path(cur);
    //cout<<aaa<<endl;
    } else {
      run_Path(cur, unclear_matrix);
      show_Path(cur,Toutfile);
      //cout<<big_step<<endl;
      bat -= big_step;
      total += big_step;
    }
  }
  if (!(temp_x == start_x && temp_y == start_y)) {

    cur = find_shortest_Path(matrix, temp_x, temp_y, start_x, start_y);
    run_Path(cur, unclear_matrix);
    show_Path(cur,Toutfile);

    //Toutfile<< std::flush;
    total += Count_Path(cur);
    int aaa= Count_Path(cur);
   // cout<<aaa<<endl;
  }
  delete cur;
 //           cur=NULL;
  delete potential;
 //potential=NULL;
  //if(smallest_total!=total){
  //  cout<<"unexpected case:"<<Bat<<endl;
 //  cout<<smallest_total<<"!="<<total<<endl;
 // }
  //cout<<Bat<<endl;
 // cout<<BBat*2<<endl;
 // cout<<total<<endl;
  // for(int i=0;i<m;i++){
   // for(int j=0;j<n;j++){
  //      cout<<unclear_matrix[i][j];
    //  }
    //  cout<<endl;
   //}


        Toutfile.close();

	return 0;

}