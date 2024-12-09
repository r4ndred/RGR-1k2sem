#include <iostream>
#include <fstream>
#include <stdexcept>
#include <codecvt>
#include <Windows.h>
#include "PolybiusCipher.h"

// Функция для создания квадратов Полибия для английского алфавита (заглавные буквы)
map<char, string> createPolybiusSquareEngUpper() {
    map<char, string> polybiusSquare;
    polybiusSquare['A'] = "11"; polybiusSquare['B'] = "12"; polybiusSquare['C'] = "13"; polybiusSquare['D'] = "14"; polybiusSquare['E'] = "15";
    polybiusSquare['F'] = "21"; polybiusSquare['G'] = "22"; polybiusSquare['H'] = "23"; polybiusSquare['I'] = "24"; polybiusSquare['J'] = "26"; polybiusSquare['K'] = "25";
    polybiusSquare['L'] = "31"; polybiusSquare['M'] = "32"; polybiusSquare['N'] = "33"; polybiusSquare['O'] = "34"; polybiusSquare['P'] = "35";
    polybiusSquare['Q'] = "41"; polybiusSquare['R'] = "42"; polybiusSquare['S'] = "43"; polybiusSquare['T'] = "44"; polybiusSquare['U'] = "45";
    polybiusSquare['V'] = "51"; polybiusSquare['W'] = "52"; polybiusSquare['X'] = "53"; polybiusSquare['Y'] = "54"; polybiusSquare['Z'] = "55";
    return polybiusSquare;
}

// Функция для создания квадратов Полибия для английского алфавита (строчные буквы)
map<char, string> createPolybiusSquareEngLower() {
    map<char, string> polybiusSquare;
    polybiusSquare['a'] = "11"; polybiusSquare['b'] = "12"; polybiusSquare['c'] = "13"; polybiusSquare['d'] = "14"; polybiusSquare['e'] = "15";
    polybiusSquare['f'] = "21"; polybiusSquare['g'] = "22"; polybiusSquare['h'] = "23"; polybiusSquare['i'] = "24"; polybiusSquare['j'] = "26"; polybiusSquare['k'] = "25";
    polybiusSquare['l'] = "31"; polybiusSquare['m'] = "32"; polybiusSquare['n'] = "33"; polybiusSquare['o'] = "34"; polybiusSquare['p'] = "35";
    polybiusSquare['q'] = "41"; polybiusSquare['r'] = "42"; polybiusSquare['s'] = "43"; polybiusSquare['t'] = "44"; polybiusSquare['u'] = "45";
    polybiusSquare['v'] = "51"; polybiusSquare['w'] = "52"; polybiusSquare['x'] = "53"; polybiusSquare['y'] = "54"; polybiusSquare['z'] = "55";
    return polybiusSquare;
}

// Функция для создания квадратов Полибия для русского алфавита (заглавные буквы)
map<char, string> createPolybiusSquareRusUpper() {
    map<char, string> polybiusSquare;
    polybiusSquare['А'] = "11"; polybiusSquare['Б'] = "12"; polybiusSquare['В'] = "13"; polybiusSquare['Г'] = "14"; polybiusSquare['Д'] = "15"; polybiusSquare['Е'] = "16";
    polybiusSquare['Ё'] = "21"; polybiusSquare['Ж'] = "22"; polybiusSquare['З'] = "23"; polybiusSquare['И'] = "24"; polybiusSquare['Й'] = "25"; polybiusSquare['К'] = "26";
    polybiusSquare['Л'] = "31"; polybiusSquare['М'] = "32"; polybiusSquare['Н'] = "33"; polybiusSquare['О'] = "34"; polybiusSquare['П'] = "35"; polybiusSquare['Р'] = "36"; 
    polybiusSquare['С'] = "41"; polybiusSquare['Т'] = "42"; polybiusSquare['У'] = "43"; polybiusSquare['Ф'] = "44"; polybiusSquare['Х'] = "45"; polybiusSquare['Ц'] = "46"; 
    polybiusSquare['Ч'] = "51"; polybiusSquare['Ш'] = "52"; polybiusSquare['Щ'] = "53"; polybiusSquare['Ъ'] = "54"; polybiusSquare['Ы'] = "55"; polybiusSquare['Ь'] = "56"; 
    polybiusSquare['Э'] = "61"; polybiusSquare['Ю'] = "62"; polybiusSquare['Я'] = "63";
    return polybiusSquare;
}

