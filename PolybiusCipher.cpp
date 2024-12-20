#include <iostream>
#include <fstream>
#include <stdexcept>
#include <codecvt>
#include <Windows.h>
#include "PolybiusCipher.h"

// ������� ��� �������� ��������� ������� ��� ����������� �������� (��������� �����)
map<char, string> createPolybiusSquareEngUpper() {
    map<char, string> polybiusSquare;
    polybiusSquare['A'] = "11"; polybiusSquare['B'] = "12"; polybiusSquare['C'] = "13"; polybiusSquare['D'] = "14"; polybiusSquare['E'] = "15";
    polybiusSquare['F'] = "21"; polybiusSquare['G'] = "22"; polybiusSquare['H'] = "23"; polybiusSquare['I'] = "24"; polybiusSquare['J'] = "26"; polybiusSquare['K'] = "25";
    polybiusSquare['L'] = "31"; polybiusSquare['M'] = "32"; polybiusSquare['N'] = "33"; polybiusSquare['O'] = "34"; polybiusSquare['P'] = "35";
    polybiusSquare['Q'] = "41"; polybiusSquare['R'] = "42"; polybiusSquare['S'] = "43"; polybiusSquare['T'] = "44"; polybiusSquare['U'] = "45";
    polybiusSquare['V'] = "51"; polybiusSquare['W'] = "52"; polybiusSquare['X'] = "53"; polybiusSquare['Y'] = "54"; polybiusSquare['Z'] = "55";
    return polybiusSquare;
}

// ������� ��� �������� ��������� ������� ��� ����������� �������� (�������� �����)
map<char, string> createPolybiusSquareEngLower() {
    map<char, string> polybiusSquare;
    polybiusSquare['a'] = "11"; polybiusSquare['b'] = "12"; polybiusSquare['c'] = "13"; polybiusSquare['d'] = "14"; polybiusSquare['e'] = "15";
    polybiusSquare['f'] = "21"; polybiusSquare['g'] = "22"; polybiusSquare['h'] = "23"; polybiusSquare['i'] = "24"; polybiusSquare['j'] = "26"; polybiusSquare['k'] = "25";
    polybiusSquare['l'] = "31"; polybiusSquare['m'] = "32"; polybiusSquare['n'] = "33"; polybiusSquare['o'] = "34"; polybiusSquare['p'] = "35";
    polybiusSquare['q'] = "41"; polybiusSquare['r'] = "42"; polybiusSquare['s'] = "43"; polybiusSquare['t'] = "44"; polybiusSquare['u'] = "45";
    polybiusSquare['v'] = "51"; polybiusSquare['w'] = "52"; polybiusSquare['x'] = "53"; polybiusSquare['y'] = "54"; polybiusSquare['z'] = "55";
    return polybiusSquare;
}

// ������� ��� �������� ��������� ������� ��� �������� �������� (��������� �����)
map<char, string> createPolybiusSquareRusUpper() {
    map<char, string> polybiusSquare;
    polybiusSquare['�'] = "11"; polybiusSquare['�'] = "12"; polybiusSquare['�'] = "13"; polybiusSquare['�'] = "14"; polybiusSquare['�'] = "15"; polybiusSquare['�'] = "16";
    polybiusSquare['�'] = "21"; polybiusSquare['�'] = "22"; polybiusSquare['�'] = "23"; polybiusSquare['�'] = "24"; polybiusSquare['�'] = "25"; polybiusSquare['�'] = "26";
    polybiusSquare['�'] = "31"; polybiusSquare['�'] = "32"; polybiusSquare['�'] = "33"; polybiusSquare['�'] = "34"; polybiusSquare['�'] = "35"; polybiusSquare['�'] = "36"; 
    polybiusSquare['�'] = "41"; polybiusSquare['�'] = "42"; polybiusSquare['�'] = "43"; polybiusSquare['�'] = "44"; polybiusSquare['�'] = "45"; polybiusSquare['�'] = "46"; 
    polybiusSquare['�'] = "51"; polybiusSquare['�'] = "52"; polybiusSquare['�'] = "53"; polybiusSquare['�'] = "54"; polybiusSquare['�'] = "55"; polybiusSquare['�'] = "56"; 
    polybiusSquare['�'] = "61"; polybiusSquare['�'] = "62"; polybiusSquare['�'] = "63";
    return polybiusSquare;
}

