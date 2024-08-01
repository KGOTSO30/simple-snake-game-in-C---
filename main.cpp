#include <iostream>
#include <stdlib.h>
#include<conio.h>
#include <windows.h>

using namespace std;

// global variables and grid variables
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[110],  tailY[110];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = (width / 2);
    y = (height /2);
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    system("cls");

                // TOP BORDER
    for (int i = 0; i < width+2; i++)  {
        cout << "*";
    }  
    cout << endl;

                    // BODY OF THE BOARD
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
               cout << "*";
            }
                        //Snake Head
            if(i == y && j == x)
                cout << "O";

                        //The Fruit or target
             else if (i == fruitY && j == fruitX)
                    cout << "F";

                else
                 {      // printing the tail

                    bool print = false;
                    for(int k=0;k<nTail; k++){
                       

                        if(tailX[k] == j && tailY[k] == i){
                            cout<< "o";
                            print = true;
                        }

                       
                    }

                     if(print == false)

                        cout << " ";
                }
                    


            if (j == width -1)    
            {
                cout << "*";
            }
                
        }
         cout << endl;
        
    }
    

                // BOTTOM BORDER

     for (int i = 0; i < width+2; i++)  {
        cout << "*";
    }   
    cout << endl;

                //Showing the Score
  cout << "Score:" << score <<endl;
}

void Input()
{
   // gameOver = true;
   if(_kbhit()){
    switch (_getch())
    {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'w':
            dir = UP;
            break;
        case 'x':
            gameOver = true;
            break;
    }
   }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X, prev2Y;

    //need to make the tail follow the head
     tailX[0] = x;
     tailY[0] = y;


    //rearranging the coordinates givem the size --- There's a better way to say this....

    for(int i=1; i<nTail; i++){
        prev2X= tailX[i];
        prev2Y= tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
  
    case LEFT:
       x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
       y++;
        break;
    
    default:
        break;
    }
    //
    //  If you go out of bounds

   // if (x > width || x <0 || y> height || y<0) {gameOver = true;}   --- // Death Option
    if(x >= width) {x = 0;} else if (x < 0) {x = width -1;}
    if(y >= height) {y = 0;} else if (y < 0) {y = height -1;}
    

    
    //if you bite yourself --

    for(int i=0; i < nTail; i++){
        if(tailX[i] == x && tailY[i] == y){
            gameOver = true;
        }
    }
    //if you eat the fruit 'F' Should increase in size(tail) or score

    if( x == fruitX && y ==fruitY){
        score = score +10;
         fruitX = rand() % width;
        fruitY = rand() % height;
        nTail = nTail +1;
    }
    
}
int main()
{
    Setup();
    while (!gameOver)
    {
       Draw();
       Input();
       Logic();
       Sleep(20);
       
    }
    

    return 0;
}


///
// The last coordinates of the head 'O' will be the new coordinates of the tail 'o'
// Should look like 'Oooo' as it grows