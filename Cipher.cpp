#include "Cipher.h"

// Функция для чтения содержимого файла в строку
string readFileToString(const string& fileName) {
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

// Функция для шифрования текста
string encryptCipher(const string& text, int k, const vector<int>& permutation) {
    string resultCipher; // Переменная для хранения зашифрованного текста

    for (size_t i = 0; i < text.size(); i += k) {    // Проход по тексту блоками длиной k
        for (int j = 0; j < k; j++) { // Внутренний цикл проходит по каждому символу в текущем блоке длиной k.
            // Проверка, что индекс находится в пределах строки
            if (i + permutation[j] - 1 < text.size()) {
                // Добавление символа в результат, используя перестановку
                resultCipher += text[i + permutation[j] - 1];
            }
            else { // Если текущий блок заканчивается раньше, чем требуемое количество символов, добавляется пробел.
                resultCipher += ' ';
            }
        }
    }
    return resultCipher; // Возвращаем зашифрованный текст
}


string decryptCipher(const string& text, int k, const vector<int>& permutation) {
    string resultCipher; // Переменная для хранения результата дешифрования
    vector<int> inverse_permutation(k); // Вектор для хранения обратной перестановки

    // Вычисление обратной перестановки
    for (int i = 0; i < k; i++) {
        inverse_permutation[permutation[i] - 1] = i + 1; //возвращаем обычную последовательность
    }

    // Проход по тексту блоками длиной k
    for (size_t i = 0; i < text.size(); i += k) {
        for (int j = 0; j < k; j++) {
            // Проверка, что индекс находится в пределах строки
            if (i + inverse_permutation[j] - 1 < text.size()) {
                // Добавление символа в результат, используя обратную перестановку
                resultCipher += text[i + inverse_permutation[j] - 1];
            }
        }
    }
    return resultCipher; // Возвращаем результат дешифрования
}

void displayCipher() {
    setlocale(LC_ALL, "Russian");
    while (true) {
        try {

            int k; // переменная для работы с шифром
            while (true) {
                try {
                    cout << "Введите значение k (количество символов для перестановки в группе): ";
                    string input;
                    getline(cin, input);

                    // Проверка наличия пробелов
                    if (input.find(' ') != string::npos) { //string::npos  является константой, обозначающей "не найдено".
                        throw invalid_argument("Введите одно число без пробелов.\n");
                    }

                    stringstream ss(input); //  преобразуем введеную строку в поток
                    if (ss >> k && k > 0 && ss.eof()) { //проверка на 1) k больше 0 2)конец потока. также извлекаем значение из потока в k.
                        break;
                    }
                    else {
                        throw invalid_argument("Введите корректное натуральное значение для k(без пробелов).\n");
                    }
                }
                catch (const invalid_argument& e) {
                    cerr << "Ошибка: " << e.what();
                    continue; // Повторяем цикл при ошибке ввода
                }
            }

            vector<int> permutation(k); //вектор последовательности
            set<int> uniqueNumbers; // Множество для проверки уникальности чисел

            while (true) { // Цикл для ввода всей последовательности
                try {
                    uniqueNumbers.clear();
                    cout << "Введите последовательность из " << k << " чисел\n (перестановка символов, каждое число через пробел, используя числа от 1 до " << k <<"): ";

                    for (int i = 0; i < k; i++) { // Цикл по каждому элементу перестановки
                        int number; // Временная переменная для хранения чисел ввода
                        if (!(cin >> number) || number < 1 || number > k || !uniqueNumbers.insert(number).second) { // Проверка 1)успешность считывания из потока 2) диапазон число от 1 до k 3)что число является уникальным.
                            cin.clear(); //возвращаем поток в рабочее состояние, если была ошибка ввода
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //игнорируем максимальное число символов  в потоке ,включая символ новой строки.
                            throw invalid_argument("Введена неправильная последовательность. Последовательность должна включать в себя цифры от 1 до " + to_string(k) + " без повторений.\n");
                        }
                        permutation[i] = number; // Сохранение числа в векторе перестановки
                    }

                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем остаток строки
                    break; // Выходим из цикла при успешном вводе всей последовательности
                }
                catch (const invalid_argument& e) {
                    cerr << "Ошибка: " << e.what();
                    // Сообщаем пользователю об ошибке и просим ввести последовательность заново
                    cout << "Введите последовательность заново.\n";
                }
            }

            string inputCipher;
            string fileName;
            cout << "Введите имя файла: ";
            cin >> fileName;

            try {
                inputCipher = readFileToString(fileName);

            } catch (const exception& e) {
                cerr << "Ошибка: " << e.what() << endl;
                break;
            }

            // Открытие файла для записи зашифрованного текста
            ofstream encryptedFile("encryptedCipher.txt");
            if (!encryptedFile.is_open()) {
                throw runtime_error("Файл не найден.\n");
            }

            string encryptedCipher = encryptCipher(inputCipher, k, permutation);
            encryptedFile << encryptedCipher;
            encryptedFile.close();
            cout << "Зашифрованный текст сохранен в файл encryptedCipher.txt\n";
            cout << "Зашифрованный текст: " << encryptedCipher << "\n";

            // Открытие файла для чтения зашифрованного текста
            ifstream inputFile("encryptedCipher.txt");
            if (!inputFile.is_open()) {
                throw runtime_error("Файл не найден.\n");
            }

            getline(inputFile, encryptedCipher);
            inputFile.close();

            // Дешифрование текста
            string decryptedCipher = decryptCipher(encryptedCipher, k, permutation);

            // Открытие файла для записи расшифрованного текста
            ofstream decryptedFile("decryptedCipher.txt");
            if (!decryptedFile.is_open()) {
                throw runtime_error("Файл не найден.\n");
            }

            decryptedFile << decryptedCipher;
            decryptedFile.close();
            cout << "Расшифрованный текст сохранен в файл decryptedCipher.txt\n";
            cout << "Расшифрованный текст: " << decryptedCipher << "\n";

            break;

        }
        catch (const invalid_argument& e) {
            cerr << "Ошибка: " << e.what();
            continue; // Прекращаем цикл при ошибке ввода
        }
        catch (const runtime_error& e) {
            cerr << "Ошибка: " << e.what();
            break; // Прекращаем цикл при ошибке чтения/записи файла
        }
    }
}