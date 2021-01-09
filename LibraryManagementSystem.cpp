#include<iostream>
#include<vector>
#include<conio.h>
#include<Windows.h>
#include"mylist.h"
#include"library.h"
using std::cout;
using std::cin;
using std::system;
LibOperate lib;
void menu()//主菜单显示及操作
{
	if (lib.getAuthority() == authority::unlogin)
	{
		int num;
		cout << "********注册登录页面********" << endl;
		cout << "1.注册用户" << endl;
		cout << "2.登录系统" << endl;
		cout << "0.退出系统" << endl;
		while (1)
		{	
			cout << "请输入操作的序号：";
			cin >> num;
			if (num == 1)
			{
				lib.regist(authority::borrower); 
				cout << "一秒后自动退出。。。";
				Sleep(1000);
				system("cls");
				menu();
			}
			else if (num == 2)
			{
				if (lib.sign())
				{
					cout << "一秒后自动退出。。。";
					Sleep(1000);
					system("cls");
					menu();
				}
			}
			else if (num == 0)
			{
				exit(0);
			}
			else cout << "输入错误，请重新输入！";
		}
	}
	else if (lib.getAuthority() == authority::borrower)
	{
		int num;
		cout << "********图书管理系统********" << endl;
		cout << "1.浏览所有图书" << endl;
		cout << "2.查询图书" << endl;
		cout << "3.借阅书籍" << endl;
		cout << "4.归还书籍" << endl;
		cout << "5.用户信息查看" << endl;
		cout << "0.退出登录" << endl;
		cout << "你好，借书人！" << endl;
		while (1)
		{
			cout << "请输入操作的序号：";
			cin >> num;
			switch (num)
			{
			case 1:
				system("cls");
				lib.browse();
				system("pause");
				system("cls");
				menu();
				break;
			case 2:
				system("cls");
				lib.check();
				system("pause");
				system("cls");
				menu();
				break;
			case 3:
				system("cls");
				lib.borrow();
				system("pause");
				system("cls");
				menu();
				break;
			case 4:
				system("cls");
				lib.send_back();
				system("pause");
				system("cls");
				menu();
				break;
			case 5:
				system("cls");
				cout << "你好，借书人！" << endl;
				lib.info();
				system("pause");
				system("cls");
				menu();
				break;
			case 0:
				system("cls");
				lib.exit();
				menu();
				break;
			}
		}
		
	}
	else
	{
		int num;
		cout << "********图书管理系统********" << endl;
		cout << "1.浏览所有图书" << endl;
		cout << "2.查询图书" << endl;
		cout << "3.借阅书籍" << endl;
		cout << "4.归还书籍" << endl;
		cout << "5.用户信息查看" << endl;
		cout << "6.添加图书" << endl;
		cout << "7.删除图书" << endl;
		cout << "8.删除所有图书" << endl;
		cout << "9.修改图书" << endl;
		cout << "10.管理员登记" << endl;
		cout << "11.人员删除" << endl;
		cout << "0.退出登录" << endl;
		cout << "你好！管理者！" << endl;
		while (1)
		{
			cout << "请输入操作的序号：";
			cin >> num;
			switch (num)
			{
			case 1:
				system("cls");
				lib.browse();
				system("pause");
				system("cls");
				menu();
				break;
			case 2:
				system("cls");
				lib.check();
				system("pause");
				system("cls");
				menu();
				break;
			case 3:
				system("cls");
				lib.borrow();
				system("pause");
				system("cls");
				menu();
				break;
			case 4:
				system("cls");
				lib.send_back();
				system("pause");
				system("cls");
				menu();
				break;
			case 5:
				system("cls");
				cout << "你好，借书人！" << endl;
				lib.info();
				system("pause");
				system("cls");
				menu();
				break;
			case 6:
				system("cls");
				lib.add();
				system("pause");
				system("cls");
				menu();
				break;
			case 7:
				system("cls");
				lib.del();
				system("pause");
				system("cls");
				menu();
				break;
			case 8:
				system("cls");
				lib.del_all();
				system("pause");
				system("cls");
				menu();
				break;
			case 9:
				system("cls");
				lib.change();
				system("pause");
				system("cls");
				menu();
				break;
			case 10:
				system("cls");
				lib.regist(authority::manager);
				system("pause");
				system("cls");
				menu();
				break;
			case 11:
				system("cls");
				lib.del_ppl();
				system("pause");
				system("cls");
				menu();
				break;
			case 0:
				system("cls");
				lib.exit();
				menu();
				break;
			default:
				system("cls");
				cout << "输入错误，请重新输入！" << endl;
				menu();
				break;
			}
		}
	}
}
int main()
{
	//读入文件
	readfile();
	readfile_book();
	//异常处理
	try {

		menu();
	}
	catch (int)
	{
		cerr << "error！" << endl;
		exit(0);
	}
	//退出前再次写入文件
	writefile();
	writefile_book();
}