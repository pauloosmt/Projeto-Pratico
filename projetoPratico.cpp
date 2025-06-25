#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

// Ultima alteração 00:10, 24/06
// Por Paulo;

using namespace std;

struct Musicas
{
    char artista[50];       // Nome do artista
    char nomeMsc[50];       // Nome da música
    int duracaoMs;          // Duração da música em milissegundos
    char generoMusical[30]; // Gênero musical
    int anoLancamento;      // Ano de lançamento
    double streams;         // Quantidade de streams (em bilhões)
    double volumeMedio;     // Volume médio da música (em decibéis)
    bool apagada = false;   // Marca se a música foi apagada logicamente

    // Função para imprimir os dados da música
    void imprimir()
    {
        if (!apagada)
        { // Só imprime se a música não estiver apagada
            cout << endl;
            cout << "Artista: " << artista << endl;
            cout << "Música: " << nomeMsc << endl;
            cout << "Duração: " << duracaoMs << " ms" << endl;
            cout << "Genero: " << generoMusical << endl;
            cout << "Ano: " << anoLancamento << endl;
            cout << "Streams: " << streams << " bilhões" << endl;
            cout << "Volume médio: " << volumeMedio << " dB" << endl;
            cout << "---------------------------" << endl;
        }
    }
    void leitura(ifstream &arquivo, Musicas &musicAdd)
    {
        
        string lixo, temp;
        arquivo.ignore();
        arquivo.ignore();
        getline(arquivo, temp, ',');
        strncpy(musicAdd.artista, temp.c_str(), sizeof(artista) - 1);
        musicAdd.artista[sizeof(artista) - 1] = '\0';
        getline(arquivo, temp, ',');
        strncpy(musicAdd.nomeMsc, temp.c_str(), sizeof(nomeMsc) - 1);
        musicAdd.nomeMsc[sizeof(nomeMsc) - 1] = '\0';
        arquivo >> musicAdd.anoLancamento;
        getline(arquivo, lixo, ',');
        getline(arquivo, temp, ',');
        strncpy(musicAdd.generoMusical, temp.c_str(), sizeof(generoMusical) - 1);
        musicAdd.generoMusical[sizeof(generoMusical) - 1] = '\0';
        arquivo >> musicAdd.streams;
        getline(arquivo, lixo, ',');
        arquivo >> musicAdd.duracaoMs;
        getline(arquivo, lixo, ',');
        arquivo >> musicAdd.volumeMedio;
        getline(arquivo, lixo, ';');
    }
};
// Função para converter uma string para minúsculas
string toLowerCustom(string str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {                 // Verifica se é letra maiúscula
            str[i] += 32; // Converte para minúscula (diferença entre ASCII maiúscula e minúscula)
        }
    }
    return str;
}

// Função para buscar e apagar (logicamente) uma música por nome
void apagarMusica(Musicas vetor[], int numMsc)
{
    string nomeBusca;
    cout << "Digite o nome da música que deseja apagar: ";
    getline(cin, nomeBusca);
    nomeBusca = toLowerCustom(nomeBusca); // Converte a busca para minúsculo

    bool encontrou = false; // Flag para verificar se encontrou

    for (int i = 0; i < numMsc; i++)
    {
        // Verifica se a música ainda não foi apagada e se o nome bate
        if (!vetor[i].apagada && toLowerCustom(vetor[i].nomeMsc) == nomeBusca)
        {
            vetor[i].apagada = true; // Marca como apagada
            encontrou = true;
            
            cout << "\33[1;32m===============================================" << endl;
            cout << " Música '" << vetor[i].nomeMsc << "' apagada com sucesso! " << endl;
			cout << "===============================================\033[m" << endl;
        }
    }

    if (!encontrou)
    {
		cout << "\033[1;31m================================================" << endl;
        cout << "| Nenhuma musica com esse nome foi encontrada! |" << endl;
		cout << "================================================\033[m" << endl;
    }
}

