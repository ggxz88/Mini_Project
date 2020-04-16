#include <iostream>
#include "parttime.h"
using namespace std;
const int MAX_NAME = 50;
PTJ::PTJ() { //인자 없는 생성자
	id = 0;
	salary = 0;
	workplace = new char[MAX_NAME];
	name = new char[MAX_NAME];
}

PTJ::PTJ(const char * w, const char * n, int i, int s) { // 인자있는 생성자
	id = i;
	salary = s;
	workplace = new char[strlen(w)+1];
	name = new char[strlen(n) + 1];
	strcpy_s(workplace, strlen(w) + 1, w);
	strcpy_s(name, strlen(n) + 1, n);
}

PTJ::PTJ(const PTJ& obj) { // 깊은 복사 생성자
	id = obj.id;
	salary = obj.salary;
	name = new char[strlen(obj.name) + 1];
	workplace = new char[strlen(obj.workplace) + 1];
	strcpy_s(name, strlen(obj.name) + 1, obj.name);
	strcpy_s(workplace, strlen(obj.workplace) + 1, obj.workplace);
}

PTJ::~PTJ() { // 소멸자
	delete[] name; name = NULL;
	delete[] workplace; workplace = NULL;
}

PTJ & PTJ::operator=(const PTJ & p)
{
	if (this != &p)
	{
		delete[] name;
		name = new char[strlen(p.name) + 1];
		strcpy_s(name, strlen(p.name) + 1, p.name);
		delete[] workplace;
		workplace = new char[strlen(p.workplace) + 1];
		strcpy_s(workplace, strlen(p.workplace) + 1, p.workplace);
		id = p.id;
		salary = p.salary;
	}
	return *this;
}

void PTJ::ShowAllData() const
{
	cout << "ID : " << id << " 직장 : " << workplace << " 이름 : " << name << " 월급 : " << salary << endl;
}

int PTJ::GetId() const
{
	return id;
}

char * PTJ::GetWork() const
{
	return workplace;
}

char * PTJ::GetName() const
{
	return name;
}

void PTJ::SetId(int val)
{
	id = val;
}

void PTJ::SetWork(char * work)
{
	if (this->workplace) { delete[] this->workplace; }
	this->workplace = new char[strlen(work) + 1];
	strcpy_s(this->workplace, strlen(work) + 1, work);
}

void PTJ::SetName(char * name)
{
	if (this->name) { delete[] this->name; }
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
}

PTJ_tax::PTJ_tax()
	:PTJ()
{ // 인자없는 생성자
	incometax = 0;
	fourinsurance = 0;
	tax = 0;
}

PTJ_tax::PTJ_tax(const char * w, const char * n, int i, int s, float ic, float fi, float t)
	:PTJ(w, n, i, s)
{ // 인자있는 생성자
	incometax = ic;
	fourinsurance = fi;
	tax = t;
}

PTJ_tax::PTJ_tax(const PTJ_tax & obj)
	:PTJ(obj)
{ //깊은 복사 생성자
	incometax = obj.incometax;
	fourinsurance = obj.fourinsurance;
	tax = obj.tax;
}

PTJ_tax::~PTJ_tax()
{ // PTJ_tax 소멸자
}

int PTJ_tax::GetIncome() const
{
	return incometax;
}

int PTJ_tax::GetFour() const
{
	return fourinsurance;
}

int PTJ_tax::GetTax() const
{
	return tax;
}

void PTJ_tax::SetIncome(int val)
{
	incometax = val;
}

void PTJ_tax::SetFour(int val)
{
	fourinsurance = val;
}

void PTJ_tax::SetTax(int val)
{
	tax = val;
}

//PTJ_add::PTJ_add()
//	:PTJ()
//{ // 인자없는 생성자
//	addmoney = 0;
//}
//
//PTJ_add::PTJ_add(const char * w, const char * n, int i, int s, float a)
//	:PTJ(w, n, i, s)
//{ // 인자있는 생성자
//	addmoney = a;
//}
//
//PTJ_add::PTJ_add(const PTJ_add & obj)
//	:PTJ(obj)
//{ // 깊은 복사 생성자
//	addmoney = obj.addmoney;
//}
//
//PTJ_add::~PTJ_add()
//{ // PTJ_add 소멸자
//}
//
//int PTJ_add::GetAdd() const
//{
//	return addmoney;
//}
//
//void PTJ_add::SetAdd(int val)
//{
//	addmoney = val;
//}

PTJ_weeklyholiday::PTJ_weeklyholiday()
	:PTJ()
{
	weekly_holidaypay = 0;
}

PTJ_weeklyholiday::PTJ_weeklyholiday(const char * w, const char * n, int i, int s, int wh)
	:PTJ(w, n, i, s)
{
	weekly_holidaypay = wh;
}

PTJ_weeklyholiday::PTJ_weeklyholiday(const PTJ_weeklyholiday & obj)
	: PTJ(obj)
{
	weekly_holidaypay = obj.weekly_holidaypay;
}

PTJ_weeklyholiday::~PTJ_weeklyholiday()
{
}

int PTJ_weeklyholiday::Get_wh() const
{
	return weekly_holidaypay;
}

void PTJ_weeklyholiday::SetName(int val)
{
	weekly_holidaypay = val;
}
