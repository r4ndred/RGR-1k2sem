#include "Cipher.h"

// ������� ��� ������ ����������� ����� � ������
string readFileToString(const string& fileName) {
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

// ������� ��� ���������� ������
string encryptCipher(const string& text, int k, const vector<int>& permutation) {
    string resultCipher; // ���������� ��� �������� �������������� ������

    for (size_t i = 0; i < text.size(); i += k) {    // ������ �� ������ ������� ������ k
        for (int j = 0; j < k; j++) { // ���������� ���� �������� �� ������� ������� � ������� ����� ������ k.
            // ��������, ��� ������ ��������� � �������� ������
            if (i + permutation[j] - 1 < text.size()) {
                // ���������� ������� � ���������, ��������� ������������
                resultCipher += text[i + permutation[j] - 1];
            }
            else { // ���� ������� ���� ������������� ������, ��� ��������� ���������� ��������, ����������� ������.
                resultCipher += ' ';
            }
        }
    }
    return resultCipher; // ���������� ������������� �����
}


string decryptCipher(const string& text, int k, const vector<int>& permutation) {
    string resultCipher; // ���������� ��� �������� ���������� ������������
    vector<int> inverse_permutation(k); // ������ ��� �������� �������� ������������

    // ���������� �������� ������������
    for (int i = 0; i < k; i++) {
        inverse_permutation[permutation[i] - 1] = i + 1; //���������� ������� ������������������
    }

    // ������ �� ������ ������� ������ k
    for (size_t i = 0; i < text.size(); i += k) {
        for (int j = 0; j < k; j++) {
            // ��������, ��� ������ ��������� � �������� ������
            if (i + inverse_permutation[j] - 1 < text.size()) {
                // ���������� ������� � ���������, ��������� �������� ������������
                resultCipher += text[i + inverse_permutation[j] - 1];
            }
        }
    }
    return resultCipher; // ���������� ��������� ������������
}

void displayCipher() {
    setlocale(LC_ALL, "Russian");
    while (true) {
        try {

            int k; // ���������� ��� ������ � ������
            while (true) {
                try {
                    cout << "������� �������� k (���������� �������� ��� ������������ � ������): ";
                    string input;
                    getline(cin, input);

                    // �������� ������� ��������
                    if (input.find(' ') != string::npos) { //string::npos  �������� ����������, ������������ "�� �������".
                        throw invalid_argument("������� ���� ����� ��� ��������.\n");
                    }

                    stringstream ss(input); //  ����������� �������� ������ � �����
                    if (ss >> k && k > 0 && ss.eof()) { //�������� �� 1) k ������ 0 2)����� ������. ����� ��������� �������� �� ������ � k.
                        break;
                    }
                    else {
                        throw invalid_argument("������� ���������� ����������� �������� ��� k(��� ��������).\n");
                    }
                }
                catch (const invalid_argument& e) {
                    cerr << "������: " << e.what();
                    continue; // ��������� ���� ��� ������ �����
                }
            }

            vector<int> permutation(k); //������ ������������������
            set<int> uniqueNumbers; // ��������� ��� �������� ������������ �����

            while (true) { // ���� ��� ����� ���� ������������������
                try {
                    uniqueNumbers.clear();
                    cout << "������� ������������������ �� " << k << " �����\n (������������ ��������, ������ ����� ����� ������, ��������� ����� �� 1 �� " << k <<"): ";

                    for (int i = 0; i < k; i++) { // ���� �� ������� �������� ������������
                        int number; // ��������� ���������� ��� �������� ����� �����
                        if (!(cin >> number) || number < 1 || number > k || !uniqueNumbers.insert(number).second) { // �������� 1)���������� ���������� �� ������ 2) �������� ����� �� 1 �� k 3)��� ����� �������� ����������.
                            cin.clear(); //���������� ����� � ������� ���������, ���� ���� ������ �����
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //���������� ������������ ����� ��������  � ������ ,������� ������ ����� ������.
                            throw invalid_argument("������� ������������ ������������������. ������������������ ������ �������� � ���� ����� �� 1 �� " + to_string(k) + " ��� ����������.\n");
                        }
                        permutation[i] = number; // ���������� ����� � ������� ������������
                    }

                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������� ������� ������
                    break; // ������� �� ����� ��� �������� ����� ���� ������������������
                }
                catch (const invalid_argument& e) {
                    cerr << "������: " << e.what();
                    // �������� ������������ �� ������ � ������ ������ ������������������ ������
                    cout << "������� ������������������ ������.\n";
                }
            }

            string inputCipher;
            string fileName;
            cout << "������� ��� �����: ";
            cin >> fileName;

            try {
                inputCipher = readFileToString(fileName);

            } catch (const exception& e) {
                cerr << "������: " << e.what() << endl;
                break;
            }

            // �������� ����� ��� ������ �������������� ������
            ofstream encryptedFile("encryptedCipher.txt");
            if (!encryptedFile.is_open()) {
                throw runtime_error("���� �� ������.\n");
            }

            string encryptedCipher = encryptCipher(inputCipher, k, permutation);
            encryptedFile << encryptedCipher;
            encryptedFile.close();
            cout << "������������� ����� �������� � ���� encryptedCipher.txt\n";
            cout << "������������� �����: " << encryptedCipher << "\n";

            // �������� ����� ��� ������ �������������� ������
            ifstream inputFile("encryptedCipher.txt");
            if (!inputFile.is_open()) {
                throw runtime_error("���� �� ������.\n");
            }

            getline(inputFile, encryptedCipher);
            inputFile.close();

            // ������������ ������
            string decryptedCipher = decryptCipher(encryptedCipher, k, permutation);

            // �������� ����� ��� ������ ��������������� ������
            ofstream decryptedFile("decryptedCipher.txt");
            if (!decryptedFile.is_open()) {
                throw runtime_error("���� �� ������.\n");
            }

            decryptedFile << decryptedCipher;
            decryptedFile.close();
            cout << "�������������� ����� �������� � ���� decryptedCipher.txt\n";
            cout << "�������������� �����: " << decryptedCipher << "\n";

            break;

        }
        catch (const invalid_argument& e) {
            cerr << "������: " << e.what();
            continue; // ���������� ���� ��� ������ �����
        }
        catch (const runtime_error& e) {
            cerr << "������: " << e.what();
            break; // ���������� ���� ��� ������ ������/������ �����
        }
    }
}