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

int alturaArv(NoArv *raiz){

    if(raiz == NULL){
        return -1;
    }
    else{

        int esq = alturaArv(raiz->esquerda);
        int dir = alturaArv(raiz->direita);

        if(esq > dir){
            return esq + 1;
        }
        else{
            return dir + 1;
        }
    }
}

int quantidadeDeNosArv(NoArv *raiz){
    return (raiz == NULL) ? 0 : 1 + quantidadeDeNosArv(raiz->esquerda) + quantidadeDeNosArv(raiz->direita);
}

int quantidadeDeFolhasArv(NoArv *raiz){

    if(raiz == NULL){
        return 0;
    }
    else if(raiz->esquerda == NULL && raiz->direita == NULL){
        return 1;
    }
    else{
        return quantidadeDeFolhasArv(raiz->esquerda) + quantidadeDeFolhasArv(raiz->direita);
    }
}

NoArv* remover(NoArv *raiz, int chave){

    if(raiz == NULL){
        printf("\n\tValor Nao Encontrado!\n");
        return NULL;
    }
    else{

        if(raiz->valor == chave){

            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                printf("\n\tElemento Folha Removido: %d\n", chave);
                return NULL;
            }
            else{

                if(raiz->esquerda != NULL && raiz->direita != NULL){

                    NoArv *aux = raiz->esquerda;

                    while(aux->direita != NULL){
                        aux = aux->direita;
                    }

                    raiz->valor = aux->valor;
                    aux->valor = chave;

                    printf("\n\tElemento Trocado: %d\n", chave);

                    raiz->esquerda = remover(raiz->esquerda, chave);

                    return raiz;
                }
                else{

                    NoArv *aux;

                    if(raiz->esquerda != NULL){
                        aux = raiz->esquerda;
                    }
                    else{
                        aux = raiz->direita;
                    }

                    free(raiz);
                    printf("\n\tElemento com 1 Filho Removido: %d\n", chave);
                    return aux;
                }
            }
        }
        else{

            if(chave < raiz->valor){
                raiz->esquerda = remover(raiz->esquerda, chave);
            }
            else{
                raiz->direita = remover(raiz->direita, chave);
            }

            return raiz;
        }
    }
}

int maiorValor(NoArv *raiz){

    if(raiz != NULL){

        if(raiz->direita != NULL){
            return maiorValor(raiz->direita);
        }
        else{
            return raiz->valor;
        }
    }
}

int menorValor(NoArv *raiz){

    if(raiz != NULL){

        if(raiz->esquerda != NULL){
            return menorValor(raiz->esquerda);
        }
        else{
            return raiz->valor;
        }
    }
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
        printf("\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Buscar\n\t4 - Altura da Arvore\n");
        printf("\t5 - Quantidade de Nos\n\t6 - Quantidade de Folhas\n\t7 - Remover\n");
        printf("\t8 - Maior Valor\n\t9 - Menor Valor\n\t0 - Sair\n");
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
        case 4:

            if(raiz != NULL){
                printf("\n\tAltura da Arvore: %d\n", alturaArv(raiz));
            }
            else{
                printf("\n\tArvore Vazia!\n");
            }

            break;
        case 5:

            if(raiz != NULL){
                printf("\n\tQuantidade de Nos: %d\n", quantidadeDeNosArv(raiz));
            }
            else{
                printf("\n\tArvore Vazia!\n");
            }

            break;
        case 6:

            if(raiz != NULL){
                printf("\n\tQuantidade de Folhas: %d\n", quantidadeDeFolhasArv(raiz));
            }
            else{
                printf("\n\tArvore Vazia!\n");
            }

            break;
        case 7:

            if(raiz != NULL){

                printf("\n------------- ARVORE -------------\n");
                imprimirArv(raiz);
                printf("\n----------------------------------\n");

                raiz = remover(raiz, lerValor());
            }
            else{
                printf("\n\tArvore Vazia!\n");
            }

            break;
        case 8:

            if(raiz != NULL){
                printf("\n\tMaior Valor: %d\n", maiorValor(raiz));
            }
            else{
                printf("\n\tArvore Vazia!\n");
            }

            break;
        case 9:

            if(raiz != NULL){
                printf("\n\tMenor Valor: %d\n", menorValor(raiz));
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