// Функция для создания квадратов Полибия для русского алфавита (строчные буквы)
map<char, string> createPolybiusSquareRusLower() {
    map<char, string> polybiusSquare;
    polybiusSquare['а'] = "11"; polybiusSquare['б'] = "12"; polybiusSquare['в'] = "13"; polybiusSquare['г'] = "14"; polybiusSquare['д'] = "15"; polybiusSquare['е'] = "16";
    polybiusSquare['ё'] = "21"; polybiusSquare['ж'] = "22"; polybiusSquare['з'] = "23"; polybiusSquare['и'] = "24"; polybiusSquare['й'] = "25"; polybiusSquare['к'] = "26";
    polybiusSquare['л'] = "31"; polybiusSquare['м'] = "32"; polybiusSquare['н'] = "33"; polybiusSquare['о'] = "34"; polybiusSquare['п'] = "35"; polybiusSquare['р'] = "36"; 
    polybiusSquare['с'] = "41"; polybiusSquare['т'] = "42"; polybiusSquare['у'] = "43"; polybiusSquare['ф'] = "44"; polybiusSquare['х'] = "45"; polybiusSquare['ц'] = "46"; 
    polybiusSquare['ч'] = "51"; polybiusSquare['ш'] = "52"; polybiusSquare['щ'] = "53"; polybiusSquare['ъ'] = "54"; polybiusSquare['ы'] = "55"; polybiusSquare['ь'] = "56"; 
    polybiusSquare['э'] = "61"; polybiusSquare['ю'] = "62"; polybiusSquare['я'] = "63";
    return polybiusSquare;
}

// Функция для создания обратных квадратов Полибия для английского алфавита (заглавные буквы)
map<string, char> createReversePolybiusSquareEngUpper() {
    map<string, char> reversePolybiusSquare;
    reversePolybiusSquare["11"] = 'A'; reversePolybiusSquare["12"] = 'B'; reversePolybiusSquare["13"] = 'C'; reversePolybiusSquare["14"] = 'D'; reversePolybiusSquare["15"] = 'E';
    reversePolybiusSquare["21"] = 'F'; reversePolybiusSquare["22"] = 'G'; reversePolybiusSquare["23"] = 'H'; reversePolybiusSquare["24"] = 'I'; reversePolybiusSquare["26"] = 'J'; reversePolybiusSquare["25"] = 'K';
    reversePolybiusSquare["31"] = 'L'; reversePolybiusSquare["32"] = 'M'; reversePolybiusSquare["33"] = 'N'; reversePolybiusSquare["34"] = 'O'; reversePolybiusSquare["35"] = 'P';
    reversePolybiusSquare["41"] = 'Q'; reversePolybiusSquare["42"] = 'R'; reversePolybiusSquare["43"] = 'S'; reversePolybiusSquare["44"] = 'T'; reversePolybiusSquare["45"] = 'U';
    reversePolybiusSquare["51"] = 'V'; reversePolybiusSquare["52"] = 'W'; reversePolybiusSquare["53"] = 'X'; reversePolybiusSquare["54"] = 'Y'; reversePolybiusSquare["55"] = 'Z';
    return reversePolybiusSquare;
}

// Функция для создания обратных квадратов Полибия для английского алфавита (строчные буквы)
map<string, char> createReversePolybiusSquareEngLower() {
    map<string, char> reversePolybiusSquare;
    reversePolybiusSquare["11"] = 'a'; reversePolybiusSquare["12"] = 'b'; reversePolybiusSquare["13"] = 'c'; reversePolybiusSquare["14"] = 'd'; reversePolybiusSquare["15"] = 'e';
    reversePolybiusSquare["21"] = 'f'; reversePolybiusSquare["22"] = 'g'; reversePolybiusSquare["23"] = 'h'; reversePolybiusSquare["24"] = 'i'; reversePolybiusSquare["26"] = 'j'; reversePolybiusSquare["25"] = 'k';
    reversePolybiusSquare["31"] = 'l'; reversePolybiusSquare["32"] = 'm'; reversePolybiusSquare["33"] = 'n'; reversePolybiusSquare["34"] = 'o'; reversePolybiusSquare["35"] = 'p';
    reversePolybiusSquare["41"] = 'q'; reversePolybiusSquare["42"] = 'r'; reversePolybiusSquare["43"] = 's'; reversePolybiusSquare["44"] = 't'; reversePolybiusSquare["45"] = 'u';
    reversePolybiusSquare["51"] = 'v'; reversePolybiusSquare["52"] = 'w'; reversePolybiusSquare["53"] = 'x'; reversePolybiusSquare["54"] = 'y'; reversePolybiusSquare["55"] = 'z';
    return reversePolybiusSquare;
}

