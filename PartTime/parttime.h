#pragma once
#ifndef PARTTIME_H
#define PARTTIME_H
class PTJ {
private:
	int id; // id
	char* workplace; // 직장
	char* name; // 이름
	
	
public:
	int salary; // 월급
	float sal; // 세금 적용을 위한 월급(실수)

	PTJ();
	PTJ(const char * w, const char * n, int i, int s, float sa);
	PTJ(const PTJ& obj);
	~PTJ();
	PTJ& operator = (const PTJ &p);
	void ShowAllData() const; // 전체 조회

	// Getters
	int GetId() const;
	char* GetWork() const;
	char* GetName() const;
	float GetSal() const;

	// Setters
	void SetId(int val);
	void SetWork(char* workplace);
	void SetName(char* name);
	void SetSal(float val);
	
};

class PTJ_weeklyholiday :public PTJ {
public:
	int weekly_holidaypay; // 주휴 수당
	
	PTJ_weeklyholiday();
	PTJ_weeklyholiday(const char * w, const char * n, int i, int s, float sa, int wh);
	PTJ_weeklyholiday(const PTJ_weeklyholiday& obj);
	~PTJ_weeklyholiday();

	//Getter
	int Get_wh() const;

	//Setter
	void Set_wh(int val);
};

class PTJ_tax :public PTJ {
public:
	float incometax; // 소득세
	float fourinsurance; // 4대 보험
	float tax; // 기타 세금(직접 입력)

	PTJ_tax();
	PTJ_tax(const char * w, const char * n, int i, int s, float sa, float ic, float fi, float t);
	PTJ_tax(const PTJ_tax& obj);
	~PTJ_tax();

	// Getters
	float GetIncome() const;
	float GetFour() const;
	float GetTax() const;

	// Setters
	void SetIncome(float val);
	void SetFour(float val);
	void SetTax(float val);

};

#endif // !CALC_H