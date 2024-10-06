#include<iostream>
#include<curses.h>
#include<ctime>
using namespace std;

string to_string1(int num){
    string result="";
    while(num>0){
        result+=(num%10)+'0';
        num/=10;
    }
    cout << result.length() << endl;
    for(int i=0,j=result.length()-1;i<=j;i++,j--){
        char temp=result[i];
        result[i]=result[j];
        result[j]=temp;
    }
    return result;
}

class Node{
    public:
        char ch;
        Node* right;
        Node* left;
        Node* up;
        Node* down;
};

class my_stack{
    Node* top;
    public:
        my_stack(){
            top=NULL;
        }
        void push(char c){
            Node* temp=new Node();
            temp->ch=c;
            temp->up=NULL;
            temp->down=NULL;
            temp->left=NULL;
            temp->right=NULL;
            temp->right=top;
            top=temp;
        }
        char gettop(){
            if(top!=NULL){
                return top->ch;
            }
            return '\0';
        }
        void pop(){
            Node* temp=top;
            top=top->right;
            delete temp;
        }
};

class Board{
    private:
        int size;
        Node* head;
        Node* current;
        my_stack S;
    public:
        Board(){
            head=NULL;
            current=head;
            size=0;
        }

        void setBoard(int s){
            srand(time(0));
            size=s;
            Node* my_board[size][size];
            for(int i=0 ; i<size; i++){
                for(int j=0 ; j<size; j++){
                    my_board[i][j]=new Node();
                    my_board[i][j]->up=NULL;
                    my_board[i][j]->down=NULL;
                    my_board[i][j]->right=NULL;
                    my_board[i][j]->left=NULL;
                    my_board[i][j]->ch='-';
                }
            }
            head = my_board[0][0];       
            for(int i=0 ; i<size; i++){
                for(int j=0 ; j<size; j++){
                    if(i>0){
                        my_board[i][j]->up=my_board[i-1][j];
                    }
                    if(j>0){
                        my_board[i][j]->left=my_board[i][j-1];
                    }
                    if(i<size-1){
                        my_board[i][j]->down=my_board[i+1][j];
                    }
                    if(j<size-1){
                        my_board[i][j]->right=my_board[i][j+1];
                    }
                }
            }
            for(int i=0 ; i<3; i++){
                my_board[rand()%size][rand()%size]->ch='B';    
                my_board[rand()%size][rand()%size]->ch='c';
            }
            int rand1, rand2;
            bool check=true;
            rand1=rand()%size;
            rand2=rand()%size;
            my_board[rand1][rand2]->ch='k';
            rand1=rand()%size;
            rand2=rand()%size;
            while(check){
                if(my_board[rand1][rand2]->ch=='-'){
                    my_board[rand1][rand2]->ch='d';
                    check=false;
                }
                else{
                    rand1=rand()%size;
                    rand2=rand()%size;
                }
            }
            rand1=rand()%size;
            rand2=rand()%size;
            check=true;
            while(check){
                if(my_board[rand1][rand2]->ch=='-'){
                    my_board[rand1][rand2]->ch='P';
                    check=false;
                }
                else{
                    rand1=rand()%size;
                    rand2=rand()%size;
                }
            }
        }

        void setCurrent(){
            Node* curr = head;
            for(int i=0 ; i<size; i++){
                curr=head;
                for(int j=0 ; j<i; j++){
                    curr=curr->down;
                }
                for(int j=0 ; j<size; j++){
                    if(curr->ch=='P'){
                        current=curr;
                        break;
                    }
                    curr = curr->right;
                }
            }
        }
        void move(char choice){
            if(choice=='w'&&current->up!=NULL){
                current->ch='-';
                current=current->up;
                S.push('u');
            }
            else if(choice=='s'&&current->down!=NULL){
                current->ch='-';
                current=current->down;
                S.push('d');
            }
            else if(choice=='a'&&current->left!=NULL){
                current->ch='-';
                current=current->left;
                S.push('l');
            }
            else if(choice=='d'&&current->right!=NULL){
                current->ch='-';
                current=current->right;
                S.push('r');
            }
            current->ch='P';
        }

        int undo(){
            char back=S.gettop();
            if(back!='\0'){
                if(back=='u'){
                    current->ch='-';
                    current=current->down;
                }
                else if(back=='d'){
                    current->ch='-';
                    current=current->up;
                }
                else if(back=='l'){
                    current->ch='-';
                    current=current->right;
                }
                else if(back=='r'){
                    current->ch='-';
                    current=current->left;
                }
                current->ch='P';
                S.pop();
                return 1;
            }
            return 0;
        }

        void calculateDistance(){
            int x1,x2,y1,y2;
            Node* curr = head;
            for(int i=0 ; i<size; i++){
                curr=head;
                for(int j=0 ; j<i; j++){
                    curr=curr->down;
                }
                for(int j=0 ; j<size; j++){
                    if(curr->ch=='P'){
                        x1=j;
                        y1=i;
                    }
                    if(curr->ch=='k'){
                        x2=j;
                        y2=i;
                    }
                    curr = curr->right;
                }
            }
            int res,res1,res2,resx,resy;
            if(x2>x1){
                resx=x2-x1;
            }
            else{
                resx=x1-x2;
            }
            if(y2>y1){
                resy=y2-y1;
            }
            else{
                resy=y1-y2;
            }
            res1=resx+resy;
            curr = head;
            for(int i=0 ; i<size; i++){
                curr=head;
                for(int j=0 ; j<i; j++){
                    curr=curr->down;
                }
                for(int j=0 ; j<size; j++){
                    if(curr->ch=='d'){
                        x1=j;
                        y1=i;
                    }
                    curr = curr->right;
                }
            }
            if(x2>x1){
                resx=x2-x1;
            }
            else{
                resx=x1-x2;
            }
            if(y2>y1){
                resy=y2-y1;
            }
            else{
                resy=y1-y2;
            }
            res2=resx+resy;
            res=res1+res2;
            string result=to_string1(res);
            char result2[result.length()+1];
            for(int i=0 ; i<result.length();i++){
                result2[i]=result[i];
            }
            result2[result.length()]='\0';
            mvprintw(11,0,result2);
        }

        void display(){
            Node* curr = head;
            for(int i=0 ; i<=size+1; i++){
                mvprintw(0,i*2,"#");
            }
            for(int i=0 ; i<size; i++){
                mvprintw(i+1,0,"#");
                curr=head;
                for(int j=0 ; j<i; j++){
                    curr=curr->down;
                }
                for(int j=0 ; j<size; j++){
/*                    if(curr->ch=='k'||curr->ch=='d'){
                        mvprintw(i+1,(j+1)*2,"-");
                    }
*/                    {
                        mvprintw(i+1,(j+1)*2,"%c",curr->ch);
                    }
                    curr = curr->right;
                }
                mvprintw(i+1,(size+1)*2,"#");
                cout << endl;
            }
            for(int i=0 ; i<=size+1; i++){
                mvprintw(size+1,i*2,"#");
            }
        }
};

int main(){
    initscr();
    curs_set(0);
    Board B1;
    B1.setBoard(9);
    char choice='m';
    int choice2=1;
    B1.calculateDistance();
    while(choice!='e')
    {
        if(choice2==1){
            B1.display();
            refresh();
            B1.setCurrent();
        }
        choice=getch();
        if(choice=='q'){
            choice2=B1.undo();
        }
        else{
            B1.move(choice);
            choice2=1;
        }
    }
    endwin();
}