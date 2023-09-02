#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <locale>
#include <cmath>
#include <cstdint>

using namespace std;

#pragma pack(push)
#pragma pack(1)
struct cabecalho_arq { //cabe�alho de arquivo
    char assinatura[2];
    int32_t tam_arquivo;
    short int reserve_1; // como o int � 4 bytes usamos short
    short int reserve_2; // que ira reduzir para 2 bytes
    int dataOffset;
};

struct cabecalho_bitMapa{ //cabe�alho de mapa de bits
    int tam_cabecalho;
    unsigned int largura_img; // 4 bytes com valores int +
    unsigned int altura_img;
    short int planes; // apenas 2 bytes
    short int bitsPorPixel;
    int compressao;
    int tam_img;
    int PixelsPorMetro_X;
    int PixelsPorMetro_Y;
    int total_cores;
    int cores_imp; // cores importantes

};
#pragma pack(pop)


int main()
{
    setlocale(LC_ALL,"");

    ifstream inFile; //para acessar o arquivo para leitura
    ofstream outFile; //para aceesaor o arquivo de relatorio
    ofstream arqsaida;

    inFile.open("teste.bmp", ios::in|ios::binary);
    if (!inFile) // testando se o arquivo existe
    {
        cerr << "Arquivo saida nao pode ser aberto" << endl;
        return -1;
    }

    cabecalho_arq cab_arq; // Cabe�alho de arquivo
    cabecalho_bitMapa cab_bit; // Cabe�alho de mapa de bits

    // preenchendo os campos do cabe�alho de arquivo
    inFile.read((char *)&cab_arq, sizeof(cabecalho_arq));
    cout << "Assinatuura: "<< cab_arq.assinatura[0] << cab_arq.assinatura[1] << endl;
    cout << "Tamanho do arquivo: " << cab_arq.tam_arquivo << " bytes" << endl;
    cout << "Offset dos dados: " << cab_arq.dataOffset << " bytes" << endl;

    // preenchendo os campos do cabe�alho de mpa de bit
    inFile.read((char *)&cab_bit, sizeof(cabecalho_bitMapa));
    cout << "Tamanho da Imagem: " << cab_bit.tam_img << endl;
    cout << "Planos: : "<< cab_bit.planes << endl;
    cout << "Largura: " << cab_bit.largura_img << endl;
    cout << "Altura: " << cab_bit.altura_img << endl;

    // calculando o resto de bytes em cada linha
    int resto = 0;
    if(cab_bit.largura_img%4 != 0){
        resto += (4 - (cab_bit.largura_img%4));
    }

    // calculando numero de bytes em uma linha
    int bytes_Linha = (cab_bit.largura_img*3) + resto;

    // calculando o numero de bytes total usados
    int numBytes = (cab_bit.altura_img * bytes_Linha);

    char *rgb = new char[numBytes]; // todos os bytes de todos os pixels
    cout << "total de bytes: " << numBytes <<endl;

    //gravando todos os bytes
    inFile.read(rgb, numBytes);
    inFile.close();

    //escrevendo o arquivo de saida
    outFile.open("textoDeco.bmp", ios::out);
    outFile.write((char *)&cab_arq, sizeof(cabecalho_arq));
    outFile.write((char *)&cab_bit, sizeof(cabecalho_bitMapa));

    arqsaida.open("texo_gs.txt", ios::out);
    for (int y = 0; y < cab_bit.altura_img; y++) {
        for (int x = 0; x < cab_bit.largura_img; x++) {
            // calculando a posição do ponteiro rgb
            int offset = y * bytes_Linha + x * 3;

            // calculando para grayscale
            int media = (rgb[offset] + rgb[offset + 1] + rgb[offset + 2]) / 3;

            // Set R, G, and B values to the grayscale value
            rgb[offset] = media;         // Red
            rgb[offset + 1] = media;     // Green
            rgb[offset + 2] = media;     // Blue

            arqsaida << y << "|"  << x << "|" <<offset << "|" << rgb[offset] << "|" << rgb[offset + 1] << "|" << rgb[offset + 2] << endl;

        }
    }


    outFile.write(rgb, numBytes);
    outFile.close();


    delete[] rgb;
    return 0;
}
