#include <iostream>
#include <cstring>
#include "parttime.h"
using namespace std;
const int MAX_NAME = 50;
int year = 0, month = 0;
int day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int hourly_wage;

// 함수 선언
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
		cout << "선택: ";
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
			cout << "다시 선택해주세요." << endl;
			break;
		}
	}

	return 0;
}

// 함수 정의
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

	cout << "<" << year << "년" << month << "월" << ">" << endl;
	cout << "일\t월\t화\t수\t목\t금\t토" << endl;

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
	cout << "1(id 생성)" << endl;
	cout << "2(일한 정보 입력)" << endl;
	cout << "3(월급 조회)" << endl;
	cout << "4(전체 조회)" << endl;
	cout << "5(종료)" << endl;
	cout << "----------------------------------------------------" << endl;
}

void MakeId(PTJ* DyArr, int& index, int size) {
	cout << "생성" << endl;
	int id;
	char workplace[MAX_NAME];
	char name[MAX_NAME];
	if (index < size) {

		cout << "id 생성을 위한 입력(ID 직장 이름)";
		cin >> id >> workplace >> name;
		

		for (int i = 0; i < index; i++) {
			if (id == DyArr[i].GetId()) {
				cout << "중복된 id가 있습니다. 다시 입력해주세요" << endl;
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

		cout << "ID : " << id << " 직장 : " << workplace << " 이름 : " << name << endl;
		
	}
	else {
		cout << "최대 " << size << "개를 만들 수 있습니다." << endl;
	}
}

void Input(PTJ* DyArr, PTJ_weeklyholiday* DyArr_wh, PTJ_tax* DyArr_t/*, PTJ_add* DyArr_a*/, int& index)
{
	cout << "일한 정보 입력" << endl;

	int id, workday;
	int start_hour, start_min, end_hour, end_min; // 시작 시간, 분, 끝난 시간, 분
	int hour = 0; // 일한 시간
	int minute = 0; // 일한 분
	int daily_wage; //일급
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
		cout << "존재하지 않는 ID입니다." << endl;
		return;
	}
	
	cout << "시급 : ";
	cin >> hourly_wage;

	cout << "일한 일은 며칠인가요?";
	cin >> workday;

	cout << "년과 월을 입력해주세요(년 월)";
	cin >> year >> month;
	printCal(year, month);

	char reply1[10];
	cout << "추가 수당을 설정하시겠습니까?(y/n)";
	cin >> reply1;

	if (strcmp(reply1, "y") == 0) {
		for (int j = 1; j <= day[month - 1]; j++) {
			cout << j << "일 일한 시간(시작 시, 분, 끝난 시, 분)";
			cin >> start_hour >> start_min >> end_hour >> end_min;
			if (end_min >= start_min) {
				hour = end_hour - start_hour;
				minute = end_min - start_min;
			}
			else {
				hour = end_hour - start_hour - 1;
				minute = (end_min + 60) - start_min;
			}

			// 연장 수당
			if (hour >= 8) {
				int addmoney1 = 0;
				int add1 = 0;
				add1 = ((hour - 8) * hourly_wage * 1.5) + ((hourly_wage / 60) * minute * 1.5);
				addmoney1 += add1;
			}
			// 야간 수당
			if (end_hour >= 22 || end_hour <= 5) {
				int addmoney2 = 0;
				int add2 = 0;
				int night_hour, night_min, ord_hour, ord_min;

			}

			daily_wage = (hourly_wage*hour) + ((hourly_wage / 60) * minute);
			sum += daily_wage;
		}
		// 휴일 수당
		int holiday, holi_time, holi_min, money;
		int holi_money = 0;
		int sum1 = 0, sum2 = 0;
		cout << "휴일에 일한 날은 총 며칠인가요?";
		cin >> holiday;

		if (holiday != 0) {
			for (int i = 0; i < holiday; i++) {
				cout << "몇시간 일하셨나요?(시 분)";
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
			cout << j << "일 일한 시간(시작 시, 분, 끝난 시, 분)";
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
		cout << "다시 입력해주세요" << endl;
		return;
	}

	while(true) {
		printlist();
		int choice1;
		int week, week_time;
		int week_money = 0;
		int week_sum = 0;
		float share = 0;
		cout << "선택";
		cin >> choice1;
		switch (choice1) {
		case 1:
			cout << "주휴수당(주 15시간 이상, 4대 보험 적용)" << endl;
			
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
				cout << j << "주에 일한 시간 : ";
				cin >> week_time;
				if (week_time >= 15 && week_time < 40) {
					share = week_time / 40;
					week_money = share * hourly_wage;
				}
				else if (week_time >= 40) {
					week_money = 8 * hourly_wage;
				}
				else {
					cout << "주 15시간 미만으므로 주휴수당이 없습니다." << endl;
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
			// 세금
			cout << "세금 : 4대 보험(8.65%), 소득세 (3.3%), 기타 세금(직접 입력)" << endl;
			int reply2;
			cout << "1. 4대 보험(8.65%)" << endl;
			cout << "2. 소득세(3.3%)" << endl;
			cout << "3. 기타 세금(직접 입력)" << endl;
			cin >> reply2;
			if (reply2 == 1) {
				cout << "4대 보험(8.65%)" << endl;
				DyArr_t[index].SetFour(0.0865);
				for (int i = 0; i < index; i++) {
					DyArr[i].salary = DyArr[i].salary - (DyArr[i].salary * DyArr_t[i].GetFour());
				}
			}
			else if (reply2 == 2) {
				cout << "소득세(3.3%)" << endl;
				DyArr_t[index].SetIncome(0.065);
				for (int i = 0; i < index; i++) {
					DyArr[i].salary = DyArr[i].salary - (DyArr[i].salary * DyArr_t[i].GetIncome());
				}
			}
			else if (reply2 == 3) {
				cout << "기타 세금(직접 입력)" << endl;
				float tax;
				cout << "세금 입력 : " << endl;
				cin >> tax;
				DyArr_t[index].SetTax(tax / 100);
				for (int i = 0; i < index; i++) {
					DyArr[i].salary = DyArr[i].salary - (DyArr[i].salary * DyArr_t[i].GetTax());
				}
			}
			else {
				cout << "다시 입력해주세요" << endl;
				return;
			}
			break;
		case 3:
			cout << "시급으로만 계산(세금 x)" << endl;
			DyArr[index].salary = sum;
			break;
		default:
			cout << "다시 선택해주세요" << endl;
			break;
		}
	}

	// 월급 출력
	for (int i = 0; i < index; i++) {
		if (DyArr[i].GetId() == id) {
			DyArr[i].salary = sum;
			cout << "월급 : " << DyArr[i].salary << endl;
			break;
		}
	}	
}

void printlist()
{
	cout << "-------------------------- Menu --------------------------" << endl;
	cout << "1(주휴수당(주 15시간 이상))" << endl;
	cout << "2(세금 : 4대 보험(8.65%), 소득세 (3.3%), 기타 세금(직접 입력))" << endl;
	cout << "3(시급으로만 계산(세금 x))" << endl;
	cout << "----------------------------------------------------------" << endl;
}

void Salary_inquire(PTJ* DyArr, int& index) {
	cout << "월급 조회" << endl;
	

	int id;
	cout << "ID : ";
	cin >> id;

	for (int i = 0; i < index; i++) {
		if (DyArr[i].GetId() == id) {
			
			cout << "ID : " << DyArr[i].GetId() << " 직장 : " << DyArr[i].GetWork() << " 이름: " << DyArr[i].GetName() << " 월급: " << DyArr[i].salary << endl;
		}
	}
}

void Inquire(PTJ* DyArr, int& index) {
	cout << "전체 조회" << endl;
	for (int i = 0; i < index; i++) {
		(DyArr + i)->ShowAllData();
	}
}

void exit() {
	cout << "종료합니다." << endl;
}