void ordenaVetorStrings(string vet[], int tam, int vet_aux[])
{
    // transformando em minuscula todos os nomes de artistas antes de ordenar
    for (int i = 0; i < tam; i++)
        vet[i] = toLowerCustom(vet[i]);

    string aux;
    int aux2;
    for (int i = 0; i < tam - 1; i++)
    {
        int indice_menor = i;
        for (int j = i + 1; j < tam; j++)
            if (vet[j] < vet[indice_menor])
                indice_menor = j;
        aux = vet[i];
        vet[i] = vet[indice_menor];
        vet[indice_menor] = aux;
        // ordenando o vetor auxiliar que tem os indices de cada musica no vetor original junto
        aux2 = vet_aux[i];
        vet_aux[i] = vet_aux[indice_menor];
        vet_aux[indice_menor] = aux2;
    }
}

// funçao que, atraves da busca binaria, faz a procura do nome do artista buscado
void procuraArtista(int tam, string vet[], string artista, Musicas musicAdd[], int vet_aux[])
{

    ordenaVetorStrings(vet, tam, vet_aux);

    int posicao_inicial = 0, posicao_final = tam - 1, meio, posicao_desejada = -1;
    while (posicao_inicial <= posicao_final)
    {
        meio = (posicao_inicial + posicao_final) / 2;

        if ((artista == vet[meio]) and (!musicAdd[vet_aux[meio]].apagada))
        {
            posicao_desejada = meio;
            posicao_inicial = posicao_final + 1;
        }
        else
        {
            if (artista > vet[meio])
                posicao_inicial = meio + 1;
            else
                posicao_final = meio - 1;
        }
    }
    // imprime o artista na posiçao encontrada e todas as outras possiveis apariçoes do mesmo artista
    if (posicao_desejada != -1)
    {
        musicAdd[vet_aux[posicao_desejada]].imprimir();
        int x = 1, y = 1;
        while (((vet[posicao_desejada + x]) == artista) and (!musicAdd[vet_aux[posicao_desejada + x]].apagada))
        {
            musicAdd[vet_aux[posicao_desejada + x]].imprimir();
            x++;
        }
        while (((vet[posicao_desejada - y]) == artista) and (!musicAdd[vet_aux[posicao_desejada - y]].apagada))
        {
            musicAdd[vet_aux[posicao_desejada - y]].imprimir();
            y++;
        }
    }
    else
    {
        cout << endl << "\33[1;31m=========================================" << endl;
        cout << "| Não existe esse artista no arquivo!! |" << endl;
        cout << "=========================================\33[m" << endl;
    }
}
// funçao que, atraves da busca binaria, faz a procura do nome da musica buscada
void procuraMusica(int tam, string vet[], string musica, int vet_aux[], Musicas musicAdd[])
{
    ordenaVetorStrings(vet, tam, vet_aux);
    // busca binaria simples pra encontrar a musica

    int posicao_inicial = 0, posicao_final = (tam - 1), meio, posicao_desejada = -1;
    while (posicao_inicial <= posicao_final)
    {
        meio = (posicao_inicial + posicao_final) / 2;
        if ((musica == vet[meio]) and (!musicAdd[vet_aux[meio]].apagada))
        {
            posicao_desejada = meio;
            posicao_inicial = posicao_final + 1;
        }
        else
        {
            if (musica > vet[meio])
                posicao_inicial = meio + 1;
            else
                posicao_final = meio - 1;
        }
    }
    // imprime a(s) musica(s) desejada(s) ou mensagem de erro caso ela n exista no arquivo
    if (posicao_desejada != -1)
    {
        musicAdd[vet_aux[posicao_desejada]].imprimir();
        int x = 1, y = 1;
        while (((vet[posicao_desejada + x]) == musica) and (!musicAdd[vet_aux[posicao_desejada + x]].apagada))
        {
            musicAdd[vet_aux[posicao_desejada + x]].imprimir();
            x++;
        }
        while (((vet[posicao_desejada - y]) == musica) and (!musicAdd[vet_aux[posicao_desejada - y]].apagada))
        {
            musicAdd[vet_aux[posicao_desejada - y]].imprimir();
            y++;
        }
    }

    else
    {
        cout << endl << "\33[1;31m=========================================" << endl;
        cout << "| Não existe essa música no arquivo!! |" << endl;
        cout << "=========================================\33[m" << endl;
    }
}

