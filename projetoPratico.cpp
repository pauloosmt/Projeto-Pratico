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

        for (int i = 0; i < numMsc; i++) {


        }



        


    
        delete[] musicAdd;
    }
    
    return 0;
    
}