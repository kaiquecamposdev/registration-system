#include <stdio.h>
#include <stdlib.h>
#include "../Headers/arquivo.h"

FILE* abrirArquivo(char* nomeArquivo, char* modo) {
    FILE* arquivo = fopen(nomeArquivo, modo);
    if(arquivo == NULL) {
        perror(ERRO_ABRIR_ARQUIVO);
        exit(1);
    }
    return arquivo;
}

void fecharArquivo(FILE* arquivo) {
    if(!fclose(arquivo)){
        puts("\nFECHAR: Sucesso no fechamento\n");
    } else {
        puts("\nFECHAR: Erro no fechamento\n");
    }
}

void gravarDados(void* dados, size_t tamanho, FILE* arquivo) {
    fwrite(dados, tamanho, 1, arquivo);
    if(ferror(arquivo)){
        puts("\nErro na gravação\n");
    } else {
        puts("\nGravação OK\n");
    }
}

void lerDados(void* dados, size_t tamanho, FILE* arquivo) {
    while(!feof(arquivo)) {
        int controlador = fread(dados, tamanho, 1, arquivo);
        if(ferror(arquivo)) {
            puts("\nErro na leitura do arquivo");
        } else {
            if(controlador != 0) {
                return;
            }
        }
    }
}
