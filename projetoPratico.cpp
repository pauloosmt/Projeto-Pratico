#include <iostream>
#include <fstream>
#include <string>

// Ultima alteracao 19:54, 10/06
// Por Paulo;



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

void ordenarANO(int tam, int *&vetor_pos, int vet[], int anoBusca, int &ocasioes) {
    //Primeira parte: Ordenação dos anos
    int menor, aux; 
    for(int i = 0; i < tam -1; i++) {
        menor = i;
        for (int j = i+1; j < tam; j++) {
            if(vet[vetor_pos[j]] < vet[vetor_pos[menor]]) {
                menor = j;
            }
        }
        aux = vetor_pos[i];
        vetor_pos[i] = vetor_pos[menor];
        vetor_pos[menor] = aux;
    }
    //Foi ordenado por Selection Sort

    // Segunda parte: Fazer a busca binaria e achar todas as repeticoes

    // Comeca fazendo a busca binaria padrao
    int elementosEsquer = 0, elementosDirei = tam -1;
    bool encontrado = false;
    int posEncontrado = 0;

    while(elementosEsquer <= elementosDirei and !encontrado) {
        int meioVetor = (elementosDirei + elementosEsquer) / 2;
        if(vet[vetor_pos[meioVetor]] == anoBusca) {
            posEncontrado = meioVetor;
            encontrado = true;
            ocasioes++;
        } else if (vet[vetor_pos[meioVetor]] < anoBusca) {
            elementosEsquer = meioVetor + 1;
        } else {
            elementosDirei = meioVetor - 1;
        }

    }
    
    if(!encontrado){
        cout << "ERRO! Não foi possivel achar uma musica na lista lancada em " << anoBusca << "!!!" << endl;
        return;
    } 

    // Agora, vamos achar todas as repeticoes, comecando pela esquerda
    int inicio = posEncontrado;
    while (inicio > 0 and vet[vetor_pos[inicio - 1]] == anoBusca) {
        inicio--;
        ocasioes++; 
    }

    // Agora, vamos achar todas as repeticoes, que esta a direita da posicao encontrada na busca binaria
    int fim = posEncontrado;
    while(fim < tam -1 and vet[vetor_pos[fim + 1]] == anoBusca) {
        fim++;
        ocasioes++;
    }

    /* Nessa parte iremos redimensionar o vetor_pos, para que ele armazene apenas as 
    posicoes que contenham musicas que forem lançadas no ano desejado */

    int *temp = new int[ocasioes]; /*A variavel ocasioes auxilia, pois ela conta quantas repeticoes 
                                       do mesmo ano existem na lista original */

    for (int i = 0; i < ocasioes and inicio <= fim; i++) {
        temp[i] = vetor_pos[inicio];
        inicio++;
    } 
    

    vetor_pos = temp; // Por fim, o vetor_pos passa a apontadar para o nosso vetor temporario
    

    
    return;
    
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




        int busca = 0;

        while(busca != 5){
            cout << "------------------------" << endl;
            cout << "O que voce deseja buscar? " << endl;
            cout << "------------------------" << endl;
            cout << "[1] Imprimir" << endl << "[2] Buscar por ano" << endl << "[3] Buscar por artista" << endl << "[4] Buscar por numero de streams" <<
            endl << "[5] Sair" << endl; 

            cin >> busca;

            if(busca == 1) {
                for(int i =0 ; i < numMsc; i++) {
                    buscas(busca, musicAdd[i]);
                }
            }
            else if(busca == 2) {
                int buscaAno;
                cin >> buscaAno;

                //Vetores auxiliares que ajudarao na ordenacao
                int *vetor_aux = new int[numMsc]; // Esse recebe o indice que cada musica
                int *vetorAno = new int[numMsc]; // Esse recebe o ano de cada musica

                /*Ao fim da ordenacao, o vetorAno possuira todos os anos em ordem crescente,
                enquanto o vetor_aux, possuira a posicao desses anos em relacao ao arquivo original
                Portanto, os elemntos do vetor_aux sao indices para buscarmos musicas no "musicAdd"
                de maneira ordenada*/
                
                
                for(int i = 0; i < numMsc; i++) {
                    
                    vetor_aux[i] = i;
                    vetorAno[i] = musicAdd[i].anoLancamento;
            

                }

                

                int numOCasioes = 0;
                ordenarANO(numMsc, vetor_aux, vetorAno, buscaAno, numOCasioes);
                
                /*Imprimindo apenas asd musicas, cujo ano de lancamento 
                e o mesmo do ano que o usuario digitou */
                
                for(int i = 0; i < numOCasioes ; i++) {
                   musicAdd[vetor_aux[i]].imprimir();
                } 
                
                


                delete[] vetor_aux;
                delete[] vetorAno;
            }
        
        

            
            
            
            
        }


       
            

        


    
        delete[] musicAdd;
    }
    
    return 0;
    
}