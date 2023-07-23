#include <iostream>
#include<vector>
#include"Statement.h"
#include<crtdbg.h>
using namespace std;

int main()
{
	Text vectors;
	vector<Text>vector_t;
	Loadfile(vector_t, vectors);
	Func funcs[] = { (Func)Exits,(Func)Addperson,(Func)Deletely, (Func)Modify, (Func)View, (Func)Sortly };
	while (1)
	{
		system("cls");
		Menu();
		char c;
		cin >> c;
		int num = atoi(&c);
		if (num >= 0 && num <= 5)
			funcs[num](vector_t, vectors);
		else
		{
			std::cout << std::endl << Blank(6) << "   ÎÞÐ§²Ù×÷£¡" << std::endl;
		}
		std::cout << std::endl << Blank(6) << "  ";
		system("pause");
	}

	return 0;
}