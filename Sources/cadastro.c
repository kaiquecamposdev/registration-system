#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/global.h"
#include "../Headers/cadastro.h"
#include "../Headers/arquivo.h"

FILE *arquivo;
int controlador;

void cadastrarUsuario() {
  Funcionario dadosUsuario;

  lerEntrada("Digite o nome de usuário: \n", dadosUsuario.nome, 50);
  lerEntrada("Digite seu email: \n", dadosUsuario.email, 100);
  lerEntrada("Digite sua senha: \n", dadosUsuario.senha, 20);

  gerarID(dadosUsuario.id);

  if(dadosUsuario.nome == NULL && dadosUsuario.email == NULL && dadosUsuario.senha == NULL) {
    perror(ERRO_CREDENCIAIS);
    exit(1);
  }

  verificarUsuario(dadosUsuario);
  gravarUsuario(dadosUsuario);

  limparTela();
}

int gravarUsuario(Funcionario dadosUsuario) {
  arquivo = abrirArquivo("funcionarios.txt", "ab+");
  gravarDados(&dadosUsuario, sizeof(struct Funcionario), arquivo);
  fecharArquivo(arquivo);
  return 0;
}

int printarUsuario(Funcionario dadosUsuario) {
  arquivo = abrirArquivo("funcionarios.txt", "r");
  lerDados(&dadosUsuario, sizeof(struct Funcionario), arquivo);

  while(!feof(arquivo)) {
    controlador = fread(&dadosUsuario, sizeof(struct Funcionario), 1, arquivo);

    if(ferror(arquivo)) {
      perror("\nErro na leitura do arquivo\n");
    }else {
      if(controlador != 0) {
        puts("\nDados do Usuário.\n");

        printf("\nID: %s\n", dadosUsuario.id);
        printf("\nNome do usuário: %s\n", dadosUsuario.nome);
        printf("\nEmail do usuário: %s\n", dadosUsuario.email);
        printf("\nSenha do usuário: %s\n", dadosUsuario.senha);
      }
    }
  }
  fecharArquivo(arquivo);
  return 0;
}

int verificarUsuario(Funcionario dadosUsuarioEntrada) {
  Funcionario dadosUsuario;
  arquivo = abrirArquivo("funcionarios.txt", "r");

  puts("Verificando usuário...");
  limparTela();

  if(arquivo == NULL) {
    perror(ERRO_ABRIR_ARQUIVO);
    return 1;
  }

  while(!feof(arquivo)) {
    controlador = fread(&dadosUsuario, sizeof(Funcionario), 1, arquivo);

    if(controlador < 1) {
      perror(ERRO_LEITURA_ARQUIVO);
    } else {
      if(strcmp(dadosUsuarioEntrada.nome, dadosUsuario.nome) == 0) {
        puts("Usuário verificado com sucesso!");
        fclose(arquivo);
        return 0;
      } else {
        puts("Usuário não existe!");
        system("pause");
        return 1;
      }
    }
  }
  fecharArquivo(arquivo);
  return 0;
}

void cadastrarEmpresa(Funcionario dadosUsuarioEntrada) {
  EmpresaCliente dadosEmpresa;

  strcpy(dadosEmpresa.userId, dadosUsuarioEntrada.id);

  puts("\nDados do Cliente\n");
  lerEntrada("\nDigite nome completo do cliente: \n", dadosEmpresa.cliente.nomeCompleto, 50);
  lerInteiro("\nDigite CPF do cliente: \n", &dadosEmpresa.cliente.CPF);
  limparTela();

  puts("\nIdentificação da Empresa\n");
  lerInteiro("\nDigite CNPJ da empresa: \n", &dadosEmpresa.CNPJ);
  lerEntrada("\nDigite nome fantasia: \n", dadosEmpresa.nomeFantasia, 20);
  lerEntrada("\nDigite razão social: \n", dadosEmpresa.razaoSocial, 50);
  lerEntrada("\nDigite a data de abertura(00/00/0000): \n", dadosEmpresa.dataAbertura, 12);
  limparTela();

  puts("\nContato da Empresa\n");
  lerInteiro("\nDigite número de telefone: \n", &dadosEmpresa.contato.telefone);
  lerEntrada("\nDigite email: \n", dadosEmpresa.contato.email, 50);
  limparTela();

  puts("\nEndereço da Empresa\n");
  lerInteiro("\nDigite o número do CEP: \n", &dadosEmpresa.endereco.CEP);
  lerEntrada("\nDigite nome da rua: \n", dadosEmpresa.endereco.rua, 50);
  lerEntrada("\nDigite nome do bairro: \n", dadosEmpresa.endereco.bairro, 50);
  lerEntrada("\nDigite nome da cidade: \n", dadosEmpresa.endereco.cidade, 20);
  lerEntrada("\nDigite nome do estado: \n", dadosEmpresa.endereco.estado, 20);
  lerInteiro("\nDigite número do endereço: \n", &dadosEmpresa.endereco.numero);
  limparTela();

  gerarID(dadosEmpresa.id);
  gerarID(dadosEmpresa.contato.id);
  gerarID(dadosEmpresa.endereco.id);

  strcpy(dadosEmpresa.contato.empresaId, dadosEmpresa.id);
  strcpy(dadosEmpresa.endereco.empresaId, dadosEmpresa.id);

  gravarEmpresa(dadosEmpresa);
  limparTela();

  printarEmpresa(dadosEmpresa);
}

