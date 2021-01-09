#pragma once
#include<iostream>
#include<fstream>
using namespace std;
enum class authority{borrower,manager,unlogin};//权限
//人员类
class People
{
public:
	friend class LibOperate;
	People(string n="小明", string s="男", int a=18) :name(n), sex(s), age(a) {}//构造函数
	bool operator==(People& p);
	void regist();//注册信息输入
	void showInfo();//信息显示
	string getUser();//返回用户名
	string getPass();//返回密码
	friend void writefile();//写入人员信息文件
	friend void readfile();//读取人员信息文件
private:
	string name;//姓名
	string sex;//性别
	int age;//年龄
	string username;//用户名
	string password;//密码
};
//书类
class Book
{
public:
	friend class LibOperate;
	Book(string o="NULL",string c="0000",string n="空",string a="空",bool s = true) :code(c),name(n),author(a),state(s) ,owner(o){}
	void input();//输入书籍数据
	void showInfo();//显示书籍数据
	friend void writefile_book();//写入书籍信息
	friend void readfile_book();//读取书籍信息
	string getName();//返回书名
	string getAuthor();//返回作者
	bool getState();//返回借阅状态
private:
	string code;//编码
	string name;//书名
	string author;//作者
	bool state;//状态（借走或未借阅）
	string owner;//书籍拥有者
};
//图书馆操作类
class LibOperate
{
public:
	//类函数
	authority getAuthority() { return auth; }//返回权限
	LibOperate(authority a = authority::unlogin) :auth(a) {}//构造函数
	//普通用户操作权限
	void regist(authority a);//用户注册
	bool sign();//用户登录
	void exit();//退出登录
	void browse();//浏览所有图书
	void check();//查询图书
	void borrow();//借书
	void send_back();//还书
	void info();//人员信息
	//管理员权限
	void add();//添加书籍
	void del();//删除图书
	void change();//修改图书数据
	void del_all();//删除所有图书
	void del_ppl();//删除人员信息
private:
	authority auth;//图书馆权限
};
void readfile();
void writefile();
void readfile_book();
void writefile_book();