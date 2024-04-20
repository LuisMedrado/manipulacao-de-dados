#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definição de código de erro
#define ERRO 1

// Estrutura "dados" para armazenar as variáveis relacionadas aos alunos
struct dados{
    char nome[255];
    char telefone[15];
    char curso[50];
    double nota1;
    double nota2;
    double notafin;
};

// Estrutura "defmatriz" para armazenar as variáveis utilizadas na manipulação
struct defmatriz{
    char linha[5115];
    char *virgula;
    int i;
    int j;
};

// Definição das funções
void cl();

void verifnull(FILE * arqEntrada, FILE * arqSaida);

void printar(struct dados alunos[], FILE * arqSaida, int num_alunos);

// Função main
int main() {
    // Inserção de caracteres, acentos e símbolos presentes no português brasileiro
    setlocale(LC_ALL, "Portuguese");

    // Definição dos arquivos a serem usados
    FILE * arqEntrada;
    FILE * arqSaida;

    // Chamada das estruturas
    struct dados alunos[300];
    struct defmatriz mat;

    int num_alunos = 0;

    //  Abertura do arquivo de entrada (leitura) e de saída (escrita)
    arqEntrada = fopen("DadosEntrada.csv", "r");
    arqSaida = fopen("SituacaoFinal.csv", "w");

    // Function call para limpar a tela

    cl();

    // Function call pra verificar a nulidade dos arquivos
    verifnull(arqEntrada, arqSaida);

    // Função que percorre as strings do arquivo e salva o conteúdo nas variáveis 
    while (fgets(mat.linha, sizeof(mat.linha), arqEntrada) != NULL) {
        mat.virgula = strtok(mat.linha, ",");
        if (mat.virgula != NULL) {
            strcpy(alunos[num_alunos].nome, mat.virgula);
            mat.virgula = strtok(NULL, ",");
            strcpy(alunos[num_alunos].telefone, mat.virgula);
            mat.virgula = strtok(NULL, ",");
            strcpy(alunos[num_alunos].curso, mat.virgula);
            mat.virgula = strtok(NULL, ",");
            alunos[num_alunos].nota1 = atof(mat.virgula);
            mat.virgula = strtok(NULL, ",");
            alunos[num_alunos].nota2 = atof(mat.virgula);

            num_alunos++;
        }
    }

    // Function call para ler, calcular a nota final e printar o resultado no arquivo de saída
    printar(alunos, arqSaida, num_alunos);

    // Fechamento dos arquivos
    fclose(arqEntrada);
    fclose(arqSaida);

    printf("Arquivo gerado com sucesso!");

}

// Escrita das funções definidas previamente
void cl() {
    system("@cls || @clear");
}

void verifnull(FILE * arqEntrada, FILE * arqSaida) {
    if (arqEntrada == NULL || arqSaida == NULL) {
        printf("O arquivo apresentou erros de leitura, escrita e/ou acesso. Código de erro: %d\n", ERRO);
        exit(1);
    }
}

void printar(struct dados alunos[], FILE * arqSaida, int num_alunos) {
       for(int i = 1; i < num_alunos; i++) {
        alunos[i].notafin = (alunos[i].nota1 + alunos[i].nota2) / 2;
        if (alunos[i].notafin >= 7) {
            fprintf(arqSaida, "%s, %.2f, APROVADO\n", alunos[i].nome, alunos[i].notafin);
        }
        else if (alunos[i].notafin < 7) {
            fprintf(arqSaida, "%s, %.2f, REPROVADO\n" , alunos[i].nome, alunos[i].notafin);
        }
    } 
}
