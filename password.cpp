#include "password.h"

bool checkPassword(const string& password) {
    string cypherpassword, result = ""; // ������������� ����� ��� �������� �������������� ������ � ���������� ������������
    int step; // ���������� ��� �������� ���� ������ ��� ���������� ������
    ifstream in("password.txt"); // �������� ����� � ������������� ������� ��� ������

    if (!in.is_open()) { // �������� ��������� �������� �����
        throw runtime_error("�� ������� ������� ���� password.txt ��� ������.\n"); // ��������� ���������� � ������ ������ �������� �����
    }

    in >> cypherpassword >> step; // ���������� �������������� ������ � ���� ������ �� �����
    in.close(); // �������� ����� ����� ����������


    for (size_t i = 0; i < cypherpassword.size(); i++) { // ���� �� �������� �������������� ������
        if (cypherpassword[i] >= step && cypherpassword[i] <= 127) { // ��������, ��� ������ � ��������� ASCII � ������� �����������
            result += static_cast<char>((cypherpassword[i] - step) % 128); // ���������� ������� � ���������� � ����������
        } else { // ���� ������ �� ������� ���������� (�� ������ � �������� ASCII)
            result += static_cast<char>(cypherpassword[i]); // ������ ���������� ������� � ����������
        }
    }

    if(password == result){
        return true; // ��������� ���������� ������ � �������������� ������� � ����������� ���������� ���������
    }
    else{
        return false;
    }

}