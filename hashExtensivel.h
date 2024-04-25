#ifndef hashExtensivel
#define hashExtensivel
#include <iostream>
#include <string>
#include <stack>
#include <math.h>
#include <fstream>
#include <vector>


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

    int funcaoHashAlternativa(int profundidade, int indice){
      stack<int> pilha;
      int resto;
      for(int i=0; i<profundidade; i++){        
        resto = indice % 2;
       
        pilha.push(resto);     
        indice /= 2;
      }
      string aux; 
       
       while(!pilha.empty()){
          aux.append(to_string(pilha.top()));
          pilha.pop();        
      }  
   
      return stoi(aux);
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
      //file.open("D:/banco_tabalho1_sgbd/compras.csv");
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
         //  cout<<"Registro "<<newCount<<": "<<lines[newCount]<<endl;          
           newCount++;

        }
        i++;      
    }
    
file.close();

if(newCount== 0){
      cout<<"Nao ha registros com este valor"<<endl;
    }
      int count2=0;
      string* hash = this->hash; 
      int total = pow(2,pg);
      int funcao_hash=funcaoHash(pg, ano);
      ofstream arquivo7;

      for(int i=0; i<total; i++) {
        if(funcao_hash==i){
         // cout<<"Valor do hash na posicao "<<i<<": "<<hash[i]<<endl;
        int contador1 = getSizeFile(hash[i]);
        // cout<<"tamanho de linhas do arquivo "<<i<<".txt: "<< contador1<<endl; 
          if(bucketCheio(ano)  || (newCount+contador1) >3){
            //  cout<<"O bucket está cheio para o ano "<< ano<<endl<<endl;
             duplicaDiretorio(pg, ano);
             
             int newfuncHash = funcaoHash(this->pg,ano);
             arquivo7.open(this->hash[newfuncHash], ios::app);
            
             for(int j=0; j< newCount;j++){
                 arquivo7 << lines[j]<<endl;
          }
          }
          arquivo7.open(hash[i], ios::app);
         
          for(int j=0; j< newCount;j++){
            arquivo7 << lines[j]<<endl;
          }
                 
        }

      }   
      printf("INC:%d/<%d>,<%d>\n", ano, this->pg, this->pl[funcao_hash]); 
    }
 /*
      Verificar antes todos os buckets associados ao indice
      do ano estão cheios
      */
    bool bucketCheio(int ano){
      int idx1 = funcaoHash(this->pg,ano);

      if(this->pl[idx1] > this->pgOriginal ){
       int idx2 = funcaoHash((this->pg)-1,ano);
       if(getSizeFile(hash[idx1]) == 3 && getSizeFile(hash[idx2])==3){

        if(hash[idx1] == hash[idx2]){

         ofstream ofile(diretorio+"indice.txt");

         ofile<<"PG:"<< this->pg;

         for(int i=0; i<pow(2,this->pg);i++){
          if(i == idx1){
            this->hash[idx1] = diretorio+"bucket/"+to_string(idx1)+".txt";
            ofile<< to_string(idx1)<<":"<<to_string(this->pl[idx1])<<":"<<this->hash[idx1]<<endl; 
            ofstream ofile2(this->hash[idx1]);
            ofile2.close();
            
          }
          ofile<< to_string(i)<<":"<<to_string(this->pl[i])<<":"<<this->hash[i]<<endl; 
         }
         ofile.close();
         return false;

        }
        else{
          return true;
        }         
       }
       return false;
      }
      else if(getSizeFile(hash[idx1])==3) {
          return true;
       }
      return false;
    }
