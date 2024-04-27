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
           newCount++;
        }
        i++;      
    }
    
file.close();
if(newCount== 0){
      cout<<"Nao ha registros com este valor"<<endl;
    }
      
      int count2=0;
      
      int total = pow(2,this->pg);
      
      int newFuncaoHash = funcaoHashAtual(ano);
      
      ofstream arquivo7;
      int countLine;
      for(int i=0; i<total; i++) {
        
        if(newFuncaoHash==i){
       
        int contador1 = getSizeFile(this->hash[i]);
        
          if(bucketCheio(ano)){
          
             duplicaDiretorio(this->pg, ano,lines,newCount);            
           }
           else{
            
                int funcao_hash = funcaoHash(this->pgOriginal, ano);
                int funcao_hash_original = funcao_hash;
                
                for(int k=this->pgOriginal; k<=this->pg; k++){
                    
                       
                      if(this->pg > this->pgOriginal){
                         
                       if(funcao_hash != funcaoHash(this->pgOriginal, ano)){
                        cout<< "OXENTE ano "<<ano<<", funcHash "<<funcao_hash<<" total "<<total<<endl;
                        if(this->hash[funcao_hash] == this->hash[funcaoHash(this->pgOriginal, ano)]){
                          

                          string nomef = diretorio+"bucket/"+to_string(funcao_hash)+".txt";                          
                          ofstream ofile(nomef);
                          
                          ifstream ifile(diretorio+"bucket/"+to_string(funcao_hash-4)+".txt"); 
                          
                          string line;
                          string linhas1[3];                         
                          this->hash[funcao_hash] = nomef;

                          for(int w=this->pgOriginal; w<=this->pg; w++){
                            this->pl[funcao_hash_original]++;
                            funcao_hash_original+=4;
                          } 
                           
                          int count = 0 ;               
                          while(getline(ifile, line)){
                               
                              linhas1[count] = line;                             
                              if(count == 2){
                                
                                ofile << linhas1[count]<<endl;
                              } 
                              count++;
                          }
                          ofstream ofile2(diretorio+"bucket/"+to_string(funcao_hash-4)+".txt");
                          for(int y=0; y< 2;y++){
                            ofile2<<linhas1[y]<<endl;
                          }
                         
                          ofile.close();
                          ofile.open(nomef, ios::app);

                          for(int j=0; j< newCount;j++){
                              ofile<< lines[j]<<endl;
                           }
                           ofile.close();
                          ofile.open(diretorio+"indice.txt");
                          for(int i=0; i<total; i++)  {
                              if(i==0){
                                ofile<<"PG:"<<this->pg<<endl;  
                              }
                                   
                                ofile<< i<<":"<<this->pl[i]<<":"<< this->hash[i]<<endl; 
                            }
                          ofile.close();
                          break;
                        }
                        else{

                          if(getSizeFile(this->hash[funcao_hash] ) <3){
                            ofstream ofile(this->hash[funcao_hash], ios::app);
                            for(int j=0; j< newCount;j++){
                              ofile<< lines[j]<<endl;
                           }
                           ofile.close();
                          
                          }
                        }
                        }
                        else{
                          
                           countLine = getSizeFile(this->hash[funcao_hash]); 
                          if(countLine == 3){       
                                      
                          }
          
                          else{
                             
                               string nomef = diretorio+"bucket/"+to_string(funcao_hash)+".txt";                          
                               ofstream ofile(nomef,ios::app);                          
                              this->hash[funcao_hash] = nomef;

                              for(int j=0; j< newCount;j++){
                              ofile<< lines[j]<<endl;
                           }
                           ofile.close();
                           break;
                          }
                        }
                       }
                       else{
                        
                      countLine = getSizeFile(this->hash[funcao_hash]);  
                      if(countLine ==3){
                                                                                            
                    }
                    else{
                      arquivo7.open(this->hash[funcao_hash], ios::app); 
                      for(int j=0; j< newCount;j++){
                              arquivo7<< lines[j]<<endl;
                           }
                    }       
                    }
                   funcao_hash+=4;
          }                   
        }
        arquivo7.close();
      }   
    
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
   bool bucketCheio(int ano){
    bool ehsim = false;
    int idx1 = funcaoHash(this->pgOriginal,ano);
    int aux = idx1;
    if(this->pl[aux] == this->pg){
      
       for(int j = this->pgOriginal; j<=this->pg;j++){
        if (getSizeFile(this->hash[aux]) == 3){             
          for(int k = this->pgOriginal; k<=this->pg;k++){ 
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
       cout<<"Alguem entrou aqui?"<<endl; 
       aux+=4;       
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
    void duplicaDiretorio(int pg, int ano, string* linhas, int numberOfLines){
     
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
            iline.open(diretorio+"bucket/"+to_string(funcao_hash_anterior)+".txt");   
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
              
              //escrevendo os dados no arquivo duplicado:
              ofstream ofile3;
              ofile3.open(diretorio+"bucket/"+to_string(i)+".txt",ios::app); 
              
              string* newLine;
              cout<<"Tamanho das linhas: "<<numberOfLines<<endl;
              
               if(numberOfLines < 3){
                for(int i=0; i<numberOfLines; i++){
                  cout<<"Escreveu ai? "<< linhas[i]<<endl;
                  ofile3<<linhas[i]<<endl;
                }
               }
              else{
                for(int i=0; i<2; i++){
                ofile3<<linhas[i]<<endl;  
              }   
              numberOfLines = 0;  
              for(int j=3, k = 0; j<=numberOfLines; j++, k++){
                newLine[k]  = linhas[j];
                numberOfLines ++;
              }
              
            //  duplicaDiretorio(this->pg, ano, newLine,numberOfLines);
              }
             
              ofile3.close();
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
        for(int i = pgOriginal; i <=pl; i++){
   
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
       ofstream arqtemp;
       string filename;
       string line;
       int count = 0;
       int qtde_buckets = pl-pgOriginal + 1; //qtde buckets q uma chave(ano) pode estar
       int funcao_hash = funcaoHash(pgOriginal, ano); //menor indice q a chave pode estar
       vector<string> linhasNewfile;
      string auxFileName = diretorio+"bucket/"+"arqtemp.txt";

      if (pl > pgOriginal){ 

        for(int i=0; i<qtde_buckets; i++){ //contador p ir de bucket em bucket
          int indice = funcao_hash;
          filename=diretorio+"bucket/"+to_string(indice)+".txt";
          ifile.open(filename);
          while(getline(ifile, line)){
            if(line.find(to_string(ano)) != string::npos){ //procurando em cada linha do bucket
              count++;
            } 
            else{
              //linhasNewfile.push_back(line); //se nao tiver o ano, copia p o vetor
              arqtemp.open(auxFileName,ios::app);
              arqtemp<<line<<endl;
              arqtemp.close();
            }
          }

          remove(filename.c_str());
          rename(auxFileName.c_str(), filename.c_str());
          if(funcao_hash !=indiceAno)
          if(getSizeFile(filename) == 0 ){
           remove(filename.c_str());
           this->hash[funcao_hash] = this->hash[funcao_hash-4];
           int aux12 = funcaoHash(pgOriginal, ano);

           for(int j = this->pgOriginal; j<= this->pg; j++){
             this->pl[aux12] --;
             funcao_hash+=4;
           }

      }

          indice = indice + 4;
        
        }
        ifile.close();
      }
      else{
        filename=diretorio+"bucket/"+to_string(funcao_hash)+".txt";
        ifile.open(filename);
          while(getline(ifile, line)){
            if(line.find(to_string(ano)) != string::npos){ //procurando em cada linha do bucket
              count++;

            } 
            else{
              //linhasNewfile.push_back(line); //se nao tiver o ano, copia p o vetor
              arqtemp.open(auxFileName,ios::app);
              arqtemp<<line<<endl;
              arqtemp.close();
            }
          }
      ifile.close();
     
      remove(filename.c_str());
      rename("temp.txt", filename.c_str());
          }
      


    printf("REM:%d/<%d>,<%d>,<%d>\n",ano,count,this->pg, this->pl[indiceAno]);


  }
};

#endif