int gravarEmpresa(EmpresaCliente dadosEmpresa) {
  arquivo = fopen("empresas.txt", "ab+");

  if(arquivo == NULL) {
    perror(ERRO_ABRIR_ARQUIVO);
    return 1;
  }

  fwrite(&dadosEmpresa, sizeof(struct EmpresaCliente), 1, arquivo);
  if(ferror(arquivo)){
    puts("\nErro na gravação\n");
  } else {
    puts("\nGravação OK\n");
  }

  if(!fclose(arquivo)){
    puts("\nFECHAR: Sucesso no fechamento\n");
  } else {
    puts("\nFECHAR: Erro no fechamento\n");
  }

  return 0;
}

int printarEmpresa(EmpresaCliente dadosEmpresa) {
  arquivo = fopen("empresas.txt", "ab+");

  if(arquivo == NULL) {
    perror(ERRO_ABRIR_ARQUIVO);
    return 1;
  }

  while(!feof(arquivo)) {
    controlador = fread(&dadosEmpresa, sizeof(struct EmpresaCliente), 1, arquivo);

    if(ferror(arquivo)) {
      puts("\nErro na leitura do arquivo");
    } else {
      if(controlador != 0) {
        puts("\nDados do Cliente.\n");
        printf("ID: %s\n", dadosEmpresa.id);
        printf("Nome completo do cliente: %s", dadosEmpresa.cliente.nomeCompleto);
        printf("CPF do cliente: %d\n\n", &dadosEmpresa.cliente.CPF);

        puts("\nIdentificação da Empresa.\n");
        printf("CNPJ da empresa: %d\n", &dadosEmpresa.CNPJ);
        printf("Nome fantasia: %s\n", dadosEmpresa.nomeFantasia);
        printf("Razão social: %s\n", dadosEmpresa.razaoSocial);
        printf("Data de abertura: %s\n", dadosEmpresa.dataAbertura);

        puts("\nContato da Empresa.\n");
        printf("ID: %s\n", dadosEmpresa.contato.id);
        printf("Número de telefone da empresa: %d\n", &dadosEmpresa.contato.telefone);
        printf("Email da empresa: %s\n", dadosEmpresa.contato.email);

        puts("\nEndereço da Empresa.\n");
        printf("ID: %s\n", dadosEmpresa.endereco.id);
        printf("Rua: %s\n", dadosEmpresa.endereco.rua);
        printf("Bairro: %s\n", dadosEmpresa.endereco.bairro);
        printf("Número: %d\n", &dadosEmpresa.endereco.numero);
        printf("Cidade: %s\n", dadosEmpresa.endereco.cidade);
        printf("Estado: %s\n", dadosEmpresa.endereco.estado);
        printf("CEP: %d\n", &dadosEmpresa.endereco.CEP);
      }
    }
  }
  if(!fclose(arquivo)){
    puts("\nFECHAR: Sucesso no fechamento\n");
  } else {
    puts("\nFECHAR: Erro no fechamento\n");
  }

  return 0;
}

void lerEntrada(char *texto, char *buffer, int tamanho) {
    printf("%s", texto);
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

void lerInteiro(char *texto, int *valor) {
    printf("%s", texto);
    scanf("%d", valor);
    while(getchar() != '\n');
}
