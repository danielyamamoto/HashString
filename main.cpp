/*
Dado un string, se crea una matriz de n columnas (16 <= n <= 64), donde se suman todos 
los caracteres de dicha columna para posteriormente transfomarlo/procesarlo a hexadecimal. 
Dando como resultado un Hash String. La salida son los hexadecimales concatenados, es decir, el Hash String.

Autores:
A01653120 - Yusdivia Molina Román
A01658318 - Jesús Daniel Lara Yamamoto
A01023808 - Héctor Arturo Noyola Mondragón

Fecha de modificación: 07/09/2021
*/

#include <iostream>
#include <string>
#include <algorithm> 
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

// Crea la matriz de los caracteres
// Complejidad O(2n)
vector<vector<char>> createTable(string s, int n) {
    vector<vector<char>> table;
    vector<char> tmp;
    while(s.size() % n != 0) {
        char tem = n + '0';
        s.push_back(tem);
    }
    cout << "String to convert " << s << endl;
    for (int i = 1; i < s.size() + 1; i++) {
        tmp.push_back(s[i-1]);
        if(i % n == 0){
            table.push_back(tmp);
            tmp.clear();
        }
    }
    return table;
}

// Lee el archivo y regresa la matriz de los caracteres a través de la función createTable
//Complejidad O(n) + O(2n) ---> O(n)
vector<vector<char>> readFile(string file) {
    string en, str, strResult;
    fstream f;
    f.open(file);
    getline(f, en);
    int entero = stoi(en);
    while(!f.eof()) {
        getline(f, str);
        strResult += str;
        if(!f.eof()) {
            strResult += "\n";
        }
    }
    return createTable(strResult, entero); // Complejidad O(2n)
}

// Imprime la tabla de caracteres
// Complejidad O(n^2)
void printTable(vector<vector<char>> c) {
    for (int i = 0; i < c.size(); i++) {
        for (int j = 0; j < c[i].size(); j++) {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
}

// Se obtiene el módulo de 256 de la suma de todos los caracteres por columna
// Complejidad O(n^2)
vector<int> intToHex(vector<vector<char>> c) {
    vector<int> a;
    for (int i = 0; i < c[i].size(); i++) {
        int sum = 0;
        for (int j = 0; j < c.size(); j++) {
            sum += int(c[j][i]);
        }
        sum %= 256;
        a.push_back(sum);
    }
    cout << endl;
    return a;
}

// Convierte los enteros a hexadecimal y los concatena en forma de string
//Complejidad O(n)
string toHash(vector<int> v) {
    string hash;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] < 10) {
            string str = "0";
            str += to_string(v[i]);
            hash += str;
        } else {
            std::stringstream sstream;
            sstream << std::hex << v[i];
            hash += sstream.str();
        }
    }
    // Transforma las minúsculas a mayúsculas
    transform(hash.begin(), hash.end(), hash.begin(), ::toupper);
    return hash;
}

int main() {
    vector<vector<char>> matrix = readFile("in.txt");
    cout << "Table: ";
    printTable(matrix);

    vector<int> hexs = intToHex(matrix);
    string hash = toHash(hexs);
    cout << "HASH: " + hash << endl;
    
    return 0;
}