// Функция для создания обратных квадратов Полибия для русского алфавита (заглавные буквы)
map<string, char> createReversePolybiusSquareRusUpper() {
    map<string, char> reversePolybiusSquare;
    reversePolybiusSquare["11"] = 'А'; reversePolybiusSquare["12"] = 'Б'; reversePolybiusSquare["13"] = 'В'; reversePolybiusSquare["14"] = 'Г'; reversePolybiusSquare["15"] = 'Д'; reversePolybiusSquare["16"] = 'Е'; 
    reversePolybiusSquare["21"] = 'Ё'; reversePolybiusSquare["22"] = 'Ж'; reversePolybiusSquare["23"] = 'З'; reversePolybiusSquare["24"] = 'И'; reversePolybiusSquare["25"] = 'Й'; reversePolybiusSquare["26"] = 'К';
    reversePolybiusSquare["31"] = 'Л'; reversePolybiusSquare["32"] = 'М'; reversePolybiusSquare["33"] = 'Н'; reversePolybiusSquare["34"] = 'О'; reversePolybiusSquare["35"] = 'П'; reversePolybiusSquare["36"] = 'Р'; 
    reversePolybiusSquare["41"] = 'С'; reversePolybiusSquare["42"] = 'Т'; reversePolybiusSquare["43"] = 'У'; reversePolybiusSquare["44"] = 'Ф'; reversePolybiusSquare["45"] = 'Х'; reversePolybiusSquare["46"] = 'Ц'; 
    reversePolybiusSquare["51"] = 'Ч'; reversePolybiusSquare["52"] = 'Ш'; reversePolybiusSquare["53"] = 'Щ'; reversePolybiusSquare["54"] = 'Ъ'; reversePolybiusSquare["55"] = 'Ы'; reversePolybiusSquare["56"] = 'Ь'; 
    reversePolybiusSquare["61"] = 'Э'; reversePolybiusSquare["62"] = 'Ю'; reversePolybiusSquare["63"] = 'Я';
    return reversePolybiusSquare;
}

// Функция для создания обратных квадратов Полибия для русского алфавита (строчные буквы)
map<string, char> createReversePolybiusSquareRusLower() {
    map<string, char> reversePolybiusSquare;
    reversePolybiusSquare["11"] = 'а'; reversePolybiusSquare["12"] = 'б'; reversePolybiusSquare["13"] = 'в'; reversePolybiusSquare["14"] = 'г'; reversePolybiusSquare["15"] = 'д'; reversePolybiusSquare["16"] = 'е'; 
    reversePolybiusSquare["21"] = 'ё'; reversePolybiusSquare["22"] = 'ж'; reversePolybiusSquare["23"] = 'з'; reversePolybiusSquare["24"] = 'и'; reversePolybiusSquare["25"] = 'й'; reversePolybiusSquare["26"] = 'к';
    reversePolybiusSquare["31"] = 'л'; reversePolybiusSquare["32"] = 'м'; reversePolybiusSquare["33"] = 'н'; reversePolybiusSquare["34"] = 'о'; reversePolybiusSquare["35"] = 'п'; reversePolybiusSquare["36"] = 'р'; 
    reversePolybiusSquare["41"] = 'с'; reversePolybiusSquare["42"] = 'т'; reversePolybiusSquare["43"] = 'у'; reversePolybiusSquare["44"] = 'ф'; reversePolybiusSquare["45"] = 'х'; reversePolybiusSquare["46"] = 'ц'; 
    reversePolybiusSquare["51"] = 'ч'; reversePolybiusSquare["52"] = 'ш'; reversePolybiusSquare["53"] = 'щ'; reversePolybiusSquare["54"] = 'ъ'; reversePolybiusSquare["55"] = 'ы'; reversePolybiusSquare["56"] = 'ь'; 
    reversePolybiusSquare["61"] = 'э'; reversePolybiusSquare["62"] = 'ю'; reversePolybiusSquare["63"] = 'я';
    return reversePolybiusSquare;
}

// Функция шифрования текста с использованием квадрата Полибия
string encryptPolybius(const string& text, const map<char, string>& polybiusSquare) {
    string encryptedText;
    for (char c : text) {
        // Проверяем наличие символа в таблице и заменяем его
        if (polybiusSquare.count(c) > 0) {
            encryptedText += polybiusSquare.at(c);
        } else {
            // Добавляем символ без изменений, если его нет в таблице
            encryptedText += c;
        }
    }
    return encryptedText;
}

