#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;

//MULTIPLAYER-BOUNDARY DIES!!!!!!
const int width = 80;
const int height = 20;
int xPlayer1, yPlayer1;
int xPlayer2, yPlayer2;
int fruitCordX, fruitCordY;
int player1Score, player2Score;
int snakeTailXPlayer1[100], snakeTailYPlayer1[100];
int snakeTailXPlayer2[100], snakeTailYPlayer2[100];
int snakeTailLenPlayer1, snakeTailLenPlayer2;
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
snakesDirection sDirPlayer1, sDirPlayer2;
bool isGameOver;

void GameInit()
{
    isGameOver = false;
    sDirPlayer1 = STOP;
    sDirPlayer2 = STOP;
    xPlayer1 = width / 4;
    yPlayer1 = height / 2;
    xPlayer2 = 3 * width / 4;
    yPlayer2 = height / 2;
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    player1Score = 0;
    player2Score = 0;
    snakeTailLenPlayer1 = 0;
    snakeTailLenPlayer2 = 0;
}
void GameRender(string playerName1, string playerName2) {
    system("cls");

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            if (j == 0 || j == width)
                cout << "|";
            else if (i == yPlayer1 && j == xPlayer1)
                cout << "O";
            else if (i == yPlayer2 && j == xPlayer2)
                cout << "X";
            else if (i == fruitCordY && j == fruitCordX)
                cout << "#";
            else {
                bool prTail = false;
                for (int k = 0; k < snakeTailLenPlayer1; k++) {
                    if (snakeTailXPlayer1[k] == j && snakeTailYPlayer1[k] == i) {
                        cout << "o";
                        prTail = true;
                    }
                }
                for (int k = 0; k < snakeTailLenPlayer2; k++) {
                    if (snakeTailXPlayer2[k] == j && snakeTailYPlayer2[k] == i) {
                        cout << "x";
                        prTail = true;
                    }
                }
                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    cout << playerName1 << "'s Score: " << player1Score << endl;
    cout << playerName2 << "'s Score: " << player2Score << endl;
}
void UpdateGame()
{
    int prevXPlayer1 = snakeTailXPlayer1[0];
    int prevYPlayer1 = snakeTailYPlayer1[0];
    int prevXPlayer2 = snakeTailXPlayer2[0];
    int prevYPlayer2 = snakeTailYPlayer2[0];
    int prev2X, prev2Y;

    snakeTailXPlayer1[0] = xPlayer1;
    snakeTailYPlayer1[0] = yPlayer1;
    snakeTailXPlayer2[0] = xPlayer2;
    snakeTailYPlayer2[0] = yPlayer2;

    for (int i = 1; i < snakeTailLenPlayer1 || i < snakeTailLenPlayer2; i++) {
        if (i < snakeTailLenPlayer1) {
            prev2X = snakeTailXPlayer1[i];
            prev2Y = snakeTailYPlayer1[i];
            snakeTailXPlayer1[i] = prevXPlayer1;
            snakeTailYPlayer1[i] = prevYPlayer1;
            prevXPlayer1 = prev2X;
            prevYPlayer1 = prev2Y;
        }

        if (i < snakeTailLenPlayer2) {
            prev2X = snakeTailXPlayer2[i];
            prev2Y = snakeTailYPlayer2[i];
            snakeTailXPlayer2[i] = prevXPlayer2;
            snakeTailYPlayer2[i] = prevYPlayer2;
            prevXPlayer2 = prev2X;
            prevYPlayer2 = prev2Y;
        }
    }

    switch (sDirPlayer1) {
    case LEFT:
        xPlayer1--;
        break;
    case RIGHT:
        xPlayer1++;
        break;
    case UP:
        yPlayer1--;
        break;
    case DOWN:
        yPlayer1++;
        break;
    }

    switch (sDirPlayer2) {
    case LEFT:
        xPlayer2--;
        break;
    case RIGHT:
        xPlayer2++;
        break;
    case UP:
        yPlayer2--;
        break;
    case DOWN:
        yPlayer2++;
        break;
    }

    if (xPlayer1 >= width || xPlayer1 < 0 || yPlayer1 >= height || yPlayer1 < 0)
        isGameOver = true;

    if (xPlayer2 >= width || xPlayer2 < 0 || yPlayer2 >= height || yPlayer2 < 0)
        isGameOver = true;

    for (int i = 0; i < snakeTailLenPlayer1; i++) {
        if (snakeTailXPlayer1[i] == xPlayer1 && snakeTailYPlayer1[i] == yPlayer1)
            isGameOver = true;
    }

    for (int i = 0; i < snakeTailLenPlayer2; i++) {
        if (snakeTailXPlayer2[i] == xPlayer2 && snakeTailYPlayer2[i] == yPlayer2)
            isGameOver = true;
    }

    if (xPlayer1 == fruitCordX && yPlayer1 == fruitCordY) {
        player1Score += 10;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        snakeTailLenPlayer1++;
    }

    if (xPlayer2 == fruitCordX && yPlayer2 == fruitCordY) {
        player2Score += 10;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        snakeTailLenPlayer2++;
    }
}
void UserInput()
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            sDirPlayer1 = LEFT;
            break;
        case 'd':
            sDirPlayer1 = RIGHT;
            break;
        case 'w':
            sDirPlayer1 = UP;
            break;
        case 's':
            sDirPlayer1 = DOWN;
            break;
        case 'j':
            sDirPlayer2 = LEFT;
            break;
        case 'l':
            sDirPlayer2 = RIGHT;
            break;
        case 'i':
            sDirPlayer2 = UP;
            break;
        case 'k':
            sDirPlayer2 = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}
