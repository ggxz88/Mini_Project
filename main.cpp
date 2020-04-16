#include <iostream>
#include <cstring>
#include "parttime.h"
using namespace std;
const int MAX_NAME = 50;
int year = 0, month = 0;
int day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int hourly_wage;

// �Լ� ����
void printCal(int year, int month);
void printMenu();
void MakeId(PTJ* DyArr, int& index, int size);
void Input(PTJ* DyArr, PTJ_weeklyholiday* DyArr_wh, PTJ_tax* DyArr_t/*, PTJ_add* DyArr_a*/, int& index);
//void addmoney(PTJ* DyArr, int& index, int start_hour, int start_min, int end_hour, int end_min);
void printlist();
//void salary(PTJ* DyArr, PTJ_weeklyholiday* DyArr_wh, PTJ_tax* DyArr_t/*, PTJ_add* DyArr_a*/, int& index/*, int salary*/);
void Salary_inquire(PTJ* DyArr, int& index);
void Inquire(PTJ* DyArr, int& index);
void exit();
enum { MAKE = 1, INPUT, SALARY, INQUIRE, EXIT };

int main() {
	int size = 3;
	PTJ* DyArr = new PTJ[size];
	PTJ_weeklyholiday* DyArr_wh = new PTJ_weeklyholiday[size];
	PTJ_tax* DyArr_t = new PTJ_tax[size];
	int index = 0;
	int choice;

	while (true) {
		printMenu();
		cout << "����: ";
		cin >> choice;
		switch (choice) {
		case MAKE:
			MakeId(DyArr, index, size);
			break;
		case INPUT:
			Input(DyArr, DyArr_wh, DyArr_t, index);
			break;
		case SALARY:
			Salary_inquire(DyArr, index);
			break;
		case INQUIRE:
			Inquire(DyArr, index);
			break;
		case EXIT:
			exit();
			return 0;
		default:
			cout << "�ٽ� �������ּ���." << endl;
			break;
		}
	}

	return 0;
}

// �Լ� ����
void printCal(int year, int month)
{
	int days = 0;
	int first_date = 0;
	int count = 0;

	days = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;

	for (int i = 0; i < month - 1; i++) {
		if (i == 1) {
			if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
				day[1] = 29;
			}
			else {
				day[1] = 28;
			}
		}
		days += day[i];
	}
	first_date = days % 7;

	cout << "<" << year << "��" << month << "��" << ">" << endl;
	cout << "��\t��\tȭ\t��\t��\t��\t��" << endl;

	for (int i = 0; i <= first_date; i++) {
		cout << "\t";
		count++;
	}
	for (int i = 1; i <= day[month - 1]; i++) {
		if (count >= 7) {
			cout << endl;
			count = 0;
		}
		cout << i << "\t";
		count++;
	}
	cout << endl << endl;
}

void printMenu() {
	cout << "----------------------- Menu -----------------------" << endl;
	cout << "1(id ����)" << endl;
	cout << "2(���� ���� �Է�)" << endl;
	cout << "3(���� ��ȸ)" << endl;
	cout << "4(��ü ��ȸ)" << endl;
	cout << "5(����)" << endl;
	cout << "----------------------------------------------------" << endl;
}

void MakeId(PTJ* DyArr, int& index, int size) {
	cout << "����" << endl;
	int id;
	char workplace[MAX_NAME];
	char name[MAX_NAME];
	if (index < size) {

		cout << "id ������ ���� �Է�(ID ���� �̸�)";
		cin >> id >> workplace >> name;
		

		for (int i = 0; i < index; i++) {
			if (id == DyArr[i].GetId()) {
				cout << "�ߺ��� id�� �ֽ��ϴ�. �ٽ� �Է����ּ���" << endl;
				return;
			}	
		}

		DyArr[index].SetId(id);
		DyArr[index].SetWork(workplace);
		DyArr[index].SetName(name);

		id = DyArr[index].GetId();
		strcpy_s(DyArr[index].GetWork(), strlen(workplace) + 1, workplace);
		strcpy_s(DyArr[index].GetName(), strlen(name) + 1, name);

		index++;
		cout << endl;

		cout << "ID : " << id << " ���� : " << workplace << " �̸� : " << name << endl;
		
	}
	else {
		cout << "�ִ� " << size << "���� ���� �� �ֽ��ϴ�." << endl;
	}
}

