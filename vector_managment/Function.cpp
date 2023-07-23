//#ifdef _DEBUG
//#ifndef DBG_NEW
//#define DBG_NEW new(_NORMAL_BLOCK,_FILE_,_FINE_)
//#define new DBG_NEW
//#endif
//#endif// _DEBUG
#include "Statemnet.h"
#include<iostream>
#include<iomanip>
#include<chrono>//包含程序延迟函数，将当前线程置于睡眠状态，并暂停线程执行，当间隔时间过去线程将唤醒继续执行后续代码
#include<thread>
#include<fstream>
#include<crtdbg.h>

void Loadfile(std::vector<Text>& vec, Text& vectors)
{
	std::ifstream openfile("Vector_Message.csh");
	if (openfile.is_open())
	{
		while (openfile >> vectors.name >> vectors.id >> vectors.wages)
		{
			vec.push_back(vectors);
		}
	}
	openfile.close();
}

void Savefile(std::vector<Text>& vec, Text& vectors)
{
	std::ofstream openfile("Vector_Message.csh");
	if (openfile.is_open())
	{
		for (auto& message : vec)
		{
			openfile << message.name << std::endl << message.id << std::endl << message.wages << std::endl;
		}
	}
	openfile.close();
}

void Menu()
{
	std::cout << Blank(5) << "   <---------------------------->" << std::endl;
	std::cout << Blank(6) << "  vector模式-信息管理" << std::endl;
	std::cout << Blank(6) << "    1、添加人物" << std::endl << Blank(6) << "    2、删除人物" << std::endl;
	std::cout << Blank(6) << "    3、修改信息" << std::endl << Blank(6) << "    4、浏览信息" << std::endl;
	std::cout << Blank(6) << "    5、信息排序" << std::endl << Blank(6) << "    0、退出系统" << std::endl;
	std::cout << Blank(5) << "   <---------------------------->" << std::endl;
	std::cout << Blank(6) << "    请选择:";
}

void Exits(std::vector<Text>& vec, Text& vectors)
{
	std::cout << Blank(4) << "<------------------------------------------------------>" << std::endl;
	std::cout << Blank(5) << "是否退出系统?\t\ty[Y]/n[N]" << std::endl << std::endl << Blank(6) << "     请选择:";
	int num = Judge();
	if (num == 1)
	{
		vec.clear();
		vec.shrink_to_fit();//减少capacity到size大小
		//_CrtDumpMemoryLeaks();
		exit(0);
	}
	std::cout << (num == 0 ? "已取消退出!" : "无效输入已取消操作!");
}

void Addperson(std::vector<Text>& vec, Text& vectors)
{
	Addmessage(vec,vectors);
	vec.push_back(vectors);
	std::cout << Blank(7);
	Savefile(vec,vectors);
	Dealy(800);
	std::cout << std::endl << Blank(6) << "   信息录入成功!" << std::endl;
}

void Deletely(std::vector<Text>& vec, Text& vectors)
{
	std::cout << Blank(3) << "      <------------------------------------------------------>" << std::endl;
	std::cout << Blank(5) << "请输入删除人员编号:";
	std::string id;
	std::cin >> id;
	std::cout << Blank(3) << "      <------------------------------------------------------>" << std::endl;
	std::cout << Blank(4) << std::left << std::setw(24) << "姓名" << std::left << std::setw(24) << "编号"
		<< std::left << std::setw(24) << "工资" << std::endl << std::endl;
	int i = 0;
	for (auto& message : vec)
	{
		if (message.id == id)
		{
			std::cout << Blank(4) << std::left << std::setw(24) << message.name << std::left << std::setw(24) << message.id
				<< std::left << std::setw(24) << message.wages << std::endl << std::endl;
			std::cout << Blank(4) << "是否删除匹配数据?\t\t\ty[Y]/n[N]"<< std::endl << std::endl << Blank(6) <<"     请选择:";
			int num = Judge();
			if (num == 1)
			{
				vec.erase(vec.begin() + i);
				std::cout << Blank(7);
				Savefile(vec,vectors);
				Dealy(800);
				std::cout << std::endl << Blank(6) << "    删除成功！" << std::endl;
				return;
			}
			std::cout << std::endl << Blank(6) << (num == 0 ? "    已取消删除！" : "无效操作已取消删除！") << std::endl;
		}
		i++;
	}
	std::cout << std::endl << Blank(6) << "    无匹配数据！" << std::endl;
}

