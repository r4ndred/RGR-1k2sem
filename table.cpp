#include "table.h"

// ������� ��� ������ ����������� ����� � ������
string readFileToString1(const string& fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        throw runtime_error("���� �� ������\n");
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string fileContent = buffer.str();

    if (fileContent.empty()) {
        throw runtime_error("������ ������ �����. ��������� ���������� �����.\n");
    }

    return fileContent;
}

// ������� ��� ���������� ������� ��������� ���������
void fillTable(const string& message, vector<vector<char>>& table, int size, char fillChar, char fillChar2) {
    int msgIndex = 0; // ������ ��� ������� �� �������� ���������
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (msgIndex < message.size()) {
                if (message[msgIndex] == ' ') {
                    table[i][j] = ' '; // ���� ������ - ������, �������� ��� ��������-������������
                } else {
                    table[i][j] = message[msgIndex]; // ���������� ������� ��������� ���������
                }
                msgIndex++;
            } else {
                table[i][j] = fillChar; // ���������� �������� 'fillChar', ���� �������� �� �������
            }
        }
    }
}

// ������� ��� ������������ ����� ��� �������� �������
void permuteTablerow(vector<vector<char>>& table, const vector<int>& key) {
    int size = table.size(); // ������ ������� ��� ������������
    vector<vector<char>> tempTable = table; // ��������� ������� ��� �������� �������� ���������
    for (int i = 0; i < size; ++i) {
        int newIndex = key[i]; // ����� ������ ����� ������������
        for (int j = 0; j < size; ++j) {
            table[i][j] = tempTable[newIndex][j]; // ������������ �����
        }
    }
}

// ������� ��� ������������ ����� ��� �������� �������
void permuteTablecol(vector<vector<char>>& table, const vector<int>& key) {
    int size = table.size(); // ������ ������� ��� ������������
    vector<vector<char>> tempTable = table; // ��������� ������� ��� �������� �������� ���������
    for (int i = 0; i < size; ++i) {
        int newIndex = key[i]; // ����� ������ ����� ������������
        for (int j = 0; j < size; ++j){
            table[j][i] = tempTable[j][newIndex]; // ������������ ��������
        }
    }
}

// ������� ��� ��������� ���������� ����� ������������
vector<int> generateRandomKey(int size) {
    vector<int> key(size);
    iota(key.begin(), key.end(), 0); // ���������� ����� ������������������� {1, 2, ..., size}
    random_device rd; // �������� �����������
    mt19937 g(rd()); // ��������� ��������� �����
    shuffle(key.begin(), key.end(), g); // ������������� �����
    return key;
}

// ������� ��� ��������� ��������� ����� ������������
vector<int> generatereverseKey( vector<int>& Key1, int size) {
    vector<int> Key2(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++) {
            if (i == Key1[j]) {
                Key2[i] = j;
            }
        }
    }
    return Key2;
}

// ������� ��� ���������� ������� ������� ������������
string encrypt(const string& message, const vector<int>& colKey, const vector<int>& rowKey, char fillChar, char fillChar2) {
    int size = colKey.size(); // ������ ������� (���������� ����� � �������� ����������)
    vector<vector<char>> table(size, vector<char>(size)); // ������� ��� �������� ���������

    fillTable(message, table, size, fillChar, fillChar2); // ���������� ������� ���������� � ������������
    permuteTablecol(table, colKey); // ������������ ��������
    permuteTablerow(table, rowKey); // ������������ �����

    string encryptedMessage; // ���������� ��� �������� �������������� ���������
    for (const auto& row : table) {
        for (const auto& i : row) {
            encryptedMessage.push_back(i); // ������ �������������� ��������� �� �������
        }
    }
    return encryptedMessage; // ������� �������������� ���������
}

// ������� ��� ������������ ������� ������� ������������
string decrypt(const string& message, const vector<int>& colKey, const vector<int>& rowKey, char fillChar, char fillChar2) {
    int size = colKey.size(); // ������ ������� (���������� ����� � �������� ����������)
    vector<vector<char>> table(size, vector<char>(size)); // ������� ��� �������� �������������� ���������

    // ���������� ������� ������������� ����������
    int msgIndex = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (msgIndex < message.size()) {
                table[i][j] = message[msgIndex];
                msgIndex++;
            } else {
                table[i][j] = fillChar;
            }
        }
    }

    permuteTablerow(table, rowKey); // �������� ������������ �����
    permuteTablecol(table, colKey); // �������� ������������ ��������

    string decryptedMessage; // ���������� ��� �������� ��������������� ���������
    for (const auto& row : table) {
        for (const auto& i : row) {
            if (i != fillChar) { // ��������� ������ �������, ������� �� �������� ������������
                decryptedMessage.push_back(i); // ������ ��������������� ��������� �� �������
            }
        }
    }
    return decryptedMessage; // ������� ��������������� ���������
}

void DisplayTable() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (true) {
        string message;
        string fileName;
        cout << "������� ��� �����: ";
        cin >> fileName;

        try {
            message = readFileToString1(fileName);

        } catch (const exception& e) {
            cerr << "������: " << e.what() << endl;
            break;
        }

        try {
            int64_t messageLength = message.size(); // ����� ���������
            int64_t size = ceil(sqrt(messageLength)); // ����������� ������� �������

            // ��������� ��������� ������ ��� ������������ �������� � �����
            vector<int> colKey = generateRandomKey(size);
            vector<int> rowKey = generateRandomKey(size);
            vector<int> colKey1 = generatereverseKey(colKey, size);
            vector<int> rowKey1 = generatereverseKey(rowKey, size);

            char fillChar = '#'; // ������-�����������
            char fillChar2 = '^'; // ������-�����������

            // �������� ����� ��� ������ �������������� ������
            ofstream encryptedFile("encryptedTable.txt");
            if (!encryptedFile.is_open()) {
                throw runtime_error("���� �� ������.\n");
            }

            string encryptedMessage = encrypt(message, colKey, rowKey, fillChar, fillChar2); // ���������� ���������
            encryptedFile << encryptedMessage;
            encryptedFile.close();
            cout << "������������� ����� �������� � ���� encryptedTable.txt\n";
            cout << "������������� �����: " << encryptedMessage << "\n";

            // �������� ����� ��� ������ �������������� ������
            ifstream inputFile("encryptedTable.txt");
            if (!inputFile.is_open()) {
                throw runtime_error("���� �� ������.\n");
            }

            getline(inputFile, encryptedMessage);
            inputFile.close();

            // ������������ ������
            string decryptedMessage = decrypt(encryptedMessage, colKey1, rowKey1, fillChar, fillChar2); // ������������ ���������

            // �������� ����� ��� ������ ��������������� ������
            ofstream decryptedFile("decryptedTable.txt");
            if (!decryptedFile.is_open()) {
                throw runtime_error("���� �� ������.\n");
            }

            decryptedFile << decryptedMessage;
            decryptedFile.close();
            cout << "�������������� ����� �������� � ���� decryptedTable.txt\n";
            cout << "�������������� �����: " << decryptedMessage << "\n";

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