void Input(PTJ* DyArr, PTJ_weeklyholiday* DyArr_wh, PTJ_tax* DyArr_t/*, PTJ_add* DyArr_a*/, int& index)
{
	cout << "���� ���� �Է�" << endl;

	int id, workday;
	int start_hour, start_min, end_hour, end_min; // ���� �ð�, ��, ���� �ð�, ��
	int hour = 0; // ���� �ð�
	int minute = 0; // ���� ��
	int daily_wage; //�ϱ�
	int sum = 0;
	
	cout << "ID : ";
	cin >> id;
	
	DyArr[index].SetId(id);

	bool found = false;
	for (int i = 0; i < index; i++) {
		if (DyArr[i].GetId() == id) {
			found = true;
			break;
		}
		else {
			found = false;
		}
	}
	if (found == false) {
		cout << "�������� �ʴ� ID�Դϴ�." << endl;
		return;
	}
	
	cout << "�ñ� : ";
	cin >> hourly_wage;

	cout << "���� ���� ��ĥ�ΰ���?";
	cin >> workday;

	cout << "��� ���� �Է����ּ���(�� ��)";
	cin >> year >> month;
	printCal(year, month);

	char reply1[10];
	cout << "�߰� ������ �����Ͻðڽ��ϱ�?(y/n)";
	cin >> reply1;

	if (strcmp(reply1, "y") == 0) {
		for (int j = 1; j <= day[month - 1]; j++) {
			cout << j << "�� ���� �ð�(���� ��, ��, ���� ��, ��)";
			cin >> start_hour >> start_min >> end_hour >> end_min;
			if (end_min >= start_min) {
				hour = end_hour - start_hour;
				minute = end_min - start_min;
			}
			else {
				hour = end_hour - start_hour - 1;
				minute = (end_min + 60) - start_min;
			}

			// ���� ����
			if (hour >= 8) {
				int addmoney1 = 0;
				int add1 = 0;
				add1 = ((hour - 8) * hourly_wage * 1.5) + ((hourly_wage / 60) * minute * 1.5);
				addmoney1 += add1;
			}
			// �߰� ����
			if (end_hour >= 22 || end_hour <= 5) {
				int addmoney2 = 0;
				int add2 = 0;
				int night_hour, night_min, ord_hour, ord_min;

			}

			daily_wage = (hourly_wage*hour) + ((hourly_wage / 60) * minute);
			sum += daily_wage;
		}
		// ���� ����
		int holiday, holi_time, holi_min, money;
		int holi_money = 0;
		int sum1 = 0, sum2 = 0;
		cout << "���Ͽ� ���� ���� �� ��ĥ�ΰ���?";
		cin >> holiday;

		if (holiday != 0) {
			for (int i = 0; i < holiday; i++) {
				cout << "��ð� ���ϼ̳���?(�� ��)";
				cin >> holi_time >> holi_min;
				holi_money = (hourly_wage * holi_time * 1.5) + ((hourly_wage / 60) * holi_min * 1.5);
				money = (hourly_wage * holi_time) + ((hourly_wage / 60) * holi_min);
				sum1 += holi_money;
				sum2 += money;
			}
		}
		DyArr[index].salary = DyArr[index].salary - sum2 + sum1;
	}
	else if (strcmp(reply1, "n") == 0) {
		for (int j = 1; j <= day[month - 1]; j++) {
			cout << j << "�� ���� �ð�(���� ��, ��, ���� ��, ��)";
			cin >> start_hour >> start_min >> end_hour >> end_min;
			if (end_min >= start_min) {
				hour = end_hour - start_hour;
				minute = end_min - start_min;
			}
			else {
				hour = end_hour - start_hour - 1;
				minute = (end_min + 60) - start_min;
			}

			daily_wage = (hourly_wage*hour) + ((hourly_wage / 60) * minute);
			sum += daily_wage;
		}

		DyArr[index].salary = sum;
	}
	else {
		cout << "�ٽ� �Է����ּ���" << endl;
		return;
	}

	while(true) {
		printlist();
		int choice1;
		int week, week_time;
		int week_money = 0;
		int week_sum = 0;
		float share = 0;
		cout << "����";
		cin >> choice1;
		switch (choice1) {
		case 1:
			cout << "���޼���(�� 15�ð� �̻�, 4�� ���� ����)" << endl;
			
			for (int i = 0; i < 12; i++) {
				if (day[i] == 31) {
					week = 6;
				}
				else {
					week = 5;
				}
			}
			printCal(year, month);
			for (int j = 0; j < week; j++) {
				cout << j << "�ֿ� ���� �ð� : ";
				cin >> week_time;
				if (week_time >= 15 && week_time < 40) {
					share = week_time / 40;
					week_money = share * hourly_wage;
				}
				else if (week_time >= 40) {
					week_money = 8 * hourly_wage;
				}
				else {
					cout << "�� 15�ð� �̸����Ƿ� ���޼����� �����ϴ�." << endl;
				}
				week_sum += week_money;
			}
			//salary = salary + week_sum;
			DyArr[index].salary = DyArr[index].salary + week_sum;

			DyArr_t[index].SetFour(0.0865);
			for (int i = 0; i < index; i++) {
				DyArr[i].salary = DyArr[i].salary - (DyArr[i].salary * DyArr_t[i].GetFour());
			}
			break;
		case 2:
			// ����
			cout << "���� : 4�� ����(8.65%), �ҵ漼 (3.3%), ��Ÿ ����(���� �Է�)" << endl;
			int reply2;
			cout << "1. 4�� ����(8.65%)" << endl;
			cout << "2. �ҵ漼(3.3%)" << endl;
			cout << "3. ��Ÿ ����(���� �Է�)" << endl;
			cin >> reply2;
			if (reply2 == 1) {
				cout << "4�� ����(8.65%)" << endl;
				DyArr_t[index].SetFour(0.0865);
				for (int i = 0; i < index; i++) {
					DyArr[i].salary = DyArr[i].salary - (DyArr[i].salary * DyArr_t[i].GetFour());
				}
			}
			else if (reply2 == 2) {
				cout << "�ҵ漼(3.3%)" << endl;
				DyArr_t[index].SetIncome(0.065);
				for (int i = 0; i < index; i++) {
					DyArr[i].salary = DyArr[i].salary - (DyArr[i].salary * DyArr_t[i].GetIncome());
				}
			}
			else if (reply2 == 3) {
				cout << "��Ÿ ����(���� �Է�)" << endl;
				float tax;
				cout << "���� �Է� : " << endl;
				cin >> tax;
				DyArr_t[index].SetTax(tax / 100);
				for (int i = 0; i < index; i++) {
					DyArr[i].salary = DyArr[i].salary - (DyArr[i].salary * DyArr_t[i].GetTax());
				}
			}
			else {
				cout << "�ٽ� �Է����ּ���" << endl;
				return;
			}
			break;
		case 3:
			cout << "�ñ����θ� ���(���� x)" << endl;
			DyArr[index].salary = sum;
			break;
		default:
			cout << "�ٽ� �������ּ���" << endl;
			break;
		}
	}

	// ���� ���
	for (int i = 0; i < index; i++) {
		if (DyArr[i].GetId() == id) {
			DyArr[i].salary = sum;
			cout << "���� : " << DyArr[i].salary << endl;
			break;
		}
	}	
}

void printlist()
{
	cout << "-------------------------- Menu --------------------------" << endl;
	cout << "1(���޼���(�� 15�ð� �̻�))" << endl;
	cout << "2(���� : 4�� ����(8.65%), �ҵ漼 (3.3%), ��Ÿ ����(���� �Է�))" << endl;
	cout << "3(�ñ����θ� ���(���� x))" << endl;
	cout << "----------------------------------------------------------" << endl;
}

void Salary_inquire(PTJ* DyArr, int& index) {
	cout << "���� ��ȸ" << endl;
	

	int id;
	cout << "ID : ";
	cin >> id;

	for (int i = 0; i < index; i++) {
		if (DyArr[i].GetId() == id) {
			
			cout << "ID : " << DyArr[i].GetId() << " ���� : " << DyArr[i].GetWork() << " �̸�: " << DyArr[i].GetName() << " ����: " << DyArr[i].salary << endl;
		}
	}
}

void Inquire(PTJ* DyArr, int& index) {
	cout << "��ü ��ȸ" << endl;
	for (int i = 0; i < index; i++) {
		(DyArr + i)->ShowAllData();
	}
}

void exit() {
	cout << "�����մϴ�." << endl;
}