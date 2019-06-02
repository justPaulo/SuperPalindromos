//
//  main.c
//  SuperPalindromos
//
//  Created by Paulo on 02/06/2019.
//  Copyright © 2019 Paulo A. Nascimento. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ficheiroTexto "texto.txt"
#define kMaxLinhasFicheiro 9999
#define kMaxColunasPorLinhas 256

void Entrada(void);
char toUpperChar(char umCaractere);
void Compactar(char *umaString);
int isPalindrome(char *umaString);

int main(int argc, const char * argv[])
{
    Entrada();
 
    return EXIT_SUCCESS;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Entrada()
{
    int i;
    int numLinhasLidas=0;
    FILE *fp;
    char linha[kMaxColunasPorLinhas];
    char *buffer[kMaxLinhasFicheiro];
    char *backupBuffer[kMaxLinhasFicheiro];
    
    if ( (fp=fopen(ficheiroTexto,"r")) == NULL )
    {
        printf("\nFile not found\n");
        exit (EXIT_FAILURE);
    }
    
    // Inicialização do vector de memória
    for (i=0;i<kMaxLinhasFicheiro;i++)
    {
        buffer[i]= (char *) malloc(kMaxColunasPorLinhas * sizeof (char) );
        backupBuffer[i]= (char *) malloc(kMaxColunasPorLinhas * sizeof (char) );
    }

    i=0;
    
    // leitura do ficheiro com copia do conteudo em memoria
    while ( fgets(linha, sizeof linha, fp) != NULL )
        strncpy(buffer[i++], linha, sizeof linha);

    numLinhasLidas=i;

    for (i=0;i<numLinhasLidas;i++)
    {
        strncpy(backupBuffer[i], buffer[i], sizeof linha); // cópia do vector
        Compactar(buffer[i]);
        if ( isPalindrome(buffer[i]) )
            printf("%s > ... < %s", buffer[i], backupBuffer[i] );
    }
    
    printf("\nProgram leu %d linhas de texto.\n", numLinhasLidas);
    
    fclose(fp);
 }
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
char toUpperChar(char umCaractere) // ou #include <ctype.h> <==> std. toupper()
{
    if (umCaractere >= '0' && umCaractere <= '9') // também consideramos palindromos numéricos, yei!
        return umCaractere;
    else
        return (umCaractere >= 'a')?umCaractere-('a'-'A'):umCaractere; // a-A=32, notável eficiência linguagem C desde K&R 70's
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Compactar(char *umaString)
{
    int j=0;
    char aux[kMaxColunasPorLinhas];
    
    for (int i=0;i<= strlen(umaString); i++ )
        if (umaString[i] != ' ' && umaString[i] != '.' && umaString[i] != ','
                && umaString[i] != '!' && umaString[i] != '?' )
            aux[j++]=umaString[i];
   
    strcpy(umaString, aux);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int isPalindrome(char *umaString)
{
    int i;
    long tam=strlen(umaString)-1;
    
    for (i=0;i<tam/2;i++)
        if ( toUpperChar(umaString[i]) != toUpperChar(umaString[tam-i-1]) )
            break;

    return ( i==tam/2);
}