// ������� ��� �������� ��������� ������� ��� �������� �������� (�������� �����)
map<char, string> createPolybiusSquareRusLower() {
    map<char, string> polybiusSquare;
    polybiusSquare['�'] = "11"; polybiusSquare['�'] = "12"; polybiusSquare['�'] = "13"; polybiusSquare['�'] = "14"; polybiusSquare['�'] = "15"; polybiusSquare['�'] = "16";
    polybiusSquare['�'] = "21"; polybiusSquare['�'] = "22"; polybiusSquare['�'] = "23"; polybiusSquare['�'] = "24"; polybiusSquare['�'] = "25"; polybiusSquare['�'] = "26";
    polybiusSquare['�'] = "31"; polybiusSquare['�'] = "32"; polybiusSquare['�'] = "33"; polybiusSquare['�'] = "34"; polybiusSquare['�'] = "35"; polybiusSquare['�'] = "36"; 
    polybiusSquare['�'] = "41"; polybiusSquare['�'] = "42"; polybiusSquare['�'] = "43"; polybiusSquare['�'] = "44"; polybiusSquare['�'] = "45"; polybiusSquare['�'] = "46"; 
    polybiusSquare['�'] = "51"; polybiusSquare['�'] = "52"; polybiusSquare['�'] = "53"; polybiusSquare['�'] = "54"; polybiusSquare['�'] = "55"; polybiusSquare['�'] = "56"; 
    polybiusSquare['�'] = "61"; polybiusSquare['�'] = "62"; polybiusSquare['�'] = "63";
    return polybiusSquare;
}

// ������� ��� �������� �������� ��������� ������� ��� ����������� �������� (��������� �����)
map<string, char> createReversePolybiusSquareEngUpper() {
    map<string, char> reversePolybiusSquare;
    reversePolybiusSquare["11"] = 'A'; reversePolybiusSquare["12"] = 'B'; reversePolybiusSquare["13"] = 'C'; reversePolybiusSquare["14"] = 'D'; reversePolybiusSquare["15"] = 'E';
    reversePolybiusSquare["21"] = 'F'; reversePolybiusSquare["22"] = 'G'; reversePolybiusSquare["23"] = 'H'; reversePolybiusSquare["24"] = 'I'; reversePolybiusSquare["26"] = 'J'; reversePolybiusSquare["25"] = 'K';
    reversePolybiusSquare["31"] = 'L'; reversePolybiusSquare["32"] = 'M'; reversePolybiusSquare["33"] = 'N'; reversePolybiusSquare["34"] = 'O'; reversePolybiusSquare["35"] = 'P';
    reversePolybiusSquare["41"] = 'Q'; reversePolybiusSquare["42"] = 'R'; reversePolybiusSquare["43"] = 'S'; reversePolybiusSquare["44"] = 'T'; reversePolybiusSquare["45"] = 'U';
    reversePolybiusSquare["51"] = 'V'; reversePolybiusSquare["52"] = 'W'; reversePolybiusSquare["53"] = 'X'; reversePolybiusSquare["54"] = 'Y'; reversePolybiusSquare["55"] = 'Z';
    return reversePolybiusSquare;
}

// ������� ��� �������� �������� ��������� ������� ��� ����������� �������� (�������� �����)
map<string, char> createReversePolybiusSquareEngLower() {
    map<string, char> reversePolybiusSquare;
    reversePolybiusSquare["11"] = 'a'; reversePolybiusSquare["12"] = 'b'; reversePolybiusSquare["13"] = 'c'; reversePolybiusSquare["14"] = 'd'; reversePolybiusSquare["15"] = 'e';
    reversePolybiusSquare["21"] = 'f'; reversePolybiusSquare["22"] = 'g'; reversePolybiusSquare["23"] = 'h'; reversePolybiusSquare["24"] = 'i'; reversePolybiusSquare["26"] = 'j'; reversePolybiusSquare["25"] = 'k';
    reversePolybiusSquare["31"] = 'l'; reversePolybiusSquare["32"] = 'm'; reversePolybiusSquare["33"] = 'n'; reversePolybiusSquare["34"] = 'o'; reversePolybiusSquare["35"] = 'p';
    reversePolybiusSquare["41"] = 'q'; reversePolybiusSquare["42"] = 'r'; reversePolybiusSquare["43"] = 's'; reversePolybiusSquare["44"] = 't'; reversePolybiusSquare["45"] = 'u';
    reversePolybiusSquare["51"] = 'v'; reversePolybiusSquare["52"] = 'w'; reversePolybiusSquare["53"] = 'x'; reversePolybiusSquare["54"] = 'y'; reversePolybiusSquare["55"] = 'z';
    return reversePolybiusSquare;
}

