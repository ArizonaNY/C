#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

int verificarEmail(char email[], char emailsCadastrados[][80], int numEmails);

struct Item {
    char nome[50];
    float preco;
};

int realizarLogin(char emailsCadastrados[][80], int *numEmails) {
    char usuario[20];
    char senha[20];
    
    while (1) {
        printf("Digite o nome de usuário: ");
        scanf("%s", usuario);
        
        printf("Digite a senha: ");
        scanf("%s", senha);
        
        if (strcmp(usuario, "admin") == 0 && strcmp(senha, "admin123") == 0) {
           
            char NovoEmail[80];
            printf("Digite seu email: ");
            scanf("%s", NovoEmail);
            
            if (verificarEmail(NovoEmail, emailsCadastrados, *numEmails)) {
                strcpy(emailsCadastrados[*numEmails], NovoEmail);
                (*numEmails)++;
                printf("Acesso Permitido!\n");
            } else {
                printf("E-mail inválido ou já cadastrado.\n");
            }
            
            return 1;
        } else {
            printf("Usuário ou senha incorretos. Tente novamente.\n");
        }
    }
}

int verificarEmail(char email[], char emailsCadastrados[][80], int numEmails) {
    if (strlen(email) < 80 && strchr(email, '@')) {
        for (int i = 0; i < numEmails; i++) {
            if (strcmp(email, emailsCadastrados[i]) == 0) {
                return 0; 
            }
        }
        return 1; 
    }
    return 0;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    struct Item itens[100];
    int numItens = 0;
    
    char emailsCadastrados[100][80];
    int numEmails = 0;
    
    int loginStatus = realizarLogin(emailsCadastrados, &numEmails);
    if (loginStatus != 1) {
        printf("Acesso negado.\n");
        return 0;
    }
    system("pause");
    system("cls");
    printf("===============================|\n");
    printf("Bem-vindo à Loja!              |\n");
    
    srand(time(NULL));
    
    int opcao;
    int numeroEscolhido, linhas, colunas;
    int numeroGanhador = rand() % 100 + 1;
    
    do {
        printf("===============================|\n");
        printf("Escolha uma opção:             |\n");
        printf("-------------------------------|\n");
        printf("1. Cadastrar Item              |\n");
        printf("2. Listar Itens                |\n");
        printf("3. Editar Item                 |\n");
        printf("4. Excluir Item                |\n");
        printf("5. Participar do Sorteio       |\n");
        printf("7. Sair                        |\n");
        printf("===============================|\n");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
            	system("cls");
                printf("Digite o nome do item: \n");
                scanf("%s", itens[numItens].nome);
                printf("Digite o preço do item: \n");
                scanf("%f", &itens[numItens].preco);
                numItens++;
                printf("Produto cadastrado!\n");
                system("pause");
                system("cls");
                break;
             
            case 2:
                 system("cls");
                 printf("Lista de Itens:\n");
                for (int i = 0; i < numItens; i++) {
                    printf("%d. %s - R$%.2f\n", i + 1, itens[i].nome, itens[i].preco);
                }
                system("pause");
                system("cls");
                break;
            
            case 3:
            	system("cls");
                printf("Digite o número do item que deseja editar o preço: ");
                int numeroItem;
                scanf("%d", &numeroItem);
                
                if (numeroItem > 0 && numeroItem <= numItens) {
                    printf("Digite o novo preço para o item %s: ", itens[numeroItem - 1].nome);
                    scanf("%f", &itens[numeroItem - 1].preco);
                    printf("Preço do item atualizado com sucesso!\n");
                } else {
                    printf("Número de item inválido.\n");
                }
                break;
               system("pause");
               system("cls");
               
               case 4:
                printf("Digite o número do item que deseja excluir: ");
                int numeroItemExcluir;
                scanf("%d", &numeroItemExcluir);
                
                if (numeroItemExcluir > 0 && numeroItemExcluir <= numItens) {
                    for (int i = numeroItemExcluir - 1; i < numItens - 1; i++) {
                        strcpy(itens[i].nome, itens[i + 1].nome);
                        itens[i].preco = itens[i + 1].preco;
                    }
                    numItens--;
                    printf("Item excluído com sucesso!\n");
                } else {
                    printf("Número de item inválido.\n");
                }
                break;
            
            case 5:
            	system("cls");
                printf("Escolha um número para participar do sorteio:\n");
                scanf("%d", &numeroEscolhido);
                linhas = 10; 
                colunas = 10; 
    
                printf("\nCartela de Rifa:\n");
                for (int i = 0; i < linhas; i++) {
                    for (int j = 0; j < colunas; j++) {
                        int numeroCartela = i * colunas + j + 1;
                        if (numeroCartela == numeroEscolhido) {
                            printf("[X] "); 
                        } else {
                            printf("[%2d] ", numeroCartela);
                        }
                    }
                    printf("\n");
                }
    
                if (numeroEscolhido == numeroGanhador) {
                    printf("\nParabéns! Você escolheu o número ganhador %d!\n", numeroGanhador);
                } else {
                    printf("\nVocê escolheu o número %d para o sorteio.\n", numeroEscolhido);
                    printf("Infelizmente, não foi o número ganhador %d.\n", numeroGanhador);
                }
                system("pause");
                system("cls");
                break;
            
            case 7:
            	system("cls");
                printf("Obrigado por usar a Loja. Até logo!\n");
                break;
            
            default:
                printf("Opção inválida. Escolha uma opção válida do menu.\n");
        }
    } while (opcao != 7);
 
    return 0;
}
