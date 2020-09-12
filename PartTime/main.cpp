#include <iostream>
#include <cstring>
#include "parttime.h"
using namespace std;
const int MAX_NAME = 50; // 이름 글자 수 제한
int year = 0, month = 0; // 년, 월
int day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // 각 월의 일 
int hourly_wage; // 시급

// 함수 선언
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
	int size = 3; // id를 만들 수 있는 개수
	PTJ* DyArr = new PTJ[size];
	PTJ_weeklyholiday* DyArr_wh = new PTJ_weeklyholiday[size];
	PTJ_tax* DyArr_t = new PTJ_tax[size];
	int index = 0;
	int choice; // 메뉴 선택을 위한 숫자

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

void printMenu() { // 메뉴 출력
	cout << "----------------------- Menu -----------------------" << endl;
	cout << "1(id 생성)" << endl;
	cout << "2(일한 정보 입력)" << endl;
	cout << "3(월급 조회)" << endl;
	cout << "4(전체 조회)" << endl;
	cout << "5(종료)" << endl;
	cout << "----------------------------------------------------" << endl;
}

void MakeId(PTJ* DyArr, int& index, int size) { // id 생성
	cout << "id 생성" << endl;
	int id;
	char workplace[MAX_NAME];
	char name[MAX_NAME];
	if (index < size) {

		cout << "id 생성을 위한 입력(ID(정수) 직장(문자) 이름(문자))";
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

void Input(PTJ* DyArr, PTJ_weeklyholiday* DyArr_wh, PTJ_tax* DyArr_t, int& index) //일한 정보 입력
{
	cout << "일한 정보 입력" << endl;

	int id, workday; // id, 일한 날(전체)
	int start_hour, start_min, end_hour, end_min; // 시작 시간, 분, 끝난 시간, 분
	int hour = 0; // 일한 시간
	int minute = 0; // 일한 분
	int daily_wage; //일급
	int sum = 0; // 월급 산출을 위한 일급 합계
	
	cout << "ID : ";
	cin >> id;
	
	DyArr[index].SetId(id);

	// id 유무 검사
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

	//정보 입력
	cout << "시급 : ";
	cin >> hourly_wage;

	cout << "일한 일은 며칠인가요? : ";
	cin >> workday;

	cout << "년과 월을 입력해주세요(년 월) : ";
	cin >> year >> month;

	if (month <= 0 || month > 12) { 
		cout << "월은 1 ~ 12까지만 입력할 수 있습니다." << endl;
		return;
	}

	printCal(year, month);

	char reply1[10];
	cout << "추가 수당을 설정하시겠습니까?(y/n) : ";
	cin >> reply1;

	int addmoney1 = 0; // 연장 수당 총 합계
	int addmoney2 = 0; // 야간 수당 총 합계
	int salary = 0; // 월급

	if (strcmp(reply1, "y") == 0) {
		for (int j = 1; j <= day[month - 1]; j++) {
			cout << j << "일 일한 시간(시작 시, 분, 끝난 시, 분) : ";
			cin >> start_hour >> start_min >> end_hour >> end_min;
			if ((start_hour < 0 || start_hour > 24) || (end_hour < 0 || end_hour > 24) || ((start_hour < 0 || start_hour > 24) && (end_hour < 0 || end_hour > 24))) {
				cout << "0부터 24까지의 숫자를 입력해 주세요" << endl;
				return;
			}
			if ((start_min < 0 || start_min >= 60) || (end_min < 0 || end_min >= 60) || ((start_min < 0 || start_min >= 60) && (end_min < 0 || end_min >= 60))) {
				cout << "0부터 60까지의 숫자를 입력해 주세요" << endl;
				return;
			}

			// 입력받은 시간을 이용하여 일한 시간 산출
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
			
			// 추가 수당

			// 연장 수당
			if (hour >= 8) {
				int add1 = 0; // 1일 연장 수당
				add1 = (((hour - 8) * hourly_wage * 1.5) + ((hourly_wage / 60) * minute * 1.5)) - ((hour - 8) * hourly_wage) + ((hourly_wage / 60) * minute);
				addmoney1 += add1;
			}
			
			// 야간 수당
			int *hour_array = new int[hour+1]; // 입력한 시간 배열
			int value; // 배열 값
			int tmp1, tmp2; // 배열 값을 입력하기 위한 임시 변수
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
						hour_array[1] = 123; //의미없는 값 대입
					}
				}
			}
			else {
				if (start_hour >= 22 && start_hour <= 6) {
					hour_array[1] = start_hour;
				}
				//cout << hour_array[0] << endl; //쓰레기 값
				
			}
			
			if ((hour_array[index] >= 22 && hour_array[index] <= 24) || (hour_array[index] >= 0 && hour_array[index] <= 6)) {
				int add2 = 0; // 1일 야간 수당
				int night_hour, night_min, ord_hour, ord_min; //야간 시간, 보통 시간
				int sum_night = 0; // 야간 수당 + 보통 수당
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
						cout << "다시 입력" << endl;
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
						cout << "다시 입력" << endl;
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
				cout << "이 시간대에는 야간 수당을 받을 수 없습니다." << endl;
			}
			daily_wage = (hourly_wage * hour) + ((hourly_wage / 60) * minute);
			cout << j << "일 기본 수당 : " << daily_wage << endl;
			sum += daily_wage;
			
		}
		
		cout << "기본 수당 : " << sum << endl;
		sum += addmoney1 + addmoney2;
		salary = sum;

		// 휴일 수당 
		int holiday, holi_time, holi_min; // 휴일에 일한 날, 휴일에 일한 시간 
		int holi_money = 0; // 1일 휴일 수당
		int sum1 = 0; // 전체 휴일 수당
		cout << "휴일에 일한 날은 총 며칠인가요? : ";
		cin >> holiday;

		if (holiday != 0) {
			for (int i = 0; i < holiday; i++) {
				cout << "몇시간 일하셨나요?(시 분) : ";
				cin >> holi_time >> holi_min;
				holi_money = (hourly_wage * holi_time * 1.5) + ((hourly_wage / 60) * holi_min * 1.5) - (hourly_wage * holi_time) + ((hourly_wage / 60) * holi_min);
				sum1 += holi_money;
			}
		}
		cout << "연장 수당 : " << addmoney1 << endl;
		cout << "야간 수당 : " << addmoney2 << endl;
		cout << "휴일 수당 : " << sum1 << endl;
		sum += sum1;
		salary = sum; 
	}
	// 추가 수당 x
	else if (strcmp(reply1, "n") == 0) {
		for (int j = 1; j <= day[month - 1]; j++) {
			cout << j << "일 일한 시간(시작 시, 분, 끝난 시, 분)";
			cin >> start_hour >> start_min >> end_hour >> end_min;
			if ((start_hour < 0 || start_hour > 24) || (end_hour < 0 || end_hour > 24) || ((start_hour < 0 || start_hour > 24) && (end_hour < 0 || end_hour > 24))) {
				cout << "0부터 24까지의 숫자를 입력해 주세요" << endl;
				return;
			}
			if ((start_min < 0 || start_min >= 60) || (end_min < 0 || end_min >= 60) || ((start_min < 0 || start_min >= 60) && (end_min < 0 || end_min >= 60))) {
				cout << "0부터 60까지의 숫자를 입력해 주세요" << endl;
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
		cout << "다시 입력해주세요" << endl;
		return;
	}

	// 주휴 수당, 세금 선택
	while(true) {
		printlist();
		int choice1; // 메뉴 선택을 위한 수
		int week, week_time; // 주휴 수당을 위한 주, 주에 일한 시간
		int week_money = 0; // 한 주의 주휴 수당
		int week_sum = 0; // 전체 주휴 수당
		float share = 0; // 주휴 수당을 구하기 위한 몫(일한 시 / 40)
		float four = 0.0865; // 4대 보험
		float s; // 월급(실수)
		float income = 0.033; // 소득세
		float tax; // 기타 세금(직접 입력)
		cout << "선택 : ";
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
			for (int j = 1; j < week; j++) {
				cout << j << "주에 일한 시간 : ";
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
					cout << "주 15시간 미만으므로 주휴수당이 없습니다." << endl;
					week_money = 0;
				}
				week_sum += week_money;
				cout << "주휴 수당 : " << week_sum << endl;
			}
			DyArr_wh[index].Set_wh(week_sum); // 주휴수당 설정

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
			// 세금
			cout << "세금 : 4대 보험(8.65%), 소득세 (3.3%), 기타 세금(직접 입력)" << endl;
			int reply2; // 메뉴 선택을 위한 수
			cout << "1. 4대 보험(8.65%)" << endl;
			cout << "2. 소득세(3.3%)" << endl;
			cout << "3. 기타 세금(직접 입력)" << endl;
			cout << "선택 : ";
			cin >> reply2;
			
			if (reply2 == 1) {
				cout << "4대 보험(8.65%)" << endl;

				s = (float)salary;

				DyArr_t[index].SetFour(four);
				DyArr[index].SetSal(s);
				s = DyArr[index].GetSal() - (DyArr[index].GetSal() * DyArr_t[index].GetFour());

				DyArr[index].SetSal(s);
				salary = (int)DyArr[index].sal;
				DyArr[index].salary = salary;
				
			}
			else if (reply2 == 2) {
				cout << "소득세(3.3%)" << endl;
				s = (float)salary;

				DyArr_t[index].SetIncome(income);
				DyArr[index].SetSal(s);
				s = DyArr[index].GetSal() - (DyArr[index].GetSal() * DyArr_t[index].GetIncome());

				DyArr[index].SetSal(s);
				salary = (int)DyArr[index].sal;
				DyArr[index].salary = salary;

			}
			else if (reply2 == 3) {
				cout << "기타 세금(직접 입력)" << endl;
				s = (float)salary;
				cout << "세금 입력 : " << endl;
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
		break;
	}

	// 월급 출력
	for (int i = 0; i < index; i++) {
		if (DyArr[i].GetId() == id) {
			DyArr[i].salary = salary;
			cout << year << "년 " << month << " 월 ";
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