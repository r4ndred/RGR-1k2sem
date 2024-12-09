#include "table.h"

// Функция для чтения содержимого файла в строку
string readFileToString1(const string& fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        throw runtime_error("Файл не найден\n");
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string fileContent = buffer.str();

    if (fileContent.empty()) {
        throw runtime_error("Ошибка чтения файла. Проверьте содержимое файла.\n");
    }

    return fileContent;
}

// Функция для заполнения таблицы символами сообщения
void fillTable(const string& message, vector<vector<char>>& table, int size, char fillChar, char fillChar2) {
    int msgIndex = 0; // Индекс для прохода по символам сообщения
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (msgIndex < message.size()) {
                if (message[msgIndex] == ' ') {
                    table[i][j] = ' '; // Если символ - пробел, заменяем его символом-заполнителем
                } else {
                    table[i][j] = message[msgIndex]; // Заполнение таблицы символами сообщения
                }
                msgIndex++;
            } else {
                table[i][j] = fillChar; // Заполнение символом 'fillChar', если символов не хватает
            }
        }
    }
}

// Функция для перестановки строк или столбцов таблицы
void permuteTablerow(vector<vector<char>>& table, const vector<int>& key) {
    int size = table.size(); // Размер таблицы для перестановки
    vector<vector<char>> tempTable = table; // Временная таблица для хранения текущего состояния
    for (int i = 0; i < size; ++i) {
        int newIndex = key[i]; // Новый индекс после перестановки
        for (int j = 0; j < size; ++j) {
            table[i][j] = tempTable[newIndex][j]; // Перестановка строк
        }
    }
}

// Функция для перестановки строк или столбцов таблицы
void permuteTablecol(vector<vector<char>>& table, const vector<int>& key) {
    int size = table.size(); // Размер таблицы для перестановки
    vector<vector<char>> tempTable = table; // Временная таблица для хранения текущего состояния
    for (int i = 0; i < size; ++i) {
        int newIndex = key[i]; // Новый индекс после перестановки
        for (int j = 0; j < size; ++j){
            table[j][i] = tempTable[j][newIndex]; // Перестановка столбцов
        }
    }
}

// Функция для генерации случайного ключа перестановки
vector<int> generateRandomKey(int size) {
    vector<int> key(size);
    iota(key.begin(), key.end(), 0); // Заполнение ключа последовательностью {1, 2, ..., size}
    random_device rd; // Источник случайности
    mt19937 g(rd()); // Генератор случайных чисел
    shuffle(key.begin(), key.end(), g); // Перемешивание ключа
    return key;
}

// Функция для генерации обратного ключа перестановки
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

// Функция для шифрования методом двойной перестановки
string encrypt(const string& message, const vector<int>& colKey, const vector<int>& rowKey, char fillChar, char fillChar2) {
    int size = colKey.size(); // Размер таблицы (количество строк и столбцов одинаковое)
    vector<vector<char>> table(size, vector<char>(size)); // Таблица для хранения сообщения

    fillTable(message, table, size, fillChar, fillChar2); // Заполнение таблицы сообщением и заполнителем
    permuteTablecol(table, colKey); // Перестановка столбцов
    permuteTablerow(table, rowKey); // Перестановка строк

    string encryptedMessage; // Переменная для хранения зашифрованного сообщения
    for (const auto& row : table) {
        for (const auto& i : row) {
            encryptedMessage.push_back(i); // Сборка зашифрованного сообщения из таблицы
        }
    }
    return encryptedMessage; // Возврат зашифрованного сообщения
}

// Функция для дешифрования методом двойной перестановки
string decrypt(const string& message, const vector<int>& colKey, const vector<int>& rowKey, char fillChar, char fillChar2) {
    int size = colKey.size(); // Размер таблицы (количество строк и столбцов одинаковое)
    vector<vector<char>> table(size, vector<char>(size)); // Таблица для хранения зашифрованного сообщения

    // Заполнение таблицы зашифрованным сообщением
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

    permuteTablerow(table, rowKey); // Обратная перестановка строк
    permuteTablecol(table, colKey); // Обратная перестановка столбцов

    string decryptedMessage; // Переменная для хранения расшифрованного сообщения
    for (const auto& row : table) {
        for (const auto& i : row) {
            if (i != fillChar) { // Добавляем только символы, которые не являются заполнителем
                decryptedMessage.push_back(i); // Сборка расшифрованного сообщения из таблицы
            }
        }
    }
    return decryptedMessage; // Возврат расшифрованного сообщения
}

void DisplayTable() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (true) {
        string message;
        string fileName;
        cout << "Введите имя файла: ";
        cin >> fileName;

        try {
            message = readFileToString1(fileName);

        } catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
            break;
        }

        try {
            int64_t messageLength = message.size(); // Длина сообщения
            int64_t size = ceil(sqrt(messageLength)); // Определение размера таблицы

            // Генерация случайных ключей для перестановки столбцов и строк
            vector<int> colKey = generateRandomKey(size);
            vector<int> rowKey = generateRandomKey(size);
            vector<int> colKey1 = generatereverseKey(colKey, size);
            vector<int> rowKey1 = generatereverseKey(rowKey, size);

            char fillChar = '#'; // Символ-заполнитель
            char fillChar2 = '^'; // Символ-заполнитель

            // Открытие файла для записи зашифрованного текста
            ofstream encryptedFile("encryptedTable.txt");
            if (!encryptedFile.is_open()) {
                throw runtime_error("Файл не найден.\n");
            }

            string encryptedMessage = encrypt(message, colKey, rowKey, fillChar, fillChar2); // Шифрование сообщения
            encryptedFile << encryptedMessage;
            encryptedFile.close();
            cout << "Зашифрованный текст сохранен в файл encryptedTable.txt\n";
            cout << "Зашифрованный текст: " << encryptedMessage << "\n";

            // Открытие файла для чтения зашифрованного текста
            ifstream inputFile("encryptedTable.txt");
            if (!inputFile.is_open()) {
                throw runtime_error("Файл не найден.\n");
            }

            getline(inputFile, encryptedMessage);
            inputFile.close();

            // Дешифрование текста
            string decryptedMessage = decrypt(encryptedMessage, colKey1, rowKey1, fillChar, fillChar2); // Дешифрование сообщения

            // Открытие файла для записи расшифрованного текста
            ofstream decryptedFile("decryptedTable.txt");
            if (!decryptedFile.is_open()) {
                throw runtime_error("Файл не найден.\n");
            }

            decryptedFile << decryptedMessage;
            decryptedFile.close();
            cout << "Расшифрованный текст сохранен в файл decryptedTable.txt\n";
            cout << "Расшифрованный текст: " << decryptedMessage << "\n";

            break;
        }
        catch (const invalid_argument& e) {
            cerr << "Ошибка: " << e.what();
        }
        catch (const runtime_error& e) {
            cerr << "Ошибка: " << e.what();
        }
    }
}