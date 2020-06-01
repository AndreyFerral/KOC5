#include <windows.h>
#include <process.h>
#include <iostream>
using namespace std;

void Semaphore(void*) {
	cout << "��������� ��������� ��������\n";
	cout.flush();

	HANDLE sem = CreateSemaphore(NULL, // ������� �������
		3, // ������������������ ��������� ��������� ��������
		3, // ������������ ���������� ���������
		L"nt5bbsem"); // ��� �������

	WaitForSingleObject(sem, // ��������� ������� ����, ���������� ��������� �������� ��� ���������� 
		INFINITE); //�������, �� ��������� �������� �������� �������� 

	cout << "������� ������ � ��������\n";
	cout.flush();

	MessageBox(NULL, L"������� ������ � ��������", L"Semaphore", NULL); // ����� ���� ���������

	// ��������� ��������� �������� (������ 1) � �������� ��������, ����� ��� ��������� ��� �������� ���������� �������
	ReleaseSemaphore(sem, // ���� ��������
		1, // �� ������� �������� �������
		NULL); // ���������� ��������

	CloseHandle(sem);
}

void main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HANDLE hand;

	// ��������� ������ �������
	HANDLE ev = CreateEvent(NULL, // ������� ������
		TRUE, // ��� ������ TRUE - ������
		FALSE, // ��������� ��������� FALSE ������������
		L"nt5bbevent"); // ��� �������

	if (argc == 1) // ���� ������ ���
	{
		// ������� �����, � ������� �������� ������ ��������
		hand = (HANDLE)_beginthread(Semaphore, // ����� ������� ������
			NULL, // ��������� ������ ����� � ������
			NULL); // ��������� ��� ������

		cout << "��������� �������!\n";
		cout.flush();

		WaitForSingleObject(ev, // ��������� ������� ����, ���������� ��������� �������� ��� ���������� 
			INFINITE); //�������, �� ��������� �������� �������� �������� 

		cout << "������� ���������!\n";
		cout.flush();
	}
	if (strcmp(argv[1], "/R") == 0) // ���� ���� == "/R"
	{
		cout << "��������� �������\n";
		//SetEvent() ������ ��������� �� ����������
		SetEvent(ev); // ���������� �������
	}
	CloseHandle(ev);
}
