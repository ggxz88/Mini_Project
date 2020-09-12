#include <iostream>
#include <cstring>
#include "parttime.h"
using namespace std;
const int MAX_NAME = 50; // �̸� ���� �� ����
int year = 0, month = 0; // ��, ��
int day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // �� ���� �� 
int hourly_wage; // �ñ�

// �Լ� ����
void printCal(int year, int month);
void printMenu();
void MakeId(PTJ* DyArr, int& index, int size);
void Input(PTJ* DyArr, PTJ_weeklyholiday* DyArr_wh, PTJ_tax* DyArr_t, int& index);
void printlist();
void Salary_inquire(PTJ* DyArr, int& index);
void Inquire(PTJ* DyArr, int& index);
void exit();
enum { MAKE = 1, INPUT, SALARY, INQUIRE, EXIT };

int main() {
	int size = 3; // id�� ���� �� �ִ� ����
	PTJ* DyArr = new PTJ[size];
	PTJ_weeklyholiday* DyArr_wh = new PTJ_weeklyholiday[size];
	PTJ_tax* DyArr_t = new PTJ_tax[size];
	int index = 0;
	int choice; // �޴� ������ ���� ����

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

void printMenu() { // �޴� ���
	cout << "----------------------- Menu -----------------------" << endl;
	cout << "1(id ����)" << endl;
	cout << "2(���� ���� �Է�)" << endl;
	cout << "3(���� ��ȸ)" << endl;
	cout << "4(��ü ��ȸ)" << endl;
	cout << "5(����)" << endl;
	cout << "----------------------------------------------------" << endl;
}

void MakeId(PTJ* DyArr, int& index, int size) { // id ����
	cout << "id ����" << endl;
	int id;
	char workplace[MAX_NAME];
	char name[MAX_NAME];
	if (index < size) {

		cout << "id ������ ���� �Է�(ID(����) ����(����) �̸�(����))";
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

void Input(PTJ* DyArr, PTJ_weeklyholiday* DyArr_wh, PTJ_tax* DyArr_t, int& index) //���� ���� �Է�
{
	cout << "���� ���� �Է�" << endl;

	int id, workday; // id, ���� ��(��ü)
	int start_hour, start_min, end_hour, end_min; // ���� �ð�, ��, ���� �ð�, ��
	int hour = 0; // ���� �ð�
	int minute = 0; // ���� ��
	int daily_wage; //�ϱ�
	int sum = 0; // ���� ������ ���� �ϱ� �հ�
	
	cout << "ID : ";
	cin >> id;
	
	DyArr[index].SetId(id);

	// id ���� �˻�
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

	//���� �Է�
	cout << "�ñ� : ";
	cin >> hourly_wage;

	cout << "���� ���� ��ĥ�ΰ���? : ";
	cin >> workday;

	cout << "��� ���� �Է����ּ���(�� ��) : ";
	cin >> year >> month;

	if (month <= 0 || month > 12) { 
		cout << "���� 1 ~ 12������ �Է��� �� �ֽ��ϴ�." << endl;
		return;
	}

	printCal(year, month);

	char reply1[10];
	cout << "�߰� ������ �����Ͻðڽ��ϱ�?(y/n) : ";
	cin >> reply1;

	int addmoney1 = 0; // ���� ���� �� �հ�
	int addmoney2 = 0; // �߰� ���� �� �հ�
	int salary = 0; // ����

	if (strcmp(reply1, "y") == 0) {
		for (int j = 1; j <= day[month - 1]; j++) {
			cout << j << "�� ���� �ð�(���� ��, ��, ���� ��, ��) : ";
			cin >> start_hour >> start_min >> end_hour >> end_min;
			if ((start_hour < 0 || start_hour > 24) || (end_hour < 0 || end_hour > 24) || ((start_hour < 0 || start_hour > 24) && (end_hour < 0 || end_hour > 24))) {
				cout << "0���� 24������ ���ڸ� �Է��� �ּ���" << endl;
				return;
			}
			if ((start_min < 0 || start_min >= 60) || (end_min < 0 || end_min >= 60) || ((start_min < 0 || start_min >= 60) && (end_min < 0 || end_min >= 60))) {
				cout << "0���� 60������ ���ڸ� �Է��� �ּ���" << endl;
				return;
			}

			// �Է¹��� �ð��� �̿��Ͽ� ���� �ð� ����
			if (start_hour > end_hour) {
				hour = (end_hour + 24) - start_hour;
			}
			else if (start_hour < end_hour) {
				hour = end_hour - start_hour;
			}
			else {
				hour = 0;
			}
			if (end_min > start_min) {
				minute = end_min - start_min;
			}
			else if (start_min > end_min) {
				hour = hour - 1;
				minute = (end_min + 60) - start_min;
			}
			else {
				minute = 0;
			}
			
			// �߰� ����

			// ���� ����
			if (hour >= 8) {
				int add1 = 0; // 1�� ���� ����
				add1 = (((hour - 8) * hourly_wage * 1.5) + ((hourly_wage / 60) * minute * 1.5)) - ((hour - 8) * hourly_wage) + ((hourly_wage / 60) * minute);
				addmoney1 += add1;
			}
			
			// �߰� ����
			int *hour_array = new int[hour+1]; // �Է��� �ð� �迭
			int value; // �迭 ��
			int tmp1, tmp2; // �迭 ���� �Է��ϱ� ���� �ӽ� ����
			tmp1 = start_hour;
			tmp2 = end_hour;
			if (start_hour > end_hour) {
				for (int i = 0; i < 24 - start_hour + 1; i++) {
					value = tmp1;
					hour_array[i] = value;
					tmp1 += 1;
				}
				for (int i = (24 - start_hour + 1); i < end_hour + (24 - start_hour + 1); i++) {
					value = tmp2;
					hour_array[i] = value;
					tmp2 -= 1;
				}
			}
			else if (start_hour < end_hour) {
				int j = end_hour - start_hour + 1;
				for (int i = 1; i < j + 1; i++) {
					value = tmp2;
					hour_array[i] = value;
					tmp2 -= 1;
					if ((end_min == 0) && (end_hour == 22)) {
						hour_array[1] = 123; //�ǹ̾��� �� ����
					}
				}
			}
			else {
				if (start_hour >= 22 && start_hour <= 6) {
					hour_array[1] = start_hour;
				}
				//cout << hour_array[0] << endl; //������ ��
				
			}
			
			if ((hour_array[index] >= 22 && hour_array[index] <= 24) || (hour_array[index] >= 0 && hour_array[index] <= 6)) {
				int add2 = 0; // 1�� �߰� ����
				int night_hour, night_min, ord_hour, ord_min; //�߰� �ð�, ���� �ð�
				int sum_night = 0; // �߰� ���� + ���� ����
				night_hour = 0;
				if (start_hour > end_hour) {
					ord_hour = (22 - start_hour) + (end_hour - 6);
					night_hour = (24 + end_hour) - start_hour - ord_hour;
					
					if ((start_hour < 22) && (end_hour >= 6)) {
						ord_min = (60 - start_min) + end_min;
						if (ord_min >= 60) {
							ord_min = ord_min - 60;
							ord_hour = ord_hour + 1;
						}
						ord_hour = ord_hour - 1;
						night_min = 0;
						if ((start_min == 0) || (end_min == 0) || ((start_min == 0) && (end_hour == 0))) {
							ord_min = 0;
							night_min = 0;
						}
					}
					else if ((start_hour >= 22) && (end_hour <= 6)) {
						night_min = 60 - start_min;
						if (end_hour == 6) {
							ord_hour = 0;
							ord_min = end_min;
						}
						else {
							ord_min = 0;
							ord_hour = 0;
						}
						night_hour = night_hour - 1;
						if ((start_min == 0) || (end_min == 0) || ((start_min == 0) && (end_hour == 0))) {
							night_min = 0;
							night_hour = (24 + end_hour) - start_hour - ord_hour;
						}
						
					}
					else if (start_hour >= 22 && end_hour >= 6) {
						ord_min = end_min;
						night_min = 60 - start_min;
						night_hour = night_hour - 1;
						if ((start_min == 0) || (end_min == 0) || ((start_min == 0) && (end_hour == 0))) {
							ord_min = 0;
							night_min = 0;
							night_hour = (24 + end_hour) - start_hour - ord_hour;
						}
					}
					else {
						cout << "�ٽ� �Է�" << endl;
					}
					
				}
				else if (start_hour < end_hour) {
					night_hour = end_hour - 22;
					ord_hour = 22 - start_hour;

					if (start_hour < 22 && start_hour >= 0) {
						night_min = end_min;
						ord_min = 60 - start_min;
						ord_hour = ord_hour - 1;
						if ((start_min == 0) || (end_min == 0) || ((start_min == 0) && (end_hour == 0))) {
							ord_min = 0;
							night_min = 0;
						}
					}
					else {
						cout << "�ٽ� �Է�" << endl;
					}
				}
				else {
					ord_hour = 0;
					night_hour = 0;
					night_min = minute;
					ord_min = 0;
				}
				sum_night = ((night_hour * 1.5 * hourly_wage) + ((hourly_wage / 60) * night_min * 1.5)) + ((ord_hour * hourly_wage) + ((hourly_wage / 60) * ord_min));
				add2 = sum_night - ((hourly_wage * hour) + ((hourly_wage / 60) * minute));
				addmoney2 += sum_night;
			}
			else {
				cout << "�� �ð��뿡�� �߰� ������ ���� �� �����ϴ�." << endl;
			}
			daily_wage = (hourly_wage * hour) + ((hourly_wage / 60) * minute);
			cout << j << "�� �⺻ ���� : " << daily_wage << endl;
			sum += daily_wage;
			
		}
		
		cout << "�⺻ ���� : " << sum << endl;
		sum += addmoney1 + addmoney2;
		salary = sum;

		// ���� ���� 
		int holiday, holi_time, holi_min; // ���Ͽ� ���� ��, ���Ͽ� ���� �ð� 
		int holi_money = 0; // 1�� ���� ����
		int sum1 = 0; // ��ü ���� ����
		cout << "���Ͽ� ���� ���� �� ��ĥ�ΰ���? : ";
		cin >> holiday;

		if (holiday != 0) {
			for (int i = 0; i < holiday; i++) {
				cout << "��ð� ���ϼ̳���?(�� ��) : ";
				cin >> holi_time >> holi_min;
				holi_money = (hourly_wage * holi_time * 1.5) + ((hourly_wage / 60) * holi_min * 1.5) - (hourly_wage * holi_time) + ((hourly_wage / 60) * holi_min);
				sum1 += holi_money;
			}
		}
		cout << "���� ���� : " << addmoney1 << endl;
		cout << "�߰� ���� : " << addmoney2 << endl;
		cout << "���� ���� : " << sum1 << endl;
		sum += sum1;
		salary = sum; 
	}
	// �߰� ���� x
	else if (strcmp(reply1, "n") == 0) {
		for (int j = 1; j <= day[month - 1]; j++) {
			cout << j << "�� ���� �ð�(���� ��, ��, ���� ��, ��)";
			cin >> start_hour >> start_min >> end_hour >> end_min;
			if ((start_hour < 0 || start_hour > 24) || (end_hour < 0 || end_hour > 24) || ((start_hour < 0 || start_hour > 24) && (end_hour < 0 || end_hour > 24))) {
				cout << "0���� 24������ ���ڸ� �Է��� �ּ���" << endl;
				return;
			}
			if ((start_min < 0 || start_min >= 60) || (end_min < 0 || end_min >= 60) || ((start_min < 0 || start_min >= 60) && (end_min < 0 || end_min >= 60))) {
				cout << "0���� 60������ ���ڸ� �Է��� �ּ���" << endl;
				return;
			}
			if (start_hour > end_hour) {
				hour = (end_hour + 24) - start_hour;
			}
			else if (start_hour < end_hour){
				hour = end_hour - start_hour;
			}
			else {
				hour = 0;
			}
			if (end_min > start_min) {
				minute = end_min - start_min;
			}
			else if (start_min > end_min){
				hour = hour - 1;
				minute = (end_min + 60) - start_min;
			}
			else {
				minute = 0;
			}

			daily_wage = (hourly_wage*hour) + ((hourly_wage / 60) * minute);
			sum += daily_wage;
		}

		salary = sum;
		cout << salary << endl;
	}
	else {
		cout << "�ٽ� �Է����ּ���" << endl;
		return;
	}

	// ���� ����, ���� ����
	while(true) {
		printlist();
		int choice1; // �޴� ������ ���� ��
		int week, week_time; // ���� ������ ���� ��, �ֿ� ���� �ð�
		int week_money = 0; // �� ���� ���� ����
		int week_sum = 0; // ��ü ���� ����
		float share = 0; // ���� ������ ���ϱ� ���� ��(���� �� / 40)
		float four = 0.0865; // 4�� ����
		float s; // ����(�Ǽ�)
		float income = 0.033; // �ҵ漼
		float tax; // ��Ÿ ����(���� �Է�)
		cout << "���� : ";
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
			for (int j = 1; j < week; j++) {
				cout << j << "�ֿ� ���� �ð� : ";
				cin >> week_time;
				if (week_time >= 15 && week_time < 40) {
					share = week_time / 40.0;
					cout << share << endl;
					week_money = share * hourly_wage;
				}
				else if (week_time >= 40) {
					week_money = 8 * hourly_wage;
				}
				else {
					cout << "�� 15�ð� �̸����Ƿ� ���޼����� �����ϴ�." << endl;
					week_money = 0;
				}
				week_sum += week_money;
				cout << "���� ���� : " << week_sum << endl;
			}
			DyArr_wh[index].Set_wh(week_sum); // ���޼��� ����

			salary += DyArr_wh[index].weekly_holidaypay;
			cout << salary << endl;
			
			s = (float)salary;

			DyArr_t[index].SetFour(four);
			DyArr[index].SetSal(s);
			s = DyArr[index].GetSal() - (DyArr[index].GetSal() * DyArr_t[index].GetFour());
			cout << s << endl;

			DyArr[index].SetSal(s);
			salary = (int)DyArr[index].sal;
			DyArr[index].salary = salary;

			break;
		case 2:
			// ����
			cout << "���� : 4�� ����(8.65%), �ҵ漼 (3.3%), ��Ÿ ����(���� �Է�)" << endl;
			int reply2; // �޴� ������ ���� ��
			cout << "1. 4�� ����(8.65%)" << endl;
			cout << "2. �ҵ漼(3.3%)" << endl;
			cout << "3. ��Ÿ ����(���� �Է�)" << endl;
			cout << "���� : ";
			cin >> reply2;
			
			if (reply2 == 1) {
				cout << "4�� ����(8.65%)" << endl;

				s = (float)salary;

				DyArr_t[index].SetFour(four);
				DyArr[index].SetSal(s);
				s = DyArr[index].GetSal() - (DyArr[index].GetSal() * DyArr_t[index].GetFour());

				DyArr[index].SetSal(s);
				salary = (int)DyArr[index].sal;
				DyArr[index].salary = salary;
				
			}
			else if (reply2 == 2) {
				cout << "�ҵ漼(3.3%)" << endl;
				s = (float)salary;

				DyArr_t[index].SetIncome(income);
				DyArr[index].SetSal(s);
				s = DyArr[index].GetSal() - (DyArr[index].GetSal() * DyArr_t[index].GetIncome());

				DyArr[index].SetSal(s);
				salary = (int)DyArr[index].sal;
				DyArr[index].salary = salary;

			}
			else if (reply2 == 3) {
				cout << "��Ÿ ����(���� �Է�)" << endl;
				s = (float)salary;
				cout << "���� �Է� : " << endl;
				cin >> tax;
				tax = tax / 100;

				DyArr_t[index].SetTax(tax);
				DyArr[index].SetSal(s);
				s = DyArr[index].GetSal() - (DyArr[index].GetSal() * DyArr_t[index].GetTax());

				DyArr[index].SetSal(s);
				salary = (int)DyArr[index].sal;
				DyArr[index].salary = salary;

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
		break;
	}

	// ���� ���
	for (int i = 0; i < index; i++) {
		if (DyArr[i].GetId() == id) {
			DyArr[i].salary = salary;
			cout << year << "�� " << month << " �� ";
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