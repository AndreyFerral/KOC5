#include <windows.h>
#include <process.h>
#include <iostream>
using namespace std;

void Semaphore(void*) {
	cout << "Проверить состояние семафора\n";
	cout.flush();

	HANDLE sem = CreateSemaphore(NULL, // атрибут доступа
		3, // инициализированное начальное состояние счетчика
		3, // максимальное количество обращений
		L"nt5bbsem"); // имя объекта

	WaitForSingleObject(sem, // Описатель объекта ядра, сигнальное состояние которого нас интересует 
		INFINITE); //Таймаут, по истечению которого прервать ожидание 

	cout << "Получен доступ к семафору\n";
	cout.flush();

	MessageBox(NULL, L"Получен доступ к семафору", L"Semaphore", NULL); // вывод окна сообщений

	// Добавляет некоторое значение (обычно 1) к счетчику семафора, делая его доступным для большего количества потоков
	ReleaseSemaphore(sem, // хенд семафора
		1, // на сколько изменять счетчик
		NULL); // предыдущее значение

	CloseHandle(sem);
}

void main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HANDLE hand;

	// Создается объект событие
	HANDLE ev = CreateEvent(NULL, // атрибут защиты
		TRUE, // тип сброса TRUE - ручной
		FALSE, // начальное состояние FALSE Несигнальное
		L"nt5bbevent"); // имя обьекта

	if (argc == 1) // если ключей нет
	{
		// создаем поток, в который помещаем работу семафора
		hand = (HANDLE)_beginthread(Semaphore, // адрес функции задачи
			NULL, // начальный размер стека в байтах
			NULL); // параметры для задачи

		cout << "Подождите событие!\n";
		cout.flush();

		WaitForSingleObject(ev, // Описатель объекта ядра, сигнальное состояние которого нас интересует 
			INFINITE); //Таймаут, по истечению которого прервать ожидание 

		cout << "Событие произошло!\n";
		cout.flush();
	}
	if (strcmp(argv[1], "/R") == 0) // если ключ == "/R"
	{
		cout << "Установка события\n";
		//SetEvent() меняет состояние на сигнальное
		SetEvent(ev); // дескриптор события
	}
	CloseHandle(ev);
}
