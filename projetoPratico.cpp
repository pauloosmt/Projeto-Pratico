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
    int anoLançamento;
    int popularideEscala;
    double volumeMedio;

    void imprimir(){
        cout << artista << endl;
        cout << nomeMsc << endl;
        cout << duracaoMs << endl;
        cout << generoMusical << endl;
        cout << anoLançamento << endl;
        cout << popularideEscala << endl;
        cout << volumeMedio << endl;


        
    }

    void leitura (ifstream& arquivo, Musicas &musicAdd)  {
            string lixo;
            getline(arquivo, musicAdd.artista, ',');
            getline(arquivo, musicAdd.nomeMsc, ',');
            arquivo >> musicAdd.duracaoMs;
            getline(arquivo, lixo, ',');
            getline(arquivo, musicAdd.generoMusical, ',');
            arquivo >> musicAdd.anoLançamento;
            getline(arquivo, lixo, ',');
            arquivo >> musicAdd.popularideEscala;
            getline(arquivo, lixo, ',');
            getline(arquivo, lixo, ',');
            getline(arquivo, lixo, ',');
            getline(arquivo, lixo, ',');
            arquivo >> musicAdd.volumeMedio;
            getline(arquivo,lixo, ';');
            
            

    }



};




int main () {
    int numMsc;
    string lixo;

    ifstream arquivo_csv("songs.csv"); //abertura do arquivo

    if(!arquivo_csv) {
        cout << "Erro ao abrir arquivo!" << endl;

    } else {

        arquivo_csv >> numMsc;
        arquivo_csv >> lixo;

        Musicas *musicAdd = new Musicas[numMsc];

        
        for(int i = 0; i < numMsc; i++) {
            musicAdd[i].leitura(arquivo_csv, musicAdd[i]);

        }



        for(int i = 0; i < numMsc; i++) {
            
            musicAdd[i].imprimir();

        }


        


    
        delete[] musicAdd;
    }
    
    return 0;
    
}