void ordenarANO(int tam, int *vetor_pos, int vet[])
{
    int menor, aux;
    for (int i = 0; i < tam - 1; i++)
    {
        menor = i;
        for (int j = i + 1; j < tam; j++)
        {
            if (vet[vetor_pos[j]] < vet[vetor_pos[menor]])
            {
                menor = j;
            }
        }
        aux = vetor_pos[i];
        vetor_pos[i] = vetor_pos[menor];
        vetor_pos[menor] = aux;
    }
}

void busca_dos_anos(int tam, int *&vetor_pos, int vet[], int anoBusca, int &ocasioes)
{
    // Primeira parte: Ordenação dos anos
    ordenarANO(tam, vetor_pos, vet);
    // Foi ordenado por Selection Sort

    // Segunda parte: Fazer a busca binaria e achar todas as repeticoes

    // Comeca fazendo a busca binaria padrao
    int elementosEsquer = 0, elementosDirei = tam - 1;
    bool encontrado = false;
    int posEncontrado = 0;

    while (elementosEsquer <= elementosDirei and !encontrado)
    {
        int meioVetor = (elementosDirei + elementosEsquer) / 2;
        if (vet[vetor_pos[meioVetor]] == anoBusca)
        {
            posEncontrado = meioVetor;
            encontrado = true;
            ocasioes++;
        }
        else if (vet[vetor_pos[meioVetor]] < anoBusca)
        {
            elementosEsquer = meioVetor + 1;
        }
        else
        {
            elementosDirei = meioVetor - 1;
        }
    }

    if (!encontrado)
    {
        cout << endl << "\033[1;31m==========================================================================" << endl;
        cout << "| ERRO! Não foi possivel achar uma música na lista lançada em " << anoBusca << "!!! |" << endl;
        cout << "==========================================================================\033[m" << endl;
        return;
    }

    // Agora, vamos achar todas as repeticoes, comecando pela esquerda
    int inicio = posEncontrado;
    while (inicio > 0 and vet[vetor_pos[inicio - 1]] == anoBusca)
    {
        inicio--;
        ocasioes++;
    }

    // Agora, vamos achar todas as repeticoes, que esta a direita da posicao encontrada na busca binaria
    int fim = posEncontrado;
    while (fim < tam - 1 and vet[vetor_pos[fim + 1]] == anoBusca)
    {
        fim++;
        ocasioes++;
    }

    /* Nessa parte iremos redimensionar o vetor_pos, para que ele armazene apenas as
    posicoes que contenham musicas que forem lançadas no ano desejado */

    int *temp = new int[ocasioes]; /*A variavel ocasioes auxilia, pois ela conta quantas repeticoes
                                       do mesmo ano existem na lista original */

    for (int i = 0; i < ocasioes and inicio <= fim; i++)
    {
        temp[i] = vetor_pos[inicio];
        inicio++;
    }

    vetor_pos = temp; // Por fim, o vetor_pos passa a apontadar para o nosso vetor temporario

    return;
}

void adicionar(Musicas *&vetor, int &tam, int adicional)
{
    tam += adicional;
    string Temp;
    Musicas *temp = new Musicas[tam];

    for (int i = 0; i < tam - adicional; i++)
    {
        strncpy(temp[i].artista, vetor[i].artista, sizeof(temp[i].artista));
        temp[i].artista[sizeof(temp[i].artista) - 1] = '\0';

        strncpy(temp[i].nomeMsc, vetor[i].nomeMsc, sizeof(temp[i].nomeMsc));
        temp[i].nomeMsc[sizeof(temp[i].nomeMsc) - 1] = '\0';

        strncpy(temp[i].generoMusical, vetor[i].generoMusical, sizeof(temp[i].generoMusical));
        temp[i].generoMusical[sizeof(temp[i].generoMusical) - 1] = '\0';
        // temp[i].artista = vetor[i].artista;
        // temp[i].nomeMsc = vetor[i].nomeMsc;
        temp[i].duracaoMs = vetor[i].duracaoMs;
        // temp[i].generoMusical = vetor[i].generoMusical;
        temp[i].anoLancamento = vetor[i].anoLancamento;
        temp[i].streams = vetor[i].streams;
        temp[i].volumeMedio = vetor[i].volumeMedio;
    }
    for (int i = tam - adicional; i < tam; i++)
    {
        cout << endl
             << "Nome do Artista: ";
        cin.ignore();
        getline(cin, Temp);
        strncpy(temp[i].artista, Temp.c_str(), sizeof(temp[i].artista));
        cout << "Nome da Música: ";
        getline(cin, Temp);
        strncpy(temp[i].nomeMsc, Temp.c_str(), sizeof(temp[i].nomeMsc));
        cout << "Duração(ms): ";
        cin >> temp[i].duracaoMs;
        cout << "Gênero: ";
        cin.ignore();
        getline(cin, Temp);
        strncpy(temp[i].generoMusical, Temp.c_str(), sizeof(temp[i].generoMusical));
        cout << "Ano do Lançamento: ";
        cin >> temp[i].anoLancamento;
        cout << "Numero de Streams: ";
        cin >> temp[i].streams;
        cout << "Volume Médio: ";
        cin >> temp[i].volumeMedio;
    }

    delete[] vetor;
    vetor = temp;
    cout << endl;
    cout << "\033[1;32m====================================" << endl;
    cout << "| Músicas adicionadas com sucesso |" << endl;
    cout << "====================================\033[m" << endl;
    cout << endl;

    return;
}

