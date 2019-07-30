#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define NRES 11

typedef struct Palavras_reservadas{
    char palavras[MAX];
}P_reservadas;
P_reservadas reservadas[NRES] = { {"var"},{"int"},{"float"},{"string"},{"if"},{"then"},{"else"},{"while"},{"do"},{"read"},{"write"} };

int tokenPos;
int charPos;
char token[MAX];
char input[3000];
char nextc;

void readchr();
void nextToken();
int id(char token[MAX]);
int isnum(char a);
int num(char token[MAX]);

//funçao que realiza a leitura de cada caracter do arquivo e vai montando os tokens
void readchr() {
    if (tokenPos == MAX - 1) {
        token[tokenPos] = '\0';
        fprintf(stderr, "token too long: %s\n", token);
        exit(EXIT_FAILURE);
    }
    token[tokenPos++] = nextc;
    nextc = input[charPos++];
}
//função que realizaa leitura dos tokens
void nextToken() {
    int i;
    for(i= 0; i< tokenPos; i++){
        token[i] = '\0';
    }
    //laço que ignora os espaços
    while (isspace(nextc)) {
        nextc = input[charPos++];
    }
    tokenPos = 0;
	if (tokenPos == 0){
        if( (nextc == ':') || (nextc == '{') || (nextc == '}') || (nextc == '(') || (nextc == ')') || (nextc == ';') ){
            readchr();
        }
    }
    if (tokenPos == 0){
        if( (nextc == '+') || (nextc == '-') || (nextc == '*') || (nextc == '/') ){
            readchr();
        }
    }
	if(tokenPos == 0){

        while(isalnum(nextc) || nextc == '_') {
            readchr();
        }
	}
    if (tokenPos == 0) {
        while ( (nextc == '>') || (nextc == '<') || (nextc == '=') || (nextc == '!') ) {
            readchr();
        }
    }
	if (tokenPos == 0){
		while (isnum(nextc) == 1){
			readchr();
		}
	}
    //printf("%s\n", token);
    token[tokenPos]='\0';
}
//função que verifica se o token passado é um id, e se esse id não é uma palavra reservada
int id(char token[MAX]){
    int i = 1, tam;
    char caracter;
    tam = strlen(token);
    caracter = token[0];
    if( (isalpha(caracter) ) || (caracter == '_') ){        //verifica se a variavel comeca com uma letra ou um '_'
        while( i<tam ){
            caracter = token[i];
            if(isalnum(caracter)){
                i++;
            }else{
                return -1;
            }
        }
    }else{
        return -1;
    }
    for( i = 0; i < NRES; i++){     //percorre a tabela de simbolos procurando a variavel
        if(strcmp(token,reservadas[i].palavras) == 0){
            return -1;
        }
    }
    return 1;
}
//verifica se o caracter é um numero
int isnum(char a){
	if( (a == '0') || (a == '1') || (a == '2') || (a == '3') || (a == '4') || (a == '5') || (a == '6') || (a == '7') || (a == '8') || (a == '9') ){
		return 1;
	}else{
		return -1;
	}
}
//verifica se o token é um numero
int num(char token[MAX]){
    int i,j;
    char l;
    j = strlen(token);
    for(i = 0; i < j; i++){
        l = token[i];
        if(isnum(l) != 1){
            return -1;
        }
    }
    return 1;
}
