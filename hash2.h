#ifndef hash2
#define hash2
#include <iostream>
#include <string>
#include <stack>
#include <math.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <typeinfo>
using namespace std;


class HashExtensivel{
public:  
  int pg; //profundidade global; 
  const string diretorio = "D:/banco_tabalho1_sgbd/indice/";
  int pgOriginal; //profundidade global inicial; 
  int* pl; //profundidade local;
  string* hash;

  public:
    int getPL(int i){
        return this->pl[i];
    }
     
   int funcaoHash(int pg, int indice){
         return indice & ((1<< pg) - 1);  
    }

    string* criaHash(int pg){
       this->pgOriginal = pg;
       this->pg = pg; 
       int aux = pow(2, pg);
       this->pl = new int[aux];
       this->hash = new string[aux];  
      ifstream arquivo1;
      
      arquivo1.open(diretorio+"indice.txt");
      if(arquivo1){
        cout << " ************Arquivo ja existente, apagando os dados...************" <<endl;
        ofstream arquivo1(diretorio+"indice.txt", ios::trunc);
        arquivo1.close();
      }
      ofstream arquivo2;
      arquivo2.open(diretorio+"indice.txt");
      if(!arquivo2){
        cerr<< " ************ Erro ao abrir arquivo ************" <<endl;
      }
      else{
        arquivo2 <<"PG:"<< pg <<endl;    
       
        for(int i=0; i<aux; i++){

        string filename=diretorio+"bucket/"+to_string(i)+".txt";
        
          ofstream arquivo3(filename);
          arquivo3.open(filename);
          
          if(arquivo3.is_open()){
            this->hash[i] = filename;
            
            this->pl[i] = pg;
            arquivo2<< i<<":"<<this->pl[i]<<":"<< this->hash[i]<<endl;               
          }    
          arquivo3.close();
        }    
      arquivo2.close(); 
      
      }      
    }

    int getSizeFile(const string fileName){
      ifstream file(fileName);
   
      int count=0;
      string line;
      while(getline(file,line)){
        count++;
        }   
      return count;
    }

