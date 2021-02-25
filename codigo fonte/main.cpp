#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Configuracao da chave para criptografia
char CHAVE[] = "AbCd";
int TAM_CHAVE = strlen(CHAVE);

//vetor de entrada do texto a ser criptografado
char TEXTO[100000];
int TAM_TEXTO=100000;

//criptografia

int TEXTO_CRIPT[100000];

bool Criptografar(){
    int CHAVE_int;
    for(int i=0; i < strlen(TEXTO);i++){
        TEXTO_CRIPT[i]=TEXTO[i];

    }
    printf("\n -- %d -- \n",TEXTO_CRIPT[1]);

    for(int aux = 0; aux < strlen(TEXTO);){
        for(int i=0; i < TAM_CHAVE; i++){
        CHAVE_int= CHAVE[i];
        TEXTO_CRIPT[aux] *= CHAVE_int;
        aux++;
    }
}


    printf("\n -- %d -- \n",TEXTO_CRIPT[1]);
    return true;
}

bool Descriptografar(){
    FILE *arquivo;
    int valor;
    int pos_chave;
    int pos_texto;

    arquivo = fopen("C:\\cript\\arquivos_recebidos\\criptografado.txt","r");

    if(arquivo==NULL){
        return false;
    }

    pos_chave=0;
    pos_texto=0;

    while(!feof(arquivo)){
        fscanf(arquivo,"%d",&valor);

        valor /= CHAVE[pos_chave];

        TEXTO[pos_texto] = (char) valor;

        pos_texto++;

        if(pos_chave == TAM_CHAVE-1){
            pos_chave=0;
        }else{
            pos_chave++;
        }

    }
    fclose(arquivo);
    return true;
}

//menus

void Recebe_Texto(char tipo[]){
    char aux[TAM_TEXTO];
    char pause;
    bool ok;

    FILE *arquivo;
    char palavra[100];

    if(strcmp(tipo,"msg")== 0){
        printf("\n\nReceber texto para criptografar\n\n");
        printf("\n\nDigite o texto: ");
        gets(aux);

        if(strlen(aux) <= TAM_TEXTO){
            strcpy(TEXTO,aux);
            printf("\n\nTexto recebido com sucesso!\n\n");
            printf("\n\nCriptografando texto...\n\n");

            ok=true;

        }else{
            printf("\n\nErro!\nTamanho do texto excede o limite de caracteres\n\n");
            ok=false;
            system("pause");
        }


    }else if(strcmp(tipo,"arquivo") == 0){
        printf("\n\nInstrucoes para importar um arquivo de texto:");
        printf("\n\n 1 - Renomeie o arquivo para 'original.txt'");
        printf("\n\n 2 - Copie o arquivo para a pasta que sera aberta a seguir");
        printf("\n\n 3 - Feche o explorador e retorne a aplicacao");


        printf("\n\n\n Pressione Enter para abrir a pasta...");
        scanf("%c",&pause);
        setbuf(stdin, NULL);

        system(" explorer C:\\cript\\arquivos_originais\\");
        printf("\n\n\n Pressione enter apos colar o arquivo na pasta...");
        scanf("%c",&pause);
        setbuf(stdin,NULL);
        printf("\n\nImportando arquivo...\n\n");


        arquivo = fopen("C:\\cript\\arquivos_originais\\original.txt","r");
           if(arquivo == NULL){
            printf("\n\nErro ao abrir o arquivo...\n\n");
           }else{
                while(!feof(arquivo)){
                    fscanf(arquivo,"%s",palavra);
                    strcat(aux," ");
                    strcat(aux,palavra);
                }
                fclose(arquivo);

                 if(strlen(aux) <= TAM_TEXTO){
                    strcpy(TEXTO,aux);
                    printf("\n\nTexto recebido com sucesso!\n\n");
                    printf("\n\nCriptografando texto...\n\n");

                    ok=true;
                }else{
                    printf("\n\nErro!\nTamanho do texto excede o limite de caracteres\n\n");
                    ok=false;
                    system("pause");

                }
            }

    }else{
        printf("Erro ao receber texto\n\n");
    }

    if(ok){
        if(Criptografar()){
            printf("\n\nTexto criptografado com sucesso!\n\n");
            arquivo = fopen("C:\\cript\\arquivos_gerados\\criptografado.txt","wt");
            if(arquivo == NULL){
                printf("\n\nErro ao criar o arquivo...\n\n");
           }else{
                for(int i=0; i < strlen(TEXTO); i++){
                    fprintf(arquivo,"%d ", TEXTO_CRIPT[i]);
                }
           }
           fclose(arquivo);

            printf("\n\nPressione enter para abrir a pasta do arquivo gerado!");
            scanf("%c", &pause);
            setbuf(stdin,NULL);
            system("explorer C:\\cript\\arquivos_gerados\\");

        }else{
            printf("\n\nNão foi possivel criptografar o texto!");
        }

    }
}



void Receber_Arquivo_cript(){
        char pause;
        printf("\n\nInstrucoes para importar um arquivo criptografado:");
        printf("\n\n 1 - Renomeie o arquivo para 'criptografado.txt'");
        printf("\n\n 2 - Copie o arquivo para a pasta que sera aberta a seguir");
        printf("\n\n 3 - Feche o explorador e retorne a aplicacao");


        printf("\n\n\n Pressione Enter para abrir a pasta...");
        scanf("%c",&pause);
        setbuf(stdin, NULL);

        system(" explorer C:\\cript\\arquivos_recebidos\\");
        printf("\n\n\n Pressione enter apos colar o arquivo na pasta...");
        scanf("%c",&pause);
        setbuf(stdin, NULL);
        printf("\n\nImportando arquivo...\n\n");


        if(Descriptografar()){
            printf("\n\n\n Arquivo descriptografado com sucesso!\n\n");
            system("pause");
            system("cls");
            printf("\n%s\n\n",TEXTO);
            system("pause");
        }else{
            printf("\n\n\n Nao foi possivel descriptografar o arquivo!\n\n");
            system("pause");
        }
}

void Receber_Texto(){

}



void Menu_Criptografar(){
    int opcao;
    printf("\n\tCriptografia de dados");
    printf("\n\n Criptografar texto ou arquivo");
    printf("\n\n\n 1 - Digitar texto ");
    printf("\n\n 2 - Importar arquivo de texto (txt)");
    printf("\n\n 3 - Voltar ao menu principal ");
    printf("\n\n Informe a opcao desejada: ");
    scanf("%d", &opcao);
    setbuf(stdin,NULL);
    switch(opcao){
        case 1:
            system("cls");
            Recebe_Texto("msg");
            break;
        case 2:
            system("cls");
            Recebe_Texto("arquivo");
            break;
        case 3:
            break;
        default:
            printf("Opcao invalida! Tente Novamente...");
        }

    }




void Menu(){
    int opcao;
    while(1){
        system("cls");
        printf("\n\tCriptografia de dados");
        printf("\n\n 1 - Criptografar texto ou arquivo");
        printf("\n\n 2 - Receber Arquivo");
        printf("\n\n 3 - Sair");
        printf("\n\n Informe a opcao desejada: ");
        scanf("%d",&opcao);
        setbuf(stdin,NULL);
        switch(opcao){
            case 1:
                system("cls");
                Menu_Criptografar();
                break;

            case 2:
                system("cls");
                Receber_Arquivo_cript();
                break;
            case 3:
                 printf("\nFinalizando...\n\n");
                 system("pause");
                 exit(0);
                 break;
            default:
                 printf("Opcao invalida! Tente Novamente...");
        }
    }
}

int main()
{
    Menu();
    return 0;
}
