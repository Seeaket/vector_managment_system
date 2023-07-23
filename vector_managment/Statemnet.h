#pragma once
#include<vector>
#include<string >

#define Max 100

struct Text
{
	std::string name;
	std::string id;
	std::string wages;
};

void Savefile(std::vector<Text>& vec, Text& vectors);
void Loadfile(std::vector<Text>& vec, Text& vectors);

typedef int (*Func)(std::vector<Text>& vec, Text& vectors);
typedef int (*F)(std::vector<Text>vec, int j, int i);

void Menu();
void Exits(std::vector<Text>& vec, Text& vectors);
void Addperson(std::vector<Text>& vec, Text& vectors);//使用引用进行传参，提高传参效率
void Deletely(std::vector<Text>& vec, Text& vectors);
void Modify(std::vector<Text>& vec, Text& vectors);
void View(std::vector<Text>& vec, Text& vectors);
void Sortly(std::vector<Text>& vec, Text& vectors);

int Sortnames(std::vector<Text> vec, int j, int i);
int Sortids(std::vector<Text> vec, int j, int i);
int Sortwages(std::vector<Text> vec, int j, int i);

void Addmessage(std::vector<Text>vec, Text& vectors);
std::string Blank(int num);
int Judge();
void Dealy(int num);

