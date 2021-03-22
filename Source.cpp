#include<vector>
#include<iostream>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
#include<cmath>
constexpr auto MAXI =25;
using namespace std;
struct snake
{
	int x, y;
	snake(int m_x, int  m_y) : x(m_x), y(m_y) {};

};
struct locate
{
	int x, y;
};
int control()
{
	int press;
	 press =_getch();
	switch (press)
	{
	case 119:return 2;
	case 115: return 4;
	case 97:return 1;
	case 100: return 3;
	}
	return 0;
}
float distancesa(int x1, int y1, locate food)
{
	int x2 = food.x;
	int y2 = food.y;
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
void checkkey(int &key)
{
	int temp = control();
	if (temp != 0)
	{
		if (temp%2 != key%2)
		key = temp;
	}

}
int aichekkey(vector<snake> qsnake, int** a,locate food)
{
	int temp;
	float tempk;
	int check[4] = { 0,0,0,0 };
	int sum = 0;
	tempk = distancesa(qsnake[0].x, qsnake[0].y, food);
	for (temp = 1; temp <= 4; temp++)
	{
		switch (temp)
		{
		case 1:
			if (qsnake[0].x - 1 >= 0)
			{
				if (a[qsnake[0].y][qsnake[0].x - 1] != 2)
				{
					check[0]++; 
					if (distancesa(qsnake[0].x - 1, qsnake[0].y, food) < tempk)return 1;

				}
			}break;
		case 2:

			if (qsnake[0].y - 1 >= 0)
			{
				if (a[qsnake[0].y - 1][qsnake[0].x] != 2)
				{
					check[1]++;
					if (distancesa(qsnake[0].x, qsnake[0].y - 1, food) < tempk)return 2;
				}
			}break;
		case 3:
			if (qsnake[0].x + 1 < MAXI)
			{
				if (a[qsnake[0].y][qsnake[0].x + 1] != 2)
				{
					check[2]++;
					if (distancesa(qsnake[0].x + 1, qsnake[0].y, food) < tempk)return 3;

				}
			}
			break;
		case 4:

			if (qsnake[0].y + 1 < MAXI)
			{
				if (a[qsnake[0].y + 1][qsnake[0].x] != 2)
				{
					check[3]++;
					if (distancesa(qsnake[0].x, qsnake[0].y + 1, food) < tempk)
						return 4;
				}
			}break;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (check[i]==0) sum++;
	}
	if (sum == 4) return 1;
	do
	{
		temp = rand() % 4 + 1;
		if (check[temp-1]) return temp;
	} while (1);

}
void reset(int**& a)
{
	for (int i = 0; i < MAXI; i++)
	{
		memset(a[i], 0, MAXI * sizeof(int));
	}
}
void createfood(int**& a, int& f_x, int& f_y)
{
	int x;
	int y;
	do {
		x = rand() % (MAXI - 1) + 0;
		y = rand() % (MAXI - 1) + 0;
		if (a[y][x] == 0)
		{
			a[y][x] = 1;
			break;
		}
	} while (1);
	f_x = x;
	f_y = y;
}
void lengthsnake(vector<snake>qsnake, int& len,int**&a)
{
	for (int i = 0; i < len; i++)
	{
		int x_s = qsnake[i].x;
		int y_s = qsnake[i].y;
		a[y_s][x_s] = 1;
	}
}
void swap(snake* a, snake* b)
{
	snake* c = a;
	a = b;
	b = c;
}
void insert(vector<snake>& qsnake, int len)
{
	snake temp = qsnake[len - 1];
	for (int i = len-1 ; i > 0; i--)
	{
		qsnake[i] = qsnake[i-1];
	}
	qsnake[0] = temp;
	
}
bool snakemove(int& len, int**& a, vector<snake>& qsnake,int mode, locate &food)
{
	int x = qsnake[0].x;
	int y = qsnake[0].y;
	switch (mode)
	{
	case 1: x = x - 1; if (x >= MAXI || x < 0) return false; break;
	case 2: y = y - 1; if (y >= MAXI || y < 0) return false; break;
	case 3: x = x + 1; if (x >= MAXI || x < 0) return false; break;
	case 4: y = y + 1; if (y >= MAXI || y < 0) return false; break;
	}
	if (a[y][x] == 2)return false;
	if (a[y][x] == 1)
	{
		len++;
		qsnake.emplace_back(x, y);
		insert(qsnake, len);
		a[y][x] = 0;
		createfood(a, food.x, food.y);
	}
	else
	{
		len++;
		qsnake.emplace_back(x, y);
		insert(qsnake, len);
		len--;
		qsnake.pop_back();
	}
	return true;

}
void banchoi(int** a, vector<snake> qsnake, int len,locate &food,int key)
{
	reset(a);
	a[food.y][food.x] = 1;
	for (int i = 0; i < len; i++)
	{
		int x = qsnake[i].x;
		int y = qsnake[i].y;
		if (i == 0) a[y][x] = 3;
		else
		{
			a[y][x] = 2;
		}
	}	
	for (int j = 0; j < MAXI +2; j++)
	{
		if (j == 0 || j == MAXI + 1)
		{
			for (int i = 0; i < MAXI + 2; i++)
			{
				cout << "-";
			}
			cout << endl;
		}
		else
		{
			cout << "|";
			for (int i = 0; i < MAXI ; i++)
			{
				if (a[j-1][i]==0)	cout << " ";
				else
				{
					if (a[j - 1][i] == 1) {
						cout << "*";
					}
					else
					{
						if (a[j - 1][i] == 3)
						{
							switch (key)
							{
							case 1: cout << "<"; break;
							case 2: cout << "^"; break;
							case 3: cout << ">"; break;
							case 4: cout << "v"; break;
							}
						}
						else cout << "$";
					}
				}
			}
			if (j!=2)cout << "|" << endl;
			else
			{
				cout << "|";
				cout << "         Current length : " << qsnake.size() << endl;
			}
		}
	}
	
}
void create(int**& a)
{
	a = new int* [MAXI];
	for (int i = 0; i < MAXI; i++)
	{
		a[i] = new int[MAXI];
	}
}
void play(int playmode)
{
	int** a;
	int length = 1;
	int key = 1;
	create(a);
	reset(a);
	vector<snake> qsnake;
	int in_x, in_y;
	locate food;
	in_x = rand() % (MAXI-9)+9;
	in_y = rand() % (MAXI-9)+9;
	qsnake.emplace_back(in_x, in_y);
	createfood(a,food.x,food.y);
	banchoi(a,qsnake,length,food,key);
	while (1)
	{
		system("cls");
		if (!snakemove(length, a, qsnake, key,food))break;
		banchoi(a, qsnake, length,food,key);

		if (playmode == 1) {
			if (_kbhit()) checkkey(key);
				
		}
		else
		{
			key = aichekkey(qsnake, a,food);
		}
		switch (key)
		{
		case 1: cout << "A" << endl; break;
		case 2: cout << "W" << endl; break;
		case 3: cout << "D" << endl; break;
		case 4: cout << "S" << endl; break;
		}
		cout << "..........................." << endl;
		Sleep(50);
	}
	for (int i = 0; i < MAXI; i++)
	{
		delete[]a[i];
	}
	delete[]a;
	qsnake.clear();
}
int menu()
{
	cout << "1. Choi moi " << endl;
	cout << "2. May choi " << endl;
	cout << "0. Thoat " << endl;
	return 0;
}
int nhaplenh(int lenh)
{
	int pressa;
	do
	{
		pressa = _getch();
		pressa -= 48;
		if (pressa >= 0 && pressa <= 2) return pressa;
	} while (1);
}
int xuly(int lenh)
{
	switch (lenh)
	{
		case 1: 
		do{
			int key;
			play(1); 
			cout << " You lose " << endl;
			cout << " press R to play again" << endl;
			cout << " press E to Exit " << endl;
			do
			{
				key = _getch();
			} while (key != 101 && key != 114);
			if (key == 101)
			{
				break;
			}
		} while (1);
		return lenh;
		break;
		case 2:
			do {
				int key;
				play(2);
				cout << " You lose " << endl;
				cout << " press R to play again" << endl;
				cout << " press E to Exit " << endl;
				do
				{
					key = _getch();
				} while (key != 101 && key != 114);
				if (key == 101)
				{
					break;
				}
			} while (1);
			return lenh;
			break;
		case 0: return lenh; break;
	}
	return lenh;
}
int main()
{
	int lenh = 1;
	do
	{
		system("cls");
		lenh = xuly(nhaplenh(menu()));
	} while (lenh != 0);
	return 0;
}