// ������� ��� �������� �������� ��������� ������� ��� �������� �������� (��������� �����)
map<string, char> createReversePolybiusSquareRusUpper() {
    map<string, char> reversePolybiusSquare;
    reversePolybiusSquare["11"] = '�'; reversePolybiusSquare["12"] = '�'; reversePolybiusSquare["13"] = '�'; reversePolybiusSquare["14"] = '�'; reversePolybiusSquare["15"] = '�'; reversePolybiusSquare["16"] = '�'; 
    reversePolybiusSquare["21"] = '�'; reversePolybiusSquare["22"] = '�'; reversePolybiusSquare["23"] = '�'; reversePolybiusSquare["24"] = '�'; reversePolybiusSquare["25"] = '�'; reversePolybiusSquare["26"] = '�';
    reversePolybiusSquare["31"] = '�'; reversePolybiusSquare["32"] = '�'; reversePolybiusSquare["33"] = '�'; reversePolybiusSquare["34"] = '�'; reversePolybiusSquare["35"] = '�'; reversePolybiusSquare["36"] = '�'; 
    reversePolybiusSquare["41"] = '�'; reversePolybiusSquare["42"] = '�'; reversePolybiusSquare["43"] = '�'; reversePolybiusSquare["44"] = '�'; reversePolybiusSquare["45"] = '�'; reversePolybiusSquare["46"] = '�'; 
    reversePolybiusSquare["51"] = '�'; reversePolybiusSquare["52"] = '�'; reversePolybiusSquare["53"] = '�'; reversePolybiusSquare["54"] = '�'; reversePolybiusSquare["55"] = '�'; reversePolybiusSquare["56"] = '�'; 
    reversePolybiusSquare["61"] = '�'; reversePolybiusSquare["62"] = '�'; reversePolybiusSquare["63"] = '�';
    return reversePolybiusSquare;
}

// ������� ��� �������� �������� ��������� ������� ��� �������� �������� (�������� �����)
map<string, char> createReversePolybiusSquareRusLower() {
    map<string, char> reversePolybiusSquare;
    reversePolybiusSquare["11"] = '�'; reversePolybiusSquare["12"] = '�'; reversePolybiusSquare["13"] = '�'; reversePolybiusSquare["14"] = '�'; reversePolybiusSquare["15"] = '�'; reversePolybiusSquare["16"] = '�'; 
    reversePolybiusSquare["21"] = '�'; reversePolybiusSquare["22"] = '�'; reversePolybiusSquare["23"] = '�'; reversePolybiusSquare["24"] = '�'; reversePolybiusSquare["25"] = '�'; reversePolybiusSquare["26"] = '�';
    reversePolybiusSquare["31"] = '�'; reversePolybiusSquare["32"] = '�'; reversePolybiusSquare["33"] = '�'; reversePolybiusSquare["34"] = '�'; reversePolybiusSquare["35"] = '�'; reversePolybiusSquare["36"] = '�'; 
    reversePolybiusSquare["41"] = '�'; reversePolybiusSquare["42"] = '�'; reversePolybiusSquare["43"] = '�'; reversePolybiusSquare["44"] = '�'; reversePolybiusSquare["45"] = '�'; reversePolybiusSquare["46"] = '�'; 
    reversePolybiusSquare["51"] = '�'; reversePolybiusSquare["52"] = '�'; reversePolybiusSquare["53"] = '�'; reversePolybiusSquare["54"] = '�'; reversePolybiusSquare["55"] = '�'; reversePolybiusSquare["56"] = '�'; 
    reversePolybiusSquare["61"] = '�'; reversePolybiusSquare["62"] = '�'; reversePolybiusSquare["63"] = '�';
    return reversePolybiusSquare;
}

// ������� ���������� ������ � �������������� �������� �������
string encryptPolybius(const string& text, const map<char, string>& polybiusSquare) {
    string encryptedText;
    for (char c : text) {
        // ��������� ������� ������� � ������� � �������� ���
        if (polybiusSquare.count(c) > 0) {
            encryptedText += polybiusSquare.at(c);
        } else {
            // ��������� ������ ��� ���������, ���� ��� ��� � �������
            encryptedText += c;
        }
    }
    return encryptedText;
}

// ������� ����������� ������ � �������������� ��������� �������� �������
string decryptPolybius(const string& text, const map<string, char>& reversePolybiusSquare) {
    string decryptedText;
    string symbol;
    for (char c : text) {
        if (isdigit(c)) { // ���������, �������� �� ������ ������
            symbol += c;
            if (symbol.length() == 2) { // ���� ����� ������� 2, ��������� ��� � �������� �������
                if (reversePolybiusSquare.count(symbol) > 0) {
                    decryptedText += reversePolybiusSquare.at(symbol);
                }
                symbol.clear();
            }
        } else {
            // ��������� ������ ��� ���������, ���� ��� �� �����
            decryptedText += c;
        }
    }
    return decryptedText;
}

