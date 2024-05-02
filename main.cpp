#include "hashExtensivel.h"
//#include "hash2.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stack>
#include <math.h>
#include <typeinfo>
#include <sstream>

using namespace std;

int main(){  
  

  HashExtensivel obj;
  ifstream arq_in("D:/banco_tabalho1_sgbd/in.txt"); 

  if(!arq_in.is_open()){ 
    cout<<"Erro ao abrir arquivo!\n"<<endl;
    return -1;
  }

  //recuperando o pg
  string prim_linha; 
  getline(arq_in, prim_linha); 
  prim_linha.erase(0,3); 
  int pg = stoi(prim_linha); 
  obj.criaHash(pg); //criando a hash
  obj.Apagabuckets();
  
  arq_in.clear();
  arq_in.seekg(0);

  string line1;
  string com;
  string ano_str;
  int ano; 


  while(getline(arq_in, line1)){ 
   
    com = line1.substr(0,3);   
    if(com != "INC" && com !=  "REM" && com != "BUS"){
      
      continue;
    }
    else{
      ano_str = line1.substr(4,4);
      ano = stoi(ano_str);
     
    if(com == "INC"){ 
      obj.insereHash(pg, ano);
      }
    else if(com == "REM"){ 
     obj.removeHash(ano);
      }

    else if(com == "BUS"){
     obj.buscaHash(ano);
      }
    }
  }
  arq_in.close();

  return 0;

}

