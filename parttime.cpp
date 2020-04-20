#include <iostream>
#include "parttime.h"
using namespace std;
const int MAX_NAME = 50;
PTJ::PTJ() { //���� ���� ������
	id = 0;
	salary = 0;
	sal = 0;
	workplace = new char[MAX_NAME];
	name = new char[MAX_NAME];
}

PTJ::PTJ(const char * w, const char * n, int i, int s, float sa) { // �����ִ� ������
	id = i;
	salary = s;
	sal = sa;
	workplace = new char[strlen(w)+1];
	name = new char[strlen(n) + 1];
	strcpy_s(workplace, strlen(w) + 1, w);
	strcpy_s(name, strlen(n) + 1, n);
}

PTJ::PTJ(const PTJ& obj) { // ���� ���� ������
	id = obj.id;
	salary = obj.salary;
	sal = obj.sal;
	name = new char[strlen(obj.name) + 1];
	workplace = new char[strlen(obj.workplace) + 1];
	strcpy_s(name, strlen(obj.name) + 1, obj.name);
	strcpy_s(workplace, strlen(obj.workplace) + 1, obj.workplace);
}

PTJ::~PTJ() { // �Ҹ���
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
		sal = p.sal;
	}
	return *this;
}

void PTJ::ShowAllData() const
{
	cout << "ID : " << id << " ���� : " << workplace << " �̸� : " << name << " ���� : " << salary << endl;
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

float PTJ::GetSal() const
{
	return sal;
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

void PTJ::SetSal(float val)
{
	sal = val;
}

PTJ_tax::PTJ_tax()
	:PTJ()
{ // ���ھ��� ������
	incometax = 0;
	fourinsurance = 0;
	tax = 0;
}

PTJ_tax::PTJ_tax(const char * w, const char * n, int i, int s, float sa, float ic, float fi, float t)
	:PTJ(w, n, i, s, sa)
{ // �����ִ� ������
	incometax = ic;
	fourinsurance = fi;
	tax = t;
}

PTJ_tax::PTJ_tax(const PTJ_tax & obj)
	:PTJ(obj)
{ //���� ���� ������
	incometax = obj.incometax;
	fourinsurance = obj.fourinsurance;
	tax = obj.tax;
}

PTJ_tax::~PTJ_tax()
{ // PTJ_tax �Ҹ���
}

float PTJ_tax::GetIncome() const
{
	return incometax;
}

float PTJ_tax::GetFour() const
{
	return fourinsurance;
}

float PTJ_tax::GetTax() const
{
	return tax;
}

void PTJ_tax::SetIncome(float val)
{
	incometax = val;
}

void PTJ_tax::SetFour(float val)
{
	fourinsurance = val;
}

void PTJ_tax::SetTax(float val)
{
	tax = val;
}

PTJ_weeklyholiday::PTJ_weeklyholiday()
	:PTJ()
{ // ���ھ��� ������
	weekly_holidaypay = 0;
}

PTJ_weeklyholiday::PTJ_weeklyholiday(const char * w, const char * n, int i, int s, float sa, int wh)
	:PTJ(w, n, i, s, sa)
{ // ���� �ִ� ������
	weekly_holidaypay = wh;
}

PTJ_weeklyholiday::PTJ_weeklyholiday(const PTJ_weeklyholiday & obj)
	: PTJ(obj)
{ // ���� ���� ������
	weekly_holidaypay = obj.weekly_holidaypay;
}

PTJ_weeklyholiday::~PTJ_weeklyholiday()
{ // �Ҹ���
}

int PTJ_weeklyholiday::Get_wh() const
{
	return weekly_holidaypay;
}

void PTJ_weeklyholiday::Set_wh(int val)
{
	weekly_holidaypay = val;
}