void GameOverScreen1(string playerName1, string playerName2)
{
    system("cls");
    cout << "Game Over!" << endl;
    cout << playerName1 << "'s Score: " << player1Score << endl;
    cout << playerName2 << "'s Score: " << player2Score << endl;
    cout << "Thanks for playing!" << endl;
}
int main1() 
{
    string playerName1, playerName2;
    cout << "Enter Player 1's name: ";
    cin >> playerName1;
    cout << "Enter Player 2's name: ";
    cin >> playerName2;

    GameInit();
    while (!isGameOver) {
        GameRender(playerName1, playerName2);
        UserInput();
        UpdateGame();
        Sleep(100);
    }
    GameOverScreen1(playerName1, playerName2);

    return 0;
}  



//SINGLEPLAYER-BOUNDARY DIES!!!!!!
int x, y;
int playerScore;
int snakeTailX[100], snakeTailY[100];
int snakeTailLen;
snakesDirection sDir;

void Init1()
{
    isGameOver = false;
    sDir = STOP;
    x = width / 2;
    y = height / 2;
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    playerScore = 0;
}
void Render(string playerName)
{
    system("cls");  

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            if (j == 0 || j == width)
                cout << "|";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitCordY && j == fruitCordX)
                cout << "#";
            else {
                bool prTail = false;
                for (int k = 0; k < snakeTailLen; k++) 
                {
                    if (snakeTailX[k] == j
                        && snakeTailY[k] == i)
                    {
                        cout << "o";
                        prTail = true;
                    }
                }
                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    cout << playerName << "'s Score: " << playerScore
        << endl;
}
void Update()
{
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;

    for (int i = 1; i < snakeTailLen; i++) 
    {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (sDir)
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
    }

    if (x >= width || x < 0 || y >= height || y < 0)
        isGameOver = true;

    for (int i = 0; i < snakeTailLen; i++) 
    {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            isGameOver = true;
    }

    if (x == fruitCordX && y == fruitCordY)
    {
        playerScore += 10;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        snakeTailLen++;
    }
}
int SetDifficulty1()
{
    int dfc, choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard "
        "\nNOTE: if not chosen or pressed any other "
        "key, the difficulty will be automatically set "
        "to medium\nChoose difficulty level: ";
    cin >> choice;
    switch (choice) {
    case '1':
        dfc = 50;
        break;
    case '2':
        dfc = 100;
        break;
    case '3':
        dfc = 150;
        break;
    default:
        dfc = 100;
    }
    return dfc;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch()) 
        {
        case 'a':
            sDir = LEFT;
            break;
        case 'd':
            sDir = RIGHT;
            break;
        case 'w':
            sDir = UP;
            break;
        case 's':
            sDir = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}
