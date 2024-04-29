#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main() {
    string input = "9,7145.41,2013";
    stringstream ss(input);
    string line;

    // Ignorar as duas primeiras linhas
    for (int i = 0; i < 3; ++i) {
        getline(ss, line, ','); // Descartar a linha
        cout<<line<<endl;
       // getline(ss, line, ','); // Descartar a segunda parte da linha
    }

    // Agora obter o valor da próxima linha
  //  getline(ss, line, ',');

    // Saída do valor
    cout << "Valor depois da segunda linha: " << line << std::endl;

    return 0;
}
