#include"library.h"
#include"myList.cpp"
#include<iostream>
#include<iomanip>
#include<vector>
using std::cout; using std::cin;
vector<People> pb;//借书者
vector<People>pm;//管理人员
vector<People>::iterator it;//向量迭代器
myList<Book>b;//创建一个书类的列表
People currPpl;//储存当前账户信息；

//类函数定义
void writefile()
{
	ofstream f1("borrower.txt"),f2("manager.txt");
	if (f1.good())
	{
		for (it = pb.begin(); it < pb.end(); it++)
		{
			f1 << (*it).name<<"\t" << (*it).sex << "\t" << (*it).age << "\t" << (*it).username << "\t" << (*it).password << endl;
		}
		for (it = pm.begin(); it < pm.end(); it++)
		{
			f2<< (*it).name << "\t" << (*it).sex << "\t" << (*it).age << "\t" << (*it).username << "\t" << (*it).password << endl;
		}
	}
	f1.close();
	f2.close();
}
void readfile()
{
	People p1,p2;
	ifstream f1("borrower.txt"),f2("manager.txt");
	if (f1.good())
	{
		while (f1 >> p1.name >> p1.sex >> p1.age >> p1.username >> p1.password)
		{
			pb.push_back(p1);
		}
	}
	else
	{
		f1.close();
		cout << "error！" << endl;
		return;
	}
	f1.close();
	if (!f2.bad())
	{
		while (f2 >> p2.name >> p2.sex >> p2.age >> p2.username >> p2.password)
		{
			pm.push_back(p2);
		}
	}
	else
	{
		f2.close();
		cout << "error！" << endl;
		return;
	}
	f2.close();
}
void People::showInfo()
{
	cout << "姓名：" << name << endl;
	cout << "性别：" << sex << endl;
	cout << "年龄：" << age << endl;
}
void People::regist()
{
	cout << "请输入姓名\t性别\t年龄\t账号\t密码" << endl;
	cin >> name >> sex >> age >> username >> password;
}
string People::getUser() { return username; }
string People::getPass() { return password; }
bool People::operator==(People& p)
{
	if (name==p.name && sex == p.sex && age == p.age)return true;
	else return false;
}
void Book::input()
{
	cout << "请输入编码\t书名\t作者" << endl;
	cin >> code >> name >> author;
}
void Book::showInfo()
{
	cout << setw(10) << std::left<< code << setw(20) << std::left << name << setw(10) << std::left << author;
}
void writefile_book()
{
	ofstream f1("book.txt");
	if (f1.good())
	{
		for (int i = 0; i < b.size(); i++)
		{
			f1 << b[i]->data.code << "\t " << b[i]->data.name << "\t " << b[i]->data.author << "\t" << b[i]->data.state << "\t" << b[i]->data.owner << endl;
		}
	}
	f1.close();
}
void readfile_book()
{
	ifstream f1("book.txt");
	Book b1;
	if (f1.good())
	{
		while (f1 >> b1.code >> b1.name >> b1.author >> b1.state >> b1.owner)
		{
			b.push_back(b1);
		}
	}
	else
	{
		f1.close();
		cout << "error！" << endl;
		return;
	}
	f1.close();
	
}
string Book::getAuthor() { return author; }
string Book::getName() { return name; }
bool Book::getState() { return state; }
bool LibOperate::sign()
{
	string user, psword;

	cout << "请输入账号：";
	cin >> user;
	cout << "请输入密码：";
	cin >> psword;
	for (it = pb.begin(); it < pb.end(); it++)
	{
		if (user == (*it).getUser() && psword == (*it).getPass())
		{
			cout << "登录成功！" << endl;
			auth = authority::borrower;
			currPpl = *it;
			return true;
		}
		else
		{
			continue;
		}
	}
	for (it = pm.begin(); it < pm.end(); it++)
	{
		if (user == (*it).getUser() && psword == (*it).getPass())
		{
			cout << "登录成功！" << endl;
			auth = authority::manager;
			currPpl = *it;
			return true;
		}
		else
		{
			continue;
		}
	}
	cout << "账号或密码错误，请重新输入" << endl;
	return false;
}
void LibOperate::regist(authority a)
{
	People p1;
	p1.regist();
	if (a == authority::borrower)
	{
		for (it = pb.begin(); it < pb.end(); it++)
		{
			if (p1.username == (*it).username)
			{
				cout << "该用户名已存在！" << endl;
				return;
			}
		}
		pb.push_back(p1);
		writefile();
		cout << "注册成功！" << endl;
	}
	else if (a == authority::manager)
	{
		for (it = pm.begin(); it < pm.end(); it++)
		{
			if (p1.username == (*it).username)
			{
				cout << "该用户名已存在！" << endl;
				return;
			}
		}
		pm.push_back(p1);
		writefile();
		cout << "注册成功！" << endl;
	}
}
void LibOperate::add()
{
	Book b1;
	b1.input();
	for (int i = 0; i < b.size(); i++)
	{
		if (b[i]->data.name == b1.name && b[i]->data.author == b1.author)
			{
				cout << "该书籍已存在！" << endl;
				return;
			}
	}
	b.push_back(b1);
	writefile_book();
	cout << "添加成功！" << endl;
}
void LibOperate::exit()
{
	auth = authority::unlogin;
}
void  LibOperate::browse()
{
	cout << setw(10)<<std::left<<"编码" << setw(20) << std::left << "书名" << setw(10) << std::left << "作者" << endl;
	for (int i = 0; i < b.size(); i++)
	{
		if (b[i]->data.getState() == true)
		{
			b[i]->data.showInfo();
			cout << endl;
		}
		else
		{
			b[i]->data.showInfo();
			cout << "(已被借阅)"<<endl;
		}
	}
}
void LibOperate::check()
{
	string str; bool flag = false;
	cout << "请输入书名或作者进行检索：" << endl;
	cin >> str;
	cout << "编号\t书名\t作者" << endl;
	for (int i = 0; i < b.size(); i++)
	{
		if (str == b[i]->data.getAuthor() || str == b[i]->data.getName())
		{
			if (b[i]->data.getState() == true)
			{
				b[i]->data.showInfo();
				cout << endl;
			}
			else
			{
				b[i]->data.showInfo();
				cout << "(已被借阅)" << endl;
			}
			flag = true;
		}
		else continue;
	}
	if(flag==false)cout << "无相关书籍！" << endl;
}
void LibOperate::borrow()
{
	string str; bool flag = false;
	cout << "请输入要借阅的书籍名称：";
	cin >> str;
	for (int i = 0; i < b.size(); i++)
	{
		if (str == b[i]->data.getName())
		{
			if (b[i]->data.getState() == true)b[i]->data.showInfo();
			else
			{
				b[i]->data.showInfo();
				cout << "(已被借阅)";
				system("pause");
				return;
			}
			b[i]->data.state = false;
			b[i]->data.owner = currPpl.username;
			writefile_book();
			cout << "\t借阅成功！" << endl;
			flag = true;
		}
		else continue;
	}
	if (flag == false)cout << "无相关书籍！" << endl;
}
void LibOperate::send_back()
{
	string str;
	cout << "请输入要归还的书籍名称：";
	cin >> str;
	for (int i = 0; i < b.size(); i++)
	{
		if (str == b[i]->data.name&&b[i]->data.owner==currPpl.username)
		{
			b[i]->data.state = true;
			writefile_book();
			cout << "归还成功！" << endl;
			return;
		}
	}
	cout << "无此图书!" << endl;
}
void LibOperate::info()
{
	cout << "姓名：" << currPpl.name << endl;
	cout << "性别：" << currPpl.sex << endl;
	cout<< "年龄：" << currPpl.age << endl;
	cout << "正在借阅的书籍：" << endl;
	for (int i = 0; i < b.size(); i++)
	{
		if (b[i]->data.owner == currPpl.username)
		{
			b[i]->data.showInfo(); 
			cout << endl;
			return;
		}
	}
	cout << "无" << endl;
}
void LibOperate::del()
{
	cout << "请输入要删除的图书名称：" << endl;
	string str;
	cin >> str;
	for (int i = 0; i < b.size(); i++)
	{
		if (str == b[i]->data.name)
		{
			/*if (b[i]->data.state == false)
			{
				cout << "此书正在被借阅，不可删除!" << endl;
				return;
			}*/
			b.erase(i);
			cout << "操作成功！" << endl;
			writefile_book();
			return;
		}
	}
	cout << "无相关书籍！" << endl;
}
void LibOperate::change()
{
	string str;
	cout << "请输入书名或作者进行检索：" << endl;
	cin >> str;
	cout << "编号\t书名\t作者" << endl;
	for (int i = 0; i < b.size(); i++)
	{
		if (str == b[i]->data.getName()||str==b[i]->data.getAuthor())
		{
			if (b[i]->data.getState() == true)
			{
				b[i]->data.showInfo();
				cout << endl;
				cout << "请输入新的编号\t书名\t作者"<< endl;
				Book b1;
				cin >> b1.code >> b1.name >> b1.author;
				b[i]->data = b1;
				writefile_book();
				cout << "修改成功！" << endl;
				return;
			}
			else
			{
				b[i]->data.showInfo();
				cout << "(已被借阅)" << endl;
				cout << "请输入新的编号\t书名\t作者" << endl;
				Book b1;
				cin >> b1.code >> b1.name >> b1.author; b1.state = b[i]->data.state;
				b[i]->data = b1;
				writefile_book();
				cout << "修改成功！" << endl;
				return;
			}
		}
		else continue;
	}
	cout << "无相关书籍！" << endl;

}
void LibOperate::del_all()
{
	cout << "操作不可逆，确认删除吗？(确认输入1，退出输入0）" << endl;
	cout << "请输入：";
	bool flag;
	cin >> flag;
	if (flag == 1)
	{
		for (int i = b.size()-1; i >=0; i--)
		{
			b.erase(i);
		}
		writefile_book();
		cout << "操作成功!" << endl;
	}
	else return;
}
void LibOperate::del_ppl()
{
	cout << "请输入要删除的账户名：";
	string str;
	cin >> str;
	for (it = pb.begin(); it < pb.end(); it++)
	{
		if (str == (*it).username)
		{
			cout << "删除成功！" << endl;
			pb.erase(it);
			writefile();
			return;
		}
	}
	for (it = pm.begin(); it < pm.end(); it++)
	{
		if (str == currPpl.username)
		{
			cout << "不能删除自己！" << endl;
		}
		else
		{
			if (str == (*it).username)
			{
				cout << "删除成功！" << endl;
				pm.erase(it);
				writefile();
				return;
			}
		}
	}
	cout << "无此账户！" << endl;
}