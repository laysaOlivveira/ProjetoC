#include <stdio.h>
#include <stdlib.h>

struct VarGlobal { //Variável global auxiliar
    int global;
    char Cd;
};
struct VarGlobal Global;

//Estrutura dos produtos que irá receber o nome, o código e o preço na função de cadastro de produtos e irão ser armazenados no arquivo CadProdutos.
typedef struct{
  char *nome;
  int codigo;
  float preco;
}Cadproduto;

//Estrutura dos produtos que irá receber o nome, o telefone e o cpf na função de cadastro de clientes e irão ser armazenados no arquivo dadosclientes.
typedef struct{
  char *nome;
  char *telefone;
  char *cpf;
}cadCliente;

//Estrutura do carrinho que irá receber o código do produto escolhido na função loja. Essa estrutura será utilizada na lista encadeada.
typedef struct{
  int codigoProduto;
}Carrinho;

//A estrutura do elemento é um ponteiro para uma estrutura com uma variável utilizada para armazenar a informação inserida na lista e um ponteiro para indica o próximo elemento.
typedef struct elemento 
{
	Carrinho dados;
	struct elemento *prox;
} Elem;
typedef struct elemento *Lista;

void libera_lista(Lista *li);
int insere_lista_final(Lista *li, Carrinho carrinho);
int lista_vazia (Lista *li);
void mostra_lista(Lista *li);
int tamanho(Lista* li);
void loja(Lista *lista, Carrinho carrinho);

Cadproduto produto;
FILE *DB; //Ponteiro para o arquivo de armazenamento do cad de produtos
float total;
Carrinho carrinho;

//A função para criar lista
Lista *cria_lista()
{
	Lista *li = (Lista *) malloc(sizeof(Lista));

	if (li != NULL) 
  {
		*li = NULL;
	}
	return li;
}

//Função para verificar se a lista está vazia, ela irá considerar que a lista está vazia quando retornar NULL
int lista_vazia(Lista *li)
{
	if (li == NULL) 
		return 1;
  if (*li == NULL)
    return 1;

	return 0;
}

//A função para inserir o elemento no fim da lista não precisa que os elementos sejam mudados de lugar dentro da lista e para isso, percorre toda ela até achar o último elemento e aí, inserir o elemento após o último armazenado e é chamada na função loja para armazenar os produtos escolhidos em uma lista encadeada.
int insere_lista_final(Lista *li, Carrinho carrinho)
{
	if (li == NULL) 
  {
		return 0;
	}
	
  Elem *no;
  no = (Elem *) malloc(sizeof(Elem));
  
	if (no == NULL) 
  {
		return 0;
	}
  
	no -> dados = carrinho;
	no -> prox = NULL;
  
	if ((*li) == NULL) 
  { 
		*li = no;
	} 
  else 
  {
		Elem *aux = *li;

		while (aux->prox != NULL) //varrendo a lista até encontrar o ultimo
    {
			aux = aux -> prox;
		}
		aux -> prox = no; //insere após o aux
	}
	return 1;
}

//A função de mostar lista é chamada ao fim da função loja, a fim de mostrar os códigos dos produtos escolhidos no carrinho.
void mostra_lista(Lista *li) 
{
	if (lista_vazia(li)) 
  {
		printf("\n Carrinho vazio!");
	}
  else 
  {
		printf("\nCódigos dos produtos escolhidos: ");
		Elem *no = *li;

		while (no != NULL) 
    {
			printf("%d + ", no -> dados.codigoProduto);
      no = no -> prox;
		}
    printf("\nO valor total da compra foi: %.2f", total);
    printf("\nAgradecemos a preferência. Até a próxima!");
    sleep(1);
    
    main();
    
	}
}

//A função verifica quantos elementos estão na lista, ou seja, o seu tamanho.
int tamanho(Lista *li){
  if(li==NULL)
    return 0;
  int cont=0;
  Elem* no=*li;
  while(no != NULL){
    cont++;
    no=no->prox;
  }
  return cont;
}

