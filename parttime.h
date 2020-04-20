#pragma once
#ifndef PARTTIME_H
#define PARTTIME_H
class PTJ {
private:
	int id; // id
	char* workplace; // ����
	char* name; // �̸�
	
	
public:
	int salary; // ����
	float sal; // ���� ������ ���� ����(�Ǽ�)

	PTJ();
	PTJ(const char * w, const char * n, int i, int s, float sa);
	PTJ(const PTJ& obj);
	~PTJ();
	PTJ& operator = (const PTJ &p);
	void ShowAllData() const; // ��ü ��ȸ

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
	int weekly_holidaypay; // ���� ����
	
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
	float incometax; // �ҵ漼
	float fourinsurance; // 4�� ����
	float tax; // ��Ÿ ����(���� �Է�)

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