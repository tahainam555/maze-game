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

class Node2{
    public:
        int x;
        Node2* next;
};

class coin_queue{
    Node2* head;
    Node2* tail;
    public:
        coin_queue(){
            head=NULL;
            tail=NULL;
        }
        void enqueue(int c){
            Node2* temp=new Node2();
            temp->x=c;
            temp->next=NULL;
            if(head==NULL){
                head=temp;
                tail=temp;
            }
            else{
                tail->next=temp;
                tail=temp;
            }
        }
        char gettop(){
            if(head!=NULL){
                return head->x;
            }
            return -1;
        }
        void dequeue(){
            if(head!=NULL){
                Node2* temp=head;
                head=head->next;
                delete temp;
            }
        }
};

class Node{
    public:
        char ch;
        int row, col;
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
        int hint;
        bool over;
        bool win;
        int doorx, doory;
        Node* head;
        Node* current;
        my_stack S;
        coin_queue S2;
    public:
        Board(char mode){
            head=NULL;
            current=head;
            score=0;
            hint=2;
            over=false;
            win=false;
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
                    temp->row=i;
                    temp->col=j;
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

        void setcoins(){
            srand(time(0));
            
            Node* curr = head;
            for(int i=0 ; i<size; i++){
                curr=head;
                for(int j=0 ; j<i; j++){
                    curr=curr->down;
                }
                for(int j=0 ; j<size; j++){
                    if(curr->ch=='c'){
                        curr->ch='-';
                    }
                    curr = curr->right;
                }
            }        
            curr = head;
            for(int i=0 ; i<3; i++){
                curr=head;
                int num1=rand()%size;
                int num2=rand()%size;
                for(int j=0 ; j<num1 ; j++){
                    curr=curr->right;
                }
                for(int j=0 ; j<num2 ; j++){
                    curr=curr->down;
                }
                if(curr->ch=='-')
                    curr->ch='c';
                else
                    i--;
            }
        }

        void setBoard(){
            srand(time(0));
            my_board();
            Node* curr = head;
            for(int i=0 ; i<3; i++){
                curr=head;
                int num1=rand()%size;
                int num2=rand()%size;
                for(int j=0 ; j<num1 ; j++){
                    curr=curr->right;
                }
                for(int j=0 ; j<num2 ; j++){
                    curr=curr->down;
                }
                curr->ch='B';
            }
            setcoins();
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
                    doorx=curr->row;
                    doory=curr->col;
                    cout << doorx << "  " << doory << endl;
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
            if(choice=='w'&&current->up!=NULL&&S.gettop()!='d'){
                current->ch='-';
                current=current->up;
                S.push('u');
                moves--;
            }
            else if(choice=='s'&&current->down!=NULL&&S.gettop()!='u'){
                current->ch='-';
                current=current->down;
                S.push('d');
                moves--;
            }
            else if(choice=='a'&&current->left!=NULL&&S.gettop()!='r'){
                current->ch='-';
                current=current->left;
                S.push('l');
                moves--;
            }
            else if(choice=='d'&&current->right!=NULL&&S.gettop()!='l'){
                current->ch='-';
                current=current->right;
                S.push('r');
                moves--;
            }
            if(current->ch=='c'){
                score+=2;
                undos++;
                S2.enqueue(current->row);
                S2.enqueue(current->col);
            }
            if(current->ch=='k'){
                key=true;
                Node* curr=head;
                for(int i=0 ; i<doorx; i++){
                    curr=curr->down;
                }
                for(int j=0 ; j<doory; j++){
                    curr=curr->right;
                }
                curr->ch='d';
            }
            if(current->ch=='B'){
                over=true;
            }
            if(key==true&&current->ch=='d'){
                over=true;
                win=true;
                score+=moves;
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

        void setHint(int a, int b){
            if(a>b){
                hint=1;
            }
            else if(a==b){
                hint=2;
            }
            else{
                hint=0;
            }
        }

        bool getKey(){
            return key;
        }

        void gameOver(){
            if(moves==0){
                over=true;
            }
        }

        void display(char mode){
            if(!over){
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
                if(hint==1){
                    mvprintw(8,4,"HINT: MOVING CLOSER\n");
                }
                else if(hint==2){
                    mvprintw(8,4,"HINT: \n");
                }
                else{
                    mvprintw(8,4,"HINT: MOVING AWAY\n");
                }
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
                        if(curr->ch=='k'||curr->ch=='d'||curr->ch=='B'){
                            mvprintw(i+11,(j+1)*2,"-");
                        }
                        else{
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
            else{
                mvprintw(1,10,"GAME OVER!");
                if(win==true){
                    mvprintw(3,10,"YOU WON!!!");
                }
                else{
                    mvprintw(3,10,"YOU LOST!!");
                }
                int n=5;
                while(S2.gettop()!=-1){
                    mvprintw(n,8,"COIN COLLECTED AT: ");
                    string str1=to_string(S2.gettop());
                    S2.dequeue();
                    mvprintw(n,27,str1.c_str());
                    mvprintw(n,29,",");
                    string str2=to_string(S2.gettop());
                    S2.dequeue();
                    mvprintw(n,30,str2.c_str());
                    n++;
                }
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
    int nummoves=1;
    initscr();
    noecho();
    curs_set(0);
    Board B1(mode);
    B1.setBoard();
    B1.calculateDistance();
    char choice='m';
    int choice2=1;
    while(choice!='e')
    {
        if(nummoves%6==0){
            B1.setcoins();
        }
        if(choice2==1){
            clear();
            B1.gameOver();
            B1.display(mode);
            refresh();
            B1.setCurrent();
        }
        choice=getch();
        if(choice=='q'){
            choice2=B1.undo();
        }
        else{
            int num1, num2;
            if(!B1.getKey()){
                num1=B1.calculate('P','k');
            }
            else{
                num1=B1.calculate('P','d');
            }
            B1.move(choice);
            nummoves++;
            if(!B1.getKey()){
                num2=B1.calculate('P','k');
            }
            else{
                num2=B1.calculate('P','d');
            }
            B1.setHint(num1,num2);
            choice2=1;
        }
    }
    endwin();
}