#include <Windows.h>
#include <process.h> // ��� ��������� ������� ������
#include <iostream>
#include <string>
#include "Header.h"
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    LARGE_INTEGER Create[3], Exit[3], kernel[3], user[3]; // ��������� ���������� �������  
    double totalTime[3]; // ���������� ��� ������� ������� ������� �������
    string totalTimeStr[3], handId[3], handPriority[3], userTime[3]; // �������������� �������
    HANDLE hand[3]; // ���������� �������
    // ������������ ��������� � �������
    double FirstParametr = 13;
    double SecondParametr = 1.3;
    double ThirdParametr = -5;
    // �������� �������
    hand[0] = (HANDLE)_beginthreadex(NULL, // ��������� �� ���������� ������
        0, // ��������� ������ �����
        Func1, // ��� �������
        &FirstParametr, // ������������ ��������
        0, // ��������� ��������
        NULL); // ����� ��������� ������
    hand[1] = (HANDLE)_beginthreadex(NULL, 0, Func2, &SecondParametr, 0, NULL);
    hand[2] = (HANDLE)_beginthreadex(NULL, 0, Func3, &ThirdParametr, 0, NULL);
    WaitForMultipleObjects( // ������� ���������� �������
        3, // ������� ��� ������
        hand, // ����� �������
        true, // ��������� ���������������� ����� �� ��� ���, ���� ��� ������� ���� �� �������� � ���������� ���������
        INFINITE); // ������� ��������� ��������� �������
    system("cls");
    for (int i = 0; i < 3; i++) {
        // �������� ��������� �������������� �������
        GetThreadTimes(hand[i], (FILETIME*)&Create[i].u, (FILETIME*)&Exit[i].u, (FILETIME*)&kernel[i].u, (FILETIME*)&user[i].u);
        handPriority[i] = to_string(GetThreadPriority(hand[i])); // ��������� ������
        handId[i] = to_string(GetThreadId(hand[i])); // ������������� ������
        CloseHandle(hand[i]); // ������� �������� ���������� �������
        totalTime[i] = Exit[i].QuadPart - Create[i].QuadPart; // �������� ������ ����� ������ ������
        totalTimeStr[i] = to_string(totalTime[i] / 1e7); // ������ ����� ������ ������
        userTime[i] = to_string(user[i].QuadPart / 1e7); // ����� ���������� ������������ ���� ������
    }
    // ����� ������������� �������
    for (int i = 0; i < 3; i++) {
        cout << "\n�������������� ������ " << i + 1 << ":" << endl;
        cout << "��������� ������: " << handPriority[i] << endl;
        cout << "������������� ������: " << handId[i] << endl;
        cout << "����������������� ������ ������: " << totalTimeStr[i] << " ���" << endl;
        cout << "����� ���������� ������������ ���� ������: " << userTime[i] << " ���" << endl;
    }
    system("pause");
}
