//# Snake and Ladder Game using Linked List + OOP in C++

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>
using namespace std;

// NODE CLASS
/*
meaning of the variables:
position → current square number
next     → next square in board
jump     → snake or ladder destination
*/

class Node{
public:
    int position;                      
    Node* next, *jump;

    Node(int pos){
        position = pos;
        next = NULL;
        jump = NULL;
    }
};

//BOARD CLASS

/*
The board automatically:

Creates squares from 1 to 100
Adds snakes and ladders
*/
class Board{
private:
    Node* head;
public:
    Board(){
        createBoard();
        addSnakesAndLadders();
    }


//CREATING THE LINKED LIST BOARD
/*
What happens here?
At first:
head -> [1]
Then loop creates:
head -> [1] -> [2] -> [3] -> [4] -> ... -> [100]
*/
    void createBoard(){
    head = new Node(1);
        Node* temp = head;
    
        for(int i=2; i<=100; i++){
            temp -> next = new  Node(i);
            temp = temp -> next;
        }
    
    }

//FINDING ANY NODE
/*
Suppose we call:
getNode(27)
The linked list is traversed until square 27 is found.
*/

    Node* getNode(int pos){
        Node* temp = head;
    
        while(temp != NULL){
            if(temp -> position == pos){
                return temp;
            }
            temp = temp->next;
        }
    
        return NULL;
    }

//Adding SNAKES and LADDERS
/*
Example:
addJump(4, 25);   // ladder
addJump(27, 5);   // snake

Diagram:
Ladder:[4] -----> [25]
Snake:[27] -----> [5]

*/
//s = startNode
//e = endNode
    void addJump(int start, int end){
        Node* s = getNode(start);
        Node* e = getNode(end);
        
        if(s != NULL){
            s->jump = e;
        }
    }

    void addSnakesAndLadders(){
        // Ladders
        addJump(4, 25);
        addJump(13, 46);
        addJump(33, 49);
        addJump(42, 63);
        addJump(50, 69);
        

        // Snakes
        addJump(27, 5);
        addJump(40, 3);
        addJump(54, 31);
        addJump(66, 45);
        addJump(99, 41);

    }


    Node* getStart(){
        return head;
    }

    ~Board() {
        Node* temp = head;

        while(temp != NULL){
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }



};


//PLAYER CLASS
/*
Each player stores:
-Name
-Current position node
*/

class Player{
private:
    string name;
    Node* current;
public:
    Player(string n, Node* start){
        name = n;
        current = start;
    }

    string getName(){
        return name;
    }

    int getPosition(){
        return current->position;
    }

    bool hasWon(){
        return current->position == 100;
    }

    void move(int dice){
        if(current->position + dice > 100){
            cout<<"Need exact number to reach 100\n";
            return;
        }

        for(int i = 0; i < dice; i++){
            current = current->next;
        }

        cout<< name <<" moved to " << current->position<< endl;

        if(current->jump != NULL){
            if(current->jump->position > current->position){
                cout << "Ladder! Climbing up... \n";
            }
            else{
                cout<<"Snake! Sliding down... \n";
            }
            current = current->jump;
            cout << name << " is now at " << current->position << endl;

        }
        
    }

};

class Game{
private:
    Board board;
    Player p1;
    Player p2;

public:
    Game() : p1("Player 1", board.getStart()), p2("Player 2", board.getStart()){}

    int rollDice(){
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout <<"Rolling...";

        for(int i = 0; i < 3; i++){
            cout<< ".";
        }

        cout<< endl;
        
        int dice = rand() % 6 + 1;
        cout << "Dice = " << dice << endl;
        return dice;
    }

    void playTurn(Player& p){
        cout << "\n----------------------------------------------------\n";
        cout << p.getName() << "'s Turn" << endl;
        cout << "Current Position: " << p.getPosition() << endl;
        cout << "Press ENTER to roll the dice...";
        
        int dice = rollDice();
        p.move(dice);
        cout << "Final Position: " << p.getPosition() << endl;
    }

    void start(){
        while(true){
            playTurn(p1);

            if(p1.hasWon()){
                cout << "\nPlayer 1 Wins the Game!\n";
                break;
            }

            playTurn(p2);

            if(p2.hasWon()){
                cout << "\nPlayer 2 Wins the Game!\n";
                break;
            }
        }
    }
};

int main(){
    srand(time(0));

    Game g;
    g.start();

    return 0;
}







/*  The Whole PEDAGOGY
main()
  ↓
Game object created
  ↓
Board object creates linked list
  ↓
Snakes and ladders added
  ↓
Player 1 and Player 2 start at square 1
  ↓
Loop starts
  ↓
Player presses ENTER
  ↓
Dice generated
  ↓
Player moves through linked list
  ↓
Snake/Ladder checked
  ↓
Turn changes
  ↓
Repeat until someone reaches 100
*/