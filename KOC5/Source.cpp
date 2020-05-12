#include <Windows.h>
#include <process.h> // для измерения времени потока
#include <iostream>
#include <string>
#include "Header.h"
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    LARGE_INTEGER Create[3], Exit[3], kernel[3], user[3]; // временные показалели потоков  
    double totalTime[3]; // переменная для расчета полного времени потоков
    string totalTimeStr[3], handId[3], handPriority[3], userTime[3]; // характеристики потоков
    HANDLE hand[3]; // дескриптор потоков
    // передаваемые параметры в функции
    double FirstParametr = 13;
    double SecondParametr = 1.3;
    double ThirdParametr = -5;
    // создание потоков
    hand[0] = (HANDLE)_beginthreadex(NULL, // указатель на дескриптор защиты
        0, // начальный размер стека
        Func1, // имя функции
        &FirstParametr, // передаваемый параметр
        0, // параметры создания
        NULL); // адрес созданной задачи
    hand[1] = (HANDLE)_beginthreadex(NULL, 0, Func2, &SecondParametr, 0, NULL);
    hand[2] = (HANDLE)_beginthreadex(NULL, 0, Func3, &ThirdParametr, 0, NULL);
    WaitForMultipleObjects( // ожидаем завершение потоков
        3, // ожидаем три потока
        hand, // хендл объекта
        true, // позволяет приостанавливать поток до тех пор, пока все объекты ядра не перейдут в сигнальное состояние
        INFINITE); // ожидаем изменения состояния объекта
    system("cls");
    for (int i = 0; i < 3; i++) {
        // получаем временные характеристики потоков
        GetThreadTimes(hand[i], (FILETIME*)&Create[i].u, (FILETIME*)&Exit[i].u, (FILETIME*)&kernel[i].u, (FILETIME*)&user[i].u);
        handPriority[i] = to_string(GetThreadPriority(hand[i])); // приоритет потока
        handId[i] = to_string(GetThreadId(hand[i])); // идентификатор потока
        CloseHandle(hand[i]); // закрыть открытый дескриптор объекта
        totalTime[i] = Exit[i].QuadPart - Create[i].QuadPart; // получаем полное время работы потока
        totalTimeStr[i] = to_string(totalTime[i] / 1e7); // полное время работы потока
        userTime[i] = to_string(user[i].QuadPart / 1e7); // время выполнения собственного кода потока
    }
    // вывод характеристик потоков
    for (int i = 0; i < 3; i++) {
        cout << "\nХарактеристики потока " << i + 1 << ":" << endl;
        cout << "Приоритет потока: " << handPriority[i] << endl;
        cout << "Идентификатор потока: " << handId[i] << endl;
        cout << "Продолжительность работы потока: " << totalTimeStr[i] << " сек" << endl;
        cout << "Время выполнения собственного кода потока: " << userTime[i] << " сек" << endl;
    }
    system("pause");
}
