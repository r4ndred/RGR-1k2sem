#ifndef RGR_CIPHER_H
#define RGR_CIPHER_H


#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <set>

using namespace std;

string readFileToString(const string& fileName);
string encryptCipher(const string& text, int k, const vector<int>& permutation);
string decryptCipher(const string& text, int k, const vector<int>& permutation);
void displayCipher();



#endif //RGR_CIPHER_H