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
      
      int total = pow(2,pg);
      
      int newFuncaoHash = funcaoHashAtual(ano);
      
      ofstream arquivo7;

      for(int i=0; i<total; i++) {
        if(newFuncaoHash==i){
         
        int contador1 = getSizeFile(this->hash[i]);
        
          if(bucketCheio(ano)){
            
             duplicaDiretorio(this->pg, ano);
              newFuncaoHash = funcaoHashAtual(ano);    
             arquivo7.open(this->hash[newFuncaoHash], ios::app);
            
             for(int j=0; j< newCount;j++){
                 arquivo7 << lines[j]<<endl;
          }
           }else{
                  int funcao_hash = funcaoHash(this->pgOriginal, ano);
                for(int k=this->pgOriginal; k<=this->pl[i]; k++){
                            
                            int countLine = getSizeFile(this->hash[funcao_hash]); 
                            if(countLine ==3){
                              continue;
                            }
                            else{
                              arquivo7.open(this->hash[funcao_hash], ios::app);                       
                              for(int j=0; j< newCount;j++){
                              arquivo7 << lines[j]<<endl;
                            }
                            
                          }
                          funcao_hash+=4;
                          }
          }
             
        }
        arquivo7.close();
      }   

      printf("INC:%d/<%d>,<%d>\n", ano, this->pg, this->pl[funcaoHashAtual(ano)]); 

    }

    int funcaoHashAtual( int ano){
      int funcao_hash=funcaoHash(this->pgOriginal, ano);
     // cout<<"funcao_hash "<< funcao_hash<<endl;
      int multiplicador = this->pl[funcao_hash] - this->pgOriginal;
      //cout<<"multiplicador: "<<multiplicador<<endl;
      int newFuncaoHash = funcao_hash + 4 * multiplicador;
      return newFuncaoHash;
    }
 /*
      Verificar antes todos os buckets associados ao indice
      do ano estão cheios
      */
/*
 bool bucketCheio(int ano){
       int idx1 = funcaoHash(this->pgOriginal,ano);
      cout<<"PL: "<<idx1<<endl;    
      cout<<"PL de idx1 "<<this->pl[idx1]<<endl;
         
       if(this->pg > this->pgOriginal ){
         cout<<idx1 <<" entramos em indice e pl: "<<this->pl[idx1]<<endl;
           int idx2 = idx1 + 4;
    
       if(getSizeFile(this->hash[idx1]) == 3 && getSizeFile(this->hash[idx2])==3){
         
        if(this->hash[idx1] == this->hash[idx2]){
          
         ofstream ofile(diretorio+"indice.txt");

         ofile<<"PG:"<< this->pg;

         for(int i=0; i<pow(2,this->pg);i++){
          if(i == idx1){
            this->hash[idx1] = diretorio+"bucket/"+to_string(idx1)+".txt";
            ofile<< to_string(idx1)<<":"<<to_string(this->pl[idx1])<<":"<<this->hash[idx1]<<endl; 
  
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
*/
   bool bucketCheio(int ano){
    bool ehsim = false;
    int idx1 = funcaoHash(this->pgOriginal,ano);
    int aux = idx1;
    if(this->pl[aux] == this->pg){

       for(int j = this->pgOriginal; j<=this->pg;j++){
        if (getSizeFile(this->hash[aux]) == 3){
          for(int k = this->pgOriginal; k<=this->pg;k++){ 
            if(k == j){
              continue;
            }
            else{
              if(this->hash[k] == this->hash[j]){
                ehsim = false;
                break;
              }
              ehsim = true;
            }
            
          }
        }
        else{
          ehsim = false;
          break;
        }
       aux+=4;       
       }

       if(!ehsim){
          return false;
       }
       else{
        true;
       }
    }
    else{
      return false;
    }
   } 
