#include <windows.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) // ������������ ��������� ��� ���������� �����
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ofstream out("C:\\Users\\������\\source\\repos\\KOC5\\Debug\\id.txt", // ���� � �����
		ios::app); // �������� ������ ��� ������ � ����� �����
	if (out.is_open())
	{
		out << GetCurrentProcessId() << endl; // ���������� � id.txt id ��������
	}
	out.close(); // ��������� ��������� ����
	
	// �������� - ���� ���� ��� ���
	if (argv[1] != NULL) {
		// ���� ���� == "/R"
		if (strcmp(argv[1], "/R") == 0)
		{
			int i;
			ifstream myfile("C:\\Users\\������\\source\\repos\\KOC5\\Debug\\id.txt", ios::app);
			string line;
			int last;

			if (myfile.is_open())
			{
				last = GetCurrentProcessId(); // ����������� ���������� last ������� id
				while (!myfile.eof()) // ���� �� ����� ����� 
				{
					getline(myfile, line); // ����������� line ������� �� ����� txt
					i = stoi(line); // ������������ �������� string line � int
					if (i == last) {  // ���� i ����� ���������� �������� id, �� �������� ���� txt
						cout << "���� ������. �������� �������" << endl;
						ofstream fin("C:\\Users\\������\\source\\repos\\KOC5\\Debug\\id.txt", ios::trunc); }
					TerminateProcess(( // ���������� �������
						OpenProcess(PROCESS_ALL_ACCESS, TRUE, i)), // �������� ����� �������� � ������� ��� id
						NULL); 
				}
				myfile.close(); // ��������� ��������� ����
			}
		}
	}

	// ������� ����� ������� ��� ��������� ������������ 
	HANDLE sem = CreateSemaphore(NULL, // // ������� �������
		3, // ������������������ ��������� ��������� ��������
		3, // ������������ ���������� ���������
		L"nt5bbsem"); // ��� �������

	cout << "��������� ��������� ��������\n";
	cout.flush();

	WaitForSingleObject(sem, // //��������� ������� ����, ���������� ��������� �������� ��� ���������� 
		INFINITE); //�������, �� ��������� �������� �������� �������� 

	cout << "������� ������ � ��������\n";
	cout.flush();
	MessageBox(NULL, L"������� ������ � ��������", L"Semaphore", MB_OK);

	// ��������� ��������� �������� (������ 1) � �������� ��������, ����� ��� ��������� ��� �������� ���������� �������
	ReleaseSemaphore(sem, // ���� ��������
		1, // �� ������� �������� �������
		NULL); // ���������� ��������

	CloseHandle(sem);
}
