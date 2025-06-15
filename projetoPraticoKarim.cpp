#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Estrutura que representa uma música
struct Musica {
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
void apagarMusica(Musica vetor[], int numMsc) {
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

// Função para imprimir todas as músicas (não apagadas)
void imprimirTudo(Musica vetor[], int numMsc) {
    for (int i = 0; i < numMsc; i++) {
        vetor[i].imprimir();
    }
}

// Função para buscar músicas por artista
void buscarPorArtista(Musica vetor[], int numMsc) {
    string buscaArtista;
    cout << "Digite o nome do artista: ";
    getline(cin, buscaArtista);
    buscaArtista = toLowerCustom(buscaArtista); // Converte a busca para minúsculo

    bool encontrou = false;

    for (int i = 0; i < numMsc; i++) {
        // Verifica se a música não está apagada e se o artista bate
        if (!vetor[i].apagada && toLowerCustom(vetor[i].artista) == buscaArtista) {
            vetor[i].imprimir();
            encontrou = true;
        }
    }

    if (!encontrou) {
        cout << "Nenhuma musica desse artista foi encontrada!" << endl;
    }
}

// Função para buscar músicas por nome
void buscarPorMusica(Musica vetor[], int numMsc) {
    string buscaMusica;
    cout << "Digite o nome da musica: ";
    getline(cin, buscaMusica);
    buscaMusica = toLowerCustom(buscaMusica); // Converte a busca para minúsculo

    bool encontrou = false;

    for (int i = 0; i < numMsc; i++) {
        if (!vetor[i].apagada && toLowerCustom(vetor[i].nomeMsc) == buscaMusica) {
            vetor[i].imprimir();
            encontrou = true;
        }
    }

    if (!encontrou) {
        cout << "Essa musica nao existe no arquivo!" << endl;
    }
}

// Função para buscar músicas por ano de lançamento
void buscarPorAno(Musica vetor[], int numMsc) {
    int buscaAno;
    cout << "Digite o ano que deseja buscar: ";
    cin >> buscaAno;
    cin.ignore(); // Limpa o buffer

    bool encontrou = false;

    for (int i = 0; i < numMsc; i++) {
        if (!vetor[i].apagada && vetor[i].anoLancamento == buscaAno) {
            vetor[i].imprimir();
            encontrou = true;
        }
    }

    if (!encontrou) {
        cout << "Nenhuma musica lancada em " << buscaAno << " foi encontrada!" << endl;
    }
}

// Função para adicionar novas músicas ao vetor
void adicionarMusicas(Musica*& vetor, int& numMsc, int qtdNova) {
    int novoTam = numMsc + qtdNova; // Novo tamanho total
    Musica* temp = new Musica[novoTam]; // Aloca novo vetor com o novo tamanho

    // Copia as músicas já existentes
    for (int i = 0; i < numMsc; i++) {
        temp[i] = vetor[i];
    }

    // Lê as novas músicas
    for (int i = numMsc; i < novoTam; i++) {
        cout << "Nome do artista: ";
        getline(cin, temp[i].artista);
        cout << "Nome da musica: ";
        getline(cin, temp[i].nomeMsc);
        cout << "Duracao (ms): ";
        cin >> temp[i].duracaoMs;
        cin.ignore();
        cout << "Genero musical: ";
        getline(cin, temp[i].generoMusical);
        cout << "Ano de lancamento: ";
        cin >> temp[i].anoLancamento;
        cout << "Streams (em bilhoes): ";
        cin >> temp[i].streams;
        cout << "Volume medio (dB): ";
        cin >> temp[i].volumeMedio;
        cin.ignore();
    }

    delete[] vetor; // Libera o vetor antigo
    vetor = temp;   // Atualiza o ponteiro para o novo vetor
    numMsc = novoTam; // Atualiza o tamanho total

    cout << "Musicas adicionadas com sucesso!" << endl;
}

// Função principal
int main() {
    ifstream arquivo("spotify100.csv"); // Abre o arquivo de músicas
    if (!arquivo) { // Se não conseguir abrir
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1; // Encerra o programa
    }

    int numMsc;
    string lixo;
    arquivo >> numMsc >> lixo; // Lê o número de músicas (o formato aqui supõe um número inicial no arquivo)

    Musica* vetor = new Musica[numMsc]; // Aloca o vetor de músicas

    // Lê os dados de cada música do arquivo CSV
    for (int i = 0; i < numMsc; i++) {
        getline(arquivo, vetor[i].artista, ',');
        getline(arquivo, vetor[i].nomeMsc, ',');
        arquivo >> vetor[i].anoLancamento;
        getline(arquivo, lixo, ','); // Ignora a vírgula
        getline(arquivo, vetor[i].generoMusical, ',');
        arquivo >> vetor[i].streams;
        getline(arquivo, lixo, ',');
        arquivo >> vetor[i].duracaoMs;
        getline(arquivo, lixo, ',');
        arquivo >> vetor[i].volumeMedio;
        getline(arquivo, lixo, '\n'); // Ignora até o final da linha
    }

    string opcao;

    // Loop do menu principal
    while (opcao != "8") {
        cout << "--- MENU ---" << endl;
        cout << "[1] Imprimir tudo" << endl;
        cout << "[2] Imprimir trecho" << endl;
        cout << "[3] Buscar por ano" << endl;
        cout << "[4] Buscar por artista" << endl;
        cout << "[5] Buscar por musica" << endl;
        cout << "[6] Adicionar musicas" << endl;
        cout << "[7] Apagar uma musica" << endl;
        cout << "[8] Sair" << endl;
        cout << "Escolha: ";
        getline(cin, opcao);

        if (opcao == "1") {
            imprimirTudo(vetor, numMsc);
        }
        else if (opcao == "2") {
            int ini, fim;
            cout << "Inicio: ";
            cin >> ini;
            cout << "Fim: ";
            cin >> fim;
            cin.ignore(); // Limpa o buffer
            // Imprime do índice ini até fim
            for (int i = ini - 1; i < fim && i < numMsc; i++) {
                vetor[i].imprimir();
            }
        }
        else if (opcao == "3") {
            buscarPorAno(vetor, numMsc);
        }
        else if (opcao == "4") {
            buscarPorArtista(vetor, numMsc);
        }
        else if (opcao == "5") {
            buscarPorMusica(vetor, numMsc);
        }
        else if (opcao == "6") {
            int qtd;
            cout << "Quantas musicas deseja adicionar? ";
            cin >> qtd;
            cin.ignore();
            adicionarMusicas(vetor, numMsc, qtd);
        }
        else if (opcao == "7") {
            apagarMusica(vetor, numMsc);
        }
        else if (opcao != "8") {
            cout << "Opcao invalida! Tente novamente." << endl;
        }
    }

    delete[] vetor; // Libera a memória alocada
    return 0;
}
