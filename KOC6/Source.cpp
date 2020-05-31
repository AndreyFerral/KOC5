#include <windows.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) // передаваемые параметры для реализации ключа
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ofstream out("C:\\Users\\Андрей\\source\\repos\\KOC5\\Debug\\id.txt", // путь к файлу
		ios::app); // открытие потока для записи в конец файла
	if (out.is_open())
	{
		out << GetCurrentProcessId() << endl; // записываем в id.txt id процесса
	}
	out.close(); // закрываем текстовый файл
	
	// проверка - есть ключ или нет
	if (argv[1] != NULL) {
		// если ключ == "/R"
		if (strcmp(argv[1], "/R") == 0)
		{
			int i;
			ifstream myfile("C:\\Users\\Андрей\\source\\repos\\KOC5\\Debug\\id.txt", ios::app);
			string line;
			int last;

			if (myfile.is_open())
			{
				last = GetCurrentProcessId(); // присваиваем переменной last процесс id
				while (!myfile.eof()) // пока не конец файла 
				{
					getline(myfile, line); // присваиваем line строчку из файла txt
					i = stoi(line); // конвертируем значение string line в int
					if (i == last) {  // если i равна последнему процессу id, то очистить файл txt
						cout << "Файл очищен. Процессы закрыты" << endl;
						ofstream fin("C:\\Users\\Андрей\\source\\repos\\KOC5\\Debug\\id.txt", ios::trunc); }
					TerminateProcess(( // уничтожить процесс
						OpenProcess(PROCESS_ALL_ACCESS, TRUE, i)), // получаем хэндл процесса с помощью его id
						NULL); 
				}
				myfile.close(); // закрываем текстовый файл
			}
		}
	}

	// Создает новый семафор или открывает существующий 
	HANDLE sem = CreateSemaphore(NULL, // // атрибут доступа
		3, // инициализированное начальное состояние счетчика
		3, // максимальное количество обращений
		L"nt5bbsem"); // имя объекта

	cout << "Проверить состояние семафора\n";
	cout.flush();

	WaitForSingleObject(sem, // //Описатель объекта ядра, сигнальное состояние которого нас интересует 
		INFINITE); //Таймаут, по истечению которого прервать ожидание 

	cout << "Получен доступ к семафору\n";
	cout.flush();
	MessageBox(NULL, L"Получен доступ к семафору", L"Semaphore", MB_OK);

	// Добавляет некоторое значение (обычно 1) к счетчику семафора, делая его доступным для большего количества потоков
	ReleaseSemaphore(sem, // хенд семафора
		1, // на сколько изменять счетчик
		NULL); // предыдущее значение

	CloseHandle(sem);
}
