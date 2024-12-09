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
        {'Б', 'Щ'}, {'Щ', 'Б'},
        {'В', 'Ш'}, {'Ш', 'В'},
        {'Г', 'Ч'}, {'Ч', 'Г'},
        {'Д', 'Ц'}, {'Ц', 'Д'},
        {'Ж', 'Х'}, {'Х', 'Ж'},
        {'З', 'Ф'}, {'Ф', 'З'},
        {'К', 'Т'}, {'Т', 'К'},
        {'Л', 'С'}, {'С', 'Л'},
        {'М', 'Р'}, {'Р', 'М'},
        {'Н', 'П'}, {'П', 'Н'},
        {'б', 'щ'}, {'щ', 'б'},
        {'в', 'ш'}, {'ш', 'в'},
        {'г', 'ч'}, {'ч', 'г'},
        {'д', 'ц'}, {'ц', 'д'},
        {'ж', 'х'}, {'х', 'ж'},
        {'з', 'ф'}, {'ф', 'з'},
        {'к', 'т'}, {'т', 'к'},
        {'л', 'с'}, {'с', 'л'},
        {'м', 'р'}, {'р', 'м'},
        {'н', 'п'}, {'п', 'н'},
        {' ', '#'}
};

// Функция для чтения содержимого файла в строку
string readFileToString2(const string& fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        throw runtime_error("Файл не найден");
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string fileContent = buffer.str();

    if (fileContent.empty()) {
        throw runtime_error("Ошибка чтения файла. Проверьте содержимое файла.\n");
    }

    return fileContent;
}

string encryptTarabar(const string& text, map<char, char>& GramotaRus) {
    string encryptedGramota; // Инициализация строки для хранения зашифрованного текста
    for (char c : text) { // Цикл по символам входного текста
        if (GramotaRus.count(c)) { // Проверка, есть ли текущий символ в словаре GramotaRus
            encryptedGramota += GramotaRus[c]; // Если символ найден в словаре, добавляем его зашифрованный аналог к строке зашифрованного текста
        }
        else { // Если символ не найден в словаре
            encryptedGramota += c; // Просто добавляем символ к зашифрованному тексту без изменений
        }
    }
    return encryptedGramota; // Возвращаем зашифрованный текст
}


string decryptTarabar(const string& text, map <char, char>& Gramota) {
    string decryptedGramota; // Инициализация строки для хранения расшифрованного текста
    for (char c : text) { // Цикл по символам входного текста
        bool found = false; // переменная для отслеживания нахождения символа в словаре Gramota
        for (const auto& pair : Gramota) { // Цикл по парам символов в словаре Gramota
            if (pair.second == c) { // Если второй символ пары равен текущему символу из входного текста
                decryptedGramota += pair.first; // Добавляем первый символ пары к расшифрованному тексту
                found = true; // Устанавливаем флаг, что символ найден
                break; // Выходим из внутреннего цикла, так как символ найден
            }
        }
        if (!found) { // Если символ не был найден в словаре Gramota
            decryptedGramota += c; // Просто добавляем символ к расшифрованному тексту без изменений
        }
    }
    return decryptedGramota; // Возвращаем расшифрованный текст
}


void DisplayGramota() {
    setlocale(LC_ALL, "Russian");

    while (true) {
        string inputTarabar;
        string fileName;
        cout << "Введите имя файла: ";
        cin >> fileName;

        try {
            inputTarabar = readFileToString2(fileName);

        } catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
            break;
        }

        try {
            // Открытие файла для записи
            ofstream outputFile("encryptedTarabar.txt");
            if (!outputFile.is_open()) {
                throw runtime_error("Файл не найден.\n");
            }

            string encryptedTarabar; // строка для зашифрованного текста
            encryptedTarabar = encryptTarabar(inputTarabar, TarabarEng);

            outputFile << encryptedTarabar;
            outputFile.close();
            cout << "Зашифрованный текст записан в encryptedTarabar.txt\n";
            cout << "Зашифрованный текст: " << encryptedTarabar << "\n";

            // Открытие файла для чтения
            ifstream inputFile("encryptedTarabar.txt");
            if (!inputFile.is_open()) {
                throw runtime_error("Файл не найден.\n");
            }

            string decryptedTarabar;
            getline(inputFile, decryptedTarabar);
            inputFile.close();

            decryptedTarabar = decryptTarabar(decryptedTarabar, TarabarEng);

            // Запись расшифрованного текста в файл decryptedTarabar.txt
            ofstream decryptFile("decryptedTarabar.txt");
            if (!decryptFile.is_open()) {
                throw runtime_error("Файл не найден.\n");
            }

            decryptFile << decryptedTarabar;
            decryptFile.close();
            cout << "Расшифрованный текст записан в decryptedTarabar.txt\n";

            cout << "Расшифрованный текст: " << decryptedTarabar << "\n";

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