//****************************************************************************
    void duplicaDiretorio(int pg, int ano){
     

      int pgAtualizada = pg+1;
      int plAtual = funcaoHashAtual(ano);
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
    }
    for(int k =this->pgOriginal; k<= this->pg; k++ ){   
      
      this->pl[funcao_Hash] = this->pg;
      
      funcao_Hash+=4;
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

     ofstream ofile(diretorio+"indice.txt");
     
     int aux3;
     // Escrevendo os respectivos endereços dos para os buckets
     // em cada posição do índice:
     ofstream ofile2;
     ifstream iline;
    // cout<<"O total de registros anterior eh "<<totalRegistrosAnterior<<endl;
 
     int funcao_hash_anterior = funcaoHash(pg, ano);  
     int funcao_hash = funcao_hash_anterior+4;
     // cout<<"funcaoHash anterior eh "<<funcao_hash_anterior<<endl;
     // cout<<"funcaoHash atual eh "<<funcao_hash<<endl;

     for(int i=0; i<total; i++)  {
          if(i==0){
            ofile<<"PG:"<<pgAtualizada<<endl;  
          }
           if(i == funcao_hash){
            
            filename=diretorio+"bucket/"+to_string(i)+".txt";
            
            this->hash[i] = filename;
            ofile2.open(diretorio+"bucket/"+to_string(i)+".txt");
           // ofile1.open(diretorio+"bucket/"+to_string(aux1)+".txt", ios::in);
            iline.open(diretorio+"bucket/"+to_string(funcao_hash_anterior)+".txt");

            //cout<<"vamos duplicar: "<<diretorio+"bucket/"+to_string(funcao_hash_anterior)+".txt"<<endl;
            string line;
            string lines[3];
            int count  = 0;
            int y = 0;
            //Escrevendo o ultimo registro do bucket anterior no novo bucket
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

              ofstream ofile5(diretorio+"bucket/"+to_string(funcao_hash_anterior)+".txt");
              for(int i=0; i<2; i++){
                ofile5<<lines[i]<<endl;
                
              } 
              
              ofile5.close();          
         }
         else {
          
          // Apontando os novos indices para os buckets anteriores
           aux3 = funcaoHash(this->pgOriginal, i);
           filename=diretorio+"bucket/"+to_string(aux3)+".txt";
           
         }
          if(ofile.is_open()){
            
            this->hash[i] = filename;     
            ofile<< i<<":"<<this->pl[i]<<":"<< this->hash[i]<<endl; 
      } 
    
    }
    ofile.close();
      //  for(int i=0; i<total; i++){
      //   cout<<"pl DE "<<i<<": "<<this->pl[i]<<endl;
      //  }

   printf("DUP_DIR:/<%d>,<%d>\n",this->pg, this->pl[funcao_hash]);
    }

  
void buscaHash(int ano){
    
     int indiceAno= funcaoHash(this->pgOriginal, ano); 
       int pl = this->pl[indiceAno];
       int pgOriginal = this->pgOriginal;
       
       ifstream ifile;
       string filename;
       
       string line;
       int count = 0;
      
      if(pl > pgOriginal){
        for(int i = pgOriginal; i <= pl; i++){
           
          
          filename=diretorio+"bucket/"+to_string(indiceAno)+".txt";
          ifile.open(filename);
          while(getline(ifile,line)){
            if(line.find(to_string(ano)) != string::npos ){
                    count++;
               cout<<"Regitro "<<count<<" encontrado: "<<line <<endl;
            }        
          } 
          indiceAno+=4;
           ifile.close();
     }
}
          else{
            
             filename=diretorio+"bucket/"+to_string(indiceAno)+".txt";
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
       
       string line;
       string lines[3];
       int count = 0;
       bool found = false; 
       int j=0;

      
        for(int i = pgOriginal; i <= pl; i++){
       
          filename=diretorio+"bucket/"+to_string(indiceAno)+".txt";
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
                  
                   int newHashFun = funcaoHash(this->pl[indiceAno], ano);
                   this->hash[indiceAno] = this->hash[newHashFun];
                   for(int k = pgOriginal; k <= pl; k++){
                    funcaoHash(k,ano);
                    this->pl[k] = this->pl[k] - 1;
                                
                 }
                 ofile.close();
            }
            indiceAno+=4;
            j++;       
           
           ifile.close();
            }
     }
    printf("REM:%d/<%d>,<%d>,<%d>\n",ano,count,this->pg, this->pl[indiceAno]);
  }
};

#endif
