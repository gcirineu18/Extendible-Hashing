//-------------------------------------------------------------------------------
//g++ -o executavel2 arq_bru.cpp
// ./executavel2

#include "hashExtensivel.h"
#include <iostream>
#include <string>
#include <stack>
#include <math.h>
#include <fstream>
#include <typeinfo>
using namespace std;


int main(){
  HashExtensivel obj;
  
  ifstream arq1("D:/banco_tabalho1_sgbd/in.txt"); //p abrir e ler o arquivo

  if(!arq1.is_open()){ //tratamento caso nao seja possivel ler o arquivo
    cout<<"Erro ao abrir arquivo!\n"<<endl;
    return -1;
  }


  //recupera o PG
  string prim_linha; 
  getline(arq1, prim_linha); //pega a 1a linha do arquivo
  prim_linha.erase(0,3); //exclui os 3 primeiros caracteres "PG/"
  int pg = stoi(prim_linha); //transforma de string p/ int
  cout<<pg<<endl;

  //cria hash com o PG
  obj.criaHash(pg); 

  //reseta o estado do arquivo e o ponteiro pro começo do arq
  arq1.clear();
  arq1.seekg(0);

  //ler cada linha do arq e procurar os comandos
  string line1;
  while(getline(arq1, line1)){ 
    string com;
    com = line1.substr(0,3); //recupera o comando da linha
    string ano;
    ano = line1.substr(4,4); //recupera o ano da linha

    if(com == "INC"){ //*comando de INC (INCLUSÃO)*
      cout<<com<<ano<<endl;
      //insereHash(ano);
      }
    else if(com == "REM"){ //*comando de REM (REMOÇÃO)*
      cout<<com<<ano<<endl;
      //removeHash(ano);
      }
    else if(com == "BUS"){ //*comando de BUS (BUSCA)*
      cout<<com<<ano<<endl;
      //buscaHash(ano);
      }
    else if(com != "INC" or "REM" or "BUS"){
      cout<<"Comando da linha eh invalido"<<endl;
    }
    }


  arq1.close();

  //ofstream arq2;
  //arq2.open(diretorio+"out.txt");


  return 0;
}
//--------------------------------------------------------------------------------