//****************************************************************************
    void duplicaDiretorio(int pg, int ano){
     
      int pgAtualizada = pg+1;
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
    
    int aux1 = funcaoHash(pg, ano);
    int aux2 = funcaoHash(pgAtualizada,ano);
    this->pl[aux1] ++ ; 
   // cout<<"indice hash att "<<aux2<<endl;
   // cout<<"indice hash original "<<aux1<<endl;
    
      ifstream arquivo2;
      ofstream arquivo3;//("exemplo.txt", ios::app);
      arquivo2.open(diretorio+"indice.txt");
      arquivo3.open(diretorio+"indice.txt",ios::in);
      if(!arquivo2){
        cerr<< " ************ Erro ao abrir arquivo ************" <<endl;
      }
      string line;
      size_t found;
          
      int i=0;
      //Atualiza indices, PLs, e respectivos endereços
      while(getline(arquivo2, line) && i < pow(2,pg)){
           found = line.find("PG");
           if(found != string::npos){
             arquivo3<<"PG:"<<pgAtualizada<<endl;                                                
           }       
           
           if(i == aux1){           
                       
             arquivo3<<to_string(aux1)<<":"<<to_string(this->pl[aux1])<<":"<<this->hash[aux1]<<endl;                      
           } 
           else{
            arquivo3<<to_string(i)<<":"<<to_string(this->pl[i])<<":"<<this->hash[i]<<endl;
           }      
         i++;           
      }    
      arquivo2.close();
       arquivo3.close();
     
     ofstream ofile(diretorio+"indice.txt", ios::app);

     string filename;
     int aux3;
     // Escrevendo os respectivos endereços dos para os buckets
     // em cada posição do índice:
     ofstream ofile2;
     ifstream iline;
     ofstream ofile1;
        
     for(int i=pgAtualizada+1; i<total; i++)  {
         
         if(i == aux2){
            filename=diretorio+"bucket/"+to_string(i)+".txt";
            this->pl[i] = pgAtualizada;
            ofile2.open(diretorio+"bucket/"+to_string(i)+".txt");
           // ofile1.open(diretorio+"bucket/"+to_string(aux1)+".txt", ios::in);
            iline.open(diretorio+"bucket/"+to_string(aux1)+".txt");
            
            string line;
            string lines[3];
            int count  = 0;
            int y = 0;
            
            while(getline(iline, line)){
               count++;
               lines[y] = line;
               if(count==3){ 
                ofile2<<line<<endl;                               
               }
               y++;
               }
              ofile2.close();
              iline.close();
              ofile1.close();

              ofstream ofile5(diretorio+"bucket/"+to_string(aux1)+".txt");
              for(int i=0; i<2; i++){
                ofile5<<lines[i]<<endl;
              }              
           
         }
         else {
           aux3 = funcaoHash(pg, i);
           filename=diretorio+"bucket/"+to_string(aux3)+".txt";
           this->pl[i] = pg;
         }
          if(ofile.is_open()){
            this->hash[i] = filename;     
            ofile<< i<<":"<<this->pl[i]<<":"<< this->hash[i]<<endl; 
      } 
    
    }
    ofile.close();
   
   printf("DUP_DIR:/<%d>,<%d>\n",this->pg, this->pl[aux1]);
    }

  
void buscaHash(int ano){
    
     int indiceAno= funcaoHash(this->pgOriginal, ano); 
       int pl = this->pl[indiceAno];
       int pgOriginal = this->pgOriginal;
       
       ifstream ifile;
       string filename;
       int funcao_hash;
       string line;
       int count = 0;

      if(pl > pgOriginal){
        for(int i = pgOriginal; i <= pl; i++){
          
          funcao_hash = funcaoHash(i, ano);
          filename=diretorio+"bucket/"+to_string(funcao_hash)+".txt";
          ifile.open(filename);
          while(getline(ifile,line)){
            if(line.find(to_string(ano)) != string::npos ){
                    count++;
               cout<<"Regitro "<<count<<" encontrado: "<<line <<endl;
            }        
          } 
           ifile.close();
     }
}
          else{
            funcao_hash = funcaoHash(pgOriginal, ano);
             filename=diretorio+"bucket/"+to_string(funcao_hash)+".txt";
            ifile.open(filename);
            while(getline(ifile,line)){
              if(line.find(to_string(ano)) != string::npos ){
                      count++;
                cout<<"Regitro "<<count<<" encontrado: "<<line <<endl;
              }      
          }    
          ifile.close();
}
      printf("BUS:%d/<%d>\n",ano,count);

}
  void removeHash(int ano){
     int indiceAno= funcaoHash(this->pgOriginal, ano); 
       int pl = this->pl[indiceAno];
       int pgOriginal = this->pgOriginal;
       
       ifstream ifile;
       ofstream ofile;
       string filename;
       int funcao_hash;
       string line;
       string lines[3];
       int count = 0;
       bool found = false; 
       int j=0;

      
        for(int i = pgOriginal; i <= pl; i++){
          
          funcao_hash = funcaoHash(i, ano);
          filename=diretorio+"bucket/"+to_string(funcao_hash)+".txt";
          ifile.open(filename);

          while(getline(ifile,line)){
             
            if(line.find(to_string(ano)) != string::npos ){              
               count++;
               found=true;
            } 
          }
            if(found == true){
                 ifile.clear();
                 ifile.seekg(0);
                 while(getline(ifile,line)){
                   lines[j] = line;
                   j++;
                 }
                 ofile.open(filename);
                 for(int j = 0; j<3; j++){
                   if(lines[j].find(to_string(ano)) != string::npos){
                    continue;
                   }else{
                    ofile <<lines[j];
                   }                  
                 }

                 if(getSizeFile(filename) == 0){
                   remove(filename.c_str());
                  
                   int newHashFun = funcaoHash(this->pl[funcao_hash], ano);
                   this->hash[funcao_hash] = this->hash[newHashFun];
                   for(int k = pgOriginal; k <= pl; k++){
                    funcaoHash(k,ano);
                    this->pl[k] = this->pl[k] - 1;
                                
                 }
                 ofile.close();
            }
            j++;       
           
           ifile.close();
            }
     }
    printf("REM:%d/<%d>,<%d>,<%d>\n",ano,count,this->pg, this->pl[indiceAno]);
  }
};

#endif