void exportarCSV(int tam, Musicas musicAdd[], ofstream &arquivo, int vetor_pos[])
{

    arquivo << "artist,song,year,genre,streams_billion,duration_ms,loudness_dB;";

    for (int i = 0; i < tam; i++)
    {
        if (!musicAdd[i].apagada)
        {
            arquivo << "\n"
                    << musicAdd[vetor_pos[i]].artista << ","
                    << musicAdd[vetor_pos[i]].nomeMsc << ","
                    << musicAdd[vetor_pos[i]].anoLancamento << ","
                    << musicAdd[vetor_pos[i]].generoMusical << ","
                    << musicAdd[vetor_pos[i]].streams << ","
                    << musicAdd[vetor_pos[i]].duracaoMs << ","
                    << musicAdd[vetor_pos[i]].volumeMedio << ";";
        }
    }
}

void exportarBIN(int tam, Musicas musicAdd[], ofstream &arquivo)
{
    for (int i = 0; i < tam; i++)
    {
        if (!musicAdd[i].apagada)
        {
            arquivo.write((const char *)&musicAdd[i], sizeof(Musicas));
        }
    }
}

int main()
{
    int numMsc;
    int mscLidas;
    string lixo;

    string modelo_arq;
    while ((modelo_arq != "1") and (modelo_arq != "2"))
    {
        cout << "\033[1;33m================== ARQUIVO ==================\033[m" << endl;
        cout << " Qual arquivo você deseja abrir para leitura " << endl;
        cout << "[1] Arquivo csv" << endl
             << "[2] Arquivo binário" << endl
             << "> ";
        cin >> modelo_arq;
    }

    ifstream arquivo;
    if (modelo_arq == "1")
        arquivo.open("spotify100.csv"); // abertura do arquivo
    else if (modelo_arq == "2")
        arquivo.open("Spotify100.bin", ios::binary);

    if (!arquivo)
    {
        cout << "\033[1;31mErro ao abrir arquivo!\033[m" << endl;
        return 1;
    }
    else
    {
        Musicas *musicAdd;
        if (modelo_arq == "1")
        {
            numMsc = 40;  // Capacidade de musicas iniciais
            mscLidas = 0; // Valor de musicas que ja foram adicionadas no vetor

            arquivo >> lixo;
            musicAdd = new Musicas[numMsc]; // Vetor que armazenas as musicas
            Musicas *temp;                  // vetor temporario para fazer redimensionamento

            while (arquivo.peek() != EOF)
            { // peek() != EOF, vai conferir se o ponteiro de leitura esta ou nao no final doa arquivo

                // Redimensionamento
                if (mscLidas == numMsc)
                {
                    numMsc += 5;
                    temp = new Musicas[numMsc];

                    for (int i = 0; i < mscLidas; i++)
                    {
                        temp[i] = musicAdd[i];
                    }
                    delete[] musicAdd;
                    musicAdd = temp;
                }

                musicAdd[mscLidas].leitura(arquivo, musicAdd[mscLidas]);
                mscLidas++;
            }
        }
        else if (modelo_arq == "2")
        {
            numMsc = 40;  // Capacidade de musicas iniciais
            mscLidas = 0; // Valor de musicas que ja foram adicionadas no vetor

            musicAdd = new Musicas[numMsc]; // Vetor que armazenas as musicas
            Musicas *temp;                  // vetor temporario para fazer redimensionamento

            while (arquivo.read((char *)&musicAdd[mscLidas], sizeof(Musicas)))
            {
                mscLidas++;
                // Redimensionamento
                if (mscLidas == numMsc)
                {
                    numMsc += 5;
                    temp = new Musicas[numMsc];

                    for (int i = 0; i < mscLidas; i++)
                    {
                        temp[i] = musicAdd[i];
                    }
                    delete[] musicAdd;
                    musicAdd = temp;
                }
            }
            arquivo.close();
            numMsc = mscLidas;
        }

        string busca;

        while (busca != "9")
        {
            cout << "\33[1;33m=========================" << endl;
            cout << "| Como posso te ajudar? |" << endl;
            cout << "=========================\033[0m" << endl;
            cout << "[1] Imprimir" << endl
                 << "[2] Imprimir trecho específico" << endl
                 << "[3] Buscar por ano" << endl
                 << "[4] Buscar por artista" << endl
                 << "[5] Buscar por nome da música" << endl
                 << "[6] Adicionar Músicas" << endl
                 << "[7] Remover Músicas" << endl
                 << "[8] Salvar alterações" << endl
                 << "\033[1;31m[9] Sair\033[0m" << endl
                 << "> ";

            cin >> busca;
            cin.ignore();
            if (busca == "1")
            {
                string impressao;
                while (impressao != "5")
                {
                    cout << "\33[1;33m========IMPRESSÃO========\33[0m" << endl;
                    cout << "  Qual a ordem de impressão?  " << endl;
                    cout << "[1] Ordem padrão" << endl
                         << "[2] Por artista" << endl
                         << "[3] Por música" << endl
                         << "[4] Por ano" << endl
                         << "\033[1;31m[5] Sair\033[m" << endl
                         << "> ";
                    cin >> impressao;

                    if (impressao == "1")
                        for (int i = 0; i < numMsc; i++)
                            musicAdd[i].imprimir();
                    
                    else if (impressao == "2")
                    {
                        int *vet_aux = new int[numMsc];
                        string *vetorArtista = new string[numMsc];

                        for (int i = 0; i < numMsc; i++)
                        {
                            vetorArtista[i] = musicAdd[i].artista;
                            vet_aux[i] = i;
                        }
                        ordenaVetorStrings(vetorArtista, numMsc, vet_aux);
                        for (int i = 0; i < numMsc; i++)
                        {
                            musicAdd[vet_aux[i]].imprimir();
                        }
                        delete[] vet_aux;
                        delete[] vetorArtista;
                    }
                    else if (impressao == "3")
                    {
                        int *vet_aux = new int[numMsc];
                        string *vetorMusica = new string[numMsc];

                        for (int i = 0; i < numMsc; i++)
                        {
                            vetorMusica[i] = musicAdd[i].nomeMsc;
                            vet_aux[i] = i;
                        }
                        ordenaVetorStrings(vetorMusica, numMsc, vet_aux);
                        for (int i = 0; i < numMsc; i++)
                        {
                            musicAdd[vet_aux[i]].imprimir();
                        }
                        delete[] vet_aux;
                        delete[] vetorMusica;
                    }

                    else if (impressao == "4")
                    {
                        int *vetAux = new int[numMsc];
                        int *vetAnos = new int[numMsc];

                        for (int i = 0; i < numMsc; i++)
                        {
                            vetAnos[i] = musicAdd[i].anoLancamento;
                            vetAux[i] = i;
                        }
                        ordenarANO(numMsc, vetAux, vetAnos);
                        for (int i = 0; i < numMsc; i++)
                        {
                            musicAdd[vetAux[i]].imprimir();
                        }

                        delete[] vetAux;
                        delete[] vetAnos;
                    }
                }
            }
            else if (busca == "2")
            {
                int posicao_inicial, posicao_final;
                cout << "Informe o inicio e o fim do trecho" << endl;
                cout << "inicio: ";
                cin >> posicao_inicial;
                cout << "Fim: ";
                cin >> posicao_final;

                if ((posicao_inicial > 0 and posicao_inicial <= numMsc) and (posicao_final > 0 and posicao_final <= numMsc) and (posicao_inicial <= posicao_final))
                {
                    for (int i = posicao_inicial - 1; i <= posicao_final - 1; i++)
                        musicAdd[i].imprimir();
                }
                else
                {
                    cout << endl;
                    cout << "\033[1;31m=======================================" << endl;
                    cout << "| Trecho inválido, tente novamente!! |" << endl;
                    cout << "=======================================\033[m" << endl;
                    cout << endl;
                }
            }

            else if (busca == "3")
            {
                int buscaAno;
                cout << "Digite o ano que você deseja buscar: ";
                cin >> buscaAno;

                // Vetores auxiliares que ajudarao na ordenacao
                int *vetor_aux = new int[numMsc]; // Esse recebe o indice que cada musica
                int *vetorAno = new int[numMsc];  // Esse recebe o ano de cada musica

                /*Ao fim da ordenacao, o vetorAno possuira todos os anos em ordem crescente,
                enquanto o vetor_aux, possuira a posicao desses anos em relacao ao arquivo original
                Portanto, os elemntos do vetor_aux sao indices para buscarmos musicas no "musicAdd"
                de maneira ordenada*/

                for (int i = 0; i < numMsc; i++)
                {

                    vetor_aux[i] = i;
                    vetorAno[i] = musicAdd[i].anoLancamento;
                }

                int numOCasioes = 0;
                busca_dos_anos(numMsc, vetor_aux, vetorAno, buscaAno, numOCasioes);

                /*Imprimindo apenas asd musicas, cujo ano de lancamento
                e o mesmo do ano que o usuario digitou */

                for (int i = 0; i < numOCasioes; i++)
                {
                    musicAdd[vetor_aux[i]].imprimir();
                }

                delete[] vetor_aux;
                delete[] vetorAno;
            }

            else if (busca == "4")
            {

                string buscaArtista;
                cout << "Qual o nome do artista: ";
                getline(cin, buscaArtista);
                buscaArtista = toLowerCustom(buscaArtista);

                int *vet_aux = new int[numMsc];
                string *vetorArtista = new string[numMsc];

                for (int i = 0; i < numMsc; i++)
                {
                    vetorArtista[i] = musicAdd[i].artista;
                    vet_aux[i] = i;
                }
                procuraArtista(numMsc, vetorArtista, buscaArtista, musicAdd, vet_aux);

                delete[] vet_aux;
                delete[] vetorArtista;
            }

            else if (busca == "5")
            {
                string buscaMusica;
                cout << "Qual o nome da música: ";
                getline(cin, buscaMusica);
                // transformando a string busca pra minuscula
                buscaMusica = toLowerCustom(buscaMusica);

                int *vet_aux = new int[numMsc];
                string *vetorMusica = new string[numMsc];

                for (int i = 0; i < numMsc; i++)
                {
                    vetorMusica[i] = musicAdd[i].nomeMsc;
                    vet_aux[i] = i;
                }
                procuraMusica(numMsc, vetorMusica, buscaMusica, vet_aux, musicAdd);

                delete[] vet_aux;
                delete[] vetorMusica;
            }

            else if (busca == "6")
            {
                int msc_add;
                cout << "Quantas músicas serão adicionadas: ";
                cin >> msc_add;

                adicionar(musicAdd, numMsc, msc_add);
            }

            else if (busca == "7")
            {
                apagarMusica(musicAdd, numMsc);
            }

            else if (busca == "8")
            {
                string salvar;
                while (salvar != "3")
                {
                    cout << "\33[1;33m================SALVAR================\33[m" << endl;
                    cout << " Onde você deseja salvar as alterações? " << endl;
                    cout << "[1] Exportar para um arquivo binário" << endl
                         << "[2] Exportar para um arquivo CSV" << endl
                         << "[3] Voltar" << endl;
                    cout << "> ";
                    cin >> salvar;
                    
                    ofstream arquivo_saida;
                    if (salvar == "1")
                    {
                        arquivo_saida.open("arquivoSaidaTeste.bin", ios::binary);
                        exportarBIN(numMsc, musicAdd, arquivo_saida);
                        cout << "\033[1;32m=====================================" << endl;
                        cout << "| Músicas exportadas com sucesso!! |" << endl;
                        cout << "=====================================\033[m" << endl;
                    }
                    else if (salvar == "2")
                    {
                        arquivo_saida.open("arquivoSaidaTeste.csv");
                        string ordem_opcao;
                        bool salvar = false;
                        while (!salvar)
                        {

                            cout << "\33[1;33m===========================" << endl;
                            cout << "Deseja salvar em que ordem?\33[m" << endl;
                            cout << "[1] Ordem padrão" << endl
                                 << "[2] Ordenado por Artista" << endl
                                 << "[3] Ordenado por Músicas" << endl;
                            cout << "[4] Ordenado por Ano" << endl
                                 << "[5] Voltar" << endl;
                            cout << "> ";
                            cin >> ordem_opcao;

                            if (ordem_opcao == "1")
                            {

                                int *vetAux = new int[numMsc];
                                for (int i = 0; i < numMsc; i++)
                                {
                                    vetAux[i] = i;
                                }

                                exportarCSV(numMsc, musicAdd, arquivo_saida, vetAux);

                                cout << "\033[1;32m=====================================" << endl;
                                cout << "| Músicas exportadas com sucesso!! |" << endl;
                                cout << "=====================================\033[m" << endl;
                                salvar = true;

                                delete[] vetAux;
                            }
                            else if (ordem_opcao == "2")
                            {
                                int *vet_aux = new int[numMsc];
                                string *vetorArtista = new string[numMsc];

                                for (int i = 0; i < numMsc; i++)
                                {
                                    vetorArtista[i] = musicAdd[i].artista;
                                    vet_aux[i] = i;
                                }

                                ordenaVetorStrings(vetorArtista, numMsc, vet_aux);

                                exportarCSV(numMsc, musicAdd, arquivo_saida, vet_aux);

                                delete[] vet_aux;
                                delete[] vetorArtista;

                                cout << "\033[1;32m=====================================" << endl;
                                cout << "| Músicas exportadas com sucesso!! |" << endl;
                                cout << "=====================================\033[m" << endl;

                                salvar = true;
                            }
                            else if (ordem_opcao == "3")
                            {
                                int *vet_aux = new int[numMsc];
                                string *vetorMusica = new string[numMsc];

                                for (int i = 0; i < numMsc; i++)
                                {
                                    vetorMusica[i] = musicAdd[i].nomeMsc;
                                    vet_aux[i] = i;
                                }
                                ordenaVetorStrings(vetorMusica, numMsc, vet_aux);

                                exportarCSV(numMsc, musicAdd, arquivo_saida, vet_aux);

                                cout << "\033[1;32m=====================================" << endl;
                                cout << "| Músicas exportadas com sucesso!! |" << endl;
                                cout << "=====================================\033[m" << endl;

                                salvar = true;

                                delete[] vet_aux;
                                delete[] vetorMusica;
                            }
                            else if (ordem_opcao == "4")
                            {
                                int *vetAux = new int[numMsc];
                                int *vetAnos = new int[numMsc];

                                for (int i = 0; i < numMsc; i++)
                                {
                                    vetAnos[i] = musicAdd[i].anoLancamento;
                                    vetAux[i] = i;
                                }

                                ordenarANO(numMsc, vetAux, vetAnos);

                                exportarCSV(numMsc, musicAdd, arquivo_saida, vetAux);

                                cout << "\033[1;32m=====================================" << endl;
                                cout << "| Músicas exportadas com sucesso!! |" << endl;
                                cout << "=====================================\033[m" << endl;

                                salvar = true;

                                delete[] vetAux;
                                delete[] vetAnos;
                            }

                            else if (ordem_opcao == "5")
                            {
                                salvar = true;
                            }
                            
                        }
                      
                    }
                    arquivo.close();
                }
            }
        }

        cout << endl;
        cout << "\033[1;33m===============================" << endl;
        cout << "|   Obrigado, volte sempre!   |" << endl;
        cout << "===============================\033[m" << endl;
        cout << endl;

        delete[] musicAdd;
    }

    return 0;
}