FILE *arquivo; //ponteiro do banco de armazenamento
cadCliente cliente;
//A função cadastroCliente foi criada para receber, armazenar no arquivo e em uma lista encadeada, dentro dela e após a confirmação do cadastro, o cliente é direcionado para a função de compra.
void cadastroCliente (Lista *lista, Carrinho carrinho)
{
  int fim;
  system("clear");
  arquivo = fopen("dadosclientes.txt", "a"); //Abertura do arquivo para adicionar os dados

  if(arquivo == NULL) { //Verifica o arquivo
    printf("\nErro no Banco de Dados...\n");
    return 1;
  }
  else{
     //funções básicas pedidas ao usuario
      printf(" CADASTRO\n"); 
      printf("\nNome: ");
      char nome[100];
      scanf("%s", nome);
      cliente.nome = nome;
      printf("\nTelefone: ");
      char telefone[15];
      scanf("%s", telefone);
      cliente.telefone = telefone;
      char cpf[15];
      printf("\nCPF: ");
      scanf("%s", cpf);
      cliente.cpf = cpf;
  
      system("clear");
      printf("\nFinalizar cadastro? Sim-(1)/Não-(2) : ");
      scanf("%d", &Global.global); //Conclusão do cadastro
  
      if(Global.global == 1) {
        fprintf(arquivo, "Nome: %s \nTelefone: %s \nCPF: %s", cliente.nome, cliente.telefone, cliente.cpf);
        fprintf(arquivo, "\n----------------------\n"); //Salva os dados
        fclose(arquivo); //Fecha o arquivo
        printf("\t\tBOAS COMPRAS!\n\n");
        Lista *lista = cria_lista();//Cria a Lista encadeada
        loja(lista, carrinho);//Chama a função loja para realizar a compra
        }
       // se quiser cancelar o cadastro fecha o arquivo e volta para o menu principal
        else if(Global.global == 2) {
        system("clear");
        printf("Cadastro Cancelado.\nVoltando ao Menu Principal...\n");
        fclose(arquivo); //Fecha o arquivo
        getchar(); //Corrige bug quando fim != 1 && fim!=2   
        sleep(1);
        main();

        } else {
            printf("Valor inválido. Tente novamente...\n");
            fclose(arquivo); //Fecha o arquivo
            sleep(1);//Dá uma pausa e volta para o menu de cadastro de clientes
            cadastroCliente(lista, carrinho);

        }
    }
  } //fim da função cadastro

FILE* DB;
void cadastroProduto();
void cadastroProduto(){
  system("clear");
    DB = fopen("CadProdutos.txt", "a"); //Abertura do arquivo para adicionar os dados

    if(DB == NULL) { //Verificação do Banco de Dados
        printf("\nErro no Banco de Dados...\n");
        return 1;

    } else {
      //funções básicas que serão fornecidas pelo usuario
       printf(" CADASTRO\n"); 
       printf("\nNome: ");
       char nome[100];
       scanf("%s", nome);
       produto.nome = nome;
       printf("\nCódigo: ");
       int codigo;
       fflush(stdin);
       scanf("%d",&codigo);
       produto.codigo = codigo;
       float preco=18.00;
       produto.preco = preco;
        
        system("clear");
        printf("\nFinalizar cadastro? Sim-(1)/Não-(2) : ");
        scanf("%d", &Global.global); //Conclusão do cadastro

        if(Global.global == 1) {
            fprintf(DB, "Nome: %s \nCódigo: %d \nPreço: %.2f", produto.nome, produto.codigo, produto.preco);
            fprintf(DB, "\n----------------------\n"); //Salva os dados
      
            fclose(DB); //Fecha o arquivo
            
            system("clear");
            printf("Cadastro Concluído\n");
            sleep(1);
            
            main();

        } else if(Global.global == 2) {
            system("clear");
            printf("Cadastro Cancelado.\nVoltando ao Menu Principal...\n");
            fclose(DB); //Fecha o arquivo
            getchar(); //Corrige bug quando fim != 1 && fim!=2   
            sleep(1);
            main();

        } else {
            printf("Valor inválido. Tente novamente...\n");
            fclose(DB); //Fecha o arquivo
            sleep(1);
            cadastroProduto();

        }

    }
  
}

