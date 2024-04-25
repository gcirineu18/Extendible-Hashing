#include "hashExtensivel.h"
//#include "hash2.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
using namespace std;

int main(){
  
  HashExtensivel obj;
  int aux = obj.funcaoHash(4,1998);
  int aux2 = obj.funcaoHashAlternativa(3,1998);

//  cout<<"O indice com funcao hash aplicada eh: "<<aux<<endl;
 // cout<<"O indice com funcao hash alternativa aplicada eh: "<<aux2<<endl;


  ifstream arq("D:/banco_tabalho1_sgbd/in.txt"); //p ler o arquivo
 
  if(!arq.is_open()){ //tratamento caso nao seja possivel ler o arquivo
    cout<<"Erro ao abrir arquivo!\n"<<endl;
    //return -1;
  }

  // string line;
  // while(getline(arq, line)){ //getline: pega uma linha do arq e coloca em line
  //   cout<<line<<endl;        //imprime cada linha
  // }

  arq.close();

  obj.criaHash(2);
 obj.insereHash(2,2013);
 // obj.insereHash(2,1992);
  //obj.buscaHash(2013, 2);
  obj.duplicaDiretorio(2,2013);
  return 0;
}


