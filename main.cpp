#include <iostream>
#include <utility>
#include <ctime>

using namespace std;

typedef pair<int, char>  myPair;
const int SIZE = 40; 

class Human{
public:
    virtual bool move() = 0;
};

class Player: public Human{
public:
    bool move() override{
        char answer;
        //do{
            cout << "Вы будете брать карту? y/n\n";
            cin >> answer;
        //}while (answer != 'y' || answer == 'n');

        return (answer == 'y') ? true : false;
    }
};

class Diller: public Human{
public:
    bool move() override{
        return true;
    }   
};

class Casino{
private:

    int getResult(){
        if (scoreplayer > 21){
            cout << "\nУ вас перебор, победил диллер!\n";
            return 0;
        }
        if (scorebot > 21){  
            cout << "\nУ диллера перебор, вы победили!\n";
            return 0;
        }

        (scoreplayer > scorebot) ? cout << "\nВы победили!\n" : cout << "\nДиллер выиграл.\n";
        return 0;
     
    }
    void printName(){
        int i = 3;
        table[2][i++] = 'B';
        table[2][i++] = 'L';
        table[2][i++] = 'A';
        table[2][i++] = 'C';
        table[2][i++] = 'K';
        table[2][i++] = ' ';
        table[2][i++] = 'J';
        table[2][i++] = 'A';
        table[2][i++] = 'C';
        table[2][i++] = 'K';

    }

    void printScore(char symbol, char whose){
        int counter = 0;

        switch(symbol)
        {

            case '2':
                counter += 2;
                break;
            case '3':
                counter += 3;
                break;
            case '4':
                counter += 4;
                break;
            case '5':
                counter += 5;
                break;
            case '6':
                counter += 6;
                break;
            case '7':
                counter += 7;
                break;
            case '8':
                counter += 8;
                break;
            case '9':
                counter += 9;
                break;
            case 'T':
                counter += 10;
                break;
            case 'J':
                counter += 10;
                break;
            case 'Q':
                counter += 10;
                break;
            case 'K':
                counter += 10;
                break;
            case 'A':
                if ((whose == 'p' && scoreplayer >= 11) || (whose == 'b' && scorebot >= 11))
                    counter += 1;
                else counter += 11;
                break;
            default:
                cout << "What????";
                break;
        }

        (whose == 'p') ? scoreplayer += counter : scorebot += counter;
    }
    
    char random(){
        int a = rand() % 13 + 2;
        
        switch(a)
        {

            case 2:
                return '2';
                break;
            case 3:
                return '3';
                break;
            case 4:
                return '4';
                break;
            case 5:
                return '5';
                break;
            case 6:
                return '6';
                break;
            case 7:
                return '7';
                break;
            case 8:
                return '8';
                break;
            case 9:
                return '9';
                break;
            case 10:
                return 'T';
                break;
            case 11:
                return 'J';
                break;
            case 12:
                return 'Q';
                break;
            case 13:
                return 'K';
                break;
            case 14:
                return 'A';
                break;
            default:
                cout << "What????";
                break;
        }

    }
    void genTable(){
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE*2; j++){
                if (i == 0 || i == SIZE - 1 || j == 0 || j == SIZE*2 - 1)
                    table[i][j] = '=';
                else table[i][j] = ' ';
            }
        }
        printName();
        printCardB();
        printCloseCard();
        printCardP();
        printCardP();
        cout << endl << "Your score: " << scoreplayer << "\nScore Diller: " << scorebot << endl;


    }
    void printTable(){
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE*2; j++){
                cout << table[i][j] << ' ';
            }
            cout << endl;
        }
       
        

    }
    char genSuitB(int point){
        char symbol = random();
        table[9][point + 1] = symbol;
        table[14][point + 3] = symbol;
        return symbol;
    }

    char genSuitP(int point){
        char symbol = random();
        table[26][point + 1] = symbol;
        table[31][point + 3] = symbol;
        return symbol;
    }   

    char table[SIZE][SIZE*2];

    int scoreplayer = 0;
    int scorebot = 0;  
    Human* player[];

public:

      

    Casino(){
        player[0] = new Player();
        player[1] =  new Diller();

        genTable();

        
        while(player[0]->move()){
            printCardP();
            if (scoreplayer > 21)
                break;
            cout << endl << "Your score: " << scoreplayer << "\nScore Diller: " << scorebot << endl;
        }
        while (scoreplayer > scorebot && scoreplayer <= 21){
            printCardB();
        }

        cout << endl << "Your score: " << scoreplayer << "\nScore Diller: " << scorebot << endl;
        getResult();
    }

    void printCardP(){
        int point = 8;
        do{
        point += 6;
        }while(table[25][point] != ' ');
        
        for (int i = 25; i < 33; i++){
            for (int j = point; j < point + 5; j++){
                if (j == point || j == point + 4 || i == 25 || i == 32)
                    table[i][j] = '#';
                else table[i][j] = ' ';
            }
        }
        printScore(genSuitP(point), 'p');
        system("clear");
        printTable();
    }

    void printCardB(){
        int point = 69;
        while (table[8][point] != ' ' ){
        if (table[9][point + 1] == '#')
            break;
        point -= 6;
        }

        for (int i = 8; i < 16; i++){
            for (int j = point; j < point + 5; j++){
                if (j == point || j == point + 4 || i == 8 || i == 15)
                    table[i][j] = '#';
                else table[i][j] = ' ';
            }
        }
        printScore(genSuitB(point), 'b');
        system("clear");
        printTable();
    }

    void printCloseCard(){
        int point = 69;
        do{
            point -= 6;
        }while(table[8][point] != ' ');

        for (int i = 8; i < 16; i++){
            for (int j = point; j < point + 5; j++){
                table[i][j] = '#';
            }
        }
        system("clear");
        printTable();
    }
};

int main(){
    srand(time(NULL));
    Casino test;
}
