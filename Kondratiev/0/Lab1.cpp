//#include "pch.h"
#include <stdio.h>

double toDec(char* number, int* system);
int charToDec(char* number);				//ex.: 7->7, a->10, d->13
char decToChar(int* number);				//ex.: 7->7, 10->a, 13->d
void fromDec(double* number, int* system, char* res);
bool goodInput(char* s, int* system1, int* system2);


int main()
{
	char s[57]; int a,b; double res; //s - строка ввода-вывода, a,b - системы счисления для ввода и вывода соотв.
	scanf_s("%d %d", &a, &b);
	scanf_s("%s", &s, 14);
	
	if (goodInput(&s[0],&a,&b)) {
		res = toDec(&s[0], &a);
		fromDec(&res, &b, &s[0]);
		printf_s("%s", &s, 14);
	}else{ printf_s("%s", "Bad input"); }

	return(0);
}

bool goodInput(char* s,int* system1, int* system2) {
	int res = 0, pointCounter = 0;
	if (*s != '\0') {
		if (*s == '.') res++;
		if (*system1 < 2 || *system2 < 2 || *system1>16 || *system2>16) res++;
		for (int i = 0; i < 13; i++)
			if (*(s + i) == '.') { pointCounter++; }
			else if (*(s + i) == '\0') { if (*(s + i - 1) == '.') res++; break; }
			else if (*(s + i) < '0' || *(s + i) > '9' && *(s + i) < 'A' || *(s + i) > 'F' && *(s + i) < 'a' || *(s + i) > 'f'
				|| charToDec(s + i) >= *system1) {
				res++;
				break;
			}
	}
	if (pointCounter > 1) res++;
	return !res;
}

double toDec(char* number, int* system) {
	double res = 0; int length; double temp = 1;

	for (length = 0; *(number+length) != '\0'; length++) {};	//опред. длины строки
	int pointIndex = length;

	for (int i = 0; i != length; i++) {							//опред. индекса точки
		if (*(number+i) == '.') pointIndex = i;
	}

	for (int i = pointIndex - 1; i != -1; i--) {				//перевод целой части number
		res += (charToDec(number+i)*temp);
		temp *= *system;
	}

	temp = *system;
	for (int i = pointIndex + 1; i < length; i++) {				// перевод дробной части number
		res =res+ ((double)charToDec(number+i) / temp);
		temp *= *system;
	}

	return res;
}

int charToDec(char* number) {
	int res;
	if (*number <= '9') { res = *number - '0'; }
	else if (*number >= 'a') { res = *number + 10 - 'a'; }
	else res = *number + 10 - 'A';
	return res;
}

char decToChar(int* number) {
	char res;
	if (*number < 10) { res = '0' + *number; }
	else res = 'a' + *number - 10;
	return res;
}

void fromDec (double* number, int* system, char* res) {
	for (int i = 0; *(res + i) != '\0'; i++) { *(res + i) = '\0'; }
	unsigned long long wholePart = *number; int leftRes[48]; int currentIndex = 0;
	
	int i = 0;										//перевод целой части
	if (!wholePart) { i++; leftRes[0] = 0; }
	while (wholePart != 0) {						//коэффициенты при степенях system записываются в leftRes[] | индекс = степень
		leftRes[i++] = wholePart % *system;
		wholePart = wholePart / *system; 
	}
	i--;
	while (i != -1) {							//запись коэфф. в строку res - от наибольшей степени к наименьшей
		*(res + currentIndex++) = decToChar(&leftRes[i--]);
	}
	
	int pointIndex = currentIndex;
	*(res + currentIndex++) = '.';				//точка

	*number -= (double)((int)*number);   
	int temp; i = 0;
	while (currentIndex < 48 && i < 12) {				//перевод дробной части
		*number *= *system;
		temp = *number;  
		*(res + currentIndex++) = decToChar(&temp);
		*number -= temp;
		i++;
	}

	i = 56;							//удаление ненужных символов из правой части строки
	while (i >= pointIndex && (*(res + i) < '0' || *(res + i) > '9' && *(res + i) < 'a' || *(res + i) > 'f')) {
		*(res + i--) = '\0';
	}
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
