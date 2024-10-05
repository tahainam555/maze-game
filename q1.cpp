#include<iostream>
#include<curses.h>
#include<ctime>
using namespace std;

class Node{
    public:
        char ch;
        Node* right;
        Node* left;
        Node* up;
        Node* down;
};

class Board{
    private:
        int size;
        Node* head;
        Node* current;
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
            }
            rand1=rand()%size;
            rand2=rand()%size;
            check=true;
            while(check){
                if(my_board[rand1][rand2]->ch=='-'){
                    my_board[rand1][rand2]->ch='P';
                    check=false;
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

        void display(){
            Node* curr = head;
            for(int i=0 ; i<=size+1; i++){
                cout << "# ";
            }
            cout << endl;
            for(int i=0 ; i<size; i++){
                cout<<"# ";
                curr=head;
                for(int j=0 ; j<i; j++){
                    curr=curr->down;
                }
                for(int j=0 ; j<size; j++){
                    if(curr->ch=='k'||curr->ch=='d'){
                        cout << "- ";
                    }
                    else{
                        cout << curr->ch << " ";
                    }
                    curr = curr->right;
                }
                cout << "# ";
                cout << endl;
            }
            for(int i=0 ; i<=size+1; i++){
                cout << "# ";
            }
            cout << endl;
        }

};

int main(){
    Board B1;
    B1.setBoard(9);
    B1.display();
    
}