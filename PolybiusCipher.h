#ifndef RGR_POLYBIUS_CIPHER
#define RGR_POLYBIUS_CIPHER
#include <string>
#include <map>

using namespace std;

map<char, string> createPolybiusSquareEng();
map<char, string> createPolybiusSquareRus();
map<string, char> createReversePolybiusSquareEng();
map<string, char> createReversePolybiusSquareRus();
string encryptPolybius(const string& text, const map<char, string>& polybiusSquare);
string decryptPolybius(const string& text, const map<string, char>& reversePolybiusSquare);
void DisplayPolybius();

#endif