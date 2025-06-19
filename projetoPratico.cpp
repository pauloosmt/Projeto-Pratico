#include <iostream>
#include <fstream>
#include <string>

// Ultima alteração 16:42, 19/06
// Por João;


using namespace std;


struct Musicas {
    string artista;       // Nome do artista
    string nomeMsc;       // Nome da música
    int duracaoMs;        // Duração da música em milissegundos
    string generoMusical; // Gênero musical
    int anoLancamento;    // Ano de lançamento
    double streams;       // Quantidade de streams (em bilhões)
    double volumeMedio;   // Volume médio da música (em decibéis)
    bool apagada = false; // Marca se a música foi apagada logicamente

    // Função para imprimir os dados da música
    void imprimir() {
        if (!apagada) { // Só imprime se a música não estiver apagada
            cout << "Artista: " << artista << endl;
            cout << "Musica: " << nomeMsc << endl;
            cout << "Duracao: " << duracaoMs << " ms" << endl;
            cout << "Genero: " << generoMusical << endl;
            cout << "Ano: " << anoLancamento << endl;
            cout << "Streams: " << streams << " bilhoes" << endl;
            cout << "Volume medio: " << volumeMedio << " dB" << endl;
            cout << "---------------------------" << endl;
        }
	}
    void leitura (ifstream& arquivo, Musicas &musicAdd)  {
            string lixo;
            arquivo.ignore();
            //arquivo.ignore();
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
// Função para converter uma string para minúsculas
string toLowerCustom(string str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') { // Verifica se é letra maiúscula
            str[i] += 32; // Converte para minúscula (diferença entre ASCII maiúscula e minúscula)
        }
    }
    return str;
}

// Função para buscar e apagar (logicamente) uma música por nome
void apagarMusica(Musicas vetor[], int numMsc) {
    string nomeBusca;
    cout << "Digite o nome da musica que deseja apagar: ";
    getline(cin, nomeBusca);
    nomeBusca = toLowerCustom(nomeBusca); // Converte a busca para minúsculo

    bool encontrou = false; // Flag para verificar se encontrou

    for (int i = 0; i < numMsc; i++) {
        // Verifica se a música ainda não foi apagada e se o nome bate
        if (!vetor[i].apagada && toLowerCustom(vetor[i].nomeMsc) == nomeBusca) {
            vetor[i].apagada = true; // Marca como apagada
            encontrou = true;
            cout << "Musica '" << vetor[i].nomeMsc << "' apagada com sucesso!" << endl;
        }
    }

    if (!encontrou) {
        cout << "Nenhuma musica com esse nome foi encontrada!" << endl;
    }
}

void ordenaVetorStrings(string vet[], int tam, int vet_aux[]){
	// transformando em minuscula todos os nomes de artistas antes de ordenar
	for(int i = 0; i < tam; i++)
		vet[i] = toLowerCustom(vet[i]);
	
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
	
}



void procuraArtista(int tam, string vet[], string artista, Musicas musicAdd[],int vet_aux[]){
	
	ordenaVetorStrings(vet,tam,vet_aux);
	
	int posicao_inicial = 0, posicao_final = tam - 1, meio, posicao_desejada = -1;
	while(posicao_inicial <= posicao_final){
		meio = (posicao_inicial + posicao_final) / 2;
		
		if((artista == vet[meio]) and (!musicAdd[vet_aux[meio]].apagada)){
			posicao_desejada = meio;
			posicao_inicial = posicao_final + 1;
		}
		else{
			if(artista > vet[meio])
				posicao_inicial = meio + 1;
			else
				posicao_final = meio - 1;
		}
	}
	
	if(posicao_desejada != -1){
		musicAdd[vet_aux[posicao_desejada]].imprimir();
		int x = 1, y = 1;
		while(((vet[posicao_desejada + x]) == artista) and (!musicAdd[vet_aux[posicao_desejada + x]].apagada)){
			musicAdd[vet_aux[posicao_desejada + x]].imprimir();
			x++;
		}
		while(((vet[posicao_desejada - y]) == artista) and (!musicAdd[vet_aux[posicao_desejada - y]].apagada)){
			musicAdd[vet_aux[posicao_desejada - y]].imprimir();
			y++;
		}
	
	
	}
	else
		cout << "Nao existe esse artista no arquivo" << endl;

}





