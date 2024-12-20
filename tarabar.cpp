#include "tarabar.h"

map<char, char> TarabarEng = {
        {'B', 'A'}, {'A', 'B'},
        {'C', 'E'}, {'E', 'C'},
        {'D', 'I'}, {'I', 'D'},
        {'F', 'O'}, {'O', 'F'},
        {'G', 'U'}, {'U', 'G'},
        {'H', 'Y'}, {'Y', 'H'},
        {'J', 'Z'}, {'Z', 'J'},
        {'K', 'X'}, {'X', 'K'},
        {'L', 'W'}, {'W', 'L'},
        {'M', 'V'}, {'V', 'M'},
        {'N', 'T'}, {'T', 'N'},
        {'P', 'S'}, {'S', 'P'},
        {'Q', 'R'}, {'R', 'Q'},
        {' ', '#'},

        {'b', 'a'}, {'a', 'b'},
        {'c', 'e'}, {'e', 'c'},
        {'d', 'i'}, {'i', 'd'},
        {'f', 'o'}, {'o', 'f'},
        {'g', 'u'}, {'u', 'g'},
        {'h', 'y'}, {'y', 'h'},
        {'j', 'z'}, {'z', 'j'},
        {'k', 'x'}, {'x', 'k'},
        {'l', 'w'}, {'w', 'l'},
        {'m', 'v'}, {'v', 'm'},
        {'n', 't'}, {'t', 'n'},
        {'p', 's'}, {'s', 'p'},
        {'q', 'r'}, {'r', 'q'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {'�', '�'}, {'�', '�'},
        {' ', '#'}
};

// ������� ��� ������ ����������� ����� � ������
string readFileToString2(const string& fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        throw runtime_error("���� �� ������");
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string fileContent = buffer.str();

    if (fileContent.empty()) {
        throw runtime_error("������ ������ �����. ��������� ���������� �����.\n");
    }

    return fileContent;
}

string encryptTarabar(const string& text, map<char, char>& GramotaRus) {
    string encryptedGramota; // ������������� ������ ��� �������� �������������� ������
    for (char c : text) { // ���� �� �������� �������� ������
        if (GramotaRus.count(c)) { // ��������, ���� �� ������� ������ � ������� GramotaRus
            encryptedGramota += GramotaRus[c]; // ���� ������ ������ � �������, ��������� ��� ������������� ������ � ������ �������������� ������
        }
        else { // ���� ������ �� ������ � �������
            encryptedGramota += c; // ������ ��������� ������ � �������������� ������ ��� ���������
        }
    }
    return encryptedGramota; // ���������� ������������� �����
}


string decryptTarabar(const string& text, map <char, char>& Gramota) {
    string decryptedGramota; // ������������� ������ ��� �������� ��������������� ������
    for (char c : text) { // ���� �� �������� �������� ������
        bool found = false; // ���������� ��� ������������ ���������� ������� � ������� Gramota
        for (const auto& pair : Gramota) { // ���� �� ����� �������� � ������� Gramota
            if (pair.second == c) { // ���� ������ ������ ���� ����� �������� ������� �� �������� ������
                decryptedGramota += pair.first; // ��������� ������ ������ ���� � ��������������� ������
                found = true; // ������������� ����, ��� ������ ������
                break; // ������� �� ����������� �����, ��� ��� ������ ������
            }
        }
        if (!found) { // ���� ������ �� ��� ������ � ������� Gramota
            decryptedGramota += c; // ������ ��������� ������ � ��������������� ������ ��� ���������
        }
    }
    return decryptedGramota; // ���������� �������������� �����
}


void DisplayGramota() {
    setlocale(LC_ALL, "Russian");

    while (true) {
        string inputTarabar;
        string fileName;
        cout << "������� ��� �����: ";
        cin >> fileName;

        try {
            inputTarabar = readFileToString2(fileName);

        } catch (const exception& e) {
            cerr << "������: " << e.what() << endl;
            break;
        }

        try {
            // �������� ����� ��� ������
            ofstream outputFile("encryptedTarabar.txt");
            if (!outputFile.is_open()) {
                throw runtime_error("���� �� ������.\n");
            }

            string encryptedTarabar; // ������ ��� �������������� ������
            encryptedTarabar = encryptTarabar(inputTarabar, TarabarEng);

            outputFile << encryptedTarabar;
            outputFile.close();
            cout << "������������� ����� ������� � encryptedTarabar.txt\n";
            cout << "������������� �����: " << encryptedTarabar << "\n";

            // �������� ����� ��� ������
            ifstream inputFile("encryptedTarabar.txt");
            if (!inputFile.is_open()) {
                throw runtime_error("���� �� ������.\n");
            }

            string decryptedTarabar;
            getline(inputFile, decryptedTarabar);
            inputFile.close();

            decryptedTarabar = decryptTarabar(decryptedTarabar, TarabarEng);

            // ������ ��������������� ������ � ���� decryptedTarabar.txt
            ofstream decryptFile("decryptedTarabar.txt");
            if (!decryptFile.is_open()) {
                throw runtime_error("���� �� ������.\n");
            }

            decryptFile << decryptedTarabar;
            decryptFile.close();
            cout << "�������������� ����� ������� � decryptedTarabar.txt\n";

            cout << "�������������� �����: " << decryptedTarabar << "\n";

            break;
        }
        catch (const invalid_argument& e) {
            cerr << "������: " << e.what();
        }
        catch (const runtime_error& e) {
            cerr << "������: " << e.what();
        }
    }
}