void GameOverScreen2(string playerName1) 
{
    system("cls");
    cout << "Game Over!" << endl;
    cout << playerName1 << "'s Score: " << player1Score << endl;
    cout << "Thanks for playing!" << endl;
}
int main2()
{
    string playerName;
    cout << "enter your name: ";
    cin >> playerName;
    int dfc = SetDifficulty1();

    GameInit();
    while (!isGameOver)
    {
        Render(playerName);
        Input();
        Update();
        Sleep(100);
    }
    GameOverScreen2(playerName);
    return 0;
}

//SINGLEPLAYER-DUNIYAGOLHAI!!!!
void Init3() 
{
    isGameOver = false;
    sDir = STOP;
    x = width / 2;
    y = height / 2;
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    playerScore = 0;
}
void GameRender3(string playerName)
{
    system("cls");

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            if (j == 0 || j == width)
                cout << "|";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitCordY && j == fruitCordX)
                cout << "#";
            else {
                bool prTail = false;
                for (int k = 0; k < snakeTailLen; k++)
                {
                    if (snakeTailX[k] == j && snakeTailY[k] == i)
                    {
                        cout << "o";
                        prTail = true;
                    }
                }
                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    cout << playerName << "'s Score: " << playerScore << endl;
}
void UpdateGame3()
{
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;

    for (int i = 1; i < snakeTailLen; i++)
    {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (sDir) 
    {
    case LEFT:
        x--;
        if (x < 0) x = width - 1; 
        break;
    case RIGHT:
        x++;
        if (x >= width) x = 0; 
        break;
    case UP:
        y--;
        if (y < 0) y = height - 1; 
        break;
    case DOWN:
        y++;
        if (y >= height) y = 0; 
        break;
    }

    if (x == fruitCordX && y == fruitCordY)
    {
        playerScore += 10;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        snakeTailLen++;
    }
}
void SetDifficulty3() 
{
    int dfc, choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard\nChoose difficulty level: ";
    cin >> choice;
    switch (choice) {
    case 1:
        dfc = 50;
        break;
    case 2:
        dfc = 100;
        break;
    case 3:
        dfc = 150;
        break;
    default:
        dfc = 100;
    }
    Sleep(dfc);
}
void UserInput3()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            sDir = LEFT;
            break;
        case 'd':
            sDir = RIGHT;
            break;
        case 'w':
            sDir = UP;
            break;
        case 's':
            sDir = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}
void GameOverScreen3(string playerName1)
{
    system("cls");
    cout << "Game Over!" << endl;
    cout << playerName1 << "'s Score: " << player1Score << endl;
    cout << "Thanks for playing!" << endl;
}
int main3()
{
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    SetDifficulty3();
    Init3();

    while (!isGameOver)
    {
        GameRender3(playerName);
        UserInput3();
        UpdateGame3();
        Sleep(100);
    }
    GameOverScreen3(playerName);
    return 0;
}

