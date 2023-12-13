/*****************************************
* Русакова Екатерина Алексеевна, ПИ-231  *
* Дата: 13.12.2023                       *
* Тема: Змейка                           *
******************************************/
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int Ox, Oy, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection {
  STOP = 0,
  LEFT,
  RIGHT,
  UP,
  DOWN
};
eDirection dir;

void Setup() {
  gameOver = false;
  dir = STOP;
  Ox = width / 2 - 1;
  Oy = height / 2 - 1;
  fruitX = rand() % width;
  fruitY = rand() % height;
  score = 0;
}

void Draw() {
  system("cls");

  for (int index = 0; index < width + 1; ++index) {
    cout << '#';
  }
    cout << endl;

  for (int index = 0; index < height; ++index) {
    for (int ind = 0; ind < width; ++ind) {
      if (ind == 0 || ind == width - 1) {
        cout << '#';
      }
      if (index == Oy && ind == Ox) {
        cout << '0';
      }
      else if (index == fruitY && ind == fruitX) {
        cout << "F";
      } else {
        bool print = false;
        for (int kol = 0; kol < nTail; ++kol) {
          if (tailX[kol] == ind && tailY[kol] == index) {
            print = true;
            cout << 'o';
          }
        }
        if (print == false) {
          cout << " ";
        }
                
      }
            
    }
    cout << endl;
  }

  for (int index = 0; index < width + 1; ++index) {
    cout << '#';
  }
  cout << endl;
  cout << "Score: " << score << endl;
}

void Intup() {
  if (_kbhit()) {
    switch (_getch()) {
      case 'a' :
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

void Logic() {
  int prevX = tailX[0];
  int prevY = tailY[0];
  int prev2X, prev2Y;
  tailX[0] = Ox;
  tailY[0] = Oy;
  for (int index = 1; index < nTail; ++index) {
    prev2X = tailX[index];
    prev2Y = tailY[index];
    tailX[index] = prevX;
    tailY[index] = prevY;
    prevX = prev2X;
    prevY = prev2Y;

  }
  switch (dir) {
    case LEFT:
      --Ox;
      break;
    case RIGHT:
      ++Ox;
      break;
    case UP:
      --Oy;
      break;
    case DOWN:
      ++Oy;
      break;
  }

  if (Ox >= width - 1) {
    Ox = 0;
  } else if (Ox < 0) {
    Ox = width - 2;
  }

  if (Oy >= height - 1) {
    Oy = 0;
  } else if (Oy < 0) {
    Oy = height - 2;
  }
  for (int index = 0; index < nTail; ++index) {
    if (tailX[index] == Ox && tailY[index] == Oy) {
      gameOver = true;
    }
  }

  if (Ox == fruitX && Oy == fruitY) {
    score += 10;
    fruitX = rand() % width;
    fruitY = rand() % height;
    nTail++;
  }
}

int main() {
  Setup();
  while (!gameOver) {
    Draw();
    Intup();
    Logic();
    Sleep(200);
  }
  return 0;
}
