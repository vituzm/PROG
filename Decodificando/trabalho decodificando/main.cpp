#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <locale>
#include <cmath>

using namespace std;


int main()
{
    setlocale(LC_ALL,"");

    ifstream inFile; //para acessar o arquivo para leitura
    ofstream outFile; //objeto para o relatorio

    string arquivo;
    string sufixo;
    int sufixo_pos; //posicao do sufixo do arquivo

    //entrada do usuario do nnome do arquivo
    bool erro = true;
    while(erro){
        sufixo_pos = 0;

        cout << "-> DIGITE O NOME DO ARQUIVO PARA LEITURA COM O SEU TIPO:"
        << endl << "Ex: 'nome do arquivo.tipo'" << endl;

        cin >> arquivo;// usuario atribui o nome

        for(int z = arquivo.length()-1; z > 0; --z){ // le o nome do arquivo inversamente para achar o ponto do tipo do arquivo
            sufixo.push_back(arquivo[z]); // adiciona o caractere desejado
            sufixo_pos++;
                if(arquivo[z] == '.') {// se acharmos o "." do sufixo de tipo de arquivo
                    erro = false;
                    break; //fim do loop
                }else if(z == 1){// se não houver ".tipo"
                    cout << "---> TIPO DE ARQUIVO NAO ESPECIFICADO! TENTE NOVAMENTE <---" << endl << endl;
                    sufixo.clear(); // limpando a string para fazer o loop novamente
                    break; //fim do loop
                }
        }

    }

    // apaga o sufixo do nome do arquivo dado pelo usuario
    arquivo.erase((arquivo.length() - sufixo_pos), arquivo.length());
    // inverte sufixo pois foi atribuida de trás para frente
    reverse(sufixo.begin(), sufixo.end());

    inFile.open(arquivo+sufixo, ios::in);
    if (!inFile) // testando se o arquivo existe
    {
        cerr << "Arquivo saida " << sufixo << " nao pode ser aberto" << endl;
        return -1;
    }

    string frase_toda; // string auxiliar para saber a maior palavra
    int maior = 0;
    // calculando a maior palavra
    while (inFile >> frase_toda)
        if(maior < frase_toda.length()) maior = frase_toda.length();


    inFile.close();

    int linhas = maior;; // representara o numero de linhas
    int colunas = 0;

    //conta a quantidade de colunas e o tamanho da frase
    inFile.open(arquivo+sufixo, ios::in);

    int tamanho = 0;// tamanho da frase criptrografada
    int soma = 0;
    char palavras;
    while (!inFile.eof())
    {

        inFile.get(palavras);
        if(soma == maior){
            soma = -1;// menos um para compensar o espaço
            colunas++;
        }
        tamanho++;
        soma++;
    }
    inFile.close();

    tamanho = tamanho -2;//arrumando o tamanho da frase

    char *frase = new char[tamanho]; // frase encriptografada

    // passa para *frase toda a frase criptografada
    inFile.open(arquivo+sufixo, ios::in);
    int p = 0;
    while (!inFile.eof())
    {
        inFile.get(frase[p]);
        p++;

    }
    inFile.close();

    int chave_[colunas]; // vetor que repressenta as commbinações de chave
    for(int aux = 0; aux < colunas; aux++)chave_[aux] = aux;//primeira combinação

    char matriz[linhas][colunas];
    int posicao = 0;

    outFile.open(arquivo + "_dec" + sufixo, ios::out);
    do{
        for(int i = 0; i < colunas; i++)
        {
            for(int y = 0; y < linhas; y++)
            {
                matriz[y][chave_[i]] = frase[posicao];
                if(y == (linhas-1)){ // ignorando os espaços de fim de linha
                posicao++;
                }
            posicao++;
            }
        }

        outFile << "COMBINAÇÃO DE CHAVES: ";
        for(int i = 0; i < colunas; i++)outFile << chave_[i] << "/";


        outFile << endl;

        for(int y = 0; y < linhas; y++){
            for(int x = 0; x < colunas; x++){
                outFile << matriz[y][x];
            }

        }
        outFile << endl;

        posicao = 0; // voltando o vetor para a posição zero

        outFile << endl;
    }while(next_permutation(chave_,chave_+colunas));


    outFile << "RELATORIO FINAL: " << endl;
    outFile << "- " << linhas << " LINHAS" << endl;
    outFile << "- " << colunas << " COLUNAS " << endl;
    outFile << "- " << tamanho << " TAMANHO DA FRASE " << endl;

    outFile.close();

    cout << "RELATORIO FEITO COM SUCESSO: " << arquivo << "_dec" << sufixo;

    delete[] frase;
    return 0;
}
