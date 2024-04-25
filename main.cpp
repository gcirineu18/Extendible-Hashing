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

using namespace std;

int main(){
  HashExtensivel obj;
  
  ifstream arq1("D:/banco_tabalho1_sgbd/in.txt"); 

  if(!arq1.is_open()){ 
    cout<<"Erro ao abrir arquivo!\n"<<endl;
    return -1;
  }


  string prim_linha; 
  getline(arq1, prim_linha); 
  prim_linha.erase(0,3); 
  int pg = stoi(prim_linha); 
  //cout<<pg<<endl;

  obj.criaHash(pg); 
  arq1.clear();
  arq1.seekg(0);

  string line1;
  string com;
  string anostr;
  int ano;
  while(getline(arq1, line1)){ 
   
    com = line1.substr(0,3);
      
     if(com != "INC" && com !=  "REM" && com != "BUS"){
        cout<<"Testando 4234"<<endl;
      continue;
    }
    else{
    anostr = line1.substr(4,4);
    ano = stoi(anostr);
     
    if(com == "INC"){ 

      obj.insereHash(pg,ano);
      }
    else if(com == "REM"){ 
      
      obj.removeHash(ano);
      }
    else if(com == "BUS"){ 
      
      obj.buscaHash(ano);
      }
    
    }
 
    }


  arq1.close();

  //ofstream arq2;
  //arq2.open(diretorio+"out.txt");


  return 0;
}
//--------------------------------------------------------------------------------
