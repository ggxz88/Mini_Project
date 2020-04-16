#pragma once
#ifndef PARTTIME_H
#define PARTTIME_H
class PTJ {
private:
	int id; // id
	char* workplace;
	char* name; // 이름
	
	
public:
	int salary; // 월급

	PTJ();
	PTJ(const char * w, const char * n, int i, int s);
	PTJ(const PTJ& obj);
	~PTJ();
	PTJ& operator = (const PTJ &p);
	void ShowAllData() const;

	// Getters
	int GetId() const;
	char* GetWork() const;
	char* GetName() const;

	// Setters
	void SetId(int val);
	void SetWork(char* workplace);
	void SetName(char* name);
	
};

class PTJ_weeklyholiday :public PTJ {
public:
	int weekly_holidaypay;
	/*int incometax;
	int fourinsurance;*/

	PTJ_weeklyholiday();
	PTJ_weeklyholiday(const char * w, const char * n, int i, int s, int wh);
	PTJ_weeklyholiday(const PTJ_weeklyholiday& obj);
	~PTJ_weeklyholiday();

	//Getter
	int Get_wh() const;

	//Setter
	void SetName(int val);
};

class PTJ_tax :public PTJ {
public:
	int incometax;
	int fourinsurance;
	int tax;

	PTJ_tax();
	PTJ_tax(const char * w, const char * n, int i, int s, float ic, float fi, float t);
	PTJ_tax(const PTJ_tax& obj);
	~PTJ_tax();

	// Getters
	int GetIncome() const;
	int GetFour() const;
	int GetTax() const;

	// Setters
	void SetIncome(int val);
	void SetFour(int val);
	void SetTax(int val);

};

//class PTJ_add :public PTJ {
//public:
//	int addmoney;
//
//	PTJ_add();
//	PTJ_add(const char * w, const char * n, int i, int s, float a);
//	PTJ_add(const PTJ_add& obj);
//	~PTJ_add();
//
//	// Getter
//	int GetAdd() const;
//
//	// Setter
//	void SetAdd(int val);
//};

#endif // !CALC_H