  void insereHash(int pg, int ano){ 
      string aux = to_string(ano);   
      ifstream file;
      file.open("D:/banco_tabalho1_sgbd/compras.csv");

      if(!file){ //tratamento caso nao seja possivel ler o arquivo
         cout<<"Erro ao abrir arquivo compras.csv!\n"<<endl;
         return;
        }
      string line;
      int count = getSizeFile("D:/banco_tabalho1_sgbd/compras.csv");
      
      string lines[count];
        
      int i=0;
      int newCount=0;
      // Verifica as linhas do arquivo de compras que contem o ano
      while(getline(file,line) && i<count){
        if(line.find(aux) != string::npos){          
           lines[newCount] = line;                
           newCount++;
        }
        i++;      
    }
    
file.close();
if(newCount== 0){
      cout<<"Nao ha registros com este valor"<<endl;
    }
   
  int indiceAno= funcaoHash(this->pgOriginal, ano); 
  int pl = this->pl[indiceAno];
   int pgOriginal = this->pgOriginal;
   int indiceAtual = funcaoHash(pl,ano);
   
   int countLine;
   int total = pow(2,this->pg);
   string filename = diretorio+"bucket/"+to_string(indiceAtual)+".txt";
   

   if(bucketCheio(ano) ) {
    
    duplicaDiretorio(this->pg, ano,lines,newCount, false);  
   }
   else{
   
    if(getSizeFile(filename) +  newCount <=3){
       ofstream arquivo7;                 
      arquivo7.open(this->hash[indiceAtual], ios::app); 
      
      for(int j=0; j< newCount;j++){
          arquivo7<< lines[j]<<endl;
      
      }
     arquivo7.close();     
    }
    else{
     int funcao_hash;
    for(int k=this->pgOriginal; k<=this->pg; k++){
         funcao_hash  = funcaoHash(k, ano);
        
      if(this->pg > this->pgOriginal){         
       if(funcao_hash != funcaoHash(this->pgOriginal, ano)){     
        if(this->hash[funcao_hash] == this->hash[funcaoHash(this->pgOriginal, ano)]){
          

          string nomef = diretorio+"bucket/"+to_string(funcao_hash)+".txt";                          
          string nomef2 = diretorio+"bucket/"+to_string(funcaoHash(k-1, ano))+".txt";
          ifstream ifile(nomef2); 
         
          string line;
          string linhas1[3];                         
          this->hash[funcao_hash] = nomef;
          //Aumentando a PL
          int funcao_hash_original;
          int aux;
          for(int w=this->pgOriginal; w<=this->pg; w++){
            if(aux!=funcao_hash_original) this->pl[funcao_hash_original]++;
            aux = funcao_hash_original;
            
            funcao_hash_original = funcaoHash(w, ano);
          }
          int count = 0 ;               
          while(getline(ifile, line)){                
              linhas1[count] = line;
                                          
              count++;
               
          }
          ofstream ofile;
          // Limpando os dados do arquivo nomef2;
          ofile.open(nomef2);
          ofile.close();

          int newAno; 
          int funOriginal;
          int newFunHash; 
          ofstream ofile2;  
          if(nomef2 == nomef && (count +newCount)>3){
            cout<<"Testando"<<endl;
             continue;
          }   
           
          for(int j = 0; j<count; j++){ 
            newAno = getAnoDaLinha(linhas1[j]);
            funOriginal = funcaoHash(this->pgOriginal,newAno);
            newFunHash = funcaoHash(this->pl[funOriginal],newAno);                
            this->pl[newFunHash] = this->pl[funOriginal];
                                 
            this->hash[newFunHash] = diretorio+"bucket/"+to_string(newFunHash)+".txt";

            ofile2.open(diretorio+"bucket/"+to_string(newFunHash)+".txt",ios::app);
         
            ofile2 <<linhas1[j]<<endl;  
            ofile2.close(); 
   }  
  

           if( getSizeFile(nomef) + newCount > 3){
             
             if(this->pl[newFunHash] == this->pg){               
               duplicaDiretorio(this->pg, ano, lines,newCount, false );
               
             }
             else{
               continue;
             }
           }else{
             ofile.open(nomef);
          for(int d = 0; d< newCount; d++){
             ofile << lines[d]<<endl;
          } 
          ofile.close();
           } 
         
          break;
        }        
   }
        
}
     
 }   
 }                
}
imprimeDiretorio();
printf("INC:%d/<%d>,<%d>\n", ano, this->pg, this->pl[funcaoHash(this->pgOriginal,ano)]); 
      }   

 
  int getAnoDaLinha( string input){    
      stringstream ss(input);
       string line;
   
    for (int i = 0; i < 3; ++i) {
        getline(ss, line, ','); // Descartar a linha
    }
       return stoi(line);
    }
 /*
      Verificar antes todos os buckets associados ao indice
      do ano estão cheios
      */
   bool bucketCheio(int ano){
    bool ehsim = false;
    int idx1 = funcaoHash(this->pgOriginal,ano);
    int aux;
    if(this->pl[idx1] == this->pg){
      
       for(int j = this->pl[idx1] ; j<=this->pg;j++){
        aux = funcaoHash(j,ano);
          
        if (getSizeFile(this->hash[aux]) == 3){ 
         //  printf("pl %d, ano: %d\n", this->pl[idx1], ano);            
          for(int k = this->pl[idx1]; k<=this->pg;k++){ 
            if(k == j){        
              
            }
            else{             
              if(this->hash[k] == this->hash[j]){
                ehsim = false;
                break;
              }         
            }         
              ehsim = true;            
          }
        }
        else{

          ehsim = false;
          break;
        }        
       }

       if(ehsim){
          return true;
       }
       else{
       return false;
       }
    }
    else{
      return false;
    }
   } 
//****************************************************************************
    void duplicaDiretorio(int pg, int ano, string* linhas, int numberOfLines, bool sofreuRecursao){
     
      int pgAtualizada = pg+1;
      
      int totalRegistrosAnterior = pow(2,pg);
      int total = pow(2,pgAtualizada);
      this->pg++;

      int *newpl = new int[total];
      string *newHash = new string[total];

    for(int i=0; i<pow(2,pg); i++){
      newpl[i] = this->pl[i];
      newHash[i] = this->hash[i];
    }
     
    delete[] this->pl;
    this->pl = newpl; 
    delete[] this->hash;
    this->hash = newHash;  
    int funcao_Hash = funcaoHash(this->pgOriginal, ano);
    
    for(int i = totalRegistrosAnterior; i<total;i++){
      int funcao_hash = funcaoHash(this->pgOriginal,i);  
      this->pl[i] = this->pl[funcao_hash];
      this->hash[i] = "null";
    }
    int salva = -1;
    for(int k =this->pgOriginal; k <= this->pg; k++ ){   
      funcao_Hash = funcaoHash(k, ano);
      if(salva!=funcao_Hash) this->pl[funcao_Hash] += 1; 
       
      salva = funcao_Hash;
    }

      ifstream arquivo2;
      ofstream arquivo3;//("exemplo.txt", ios::app);
      arquivo2.open(diretorio+"indice.txt");
      arquivo3.open(diretorio+"indice.txt",ios::in);

      if(!arquivo2){
        cerr<< " ************ Erro ao abrir arquivo ************" <<endl;
      }

      string line;
      size_t found;
      bool aux10;   
      int i=0;
      string filename;

          
     int aux3;    
     ofstream ofile2;
     ifstream ifile2;
     ifstream iline;
  
     
     int funcao_hash = funcaoHash(this->pg, ano);
     int funcao_hash_anterior = funcaoHash(pg, ano);
     if(funcao_hash == funcao_hash_anterior){
      int funcaoAuxiliar = pg-1;
      while(funcao_hash == funcao_hash_anterior){
          funcao_hash_anterior = funcaoHash(funcaoAuxiliar,ano);
          funcaoAuxiliar--;
      }
     }
    
     for(int i=0; i<total; i++)  {       
           if(i == funcao_hash){  
            filename=diretorio+"bucket/"+to_string(i)+".txt"; 
                
            this->hash[i] = filename;
            ifile2.open(filename);
            bool verificador = false;
            
            if(!sofreuRecursao &&ifile2.good()){
              
              string zeilen[3];
              string zeile;
              int x=0;
              int auxiliar = 0;

              while(getline(ifile2, zeile)){                           
               zeilen[x] = zeile;                           
               x++;
               auxiliar++; 
              
               }
               
               int newAno,funOriginal,newFunHash; 
               for(int p=0; p<auxiliar; p++){
                 newAno = getAnoDaLinha(zeilen[p]);
                 funOriginal = funcaoHash(this->pgOriginal,newAno);
                 newFunHash = funcaoHash(this->pl[funOriginal],newAno);                
                  this->pl[newFunHash] = this->pl[funOriginal];
                                           
                 this->hash[newFunHash] = diretorio+"bucket/"+to_string(newFunHash)+".txt";
                 if(this->hash[newFunHash]== filename){
                    verificador = true;
                 }
                 ofile2.open(diretorio+"bucket/"+to_string(newFunHash)+".txt",ios::app); 
                 ofile2 <<zeilen[p]<<endl;  
                 ofile2.close(); 
                 
               }
              ifile2.close();
            } 
            if(verificador){
              ofile2.open(filename, ios::app);
            }else{
              ofile2.open(filename);
            }
              
       
            string filename3 = diretorio+"bucket/"+to_string(funcao_hash_anterior)+".txt";
              
            iline.open(filename3);              
            string line;
            string lines[3];
            int count  = 0;
            int y = 0;
            //Escrevendo o ultimo registro do bucket anterior no novo bucket
          
            while(getline(iline, line)){ 
               count++;
               lines[y] = line;                           
               y++;
               }
               
              ofile2.close();
              iline.close();
           
              // Esvazia todas as linhas do bucket anterior
              ofile2.open(diretorio+"bucket/"+to_string(funcao_hash_anterior)+".txt",ios::out);
              ofile2.close();
        
              int newAno;
              int newFunHash;
              int funOriginal;
             
              // Rescreve as linhas do bucket anterior para o atual                        
              for(int j = 0; j<count; j++){ 
                 newAno = getAnoDaLinha(lines[j]);
                 funOriginal = funcaoHash(this->pgOriginal,newAno);
                 newFunHash = funcaoHash(this->pl[funOriginal],newAno);                
                  this->pl[newFunHash] = this->pl[funOriginal];
                                           
                 this->hash[newFunHash] = diretorio+"bucket/"+to_string(newFunHash)+".txt";
                 ofile2.open(diretorio+"bucket/"+to_string(newFunHash)+".txt",ios::app); 
                 ofile2 <<lines[j]<<endl;  
                 ofile2.close(); 
                  
              }
               
         //escrevendo os dados no arquivo duplicado:
              ofstream ofile3;
              string filename2 = diretorio+"bucket/"+to_string(i)+".txt";
              ofile3.open(filename2,ios::app); 
              if((numberOfLines + getSizeFile(filename2)) >3){
                ofile3.close(); 
               filename2 = diretorio+"bucket/"+to_string(funcao_hash_anterior)+".txt";
               ofile3.open(filename2); 
               for(int j = 0; j<3; j++){
                   ofile3<<lines[j]<<endl;
               } 
               printf("DUP_DIR:/<%d>,<%d>\n",this->pg, this->pl[funcao_hash]);              
               duplicaDiretorio(this->pg,ano,linhas,numberOfLines, true);
            
               }    
              else{
                printf("DUP_DIR:/<%d>,<%d>\n",this->pg, this->pl[funcao_hash]); 
                
                for(int y = 0; y<numberOfLines; y++){
                  ofile3 << linhas[y] << endl;
                }
              }
              ofile3.close();                             
         }
         else {  
          // Apontando os novos indices para os buckets anteriores
       
          if(this->hash[i] == "null"){            
            aux3 = funcaoHash(this->pgOriginal, i);
           filename=diretorio+"bucket/"+to_string(aux3)+".txt"; 
           this->hash[i] = filename;      
          }
                
         }  
    }
    
   imprimeDiretorio();
    
    }