// �������� ������� ��� ������ � ������ �������
void DisplayPolybius() {
    SetConsoleCP(1251); // ������������� ��������� ������� �� ����
    SetConsoleOutputCP(1251); // ������������� ��������� ������� �� �����
    while (true) {
        try {
            // ���������� ���� ������ �����
            cout << "---------------------------------\n";
            cout << "�������� ����:\n1) English\n2) �������\n3) �����\n";
            cout << "---------------------------------\n";
            string languageChoice;
            getline(cin, languageChoice); // ��������� ����� ������������

            // ��������� ������������ ������
            if (languageChoice != "1" && languageChoice != "2" && languageChoice != "3") {
                throw invalid_argument("������������ �������. ����� ����� ������� �������� �� 1 �������: '1', '2' ��� '3'. ���������� ��� ���.\n");
            }

            int languageAction = stoi(languageChoice); // ����������� ����� � ����� �����
            if (languageAction == 3) { // ���� ������� "�����", ������� �� �����
                cout << "---------------------------------\n";
                break;
            }

            // ���������� ���� ������ ��������
            cout << "---------------------------------\n";
            cout << "�������� �������:\n1) ��������� �����\n2) �������� �����\n3) �����\n";
            cout << "---------------------------------\n";
            string caseChoice;
            getline(cin, caseChoice); // ��������� ����� ������������

            // ��������� ������������ ������
            if (caseChoice != "1" && caseChoice != "2" && caseChoice != "3") {
                throw invalid_argument("������������ �������. ����� ����� ������� �������� �� 1 �������: '1', '2' ��� '3'. ���������� ��� ���.\n");
            }

            int caseAction = stoi(caseChoice); // ����������� ����� � ����� �����
            if (caseAction == 3) { // ���� ������� "�����", ������� �� �����
                cout << "---------------------------------\n";
                continue;
            }

            // ������ ������ ��� ����������
            string inputText;
            cout << "������� ����� ��� ����������: ";
            getline(cin >> ws, inputText); // ws ���������� ������� �� ����� ������
            cout << "---------------------------------\n";

            map<char, string> polybiusSquare;
            map<string, char> reversePolybiusSquare;
            // �������� ������� ���������� �� ������ ���������� ����� � ��������
            if (languageAction == 1) {
                if (caseAction == 1) {
                    polybiusSquare = createPolybiusSquareEngUpper();
                    reversePolybiusSquare = createReversePolybiusSquareEngUpper();
                } else {
                    polybiusSquare = createPolybiusSquareEngLower();
                    reversePolybiusSquare = createReversePolybiusSquareEngLower();
                }
            } else if (languageAction == 2) {
                if (caseAction == 1) {
                    polybiusSquare = createPolybiusSquareRusUpper();
                    reversePolybiusSquare = createReversePolybiusSquareRusUpper();
                } else {
                    polybiusSquare = createPolybiusSquareRusLower();
                    reversePolybiusSquare = createReversePolybiusSquareRusLower();
                }
            }

            // ������� �����
            string encryptedText = encryptPolybius(inputText, polybiusSquare);
            
            // ������ �������������� ������ � ����
            ofstream outputFile("encryptedPolybius.txt");
            if (!outputFile.is_open()) {
                throw runtime_error("�� ������� ������� ���� ��� ������.\n");
            }
            outputFile << encryptedText;
            outputFile.close(); // ��������� ���� ����� ������
            cout << "������������� ����� �������� � ���� encryptedPolybius.txt\n";
            cout << "������������� �����: " << encryptedText << "\n";
            cout << "---------------------------------\n";

            // ������ �������������� ������ �� �����
            ifstream inputFile("encryptedPolybius.txt");
            if (!inputFile.is_open()) {
                throw runtime_error("�� ������� ������� ���� ��� ������.\n");
            }
            string readEncryptedText;
            getline(inputFile, readEncryptedText);
            inputFile.close(); // ��������� ���� ����� ������

            // �������������� �����
            string decryptedText = decryptPolybius(readEncryptedText, reversePolybiusSquare);
            cout << "�������������� �����: " << decryptedText << "\n";

            // ������ ��������������� ������ � ����
            ofstream decryptFile("decryptedPolybius.txt");
            if (!decryptFile.is_open()) {
                throw runtime_error("�� ������� ������� ���� ��� ������.\n");
            }
            decryptFile << decryptedText;
            decryptFile.close(); // ��������� ���� ����� ������
            cout << "�������������� ����� �������� � ���� decryptedPolybius.txt\n";
            cout << "---------------------------------\n";
        }
        // ��������� ���������� ��� �������� ����� ������� ��� ������� ������ � �������
        catch (const invalid_argument& e) {
            cerr << "������: " << e.what();
        }
        catch (const runtime_error& e) {
            cerr << "������: " << e.what();
        }
    }
}