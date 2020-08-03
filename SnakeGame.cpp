#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

class SnakeGame{
private:
    bool gameOver;
    const int width = 20;
    const int height = 20;
    int x, y, fruitX, fruitY, score;
    int tailX[100], tailY[100];
    int nTail;
    enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
    eDirecton dir;
public:
    void Setup()
    {
        gameOver = false;
        dir = STOP;
        x = width / 2;
        y = height / 2;
        srand(time(NULL));
        fruitX = rand() % width;
        fruitY = rand() % height;
        score = 0;
    }
    friend void Draw(SnakeGame Player); //friend Function
    void Logic()
    {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;
        for (int i = 1; i < nTail; i++)
        {
            prev2X = tailX[i];
            prev2Y = tailY[i];
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
        //if (x > width || x < 0 || y > height || y < 0)
        //  gameOver = true;
        if (x >= width) x = 0; else if (x < 0) x = width - 1;
        if (y >= height) y = 0; else if (y < 0) y = height - 1;

        for (int i = 0; i < nTail; i++)
            if (tailX[i] == x && tailY[i] == y)
               {
                 gameOver = true;
               }


        if (x == fruitX && y == fruitY)
        {
            score += 10;
            srand(time(NULL));
            fruitX = rand() % width;
            fruitY = rand() % height;
            nTail++;
        }
    }
    void Input()
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            }
        }
    }
    bool getGameOver(){
        return gameOver;
    }
    void End()
    {
        system("color 1C");
        system("cls");
        std::cout<<"--------------------------You Scored-----------------------"<<endl;
        std::cout<<"Score = "<<score<<endl<<endl<<endl;
    }
    void Start()
    {
        system("cls");
        system("color BC");
        std::cout<<"Press \nW for Up \nA for left \nS for down and \nD for Right"<<endl;
    }

};

void Draw(SnakeGame Player)
{
    system("cls");
    system("color BC");
    for (int i = 0; i < Player.width+2; i++)
        std::cout << "#";
    std::cout << endl;

    for (int i = 0; i < Player.height; i++)
    {
        for (int j = 0; j < Player.width; j++)
        {
            if (j == 0)
                std::cout << "#";
            if (i == Player.y && j == Player.x)
                std::cout << "O";
            else if (i == Player.fruitY && j == Player.fruitX)
                std::cout << "$";
            else
            {
                bool print = false;
                for (int k = 0; k <= Player.nTail+1; k++)
                {
                    if (Player.tailX[k] == j && Player.tailY[k] == i)
                    {
                        std::cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    std::cout << " ";
            }
            if (j == Player.width - 1)
                std::cout << "#";
        }
        std::cout << endl;
    }

    for (int i = 0; i < Player.width+2; i++)
        std::cout << "#";
    std::cout << endl;
    std::cout << "Score:" << Player.score << endl;
}
int main()
{
    SnakeGame Player;
    Player.Start();
    system("pause");
    Player.Setup();
    while (!Player.getGameOver())
    {
        Draw(Player);
        Player.Input();
        Player.Logic();
        Sleep(30);
    }
    Player.End();
    return 0;
}