    void Apagabuckets(){
      string filename;
      ifstream ifile;    
      for (int i = 0; i<32; i++){
        filename = diretorio+"bucket/"+to_string(i)+".txt";       
        remove(filename.c_str());
      } 
    }
  
  void imprimeDiretorio(){
    string filename = (diretorio+"indice.txt");
    ofstream ofile(filename);
    int total = pow(2,this->pg);

   if(ofile.is_open()){ 
      for(int i=0; i<total; i++)  {
          if(i==0){
            ofile<<"PG:"<<this->pg<<endl;  
          }      
          ofile<< i<<":"<<this->pl[i]<<":"<< this->hash[i]<<endl;        
      } 
    }
    ofile.close();    
  }

  
void buscaHash(int ano){    
     int indiceAno= funcaoHash(this->pgOriginal, ano); 
       int pl = this->pl[indiceAno];
       int pgOriginal = this->pgOriginal;
       int indiceAtual = funcaoHash(pl,ano);
       
       ifstream ifile;
       string filename;
       
       string line;
       int count = 0;          
   
      filename=diretorio+"bucket/"+to_string(indiceAtual)+".txt";
      ifile.open(filename);
      while(getline(ifile,line)){
        if(line.find(to_string(ano)) != string::npos ){
          count++;
          
        }        
      }       
      ifile.close(); 
      printf("BUS:%d/<%d>\n",ano,count);

}


