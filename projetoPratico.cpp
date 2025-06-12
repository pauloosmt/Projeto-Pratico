#include <iostream>
#include <fstream>
#include <string>

// Ultima alteração 12:06, 12/06
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

void ordenarMusica(int tam, string vet[], string musica, int vet_aux[], Musicas musicAdd[]){
	//selection sort pra ordenar as musicas em ordem alfabetica
	string aux;
	int aux2;
	for(int i = 0; i < tam - 1; i++){
		int indice_menor = i;
		for(int j = i + 1; j < tam; j++)
			if(vet[j] < vet[indice_menor])
				indice_menor = j;
		aux = vet[i];
		vet[i] = vet[indice_menor];
		vet[indice_menor] = aux;
	//ordenando o vetor auxiliar que tem os indices de cada musica no vetor original junto
		aux2 = vet_aux[i];
		vet_aux[i] = vet_aux[indice_menor];
		vet_aux[indice_menor] = aux2;
	}
	//busca binaria simples pra encontrar a musica
	int posicao_inicial = 0, posicao_final = (tam-1), meio, posicao_desejada = -1;
	while(posicao_inicial <= posicao_final){
		meio = (posicao_inicial + posicao_final) / 2;
		if(musica == vet[meio]){
			posicao_desejada = meio;
			posicao_inicial = posicao_final + 1;
		}
		else{
			if(musica > vet[meio])
				posicao_inicial = meio + 1;
			else
				posicao_final = meio - 1;
		}
	}
	// imprime a musica desejada ou mensagem de erro caso ela n exista no arquivo
	if(posicao_desejada != -1)
		musicAdd[vet_aux[posicao_desejada]].imprimir();
	else{
		cout << "Nao Existe essa musica no arquivo!" << endl;
	}
}



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




void buscas(string buscar, Musicas &vetor) {

        if (buscar == "1") {
                vetor.imprimir();
        }
        
    }

void Adicionar(Musicas *&vetor, int &tam, int adicional) {
    tam += adicional;

    Musicas *temp = new Musicas[tam];

    for(int i =0; i < tam-adicional; i++) {
        temp[i].artista = vetor[i].artista;
        temp[i].nomeMsc = vetor[i].nomeMsc;
        temp[i].duracaoMs = vetor[i].duracaoMs;
        temp[i].generoMusical = vetor[i].generoMusical;
        temp[i].anoLancamento = vetor[i].anoLancamento;
        temp[i].streams = vetor[i].streams;
        temp[i].volumeMedio = vetor[i].volumeMedio;
    }
    for(int i = tam - adicional; i < tam; i++) {
        cout << "Nome do Artista: ";
        cin.ignore();
        getline(cin, temp[i].artista);
        cout << endl << "Nome da Musica: ";
        getline(cin, temp[i].nomeMsc);
        cout << endl << "Duracao da Musica: ";
        cin >> temp[i].duracaoMs;
        cout << endl << "Genero da Musica: ";
        cin.ignore();
        getline(cin, temp[i].generoMusical);
        cout << endl << "Ano do Lancamento da Musica: ";
        cin >> temp[i].anoLancamento;
        cout << endl << "Numero de Streams da Musica: ";
        cin >> temp[i].streams;
        cout << endl << "Volume Medio da Musica: ";
        cin >> temp[i].volumeMedio;

    }

    delete[]vetor;
    vetor = temp;
    cout<< "--------------------------------" << endl;
    cout<< "Musicas adicionadas com sucesso" << endl;
    cout<< "--------------------------------" << endl;

    return;
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




        string busca;

        while(busca != "6"){
            cout << "------------------------" << endl;
            cout << "O que voce deseja? " << endl;
            cout << "------------------------" << endl;
            cout << "[1] Imprimir" << endl << "[2] Buscar por ano" << endl << "[3] Buscar por artista" << endl << "[4] Buscar por nome da musica" <<
            endl << "[5] Adicionar Musicas" << endl << "[6] Sair" << endl; 

            cin >> busca;
		
            if(busca == "1") {
                for(int i =0 ; i < numMsc; i++) {
                    buscas(busca, musicAdd[i]);
                }
            }
            else if(busca == "2") {
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
        
			else if(busca == "3"){
			}
			
			      
			else if(busca == "4"){
				string buscaMusica;
				cin.ignore();
				getline(cin,buscaMusica);
					
					
				int* vet_aux = new int[numMsc];
				string* vetorMusica = new string[numMsc];
					
				for(int i = 0; i < numMsc; i++){
					vetorMusica[i] = musicAdd[i].nomeMsc;
					vet_aux[i] = i;
				}
				ordenarMusica(numMsc,vetorMusica,buscaMusica,vet_aux,musicAdd);
					
					
					
				delete[] vet_aux;
				delete[] vetorMusica;
			}

            else if(busca == "5") {
                int msc_add;
                cin >> msc_add;

                Adicionar(musicAdd, numMsc, msc_add);


            }
            
            
            
            
        }


       
            

        


    
        delete[] musicAdd;
    }
    
    return 0;
    
}