//função usada para listar os produtos como string na funçao loja e na lista de produtos cadastrados na aba e funcionarios
void ListagemProd() {
    system("clear");
    DB = fopen("CadProdutos.txt", "r"); //Abertura do DB para leitura de dados

    if(DB == NULL) { //Verificação do arquivo
        printf("\nErro no Banco de Dados...\n");
        return 1;

    } else {
        printf(" LISTAGEM DE PRODUTOS\n\n");

        char listagem[250]; //String geral para os dados

        while(fgets(listagem, 250, DB) != NULL) {
            printf("%s", listagem);

        } //Considera todos os dados como uma String e exibe na tela

        fclose(DB);
    }
}
//Função que recebe os códigos dos produtos escolhidos, armazenando na lista encadeada, e chamando a função de mostrar o carrinho com o total e finalizando a compra.
void loja(Lista *lista, Carrinho carrinho){
  ListagemProd();
  int comprar, fim;
  printf("Coloque no carrinho digitando o código do produto: \n");
  scanf("%d",&comprar);
  carrinho.codigoProduto = comprar;
  insere_lista_final(lista,carrinho);//chamada da função para inserir na lista
  
  printf("Deseja finalizar a compra? (1)-Sim/(2)-Não\n");
  scanf("%d", &fim);
  if (fim==1)
  {
    total = tamanho(lista) * 18;
    mostra_lista(lista);//chamada da função para mostrar os escolhidos e dar o valor final da compra
  }
  else if (fim == 2) //caso seja escolhido, volta para o inicio da função loja
    loja(lista, carrinho);
}

void removercliente();
void removercliente(){
  printf("Para remover o cadastro feito é só acessar o arquivo dadosclientes.txt e realizar o processo manualmente, salvando o arquivo em seguida.");
  main();
}

void removerproduto();
void removerproduto(){
  printf("Para remover o produto é só acessar o arquivo CadProdutos.txt e realizar o processo manualmente, salvando o arquivo em seguida.");
  main();
}

void menu(){//Função para chamar o menu inicial de interação.
  printf("\n\t\tSEJAM BEM VINDOS AO LOJÃO L&T \n\t\t\t LEVE TUDO POR 18$!\n Você é: \n Cliente - [1]\n Funcionário - [2]\n");
}
int main(){
  system("clear");
  int opcao,resp;
  menu();
  
  scanf("%d",&opcao);
  switch (opcao){
    case 1:
      system("clear");
      printf(" BEM VINDO A ÁREA DO CLIENTE\n\n");
      do{
        printf("Cadastrar - (1)\nRemover cadastro - (2)");
        scanf("%d",&resp);
        
      }while (resp!=1 && resp!=2);

      if (resp==1){//Chama a função para criar a lista e a função para cadastro que pede as informaçoes do cliente, armazena na lista encadeada e ni arquivo de dados dos clientes
        Lista *lista = cria_lista();
        cadastroCliente(lista, carrinho);
        }
      else if (resp==2){
        removercliente();
        sleep(5);
      }
      break;
    case 2:
      system("clear");
      printf("BEM VINDO A ÁREA DO FUNCIONÁRIO!\n");
      do{ 
        printf("Cadastrar produtos - (1)\n");
        printf("Lista de produtos cadastrados - (2)\n");
         printf("Remover produto cadastrado - (3)\n");
        scanf("%d",&resp);
      }while(resp!=1 && resp!=2 && resp!=3);
      if (resp==1)
        cadastroProduto();
      else if (resp==2)
        ListagemProd();
      else if (resp==3)
        removerproduto();
        sleep(5);
      break;
    
    default:
      printf("Valor inválido...");
      system("clear");
      main();
      break;
  }  
  
return 0;
}