#include <iostream>
#include <iomanip>

using namespace std;

struct iregistros_{
    int numRegistros = 0;
    int *tvs;
};

void novoRegistro(iregistros_ *vetor){
    int oldValues[vetor->numRegistros+1]; // VETOR PARA VALORES ANTIGOS

    vetor->tvs = new int[vetor->numRegistros+1];// VETOR COM O NUMERO DE TELEVISORES QUE AUMENTA A CADA REGISTRO NOVO
    char menu = 's';

    cout << "+continuar: 's'" << endl << "+não continuar; 'q'" << endl << endl;


    while (1){
        cout << "===> REGISTRO NUMERO" << vetor->numRegistros+1 << endl;
        cout << "+Continuar? ";
        cin >> menu;
        if(menu == 'q') break; // CASO O USURAIO APERTAR 'q' ENCERRA O PROGRAMA

        cout << endl <<"+Quantos televisores há na sua casa?: "; //COLETA DE DADOS
        cin >> vetor->tvs[vetor->numRegistros]; // ATRIBUINDO O NOVO VALOR


        for(int i = 0; i < vetor->numRegistros+1; i++){
            oldValues[i] = vetor->tvs[i]; // COPIANDO OS VALORES ANTIGOS INCLUINDO O NOVO VALOR
        }

        vetor->numRegistros++; // PROXIMO REGISTRO
        vetor->tvs = new int[vetor->numRegistros+1]; // NOVA MEMÓRIA // APAGA A MEMORIA ANTIGA DO VETOR



        for(int i = 0; i < vetor->numRegistros; i++){
             vetor->tvs[i] = oldValues[i]; // COLAMOS OS VALORES ANTIGOS NA NOVA MEMORIA
        }

    }

     for(int i = 0; i < vetor->numRegistros; i++){

     }


}


void relatorio(iregistros_ *dados){
    int noTV = 0; // variavel para contar quantas casas n tem tv
    int total_tvs = 0;

    cout << "->TOTAL DE RELATORIOS NO DIA: " << dados->numRegistros << endl;

    for(int i = 0; i < dados->numRegistros; i++){
            if(dados->tvs == 0) noTV++;
            total_tvs = total_tvs+dados->tvs[i]; //total de tvs
    }

     cout << "->TOTAL DE CASAS SEM TV: " << noTV << endl;

     float media = (total_tvs) / dados->numRegistros;

     cout << "->MEDIA TOTAL DE TVS POR RESIDENCIAS: ";
     cout << fixed << setprecision(2) << media << endl;
}



int main()
{
    iregistros_ dados;

    novoRegistro(&dados); // criar novos registros

    relatorio(&dados); // relatorio dos registros

    delete dados.tvs;
}
