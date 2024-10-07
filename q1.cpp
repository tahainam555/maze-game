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
        int undos;
        int moves;
        int score;
        bool key;
        Node* head;
        Node* current;
        my_stack S;
    public:
        Board(char mode){
            head=NULL;
            current=head;
            score=0;
            if(mode=='e'){
                size=10;
                moves=6;
                undos=6;
            }
            else if(mode=='m'){
                size=15;
                moves=2;
                undos=4;
            }
            else if(mode=='d'){
                size=20;
                moves=0;
                undos=1;
            }
        }

        void my_board(){
            Node* curr = NULL;
            Node* curr1 = NULL;
            Node* curr2 = NULL;
            Node* prev = NULL;
            for(int i=0; i<size; i++){
                curr = NULL;
                prev = curr2;
                for(int j=0; j<size; j++){
                    Node* temp = new Node();
                    temp->right=NULL;
                    temp->left=NULL;
                    temp->down=NULL;
                    temp->up=NULL;
                    temp->ch='-';
                    if(head==NULL){
                        head = temp;
                        curr1 = head;
                    }
                    if(curr==NULL){
                        curr1 = temp;
                        if(prev!=NULL){
                            prev->down=temp;
                            temp->up=prev;
                            prev=prev->right;
                        }
                    } 
                    else{
                        curr->right=temp;
                        temp->left=curr;
                        if(prev!=NULL){
                            prev->down = temp;
                            temp->up = prev;
                            prev = prev->right;
                        }
                    }
                    curr=temp;
                }
                curr2=curr1;
            }
        }

        void setBoard(){
            srand(time(0));
            my_board();
            Node* curr = head;
            for(int i=0 ; i<6; i++){
                curr=head;
                int num1=rand()%size;
                int num2=rand()%size;
                for(int j=0 ; j<num1 ; j++){
                    curr=curr->right;
                }
                for(int j=0 ; j<num2 ; j++){
                    curr=curr->down;
                }
                if(i%2==0)
                    curr->ch='B';
                else
                    curr->ch='c';
            }
    
            int rand1, rand2;
            bool check=true;
            rand1=rand()%size;
            rand2=rand()%size;
            curr=head;
            for(int j=0 ; j<rand1 ; j++){
                curr=curr->right;
            }
            for(int j=0 ; j<rand2 ; j++){
                curr=curr->down;
            }
            curr->ch='k';
            rand1=rand()%size;
            rand2=rand()%size;
            while(check){
                curr=head;
                for(int j=0 ; j<rand1 ; j++){
                    curr=curr->right;
                }
                for(int j=0 ; j<rand2 ; j++){
                    curr=curr->down;
                }
                if(curr->ch=='-'){
                    curr->ch='d';
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
                curr=head;
                for(int j=0 ; j<rand1 ; j++){
                    curr=curr->right;
                }
                for(int j=0 ; j<rand2 ; j++){
                    curr=curr->down;
                }
                if(curr->ch=='-'){
                    curr->ch='P';
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
                moves--;
            }
            else if(choice=='s'&&current->down!=NULL){
                current->ch='-';
                current=current->down;
                S.push('d');
                moves--;
            }
            else if(choice=='a'&&current->left!=NULL){
                current->ch='-';
                current=current->left;
                S.push('l');
                moves--;
            }
            else if(choice=='d'&&current->right!=NULL){
                current->ch='-';
                current=current->right;
                S.push('r');
                moves--;
            }
            if(current->ch=='c'){
                score++;
            }
            current->ch='P';
        }

        int undo(){
            char back=S.gettop();
            if(back!='\0'&&undos>0){
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
                undos--;
                return 1;
            }
            return 0;
        }

        int calculate(char ch1, char ch2){
            int x1,x2,y1,y2;
            Node* curr = head;
            for(int i=0 ; i<size; i++){
                curr=head;
                for(int j=0 ; j<i; j++){
                    curr=curr->down;
                }
                for(int j=0 ; j<size; j++){
                    if(curr->ch==ch1){
                        x1=j;
                        y1=i;
                    }
                    if(curr->ch==ch2){
                        x2=j;
                        y2=i;
                    }
                    curr = curr->right;
                }
            }
            int res,resx,resy;
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
            res=resx+resy;
            return res;
        }

        void calculateDistance(){
            int res1=calculate('P','k');
            int res2=calculate('k','d');
            int res=res1+res2;
            moves+=res;
            string result=to_string(res);
            char result2[result.length()+1];
            for(int i=0 ; i<result.length();i++){
                result2[i]=result[i];
            }
            result2[result.length()]='\0';
//            mvprintw(11,0,result2);
        }

        void display(char mode){
            if(mode=='e'){
                mvprintw(0,6,"MODE: EASY");
                mvprintw(2,0,"REMAINING MOVES: ");
                string moves1=to_string(moves);    
                mvprintw(2,17,moves1.c_str());
                mvprintw(3,0,"REMAINING UNDOS: ");
                string undos1=to_string(undos);
                mvprintw(3,17,undos1.c_str());
            }
            else if(mode=='m'){
                mvprintw(0,6,"MODE: MEDIUM");
                mvprintw(2,0,"REMAINING MOVES: ");
                string moves1=to_string(moves);
                mvprintw(2,17,moves1.c_str());
                mvprintw(3,0,"REMAINING UNDOS: ");
                string undos1=to_string(undos);
                mvprintw(3,17,undos1.c_str());
            }
            else if(mode=='d'){    
                mvprintw(0,6,"MODE: HARD");
                mvprintw(2,0,"REMAINING MOVES: ");
                string moves1=to_string(moves);
                mvprintw(2,17,moves1.c_str());
                mvprintw(3,0,"REMAINING UNDOS: ");
                string undos1=to_string(undos);
                mvprintw(3,17,undos1.c_str());
            }
            mvprintw(5,0,"SCORE: ");
            string score1=to_string(score);
            mvprintw(5,7,score1.c_str());
            mvprintw(6,0,"KEY STATUS: ");
            if(key){
                mvprintw(6,12,"FOUND");
            }
            else{
                mvprintw(6,12,"NOT FOUND");
            }
            mvprintw(8,4,"HINT: ");
            Node* curr = head;
            for(int i=0 ; i<=size+1; i++){
                mvprintw(10,i*2,"#");
            }
            for(int i=0 ; i<size; i++){
                mvprintw(i+11,0,"#");
                curr=head;
                for(int j=0 ; j<i; j++){
                    curr=curr->down;
                }
                for(int j=0 ; j<size; j++){
                    if(curr->ch=='k'||curr->ch=='d'){
                        mvprintw(i+11,(j+1)*2,"-");
                    }
                    {
                        mvprintw(i+11,(j+1)*2,"%c",curr->ch);
                    }
                    curr = curr->right;
                }
                mvprintw(i+11,(size+1)*2,"#");
            }
            for(int i=0 ; i<=size+1; i++){
                mvprintw(size+11,i*2,"#");
            }
        }
};

int main(){
    char mode;
    cout << "==============SELECT MODE==================\n";
    cout << "  For Easy press:    e\n";
    cout << " For Medium press:   m\n";
    cout << "For Difficult press: d\n";
    cin >> mode;
    initscr();
    curs_set(0);
    Board B1(mode);
    B1.setBoard();
    B1.calculateDistance();
    char choice='m';
    int choice2=1;
    while(choice!='e')
    {
        if(choice2==1){
            B1.display(mode);
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