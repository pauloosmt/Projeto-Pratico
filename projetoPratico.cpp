#include <iostream>
#include <fstream>
#include <string>

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

    void buscas(int buscar) {

        if (buscar == 1) {
                imprimir();
        }




    }




};




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

        int busca = 0;

        while(busca != 5){
            cout << "------------------------" << endl;
            cout << "O que voce deseja buscar? " << endl;
            cout << "------------------------" << endl;
            cout << "[1] Imprimir" << endl << "[2] Buscar por nome" << endl << "[3] Buscar por artista" << endl << "[4] Buscar por número de streams" <<
            endl << "[5] Sair" << endl; 

            cin >> busca;

            musicAdd[0].buscas(busca);
            
            
        }




        


    
        delete[] musicAdd;
    }
    
    return 0;
    
}