#include <iostream>
#include <Windows.h>
#include "table.h"
#include "tarabar.h"
#include "password.h"
#include "PolybiusCipher.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    bool passwordEntered = false; //�������� �� ���� ������

    while (!passwordEntered) {
        string userPassword;
        cout << "[����]. ������� ������ ��� ������ ������ ���������: ";
        getline(cin, userPassword);

        try {
            if (!checkPassword(userPassword)) {
                throw invalid_argument("�������� ������\n");
            }
            passwordEntered = true; // ������ ������ ���������
        }
        catch (const invalid_argument& e) {
            cerr << "������: " << e.what() << endl;
        }
    }

    while (true) {
        try {
            string MenuChoice;
            cout << "----------------------------------------------------\n";
            cout << "[����]. �������� ����:\n1. ������� ��������� ������������\n2. ����������� �������\n3. ���� �������\n4. �����\n";
            cout << "----------------------------------------------------\n";
            getline(cin, MenuChoice);

            if (MenuChoice != "1" && MenuChoice != "2" && MenuChoice != "3" && MenuChoice != "4") {
                throw invalid_argument("���������� ������ '1', '2', '3' ��� '4' ��� ��������.\n");
            }
            int ChoiceMenu = stoi(MenuChoice);// �������������� ������ � int
            switch (ChoiceMenu) {
                case 1:
                    DisplayTable();
                    break;
                case 2:
                    DisplayGramota();
                    break;
                case 3:
                    DisplayPolybius();
                    break;
                case 4:
                    cout << "----------------------------------------------------\n";
                    cout << "������ ��������� ���������\n";
                    cout << "----------------------------------------------------\n";
                    return 0;
            }
        }
        catch (const invalid_argument& e) {
            cerr << "������: " << e.what() << endl;
            cout << "----------------------------------------------------\n";
        }
    }
}