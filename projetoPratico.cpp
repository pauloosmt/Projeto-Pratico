#include <iostream>
#include <fstream>
#include <string>

// Ultima alteracao 16:30, 10/06
// Os itens comentados estao incompletos



using namespace std;


struct Musicas {
    // Campos dos arquivos
    string artista;
    string nomeMsc;
    int duracaoMs;
    string generoMusical;
    int anoLancamento;
    double streams;
    double volumeMedio;

    void imprimir(){
        cout << artista << endl;
        cout << nomeMsc << endl;
        cout << duracaoMs << endl;
        cout << generoMusical << endl;
        cout << anoLancamento << endl;
        cout << streams << endl;
        cout << volumeMedio << endl;


        
    }

    void leitura (ifstream& arquivo, Musicas &musicAdd)  {
            string lixo;
            getline(arquivo, musicAdd.artista, ',');
            getline(arquivo, musicAdd.nomeMsc, ',');
            arquivo >> musicAdd.anoLancamento;
            getline(arquivo, lixo, ',');
            getline(arquivo, musicAdd.generoMusical, ',');
            arquivo >> musicAdd.streams;
            getline(arquivo, lixo, ',');
            arquivo >> musicAdd.duracaoMs;
            getline(arquivo, lixo, ',');
            arquivo >> musicAdd.volumeMedio;
            getline(arquivo, lixo, ';');
            
            
            

    }

   


};

void ordenarANO(int tam, int vetor_pos, Musicas vet) {
    int menor, aux;
    for(int i = 0; i < tam -1; i++) {
        menor = i;
        for (int j = i+1; j < tam; j++) {
            if(vet[j].ano < vet[menor].ano) {
                menor = j;
            }
        }
        aux = i;
        vetor_pos[i] = menor;
        vetor_pos[menor] = aux;
    }
    for(int k = 0; k < tam; k++) {
        vet[vetor_pos[k]].imprimir();
    }
}




void buscas(int buscar, Musicas &vetor) {

        if (buscar == 1) {
                vetor.imprimir();
        }

        if (buscar == 2) {



        }



    }






int main () {
    int numMsc;
    string lixo;



    ifstream arquivo_csv("spotify100.csv"); //abertura do arquivo

    if(!arquivo_csv) {
        cout << "Erro ao abrir arquivo!" << endl;

    } else {

        arquivo_csv >> numMsc;
        arquivo_csv >> lixo;

        Musicas *musicAdd = new Musicas[numMsc];
        
        
        for(int i = 0; i < numMsc; i++) {

            musicAdd[i].leitura(arquivo_csv, musicAdd[i]);
    
        }

        //for(int i = 0)


        



        int busca = 0;

        while(busca != 5){
            cout << "------------------------" << endl;
            cout << "O que voce deseja buscar? " << endl;
            cout << "------------------------" << endl;
            cout << "[1] Imprimir" << endl << "[2] Buscar por ano" << endl << "[3] Buscar por artista" << endl << "[4] Buscar por numero de streams" <<
            endl << "[5] Sair" << endl; 

            cin >> busca;

            if(busca == 1) {
                for(int i =0; i < numMsc; i++) {
                    buscas(busca, musicAdd[i]);
                }
            }
            else if(busca == 2) {
                int buscaAno;
                cin >> buscaAno;

                int *vetor = new int[numMsc];
                for(int i = 0; i < numMsc; i++) vetor[i] = i;

                ordenarANO(numMsc, vetor, musicAdd)
                
                



            }
        
        

            
            
            
            
        }


       
            

        



        delete[] musicAdd;
    }
    
    return 0;
    
}