//MULTIPLAYER-DUNIYAGOLHAI!!!!
void GameInit4()
{
    isGameOver = false;
    sDirPlayer1 = STOP;
    sDirPlayer2 = STOP;
    xPlayer1 = width / 4;
    yPlayer1 = height / 2;
    xPlayer2 = 3 * width / 4;
    yPlayer2 = height / 2;
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    player1Score = 0;
    player2Score = 0;
    snakeTailLenPlayer1 = 0;
    snakeTailLenPlayer2 = 0;
}
void GameRender4(string playerName1, string playerName2) {
    system("cls");

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            if (j == 0 || j == width)
                cout << "|";
            else if (i == yPlayer1 && j == xPlayer1)
                cout << "O";
            else if (i == yPlayer2 && j == xPlayer2)
                cout << "X";
            else if (i == fruitCordY && j == fruitCordX)
                cout << "#";
            else {
                bool prTail = false;
                for (int k = 0; k < snakeTailLenPlayer1; k++) {
                    if (snakeTailXPlayer1[k] == j && snakeTailYPlayer1[k] == i) {
                        cout << "o";
                        prTail = true;
                    }
                }
                for (int k = 0; k < snakeTailLenPlayer2; k++) {
                    if (snakeTailXPlayer2[k] == j && snakeTailYPlayer2[k] == i) {
                        cout << "x";
                        prTail = true;
                    }
                }
                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    cout << playerName1 << "'s Score: " << player1Score << endl;
    cout << playerName2 << "'s Score: " << player2Score << endl;
}
void UpdateGame4()
{
    int prevXPlayer1 = snakeTailXPlayer1[0];
    int prevYPlayer1 = snakeTailYPlayer1[0];
    int prevXPlayer2 = snakeTailXPlayer2[0];
    int prevYPlayer2 = snakeTailYPlayer2[0];
    int prev2X, prev2Y;

    snakeTailXPlayer1[0] = xPlayer1;
    snakeTailYPlayer1[0] = yPlayer1;
    snakeTailXPlayer2[0] = xPlayer2;
    snakeTailYPlayer2[0] = yPlayer2;

    for (int i = 1; i < snakeTailLenPlayer1 || i < snakeTailLenPlayer2; i++) {
        if (i < snakeTailLenPlayer1) {
            prev2X = snakeTailXPlayer1[i];
            prev2Y = snakeTailYPlayer1[i];
            snakeTailXPlayer1[i] = prevXPlayer1;
            snakeTailYPlayer1[i] = prevYPlayer1;
            prevXPlayer1 = prev2X;
            prevYPlayer1 = prev2Y;
        }

        if (i < snakeTailLenPlayer2) {
            prev2X = snakeTailXPlayer2[i];
            prev2Y = snakeTailYPlayer2[i];
            snakeTailXPlayer2[i] = prevXPlayer2;
            snakeTailYPlayer2[i] = prevYPlayer2;
            prevXPlayer2 = prev2X;
            prevYPlayer2 = prev2Y;
        }
    }

    switch (sDirPlayer1) {
    case LEFT:
        xPlayer1--;
        break;
    case RIGHT:
        xPlayer1++;
        break;
    case UP:
        yPlayer1--;
        break;
    case DOWN:
        yPlayer1++;
        break;
    }

    switch (sDirPlayer2) {
    case LEFT:
        xPlayer2--;
        break;
    case RIGHT:
        xPlayer2++;
        break;
    case UP:
        yPlayer2--;
        break;
    case DOWN:
        yPlayer2++;
        break;
    }

    // Wrap around the boundaries for player 1
    if (xPlayer1 >= width)
        xPlayer1 = 0;
    else if (xPlayer1 < 0)
        xPlayer1 = width - 1;

    if (yPlayer1 >= height)
        yPlayer1 = 0;
    else if (yPlayer1 < 0)
        yPlayer1 = height - 1;

    // Wrap around the boundaries for player 2
    if (xPlayer2 >= width)
        xPlayer2 = 0;
    else if (xPlayer2 < 0)
        xPlayer2 = width - 1;

    if (yPlayer2 >= height)
        yPlayer2 = 0;
    else if (yPlayer2 < 0)
        yPlayer2 = height - 1;

    // Check collision with self for player 1
    for (int i = 0; i < snakeTailLenPlayer1; i++) {
        if (snakeTailXPlayer1[i] == xPlayer1 && snakeTailYPlayer1[i] == yPlayer1)
            isGameOver = true;
    }

    // Check collision with self for player 2
    for (int i = 0; i < snakeTailLenPlayer2; i++) {
        if (snakeTailXPlayer2[i] == xPlayer2 && snakeTailYPlayer2[i] == yPlayer2)
            isGameOver = true;
    }

    // Update scores and fruit position if eaten by player 1
    if (xPlayer1 == fruitCordX && yPlayer1 == fruitCordY) {
        player1Score += 10;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        snakeTailLenPlayer1++;
    }

    // Update scores and fruit position if eaten by player 2
    if (xPlayer2 == fruitCordX && yPlayer2 == fruitCordY) {
        player2Score += 10;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        snakeTailLenPlayer2++;
    }
}
void UserInput4()
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            sDirPlayer1 = LEFT;
            break;
        case 'd':
            sDirPlayer1 = RIGHT;
            break;
        case 'w':
            sDirPlayer1 = UP;
            break;
        case 's':
            sDirPlayer1 = DOWN;
            break;
        case 'j':
            sDirPlayer2 = LEFT;
            break;
        case 'l':
            sDirPlayer2 = RIGHT;
            break;
        case 'i':
            sDirPlayer2 = UP;
            break;
        case 'k':
            sDirPlayer2 = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}
