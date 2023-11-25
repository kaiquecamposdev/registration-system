#include <stdio.h>
#include <stdlib.h>

#ifndef ARQUIVO_H_INCLUDED

#define ARQUIVO_H_INCLUDED
#define ERRO_ABRIR_ARQUIVO "\nErro na abertura do arquivo!\n"
#define ERRO_LEITURA_ARQUIVO "\nErro na leitura do arquivo!\n"
#define ERRO_FECHAR_ARQUIVO "\nErro no fechamento do arquivo!\n"

FILE* abrirArquivo(char* nomeArquivo, char* modo);
void fecharArquivo(FILE* arquivo);

void gravarDados(void* dados, size_t tamanho, FILE* arquivo);
void lerDados(void* dados, size_t tamanho, FILE* arquivo);

#endif // ARQUIVO_H_INCLUDED