  void removeHash(int ano){
    int indiceAno= funcaoHash(this->pgOriginal, ano); 
    int pl = this->pl[indiceAno];
    int pgOriginal = this->pgOriginal;
    int indiceAtual = funcaoHash(pl,ano);

    ifstream ifile;
    ofstream arqtemp;
    string filename;
    string line;
    int count = 0;
   
    string auxFileName = diretorio+"bucket/"+"arqtemp.txt";
    filename=diretorio+"bucket/"+to_string(indiceAtual)+".txt";   
    ifile.open(filename);
    arqtemp.open(auxFileName);
    while(getline(ifile, line)){
      if(line.find(to_string(ano)) != string::npos){ //procurando em cada linha do bucket
        count++;
      } 
      else{ 
        if(!arqtemp.is_open()){
          arqtemp.open(auxFileName,ios::app);
        }       
        arqtemp<<line<<endl;
        arqtemp.close();
      }
    }
  
    remove(filename.c_str());
    rename(auxFileName.c_str(), filename.c_str());
    cout<<"OPA: "<<filename<<"Indice atual: "<<indiceAtual<<", "<<count<<endl;
     if(getSizeFile(filename) == 0 && indiceAtual!= indiceAno ){
        remove(filename.c_str());
        this->hash[indiceAtual] = this->hash[funcaoHash((this->pg - 1), ano)];

        
     }

    printf("REM:%d/<%d>,<%d>,<%d>\n",ano,count,this->pg, this->pl[indiceAno]);
  }
};

#endif