void GameOverScreen4(string playerName1, string playerName2)
{
    system("cls");
    cout << "Game Over!" << endl;
    cout << playerName1 << "'s Score: " << player1Score << endl;
    cout << playerName2 << "'s Score: " << player2Score << endl;
    cout << "Thanks for playing!" << endl;
}
int main4()
{
    string playerName1, playerName2;
    cout << "Enter Player 1's name: ";
    cin >> playerName1;
    cout << "Enter Player 2's name: ";
    cin >> playerName2;

    GameInit4();
    while (!isGameOver) {
        GameRender4(playerName1, playerName2);
        UserInput4();
        UpdateGame4();
        Sleep(100);
    }
    GameOverScreen4(playerName1, playerName2);
    return 0;
}


//TIME BASED MULTIPLAYER
void GameInit5() 
{
    isGameOver = false;
    sDirPlayer1 = STOP;
    sDirPlayer2 = STOP;
    xPlayer1 = width / 4;
    yPlayer1 = height / 2;
    xPlayer2 = 3 * width / 4;
    yPlayer2 = height / 2;
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    player1Score = 0;
    player2Score = 0;
    snakeTailLenPlayer1 = 0;
    snakeTailLenPlayer2 = 0;
}
void GameRender5(string playerName1, string playerName2, int startTime, int duration)
{
    system("cls");

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            if (j == 0 || j == width)
                cout << "|";
            else if (i == yPlayer1 && j == xPlayer1)
                cout << "O";
            else if (i == yPlayer2 && j == xPlayer2)
                cout << "X";
            else if (i == fruitCordY && j == fruitCordX)
                cout << "#";
            else {
                bool prTail = false;
                for (int k = 0; k < snakeTailLenPlayer1; k++) {
                    if (snakeTailXPlayer1[k] == j && snakeTailYPlayer1[k] == i) {
                        cout << "o";
                        prTail = true;
                    }
                }
                for (int k = 0; k < snakeTailLenPlayer2; k++) {
                    if (snakeTailXPlayer2[k] == j && snakeTailYPlayer2[k] == i) {
                        cout << "x";
                        prTail = true;
                    }
                }
                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    cout << "Remaining Time: " << (duration - (GetTickCount() - startTime)) / 1000 << " seconds" << endl;
    cout << playerName1 << "'s Score: " << player1Score << endl;
    cout << playerName2 << "'s Score: " << player2Score << endl;

    cout << playerName1 << "'s Score: " << player1Score << endl;
    cout << playerName2 << "'s Score: " << player2Score << endl;

}
void UpdateGame5(int startTime, int duration)
{
    int prevXPlayer1 = snakeTailXPlayer1[0];
    int prevYPlayer1 = snakeTailYPlayer1[0];
    int prevXPlayer2 = snakeTailXPlayer2[0];
    int prevYPlayer2 = snakeTailYPlayer2[0];
    int prev2X, prev2Y;

    snakeTailXPlayer1[0] = xPlayer1;
    snakeTailYPlayer1[0] = yPlayer1;
    snakeTailXPlayer2[0] = xPlayer2;
    snakeTailYPlayer2[0] = yPlayer2;

    for (int i = 1; i < snakeTailLenPlayer1 || i < snakeTailLenPlayer2; i++) {
        if (i < snakeTailLenPlayer1) {
            prev2X = snakeTailXPlayer1[i];
            prev2Y = snakeTailYPlayer1[i];
            snakeTailXPlayer1[i] = prevXPlayer1;
            snakeTailYPlayer1[i] = prevYPlayer1;
            prevXPlayer1 = prev2X;
            prevYPlayer1 = prev2Y;
        }

        if (i < snakeTailLenPlayer2) {
            prev2X = snakeTailXPlayer2[i];
            prev2Y = snakeTailYPlayer2[i];
            snakeTailXPlayer2[i] = prevXPlayer2;
            snakeTailYPlayer2[i] = prevYPlayer2;
            prevXPlayer2 = prev2X;
            prevYPlayer2 = prev2Y;
        }
    }

    switch (sDirPlayer1) {
    case LEFT:
        xPlayer1--;
        break;
    case RIGHT:
        xPlayer1++;
        break;
    case UP:
        yPlayer1--;
        break;
    case DOWN:
        yPlayer1++;
        break;
    }

    switch (sDirPlayer2) {
    case LEFT:
        xPlayer2--;
        break;
    case RIGHT:
        xPlayer2++;
        break;
    case UP:
        yPlayer2--;
        break;
    case DOWN:
        yPlayer2++;
        break;
    }

    if (xPlayer1 >= width || xPlayer1 < 0 || yPlayer1 >= height || yPlayer1 < 0)
        isGameOver = true;

    if (xPlayer2 >= width || xPlayer2 < 0 || yPlayer2 >= height || yPlayer2 < 0)
        isGameOver = true;

    for (int i = 0; i < snakeTailLenPlayer1; i++) {
        if (snakeTailXPlayer1[i] == xPlayer1 && snakeTailYPlayer1[i] == yPlayer1)
            isGameOver = true;
    }

    for (int i = 0; i < snakeTailLenPlayer2; i++) {
        if (snakeTailXPlayer2[i] == xPlayer2 && snakeTailYPlayer2[i] == yPlayer2)
            isGameOver = true;
    }

    if (xPlayer1 == fruitCordX && yPlayer1 == fruitCordY) {
        player1Score += 10;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        snakeTailLenPlayer1++;
    }

    if (xPlayer2 == fruitCordX && yPlayer2 == fruitCordY) {
        player2Score += 10;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        snakeTailLenPlayer2++;
    }
}
void UserInput5()
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            sDirPlayer1 = LEFT;
            break;
        case 'd':
            sDirPlayer1 = RIGHT;
            break;
        case 'w':
            sDirPlayer1 = UP;
            break;
        case 's':
            sDirPlayer1 = DOWN;
            break;
        case 'j':
            sDirPlayer2 = LEFT;
            break;
        case 'l':
            sDirPlayer2 = RIGHT;
            break;
        case 'i':
            sDirPlayer2 = UP;
            break;
        case 'k':
            sDirPlayer2 = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}