// Функция расшифровки текста с использованием обратного квадрата Полибия
string decryptPolybius(const string& text, const map<string, char>& reversePolybiusSquare) {
    string decryptedText;
    string symbol;
    for (char c : text) {
        if (isdigit(c)) { // Проверяем, является ли символ цифрой
            symbol += c;
            if (symbol.length() == 2) { // Если длина символа 2, проверяем его в обратной таблице
                if (reversePolybiusSquare.count(symbol) > 0) {
                    decryptedText += reversePolybiusSquare.at(symbol);
                }
                symbol.clear();
            }
        } else {
            // Добавляем символ без изменений, если это не цифра
            decryptedText += c;
        }
    }
    return decryptedText;
}

// Основная функция для работы с шифром Полибия
void DisplayPolybius() {
    SetConsoleCP(1251); // Устанавливаем кодировку консоли на ввод
    SetConsoleOutputCP(1251); // Устанавливаем кодировку консоли на вывод
    while (true) {
        try {
            // Отображаем меню выбора языка
            cout << "---------------------------------\n";
            cout << "Выберите язык:\n1) English\n2) Русский\n3) Назад\n";
            cout << "---------------------------------\n";
            string languageChoice;
            getline(cin, languageChoice); // Считываем выбор пользователя

            // Проверяем корректность выбора
            if (languageChoice != "1" && languageChoice != "2" && languageChoice != "3") {
                throw invalid_argument("Неправильная команда. Нужно чтобы команда состояла из 1 символа: '1', '2' или '3'. Попробуйте еще раз.\n");
            }

            int languageAction = stoi(languageChoice); // Преобразуем выбор в целое число
            if (languageAction == 3) { // Если выбрано "Назад", выходим из цикла
                cout << "---------------------------------\n";
                break;
            }

            // Отображаем меню выбора регистра
            cout << "---------------------------------\n";
            cout << "Выберите регистр:\n1) Заглавные буквы\n2) Строчные буквы\n3) Назад\n";
            cout << "---------------------------------\n";
            string caseChoice;
            getline(cin, caseChoice); // Считываем выбор пользователя

            // Проверяем корректность выбора
            if (caseChoice != "1" && caseChoice != "2" && caseChoice != "3") {
                throw invalid_argument("Неправильная команда. Нужно чтобы команда состояла из 1 символа: '1', '2' или '3'. Попробуйте еще раз.\n");
            }

            int caseAction = stoi(caseChoice); // Преобразуем выбор в целое число
            if (caseAction == 3) { // Если выбрано "Назад", выходим из цикла
                cout << "---------------------------------\n";
                continue;
            }

            // Запрос текста для шифрования
            string inputText;
            cout << "Введите текст для шифрования: ";
            getline(cin >> ws, inputText); // ws игнорирует пробелы до ввода данных
            cout << "---------------------------------\n";

            map<char, string> polybiusSquare;
            map<string, char> reversePolybiusSquare;
            // Создание таблицы шифрования на основе выбранного языка и регистра
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

            // Шифруем текст
            string encryptedText = encryptPolybius(inputText, polybiusSquare);
            
            // Запись зашифрованного текста в файл
            ofstream outputFile("encryptedPolybius.txt");
            if (!outputFile.is_open()) {
                throw runtime_error("Не удалось открыть файл для записи.\n");
            }
            outputFile << encryptedText;
            outputFile.close(); // Закрываем файл после записи
            cout << "Зашифрованный текст сохранен в файл encryptedPolybius.txt\n";
            cout << "Зашифрованный текст: " << encryptedText << "\n";
            cout << "---------------------------------\n";

            // Чтение зашифрованного текста из файла
            ifstream inputFile("encryptedPolybius.txt");
            if (!inputFile.is_open()) {
                throw runtime_error("Не удалось открыть файл для чтения.\n");
            }
            string readEncryptedText;
            getline(inputFile, readEncryptedText);
            inputFile.close(); // Закрываем файл после чтения

            // Расшифровываем текст
            string decryptedText = decryptPolybius(readEncryptedText, reversePolybiusSquare);
            cout << "Расшифрованный текст: " << decryptedText << "\n";

            // Запись расшифрованного текста в файл
            ofstream decryptFile("decryptedPolybius.txt");
            if (!decryptFile.is_open()) {
                throw runtime_error("Не удалось открыть файл для записи.\n");
            }
            decryptFile << decryptedText;
            decryptFile.close(); // Закрываем файл после записи
            cout << "Расшифрованный текст сохранен в файл decryptedPolybius.txt\n";
            cout << "---------------------------------\n";
        }
        // Обработка исключений при неверном вводе команды или ошибках работы с файлами
        catch (const invalid_argument& e) {
            cerr << "Ошибка: " << e.what();
        }
        catch (const runtime_error& e) {
            cerr << "Ошибка: " << e.what();
        }
    }
}