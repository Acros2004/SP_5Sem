#pragma warning(disable : 4996)
#include <windows.h>
#include <iostream>

wchar_t* getWC(const char* c)
{
	wchar_t* wc = new wchar_t[strlen(c) + 1];
	mbstowcs(wc, c, strlen(c) + 1);

	return wc;
}

int main()
{
	char path[256];
	HANDLE event = CreateEvent(NULL, TRUE, FALSE, L"CloseStart");
	int answer;
	bool flagExit = true;
	while (flagExit) {
		std::cout << "1 - Close Start\n0 - Close programm" << std::endl;
		std::cin >> answer;
		switch (answer)
		{
		case 1:
			std::cout << "cin name of file" << std::endl;
			std::cin >> path;
			event = CreateEvent(NULL, TRUE, FALSE, getWC(path));
			SetEvent(event);
			break;
		case 0:
			flagExit = false;
			break;
		default:
			break;
		}
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