bool IsTimeUp(int startTime, int duration) {
    int currentTime = GetTickCount();
    return (currentTime - startTime >= duration);
}
void GameOverScreen(string playerName1, string playerName2) {
    system("cls");
    cout << "Game Over!" << endl;
    cout << playerName1 << "'s Score: " << player1Score << endl;
    cout << playerName2 << "'s Score: " << player2Score << endl;
    cout << "Thanks for playing!" << endl;
}
int main5() 
{
    string playerName1, playerName2;
    cout << "Enter Player 1's name: ";
    cin >> playerName1;
    cout << "Enter Player 2's name: ";
    cin >> playerName2;

    GameInit5();

    int durationInSeconds = 60; 
    int startTime = GetTickCount();

    while (!isGameOver && !IsTimeUp(startTime, durationInSeconds * 1000)) {
        GameRender5(playerName1, playerName2, startTime, durationInSeconds * 1000);
        UserInput5();
        UpdateGame5(startTime, durationInSeconds * 1000);
        Sleep(100);
    }

    GameOverScreen(playerName1, playerName2);

    return 0;
}

void menu()
{
    cout << "1. MULTIPLAYER-BOUNDARY DIES " << endl;
    cout << "2. SINGLEPLAYER-BOUNDARY DIES" << endl;
    cout << "3. SINGLEPLAYER-DUNIYAGOLHAI" << endl;
    cout << "4. MULTIPLAYER-DUNIYAGOLHAI" << endl;
    cout << "5. TIME BASED MULTIPLAYER" << endl;
    cout << "0. Exit" << endl;

}
int main()
{
    int choice;
    while (true)
    {
        cout << "__________________________\n" << endl;
        menu();
        cout << "__________________________\n" << endl;
        cout << "Enter Choice:";
        cin >> choice;

        switch (choice)
        {
        case 0:
            return 0;
            break;
        case 1:
            main1();

            break;
        case 2:
            main2();
            break;
        case 3:
            main3();
            break;
        case 4:
            main4();
            break;
        case 5:
            main5();
            break;
        default:
            break;
        }
    }
    return 0;
}