void Modify(std::vector<Text>& vec, Text& vectors)
{
	std::cout << Blank(3) << "      <------------------------------------------------------>" << std::endl;
	std::cout << Blank(5) << "请输入修改人员编号:";
	std::string id;
	std::cin >> id;
	std::cout << Blank(3) << "      <------------------------------------------------------>" << std::endl;
	std::cout << Blank(4) << std::left << std::setw(24) << "姓名" << std::left << std::setw(24) << "编号"
		<< std::left << std::setw(24) << "工资" << std::endl << std::endl;
	int i = 0;
	for (auto& message : vec)
	{
		if (message.id == id)
		{
			std::cout << Blank(4) << std::left << std::setw(24) << message.name << std::left << std::setw(24) << message.id
				<< std::left << std::setw(24) << message.wages << std::endl << std::endl;
			std::cout << Blank(4) << "是否修改匹配数据?\t\t\ty[Y]/n[N]" << std::endl << std::endl << Blank(6) << "     请选择:";
			int num = Judge();
			if (num == 1)
			{
				Addmessage(vec,vectors);
				vec.at(i) = vectors;
				std::cout << Blank(7);
				Savefile(vec, vectors);
				Dealy(800);
				std::cout << std::endl << Blank(6) << "    修改成功！" << std::endl;
				return;
			}
			std::cout << std::endl << Blank(6) << (num == 0 ? "    已取消修改！" : "无效操作已取消修改！") << std::endl;
		}
		i++;
	}
	std::cout << std::endl << Blank(6) << "    无匹配数据！" << std::endl;
}

void Sortly(std::vector<Text>& vec, Text& vectors)
{
	std::cout << Blank(3) << "      <------------------------排序方式----------------------->" << std::endl;
	std::cout << Blank(4) << "1、姓名排序\t    2、编号排序\t\t3、工资排序" << std::endl << std::endl << Blank(6) << "    请选择:";
	char num;
	std::cin >> num;
	int temp = 0,num1 = atoi(&num);
	Text v = vec.at(0);
	F function[] = {(F)Sortnames,(F)Sortids,(F)Sortwages};
	if(num1 >=1 && num1 <=3)
	{
		for (int i = 0; i < vec.size(); i++)
		{
			for (int j = i + 1; j < vec.size(); j++)
			{
				if (function[num1 - 1](vec,j,i))
				{
					v = vec.at(j);
					vec.at(j) = vec.at(i);
					vec.at(i) = v;
				}
			}
		}
		View(vec, vectors);
	}
	else
	{
		std::cout << std::endl << Blank(6) << "   无效操作！" << std::endl;
	}
}

int Sortnames(std::vector<Text>vec,int j,int i)
{
	return vec.at(j).name < vec.at(i).name;
}

int Sortids(std::vector<Text> vec, int j, int i)
{
	return std::stoi(vec.at(j).id) < std::stoi(vec.at(i).id);
}

int Sortwages(std::vector<Text> vec, int j, int i)
{
	return std::stoi(vec.at(j).wages) < std::stoi(vec.at(i).wages);
}



void View(std::vector<Text>& vec, Text& vectors)
{
	std::cout << Blank(3) << "      <------------------------------------------------------>" << std::endl;
	std::cout << Blank(4) << std::left << std::setw(24) << "姓名" << std::left << std::setw(24) << "编号"
		<< std::left << std::setw(24) << "工资" << std::endl << std::endl;
	for (auto& v : vec)
	{
		std::cout << Blank(4) << std::left << std::setw(24) << v.name << std::left << std::setw(24) << v.id
			<< std::left << std::setw(24) << v.wages << std::endl;
	}
	std::cout << std::endl ;
}

void Addmessage(std::vector<Text>vec, Text& vectors)
{
	std::cout << std::endl << Blank(4) << "<-----------------请按提示录入信息------------------>" << std::endl;
	std::cout << std::endl << Blank(6) << "姓名:";
	std::string name;
	std::cin >> name;
	std::cout << std::endl << Blank(6) << "编号:";
	std::string id;
	std::cin >> id;
	for (auto& message : vec)
	{
		while (message.id == id)
		{
			std::cout << Blank(6) << "编号重复!" << std::endl;
			std::cout << std::endl << Blank(6) << "编号:";
			std::cin >> id;
		}
		break;
	}
	std::cout << std::endl << Blank(6) << "工资:";
	std::string wages;
	std::cin >> wages;
	vectors.name = name, vectors.id = id, vectors.wages = wages;
}

std::string Blank(int num)
{
	std::string tabs(num, '\t');
	return tabs;
}

int Judge()
{
	char c;
	std::cin >> c;
	if (c == 'y' || c == 'Y')
		return 1;
	else if (c == 'n' || c == 'N')
		return 0;
	else
		return -1;
}

void Dealy(int num)
{
	//std::this_thread::sleep_for(std::chrono::seconds(1));//延迟1秒，但是没办法精确毫秒计算
	while(num -= 200)
	{
		auto time_t = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(num);//当前时间+800毫秒
		std::cout << ".";
		std::this_thread::sleep_until(time_t);//精确定时器，定时800毫秒
	}
	auto time_t = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(num);
	std::this_thread::sleep_until(time_t);
	std::cout << std::endl;
}




