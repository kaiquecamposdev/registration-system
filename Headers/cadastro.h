#ifndef CADASTRO_H_INCLUDED
#define CADASTRO_H_INCLUDED

#define ERRO_CREDENCIAIS "\nErro de credenciais!\n"
#define ERRO_CRIAR "\nErro ao cadastrar!\n"
#define ERRO_USUARIO "\nErro do usuário!\n"
#define ERRO_SISTEMA "\nErro no sistema!\n"

typedef struct Funcionario {
  char id[100];
  char nome[50];
  char email[100];
  char senha[20];
  struct Funcionario *proximoFuncionario;
} Funcionario;

typedef struct EnderecoEmpresa {
  char id[100];
  char empresaId[100];
  char rua[50];
  char bairro[50];
  int numero[20];
  char cidade[20];
  char estado[20];
  int CEP[8];
} EnderecoEmpresa;

typedef struct ContatoEmpresa {
  char id[100];
  char empresaId[100];
  char telefone[18];
  char email[50];
} ContatoEmpresa;

typedef struct DadosCliente {
  int id[100];
  char empresaId[100];
  char nomeCompleto[50];
  int CPF[14];
} DadosCliente;

typedef struct EmpresaCliente {
  char id[100];
  char userId[100];
  int CNPJ[18];
  char nomeFantasia[20];
  char razaoSocial[50];
  char dataAbertura[12];
  struct DadosCliente cliente;
  struct ContatoEmpresa contato;
  struct EnderecoEmpresa endereco;
  struct EmpresaCliente *proximaEmpresa;
} EmpresaCliente;

void cadastrarUsuario();
int gravarUsuario(Funcionario dadosUsuario);
int printarUsuario(Funcionario dadosUsuario);
int verificarUsuario(Funcionario dadosUsuarioEntrada);

void cadastrarEmpresa(Funcionario dadosUsuarioEntrada);
int gravarEmpresa(EmpresaCliente dadosEmpresa);
int printarEmpresa(EmpresaCliente dadosEmpresa);

void lerEntrada(char *prompt, char *buffer, int size);
void lerInteiro(char *prompt, int *value);

#endif // CADASTRO_H_INCLUDED
