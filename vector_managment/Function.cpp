//#ifdef _DEBUG
//#ifndef DBG_NEW
//#define DBG_NEW new(_NORMAL_BLOCK,_FILE_,_FINE_)
//#define new DBG_NEW
//#endif
//#endif// _DEBUG
#include "Statemnet.h"
#include<iostream>
#include<iomanip>
#include<chrono>//���������ӳٺ���������ǰ�߳�����˯��״̬������ͣ�߳�ִ�У������ʱ���ȥ�߳̽����Ѽ���ִ�к�������
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
	std::cout << Blank(6) << "  vectorģʽ-��Ϣ����" << std::endl;
	std::cout << Blank(6) << "    1���������" << std::endl << Blank(6) << "    2��ɾ������" << std::endl;
	std::cout << Blank(6) << "    3���޸���Ϣ" << std::endl << Blank(6) << "    4�������Ϣ" << std::endl;
	std::cout << Blank(6) << "    5����Ϣ����" << std::endl << Blank(6) << "    0���˳�ϵͳ" << std::endl;
	std::cout << Blank(5) << "   <---------------------------->" << std::endl;
	std::cout << Blank(6) << "    ��ѡ��:";
}

void Exits(std::vector<Text>& vec, Text& vectors)
{
	std::cout << Blank(4) << "<------------------------------------------------------>" << std::endl;
	std::cout << Blank(5) << "�Ƿ��˳�ϵͳ?\t\ty[Y]/n[N]" << std::endl << std::endl << Blank(6) << "     ��ѡ��:";
	int num = Judge();
	if (num == 1)
	{
		vec.clear();
		vec.shrink_to_fit();//����capacity��size��С
		//_CrtDumpMemoryLeaks();
		exit(0);
	}
	std::cout << (num == 0 ? "��ȡ���˳�!" : "��Ч������ȡ������!");
}

void Addperson(std::vector<Text>& vec, Text& vectors)
{
	Addmessage(vec,vectors);
	vec.push_back(vectors);
	std::cout << Blank(7);
	Savefile(vec,vectors);
	Dealy(800);
	std::cout << std::endl << Blank(6) << "   ��Ϣ¼��ɹ�!" << std::endl;
}

void Deletely(std::vector<Text>& vec, Text& vectors)
{
	std::cout << Blank(3) << "      <------------------------------------------------------>" << std::endl;
	std::cout << Blank(5) << "������ɾ����Ա���:";
	std::string id;
	std::cin >> id;
	std::cout << Blank(3) << "      <------------------------------------------------------>" << std::endl;
	std::cout << Blank(4) << std::left << std::setw(24) << "����" << std::left << std::setw(24) << "���"
		<< std::left << std::setw(24) << "����" << std::endl << std::endl;
	int i = 0;
	for (auto& message : vec)
	{
		if (message.id == id)
		{
			std::cout << Blank(4) << std::left << std::setw(24) << message.name << std::left << std::setw(24) << message.id
				<< std::left << std::setw(24) << message.wages << std::endl << std::endl;
			std::cout << Blank(4) << "�Ƿ�ɾ��ƥ������?\t\t\ty[Y]/n[N]"<< std::endl << std::endl << Blank(6) <<"     ��ѡ��:";
			int num = Judge();
			if (num == 1)
			{
				vec.erase(vec.begin() + i);
				std::cout << Blank(7);
				Savefile(vec,vectors);
				Dealy(800);
				std::cout << std::endl << Blank(6) << "    ɾ���ɹ���" << std::endl;
				return;
			}
			std::cout << std::endl << Blank(6) << (num == 0 ? "    ��ȡ��ɾ����" : "��Ч������ȡ��ɾ����") << std::endl;
		}
		i++;
	}
	std::cout << std::endl << Blank(6) << "    ��ƥ�����ݣ�" << std::endl;
}

void Modify(std::vector<Text>& vec, Text& vectors)
{
	std::cout << Blank(3) << "      <------------------------------------------------------>" << std::endl;
	std::cout << Blank(5) << "�������޸���Ա���:";
	std::string id;
	std::cin >> id;
	std::cout << Blank(3) << "      <------------------------------------------------------>" << std::endl;
	std::cout << Blank(4) << std::left << std::setw(24) << "����" << std::left << std::setw(24) << "���"
		<< std::left << std::setw(24) << "����" << std::endl << std::endl;
	int i = 0;
	for (auto& message : vec)
	{
		if (message.id == id)
		{
			std::cout << Blank(4) << std::left << std::setw(24) << message.name << std::left << std::setw(24) << message.id
				<< std::left << std::setw(24) << message.wages << std::endl << std::endl;
			std::cout << Blank(4) << "�Ƿ��޸�ƥ������?\t\t\ty[Y]/n[N]" << std::endl << std::endl << Blank(6) << "     ��ѡ��:";
			int num = Judge();
			if (num == 1)
			{
				Addmessage(vec,vectors);
				vec.at(i) = vectors;
				std::cout << Blank(7);
				Savefile(vec, vectors);
				Dealy(800);
				std::cout << std::endl << Blank(6) << "    �޸ĳɹ���" << std::endl;
				return;
			}
			std::cout << std::endl << Blank(6) << (num == 0 ? "    ��ȡ���޸ģ�" : "��Ч������ȡ���޸ģ�") << std::endl;
		}
		i++;
	}
	std::cout << std::endl << Blank(6) << "    ��ƥ�����ݣ�" << std::endl;
}

void Sortly(std::vector<Text>& vec, Text& vectors)
{
	std::cout << Blank(3) << "      <------------------------����ʽ----------------------->" << std::endl;
	std::cout << Blank(4) << "1����������\t    2���������\t\t3����������" << std::endl << std::endl << Blank(6) << "    ��ѡ��:";
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
		std::cout << std::endl << Blank(6) << "   ��Ч������" << std::endl;
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
	std::cout << Blank(4) << std::left << std::setw(24) << "����" << std::left << std::setw(24) << "���"
		<< std::left << std::setw(24) << "����" << std::endl << std::endl;
	for (auto& v : vec)
	{
		std::cout << Blank(4) << std::left << std::setw(24) << v.name << std::left << std::setw(24) << v.id
			<< std::left << std::setw(24) << v.wages << std::endl;
	}
	std::cout << std::endl ;
}

void Addmessage(std::vector<Text>vec, Text& vectors)
{
	std::cout << std::endl << Blank(4) << "<-----------------�밴��ʾ¼����Ϣ------------------>" << std::endl;
	std::cout << std::endl << Blank(6) << "����:";
	std::string name;
	std::cin >> name;
	std::cout << std::endl << Blank(6) << "���:";
	std::string id;
	std::cin >> id;
	for (auto& message : vec)
	{
		while (message.id == id)
		{
			std::cout << Blank(6) << "����ظ�!" << std::endl;
			std::cout << std::endl << Blank(6) << "���:";
			std::cin >> id;
		}
		break;
	}
	std::cout << std::endl << Blank(6) << "����:";
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
	//std::this_thread::sleep_for(std::chrono::seconds(1));//�ӳ�1�룬����û�취��ȷ�������
	while(num -= 200)
	{
		auto time_t = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(num);//��ǰʱ��+800����
		std::cout << ".";
		std::this_thread::sleep_until(time_t);//��ȷ��ʱ������ʱ800����
	}
	auto time_t = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(num);
	std::this_thread::sleep_until(time_t);
	std::cout << std::endl;
}