void procuraMusica(int tam, string vet[], string musica, int vet_aux[], Musicas musicAdd[]){
	ordenaVetorStrings(vet,tam,vet_aux);
	//busca binaria simples pra encontrar a musica
	
	int posicao_inicial = 0, posicao_final = (tam-1), meio, posicao_desejada = -1;
	while(posicao_inicial <= posicao_final){
		meio = (posicao_inicial + posicao_final) / 2;	
		if((musica == vet[meio]) and (!musicAdd[vet_aux[meio]].apagada)){
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
	if(posicao_desejada != -1){
		musicAdd[vet_aux[posicao_desejada]].imprimir();
		int x = 1, y = 1;
		while(((vet[posicao_desejada + x]) == musica) and (!musicAdd[vet_aux[posicao_desejada + x]].apagada)){
			musicAdd[vet_aux[posicao_desejada + x]].imprimir();
			x++;
		}
		while(((vet[posicao_desejada - y]) == musica) and (!musicAdd[vet_aux[posicao_desejada - y]].apagada)){
			musicAdd[vet_aux[posicao_desejada - y]].imprimir();
			y++;
		}
	}
	
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
        cout << endl << "Nome do Artista: ";
        cin.ignore();
        getline(cin, temp[i].artista);
        cout  << "Nome da Musica: ";
        getline(cin, temp[i].nomeMsc);
        cout << "Duracao da Musica: ";
        cin >> temp[i].duracaoMs;
        cout << "Genero da Musica: ";
        cin.ignore();
        getline(cin, temp[i].generoMusical);
        cout  << "Ano do Lancamento da Musica: ";
        cin >> temp[i].anoLancamento;
        cout << "Numero de Streams da Musica: ";
        cin >> temp[i].streams;
        cout  << "Volume Medio da Musica: ";
        cin >> temp[i].volumeMedio;
		
    }

    delete[]vetor;
    vetor = temp;
    cout<< endl;
    cout<< "--------------------------------" << endl;
    cout<< "Musicas adicionadas com sucesso" << endl;
    cout<< "--------------------------------" << endl;
    cout<< endl;

    return;
}




int main () {
    int numMsc;
    int mscLidas;
    string lixo;

    ifstream arquivo_csv("spotify100.csv"); //abertura do arquivo
	
    if(!arquivo_csv) {
        cout << "Erro ao abrir arquivo!" << endl;
        return 1;

    } else {

        numMsc = 40; //Capacidade de musicas iniciais
        mscLidas = 0; //Valor de musicas que ja foram adicionadas no vetor

        arquivo_csv >> lixo;
        Musicas *musicAdd = new Musicas[numMsc]; // Vetor que armazenas as musicas
        Musicas *temp; // vetor temporario para fazer redimensionamento

        while(arquivo_csv.peek() != EOF) {   // peek() != EOF, vai conferir se o ponteiro de leitura esta ou nao no final doa arquivo
            
            // Redimensionamento
            if(mscLidas == numMsc) {
                numMsc += 5;
                temp = new Musicas[numMsc];

                for(int i = 0; i < mscLidas; i++) {
                    temp[i] = musicAdd[i];

                }
                delete[] musicAdd;
                musicAdd = temp;

            }

            musicAdd[mscLidas].leitura(arquivo_csv, musicAdd[mscLidas]);
            mscLidas++;

        }

        string busca;

        while(busca != "8"){
            cout <<"------------------------" << endl;
            cout << "O que voce deseja? " << endl;
            cout << "------------------------" << endl;
            cout << "[1] Imprimir" << endl << "[2] Imprimir trecho especifico" << endl << "[3] Buscar por ano" << endl << "[4] Buscar por artista" << endl << "[5] Buscar por nome da musica" <<
            endl << "[6] Adicionar Musicas" << endl << "[7] Remover Musicas" << endl << "[8] Sair" << endl; 

            cin >> busca;
			cin.ignore();
            if(busca == "1") {
                string impressao;
                while(impressao != "5"){
					cout << "========IMPRESSAO========" << endl;
					cout << "  Qual a ordem de impressao?  "<< endl;
					cout << "[1] Por Streams" << endl << "[2] Por artista" << endl << "[3] Por musica" << endl << "[4] por ano" << endl << "[5] Sair" << endl;
					cin >> impressao;
                
					if(impressao == "1")
						for(int i =0 ; i < numMsc; i++) 
							buscas(busca, musicAdd[i]);
					else if(impressao == "2"){
						int* vet_aux = new int[numMsc];
						string* vetorArtista = new string[numMsc];
				
						for(int i = 0; i < numMsc; i++){
							vetorArtista[i] = musicAdd[i].artista;
							vet_aux[i] = i;
						}
						ordenaVetorStrings(vetorArtista, numMsc, vet_aux);
						for(int i = 0; i < numMsc; i++){
							musicAdd[vet_aux[i]].imprimir();
						}
						delete[] vet_aux;
						delete[] vetorArtista;
					
					}
					else if(impressao == "3"){
						int* vet_aux = new int[numMsc];
						string* vetorMusica = new string[numMsc];
				
						for(int i = 0; i < numMsc; i++){
							vetorMusica[i] = musicAdd[i].nomeMsc;
							vet_aux[i] = i;
						}
						ordenaVetorStrings(vetorMusica, numMsc, vet_aux);
						for(int i = 0; i < numMsc; i++){
							musicAdd[vet_aux[i]].imprimir();
						}
						delete[] vet_aux;
						delete[] vetorMusica;
					}
					
				
				
				
				}
            }
            else if(busca == "2") {
				int posicao_inicial, posicao_final;
				cout << "Informe o inicio e o fim do trecho" << endl;
				cout << "inicio: ";
				cin >> posicao_inicial;
				cout << "Fim: ";
				cin >> posicao_final;
				
				for(int i = posicao_inicial-1; i <= posicao_final-1; i++)
					musicAdd[i].imprimir();
			
            }
            
            else if(busca == "3") {
                int buscaAno;
                cout << "Qual ano vc deseja buscar?: ";
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
        
			else if(busca == "4"){
			
				string buscaArtista;
				cout << "Qual o nome do artista: ";
				getline(cin,buscaArtista);
				for(unsigned i = 0; i < buscaArtista.size(); i++){
					buscaArtista[i] = tolower(buscaArtista[i]);
				}	
				
				
				int* vet_aux = new int[numMsc];
				string* vetorArtista = new string[numMsc];
				
				for(int i = 0; i < numMsc; i++){
					vetorArtista[i] = musicAdd[i].artista;
					vet_aux[i] = i;
				}
				procuraArtista(numMsc, vetorArtista, buscaArtista, musicAdd, vet_aux);
			
			
			
				delete[] vet_aux;
				delete[] vetorArtista;
			}
			
			      
			else if(busca == "5"){
				string buscaMusica;
				cout << "Qual o nome da musica: ";
				getline(cin,buscaMusica);
				//transformando a string busca pra minuscula
				for(unsigned i = 0; i < buscaMusica.size(); i++)
					buscaMusica[i] = tolower(buscaMusica[i]);
				
				int* vet_aux = new int[numMsc];
				string* vetorMusica = new string[numMsc];
					
				for(int i = 0; i < numMsc; i++){
					vetorMusica[i] = musicAdd[i].nomeMsc;
					vet_aux[i] = i;
				}
				procuraMusica(numMsc,vetorMusica,buscaMusica,vet_aux,musicAdd);
					
					
					
				delete[] vet_aux;
				delete[] vetorMusica;
			}

            else if(busca == "6") {
                int msc_add;
                cout<< "Quantas músicas serão adicionadas?: ";
                cin >> msc_add;

                Adicionar(musicAdd, numMsc, msc_add);


            }
            
            else if(busca == "7"){
				apagarMusica(musicAdd, numMsc);
			}
            
            
        }

    
        delete[] musicAdd;
    }
    
    return 0;
    
}
