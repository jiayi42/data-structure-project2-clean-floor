#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

using namespace std;
int m,n,limit;
int start_x,start_y;
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
        ~Node(){
          delete parent;
        }
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
	int len=0;
    Node* p=path;
	while(p!=NULL){
        len++;
        p=p->getp();
	}
		//return;
     delete p;p=NULL;
	//int len = count_Path(path->getp()) + 1;
	return len;
}
int Count_Path(Node* path)
{
	if (path==NULL)
		return -1;
	int len = count_Path(path->getp());
	return len;
}
/*void Show_Path(Node* path)
{
	if (path==NULL)
		return;
	Show_Path(path->getp());
	if(path->getp()!=NULL){
        cout << "(" << path->getx() << ", " << path->gety() << ") ";

	}


}*/
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

void reverse_show_Path(Node* path, ofstream& f)
{
    Node* p=path;
	while(p!=NULL){
        f<< p->getx() << " " << p->gety()<<endl;
        p=p->getp();
	}
		//return;
     delete p;p=NULL;

	//if(path->getp()!=NULL){
        //cout << "(" << path->getx() << ", " << path->gety() << ") ";
	//reverse_show_Path(path->getp(),f);
   // }


}

void Reverse_show_Path(Node* path, ofstream& f)
{
	//if (path==NULL)
	//	return;

    //f<< path->getx() << " " << path->gety()<<endl;
	//if(path->getp()!=NULL){
        //cout << "(" << path->getx() << ", " << path->gety() << ") ";
	reverse_show_Path(path->getp(),f);
   // }


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

		//int n = matrix[i][j];

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

void spanning_tree_bfs_1000000_terminate(int** matrix,Node*** cur_to_R_matrix,int x,int y)
{
	// create a queue and enqueue first node

	Queue<Node*> q;
    Node* src;
	src=new Node(x,y);
	q.push(src);

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
        cur_to_R_matrix[i][j]=curr;
		//int n = matrix[i][j];

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


    myfile>>mmm>>nnn>>_limit;
    m=mmm;
    n=nnn;
    limit=_limit;
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


    int bat=0;
    int Bat=0;
    int BBat=0;
    int temp_x;
    int temp_y;
    int total = 0;
    Node* cur;
    Node* potential;

    int** unclear_matrix = new int*[m];//double pointer record pointer(for each row)
    for(int j = 0; j < m; ++j)
        unclear_matrix[j] = new int[n];//allocate elements space of each row
//cout<<"mom"<< space_go<<endl;

if(space_go<1000){
    int**  dist_to_R_matrix = new int*[m];//double pointer record pointer(for each row)
    for(int i = 0; i < m; ++i)
        dist_to_R_matrix[i] = new int[n];//allocate elements space of each row
    for(int i = 0; i < m; ++i)
      for(int j = 0; j < n; ++j)
          dist_to_R_matrix[i][j] =0;
   Node***  cur_to_R_matrix = new Node**[m];//double pointer record pointer(for each row)
    for(int i = 0; i < m; ++i)
        cur_to_R_matrix[i] = new Node*[n];//allocate elements space of each row

    for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
        if(matrix[i][j]!=1){
                cur_to_R_matrix[i][j] =find_shortest_Path(matrix,i,j,start_x,start_y);
               // temp_cur=find_shortest_Path(matrix,start_x,start_y,i,j);
                dist_to_R_matrix[i][j]=Count_Path(cur_to_R_matrix[i][j]);
                if(dist_to_R_matrix[i][j]>BBat)
                    BBat=dist_to_R_matrix[i][j];
            }
        else{
            dist_to_R_matrix[i][j]=-1;
        }
      }
     }

  Bat=BBat;

  Bat*=2;

  int Battery_self=Bat;
  int smallest_total = 2147483647;//INT_MAX do not mutiply and add
  int factor=1;


 while( Bat<= limit && Bat<=smallest_total){
    bat=Bat;
    total = 0;
    temp_x=start_x;
    temp_y=start_y;
   for(int i=0;i<m;i++)
      for(int j=0;j<n;j++)
        unclear_matrix[i][j]=matrix[i][j];
  //////////////////////////////
  int step, step_uc, big_step;
  float benefits = 0;
  int potential_steps=0;
  while (!Isclear(unclear_matrix, m, n)) {
    int big = 0;
    big_step = 0;
    float Benefits = 0;
    cur = find_shortest_Path(matrix, temp_x, temp_y, start_x, start_y);
    int loop=0;
    int tiny_loop=0;
    for (int i = 0; i <m; i++)
      for (int j = 0; j < n; j++) {
        if (unclear_matrix[i][j] == 0) {
          potential = find_shortest_Path(matrix, temp_x, temp_y, i, j);
          step = Count_Path(potential);
          step_uc = N_unclear_Path(potential, unclear_matrix);
          loop=dist_to_R_matrix[i][j];
          benefits = (float)step_uc / (float)(step);
          if ((dist_to_R_matrix[i][j] + step) <= bat && benefits > Benefits) {
            //delete cur;
            cur = potential;
            tiny_loop=loop;
            Benefits = benefits;
            big_step = step;
          }
          else if ((dist_to_R_matrix[i][j] + step) <= bat && benefits == Benefits  && loop>tiny_loop){
            //delete cur;
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
      total +=Count_Path(cur);
    } else {
      run_Path(cur, unclear_matrix);
      bat -= big_step;
      total += big_step;
    }
  }
  if (!(temp_x == start_x && temp_y == start_y)) {
    cur = find_shortest_Path(matrix, temp_x, temp_y, start_x, start_y);
    run_Path(cur, unclear_matrix);
    total += Count_Path(cur);
  }


    if(total<smallest_total){
            Battery_self=Bat;
    smallest_total=total;

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
    if(space_go>400){
            if(factor>2)
            Bat+=(space_go/10-20);
            if(factor>(14-space_go/100))
                break;
    }



    //cout<<Bat<<endl;
    //delete cur;
    //delete potential;

}
///////////////////
ofstream Toutfile ("final.path");
Toutfile<< smallest_total<<endl;

Bat=Battery_self;
bat=Bat;
total = 0;
    temp_x=start_x;
    temp_y=start_y;
   for(int i=0;i<m;i++)
      for(int j=0;j<n;j++)
        unclear_matrix[i][j]=matrix[i][j];
////////////////////////////////////////////////////
  Toutfile<<start_x<<" "<<start_y<<endl;
  int step, step_uc, big_step;
  float benefits = 0;
  int potential_steps=0;
  while (!Isclear(unclear_matrix, m, n)) {
    int big = 0;
    big_step = 0;
    float Benefits = 0;
    cur = find_shortest_Path(matrix, temp_x, temp_y, start_x, start_y);
    int loop=0;
    int tiny_loop=0;
    for (int i = 0; i <m; i++)
      for (int j = 0; j < n; j++) {
        if (unclear_matrix[i][j] == 0) {
          potential = find_shortest_Path(matrix, temp_x, temp_y, i, j);
          step = Count_Path(potential);
          step_uc = N_unclear_Path(potential, unclear_matrix);
          loop=dist_to_R_matrix[i][j];
          benefits = (float)step_uc / (float)(step);
          if ((dist_to_R_matrix[i][j] + step) <= bat && benefits > Benefits) {
            //delete cur;
            cur = potential;
            tiny_loop=loop;
            Benefits = benefits;
            big_step = step;
          }
          else if ((dist_to_R_matrix[i][j] + step) <= bat && benefits == Benefits  && loop>tiny_loop){
            //delete cur;
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
    } else {
      run_Path(cur, unclear_matrix);
      show_Path(cur,Toutfile);
      bat -= big_step;
      total += big_step;
    }
  }

  if (!(temp_x == start_x && temp_y == start_y)) {
    cur = find_shortest_Path(matrix, temp_x, temp_y, start_x, start_y);
    run_Path(cur, unclear_matrix);
    show_Path(cur,Toutfile);
    total += Count_Path(cur);
    int aaa= Count_Path(cur);
  }

  //delete cur;
  //delete potential;
  Toutfile.close();
}
else if(space_go>=1000 && space_go<30000){

    int**  dist_to_R_matrix = new int*[m];//double pointer record pointer(for each row)
    for(int i = 0; i < m; ++i)
        dist_to_R_matrix[i] = new int[n];//allocate elements space of each row
    for(int i = 0; i < m; ++i)
      for(int j = 0; j < n; ++j)
          dist_to_R_matrix[i][j] =0;
   Node***  cur_to_R_matrix = new Node**[m];//double pointer record pointer(for each row)
    for(int i = 0; i < m; ++i)
        cur_to_R_matrix[i] = new Node*[n];//allocate elements space of each row
    spanning_tree_bfs_1000000_terminate(matrix, cur_to_R_matrix,start_x,start_y);

    for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
        if(matrix[i][j]!=1){
                dist_to_R_matrix[i][j]=Count_Path(cur_to_R_matrix[i][j]);
                if(dist_to_R_matrix[i][j]>BBat)
                    BBat=dist_to_R_matrix[i][j];

            }
        else{
            dist_to_R_matrix[i][j]=-1;
        }
      }
     }
  //Show_Path(cur_to_R_matrix[45][45]);
  ofstream Toutfile ("temp_final.path");
 //cout<< "momw"<<BBat*2<<endl;

  Bat=limit;
  bat=Bat;
  total = 0;
  temp_x=start_x;
  temp_y=start_y;
  for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
      unclear_matrix[i][j]=matrix[i][j];
////////////////////////////////////////////////////
//cout<<start_x<<" "<<start_y<<endl;
  Toutfile<<start_x<<" "<<start_y<<endl;
  int step, step_uc, big_step;
  float benefits = 0;
  int potential_steps=0;
  int ii=start_x;
  int jj=start_y;

  while (!Isclear(unclear_matrix, m, n)) {

       bat=Bat;
      int loop=0;
      int big = 0;
      for (int i = 0; i <m; i++)
        for (int j = 0; j < n; j++) {
          if (unclear_matrix[i][j] == 0) {
            if(dist_to_R_matrix[i][j]>loop && matrix[i][j]==0){
                  loop=dist_to_R_matrix[i][j];
                  ii=i;
                  jj=j;
            }
          }
        }
      big= Count_Path(cur_to_R_matrix[ii][jj]);
      int x = ii;
      int y = jj;
      run_Path(cur_to_R_matrix[ii][jj], unclear_matrix);
      show_Path(cur_to_R_matrix[ii][jj],Toutfile);
      bat -= big;
      total += big;
      bool sig=true;

      while(bat>(dist_to_R_matrix[ii][jj]+1) && sig){
        sig=false;
        int longest=0;
        int row[] = { -1, 0, 0, 1 };
        int col[] = { 0, -1, 1, 0 };
        int iii=ii;int jjj=jj;
        for (int k = 0; k < 4; k++){
            int ix = iii + row[k] ;
            int jy = jjj + col[k] ;
            if(unclear_matrix[ix][jy]==0  && isValid(ix,jy) && dist_to_R_matrix[ix][jy]>=longest){
              longest=dist_to_R_matrix[ix][jy];
              ii=ix;
              jj=jy;
              sig=true;
            }
        }
        if(sig){
            unclear_matrix[ii][jj]=2;
            Toutfile<< ii << " " <<jj<<endl;
            bat -= 1;
            total += 1;
        }
      }

      big= Count_Path(cur_to_R_matrix[ii][jj]);
      run_Path(cur_to_R_matrix[ii][jj], unclear_matrix);
      Reverse_show_Path(cur_to_R_matrix[ii][jj],Toutfile);
      bat -= big;
      total += big;
      //cout<<""<<endl;







  }
  //cout<<total;

  //delete cur;
  //delete potential;
  Toutfile.close();
    ofstream outputFile("final.path");
    ifstream inputFile("temp_final.path");


    outputFile << total<<endl;


    outputFile << inputFile.rdbuf();

    inputFile.close();
    outputFile.close();

   std::remove("temp_final.path");

}
else if(space_go>=30000){

    int**  dist_to_R_matrix = new int*[m];//double pointer record pointer(for each row)
    for(int i = 0; i < m; ++i)
        dist_to_R_matrix[i] = new int[n];//allocate elements space of each row
    for(int i = 0; i < m; ++i)
      for(int j = 0; j < n; ++j)
          dist_to_R_matrix[i][j] =0;
   Node***  cur_to_R_matrix = new Node**[m];//double pointer record pointer(for each row)
    for(int i = 0; i < m; ++i)
        cur_to_R_matrix[i] = new Node*[n];//allocate elements space of each row
  //cout<< "momw"<<endl;
    spanning_tree_bfs_1000000_terminate(matrix, cur_to_R_matrix,start_x,start_y);

  ofstream Toutfile ("temp_final.path");
  //cout<< "ssmomw"<<endl;

  Bat=limit;
  bat=Bat;
  total = 0;
  temp_x=start_x;
  temp_y=start_y;
  for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
      unclear_matrix[i][j]=matrix[i][j];
////////////////////////////////////////////////////
//cout<<start_x<<" "<<start_y<<endl;
  Toutfile<<start_x<<" "<<start_y<<endl;
  int step, step_uc, big_step;
  float benefits = 0;
  int potential_steps=0;
  int ii=start_x;
  int jj=start_y;

//cout<<"ds"<<endl;
  while (!Isclear(unclear_matrix, m, n)) {

       bat=Bat;
      int loop=0;
      int big = 0;
      bool gg= false;
      if(start_x>m/2 && start_y>n/2)
      for (int i = 0; i <m; i++){
        for (int j = 0; j < n; j++) {
          if (unclear_matrix[i][j] == 0) {
                  ii=i;
                  jj=j;
                  gg=true;
                  break;
          }
        }
        if(gg)break;
      }

      if(start_x<=m/2 && start_y<=n/2)
      for (int i = m-1; i >=0; i--){
        for (int j = n-1; j >=0; j--) {
          if (unclear_matrix[i][j] == 0) {
                  ii=i;
                  jj=j;
                  gg=true;
                  break;
          }
        }
        if(gg)break;
      }

      if(start_x>m/2 && start_y<=n/2)
      for (int i = 0; i <m; i++){
        for (int j = n-1; j >=0; j--) {
          if (unclear_matrix[i][j] == 0) {
                  ii=i;
                  jj=j;
                  gg=true;
                  break;
          }
        }
        if(gg)break;
      }

      if(start_x<=m/2 && start_y>n/2)
      for (int i = m-1; i>=0; i--){
        for (int j = 0; j < n; j++) {
          if (unclear_matrix[i][j] == 0) {
                  ii=i;
                  jj=j;
                  gg=true;
                  break;
          }
        }
        if(gg)break;
      }


      big= Count_Path(cur_to_R_matrix[ii][jj]);
      int x = ii;
      int y = jj;
      run_Path(cur_to_R_matrix[ii][jj], unclear_matrix);
      show_Path(cur_to_R_matrix[ii][jj],Toutfile);
      bat -= big;
      total += big;
      bool sig=true;
      while(bat>(Bat/2+1) && sig){//(Bat/2+2)
            sig=false;
        int row[] = { -1, 0, 0, 1 };
        int col[] = { 0, -1, 1, 0 };
        for (int k = 0; k < 4; k++){
            int ix = ii + row[k] ;
            int jy = jj + col[k] ;
            if(unclear_matrix[ix][jy]==0 && isValid(ix,jy)){
             unclear_matrix[ix][jy]=2;
            Toutfile<< ix << " " <<jy<<endl;
              bat -= 1;
              total += 1;
              ii=ix;
              jj=jy;

              sig=true;
              break;
            }
        }
      }

      big= Count_Path(cur_to_R_matrix[ii][jj]);
      run_Path(cur_to_R_matrix[ii][jj], unclear_matrix);
      Reverse_show_Path(cur_to_R_matrix[ii][jj],Toutfile);
      bat -= big;
      total += big;

    //cout<<""<<endl;
  }
  //cout<<total;

  //delete cur;
  //delete potential;
  Toutfile.close();
    ofstream outputFile("final.path");
    ifstream inputFile("temp_final.path");


    outputFile << total<<endl;


    outputFile << inputFile.rdbuf();

    inputFile.close();
    outputFile.close();

   std::remove("temp_final.path");

}
return 0;


}
