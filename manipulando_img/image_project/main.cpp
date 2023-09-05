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
    ofstream arqmono; // arquivo de img em monocor
    ofstream arqsaida;
    ofstream arqtestetxt; // arquivo de teste

    inFile.open("teste.bmp", ios::in|ios::binary);
    if (!inFile) // testando se o arquivo existe
    {
        cerr << "Arquivo saida nao pode ser aberto" << endl;
        return -1;
    }

    cabecalho_arq cab_arq; // cabecalho de arquivo
    cabecalho_bitMapa cab_bit; // cabecalho de mapa de bits

    /**
    -> Informacoes sobre o cabecalho do arquivo e sobre a imagem
    */
    // preenchendo os campos do cabecalho de arquivo
    inFile.read((char *)&cab_arq, sizeof(cabecalho_arq));
    cout << "\tCABECALHO DO ARQUIVO" << endl;
    cout << "- Assinatuura: "<< cab_arq.assinatura[0] << cab_arq.assinatura[1] << endl;
    cout << "- Tamanho do arquivo: " << cab_arq.tam_arquivo << " bytes" << endl;
    cout << "- Offset dos dados: " << cab_arq.dataOffset << " bytes" << endl;

    // preenchendo os campos do cabecalho de mapa de bit
    inFile.read((char *)&cab_bit, sizeof(cabecalho_bitMapa));
    cout << "\n\tCABECALHO DO MAPA DE BITS" << endl;
    cout << "- Tamanho da Imagem: " << cab_bit.tam_img << endl;
    cout << "- Planos: " << cab_bit.planes << endl;
    cout << "- Largura: " << cab_bit.largura_img << endl;
    cout << "- Altura: " << cab_bit.altura_img << endl;


    /**
    -> Calculo de numero de bytes e gravacao dos mesmos
    */
    // calculando o resto de bytes em cada linha
    int resto = 0;
    if(cab_bit.largura_img%4 != 0){
        resto += (4 - (cab_bit.largura_img%4));
    }

    int bytes_Linha = (cab_bit.largura_img*3) + resto; // numero de bytes em uma linha
    int numBytes = (cab_bit.altura_img * bytes_Linha); // numero de bytes total usados

    char *rgb = new char[numBytes]; // todos os bytes de todos os pixels
    char *mono = new char[numBytes]; // todos os bytes de todos os pixels
    cout << "- Total de bytes: " << numBytes << endl;

    // gravando todos os bytes
    inFile.read(rgb, numBytes);
    inFile.read(mono, numBytes);
    inFile.close();


    /**
    -> Insercao de dados para o recorte da imagem
    */
    int x, y;
    int limiar_val;

    // entrada de informações do usuario
    cout << "\n\tDIGITE AS COORDENADAS DE SAIDA" << endl ;
    bool loop = true;
    while (loop){
        cout << "-> Posicao eixo X (0 a 488): ";
        cin >> x;
        cout << "-> Posicao eixo y (0 a 606): ";
        cin >> y;
        cout << endl << "-> Valor de limiar RGB (0 a 255): ";
        cin >> limiar_val;
        //teste - dentro dos parametros
        if(x + 48 <= cab_bit.largura_img && y - 84 > 0 && y <= cab_bit.altura_img)
            loop = false;
        if(limiar_val <= 255 && limiar_val >= 0)
            loop = false;
    }

    /**
    -> Criacao dos arquivos em mono e grayscale
    */
    // escrevendo o arquivo de saida rgb para monocor
    arqmono.open("mono.bmp", ios::out);
    arqmono.write((char *)&cab_arq, sizeof(cabecalho_arq));
    arqmono.write((char *)&cab_bit, sizeof(cabecalho_bitMapa));

    // escrevendo o arquivo de saida rgb para grayscale
    outFile.open("teste_gs.bmp", ios::out);
    outFile.write((char *)&cab_arq, sizeof(cabecalho_arq));
    outFile.write((char *)&cab_bit, sizeof(cabecalho_bitMapa));

    for (int y = 0; y < cab_bit.altura_img; y++) {
        for (int x = 0; x < cab_bit.largura_img; x++) {
            // calculando a posição do ponteiro rgb
            unsigned int offset = y * bytes_Linha + x * 3;

            // calculando para grayscale
            int media = 0.3 * rgb[offset] + 0.6* rgb[offset+1]  + 0.11* rgb[offset+2];

            // passando os valores de R, G e B para grayscale
            rgb[offset] = media;         // Red
            rgb[offset + 1] = media;     // Green
            rgb[offset + 2] = media;     // Blue

            if(media == -1) media = 255;
            if(fabs(media) < limiar_val){
                mono[offset] = 0;
                mono[offset + 1] = 0;
                mono[offset + 2] = 0;
            }else{
                mono[offset] = 255;
                mono[offset + 1] = 255;
                mono[offset + 2] = 255;
            }

        }
    }

    arqtestetxt.open("texto.h", ios::out);
    arqsaida.open("teste.h", ios::out);
    arqsaida << "unsigned int[504] = {" << endl;
    
    int aux = 0;
    int conta = 0;

    // criando o recorte da imagem
    for (int j = y; j > y - 84; j--){       // redefinindo as coordenadas de inicio do ponteiro
        for (int k = x; k < x + 48 ; k++){  // inferior esquerdo para superior esquerdo
            int byte = j * bytes_Linha + k *3;
            int pixel = mono[byte] + mono[byte + 1] + mono[byte + 2];


            if(pixel == 0){ //ponto ligado
                conta += pow(2, aux);
                arqtestetxt << 1;
            }else {
                conta += 0; // ponto desligad
                arqtestetxt << 0;
            }

            aux++;
            if(aux == 8) {
               arqsaida << "0x" << conta << hex << ", ";
               aux = 0;
               conta = 0;

            }
        }
        arqtestetxt << endl;
        arqsaida << endl;
    }
    arqsaida << "};";
    

    arqmono.write(mono, numBytes);
    arqmono.close();

    outFile.write(rgb, numBytes);
    outFile.close();
    arqtestetxt.close();
    
    cout << "\nAs informacoes foram gravadas no projeto!" << endl;
    delete[] rgb;
    delete[] mono;
    return 0;
}
