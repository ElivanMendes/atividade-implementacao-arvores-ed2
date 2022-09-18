#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct no{

    int valor;
    struct no *esquerda, *direita;

}NoArv;

int lerValor(){

    int valor;

    printf("\nDigite um Valor: ");
    scanf("%d", &valor);

    return valor;
}

int lerValorBuscado(){

    int valor;

    printf("\nDigite o Valor Buscado: ");
    scanf("%d", &valor);

    return valor;
}

void imprimirValor(int valor){
    printf("%d ", valor);
}

void imprimirValorBuscado(NoArv *valorBuscado){

    if(valorBuscado != NULL){
        printf("\n\tValor Encontrado: %d\n", valorBuscado->valor);
    }
    else{
        printf("\n\tValor Nao Encontrado!\n");
    }
}

void inserir(NoArv **raiz, int valor){

    if(*raiz == NULL){

        *raiz = malloc(sizeof(NoArv));

        (*raiz)->valor = valor;
        (*raiz)->esquerda = NULL;
        (*raiz)->direita = NULL;
    }
    else{

        if(valor < (*raiz)->valor){
            inserir(&((*raiz)->esquerda), valor);
        }
        else{
            inserir(&((*raiz)->direita), valor);
        }
    }
}

NoArv* buscar(NoArv *raiz, int valor){

    if(raiz != NULL){

        if(valor == raiz->valor){
            return raiz;
        }
        else if(valor < raiz->valor){
            return buscar(raiz->esquerda, valor);
        }
        else{
            return buscar(raiz->direita, valor);
        }
    }

    return NULL;
}

void imprimirArv(NoArv *raiz){

    if(raiz != NULL){
        imprimirArv(raiz->esquerda);
        imprimirValor(raiz->valor);
        imprimirArv(raiz->direita);
    }
}

void menu(){

    NoArv *valorBuscado, *raiz = NULL;
    int opcao;

    do{
        printf("\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Buscar\n\t0 - Sair\n");
        scanf("%d", &opcao);
        printf("\n\tOpcao: %d\n", opcao);

        switch(opcao){
        case 1:

            inserir(&raiz, lerValor());

            break;
        case 2:

            if(raiz != NULL){
                printf("\n------------- ARVORE -------------\n");
                imprimirArv(raiz);
                printf("\n----------------------------------\n");
            }
            else{
                printf("\n\tArvore Vazia!\n");
            }

            break;
        case 3:

            if(raiz != NULL){
                valorBuscado = buscar(raiz, lerValorBuscado());
                imprimirValorBuscado(valorBuscado);
            }
            else{
                printf("\n\tArvore Vazia!\n");
            }

            break;
        default:

            if(opcao != 0){
                printf("\n\tOpcao Invalida!\n");
            }
        }

        if(opcao == 0){
            printf("\n\tSAINDO...\n");
            Sleep(2000);
        }

    }while(opcao != 0);
}

int main(){

    menu();

    return 0;
}
