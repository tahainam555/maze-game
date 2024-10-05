#include<iostream>
#include<curses.h>
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
    public:
        Board(){
            head=NULL;
            size=0;
        }

        void setBoard(int s){
            size=s;
            char chh='a';
            Node* my_board[size][size];
            for(int i=0 ; i<size; i++){
                for(int j=0 ; j<size; j++){
                    my_board[i][j]=new Node();
                    my_board[i][j]->up=NULL;
                    my_board[i][j]->down=NULL;
                    my_board[i][j]->right=NULL;
                    my_board[i][j]->left=NULL;
                    my_board[i][j]->ch=chh++;
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
        
        }

        void display(){
            Node* curr = head;
            for(int i=0 ; i<size; i++){
                curr=head;
                for(int j=0 ; j<i; j++){
                    curr=curr->down;
                }
                for(int j=0 ; j<size; j++){
                    cout << curr->ch;
                    curr = curr->right;
                }
                cout << endl;
            }
        }

};

int main(){
    Board B1;
    B1.setBoard(3);
    B1.display();
    
}