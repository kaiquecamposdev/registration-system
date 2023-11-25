#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <errno.h>
#include "../Headers/global.h"
#include "../Headers/cadastro.h"

Funcionario dadosUsuario;
EmpresaCliente dadosEmpresa;

int registrarEmpresa;
int escolhaDeAcesso;
int escolhaDeSistema;

int main() {
  inicializarGerador();
  setlocale(LC_ALL, "Portuguese");

  puts("Ecovate Solutions\n");
  puts("Seja muito bem-vindo ao nosso sistema de cadastro!\n");
  puts("1 - Tela de login.\n");
  puts("2 - Tela de cadastro.\n");
  scanf("%d", &escolhaDeAcesso);
  limparTela();

  switch(escolhaDeAcesso) {
    case 1:
      loginUsuario();
      break;
    case 2:
      cadastrarUsuario();
      break;
    default:
      perror(ERRO_SISTEMA);
      return 1;
  }
  printarUsuario(dadosUsuario);

  puts("Deseja cadastrar uma empresa?\n");
  puts("1 - Sim.\n");
  puts("2 - Não.\n");
  scanf("%d", &registrarEmpresa);
  limparTela();

  switch(registrarEmpresa) {
    case 1:
      cadastrarEmpresa(dadosUsuario);
      break;
    case 2:
      puts("Sistema encerrado!\n");
      break;
    default:
      perror(ERRO_SISTEMA);
      return 1;
  }

  system("pause");
  return 0;
}

void loginUsuario() {
  lerEntrada("Digite o nome de usuário: ", dadosUsuario.nome, 50);
  lerEntrada("Digite seu email: ", dadosUsuario.email, 100);
  lerEntrada("Digite sua senha: ", dadosUsuario.senha, 20);

  if(dadosUsuario.nome == NULL && dadosUsuario.email == NULL && dadosUsuario.senha == NULL) {
    perror(ERRO_CREDENCIAIS);
    exit(1);
  }

  verificarUsuario(dadosUsuario);
}

void inicializarGerador() {
  srand((unsigned int)time(NULL));
}

void gerarID(char *destino, size_t tamanho) {
  int id = rand();
  snprintf(destino, tamanho, "%d", id);
}
