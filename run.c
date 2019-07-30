/*
Este é um trabalho da disciplina de compiladores feito na linguagem C
O objetivo é criar um compilator toy que gere o código assemble corretamente 
de acordo com uma linguagem predefinida

Autor: Paulo Henrique de Oliveira Gomes
Data: Agosto de 2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex10.c"

#define MAX_CODE_SIZE 5000		//tamanho to vertor que ira guardar o codigo assembly
#define MAX_DATA 1000
#define MAXlABEL 20			//tamanho to label
#define QTD 50				//quantidade maxima de variaeis
#define MAIOR 1
#define MENOR 2
#define MAIORIGUAL 3
#define MENORIGUAL 4
#define IGUAL 5
#define DIFERENTE 6

//estrutura da tabela de simbolos que ira guardar as variaveis ja declaradas
typedef struct tabela_simbolos{
    char tag[MAX];
    char palavras[MAX];
}P_variaveis;
P_variaveis variaveis[QTD];

char code[MAX_CODE_SIZE];
int code_pos;		//identificar a posição correta para ser escrito em code
int contLabel;		//variavel para auxiliar na geração de label's diferentes
char idGlobal[MAX];		//variavel auxiliar para guardar um identificador
int op;				//variavel auxilicar para identificar qual operador_relacional
int quantidade_variavel;	//guarda quantas variaveis ja foram declaradas
FILE *p,*o;             //ponteiros para arquivos de entrada "p" e saida "o"
char data[MAX_DATA];
int data_pos;

void programa();
void declaracoes();
void declaracao();
void declaracao_inteiro();
void declaracao_real();
void declaracao_string();
void bloco();
void comandos();
void comando();
void comando_se_ou_senao();
void comando_enquanto();
void comando_atribuicao();
void comando_leitura();
void comando_escrita();
void expressao_booleana();
void operador_relacional();
void expressao_numerica();
void expressao_numerica_r();
void termo();
void fator();
void expectd(char *s);
void emit_code(char *s);
void emit_code_data(char *s);
void gera_label(char *s);
int declarada(char idGlobal[MAX]);
void error(char *s);
void writeFile();

int main(int argc,char *argv[]){

	int i;
    char aux2[MAX];

    o = fopen("outputFile.asm","w");
	//leitura do arquivo
	p = fopen("inputFile3.txt","r");
    char aux[10];
    while(fscanf(p,"%s", aux) != EOF){
        strcat(input," ");
        strcat(input,aux);
    }
	strcat(input,"\0");
    printf("%s", input);
    puts("");


	contLabel = 0;
	quantidade_variavel = 0;
    nextc = ' ';
    tokenPos = 0;
    charPos = 0;
    code_pos = 0;
    data_pos = 0 ;



    emit_code_data("extern printf\nextern scanf\n\nSECTION .data\n\n");
    emit_code_data("str0: db \"%d\",10, 0\nstr1: db \"%s\",10, 0\n");
    emit_code_data("strin0: db \"%d\", 0\nstrin1: db \"%s\", 0\n\n");
    emit_code("\n\nSECTION .codigo\nglobal main\nmain:\n\n\tpush rbp\n");
	programa();

    for(i=0; i<quantidade_variavel; i++){
	//	printf("%s %s\n", variaveis[i].tag, variaveis[i].palavras );
        if(strcmp(variaveis[i].tag,"int") == 0){
            strcpy (aux2,variaveis[i].palavras);
            emit_code_data(aux2);
            emit_code_data(": ");
            emit_code_data("dq 0");
            emit_code_data("\n");
        }else if(strcmp(variaveis[i].tag,"string") == 0){
            strcpy (aux2,variaveis[i].palavras);
            emit_code_data(aux2);
            emit_code_data(": ");
            emit_code_data("db \'\'");
            emit_code_data("\n");
        }
	}

    emit_code(" \n\tpop rbp\n\tmov rax,0\n\tRET");
    writeFile();
    //printf("este é a sessão de data :\n%s\n",data);
//    printf("este é o codigo gerado :\n%s\n", code);

    return 0;
}

void programa(){
	nextToken();
    declaracoes();
    bloco();
}

void declaracoes(){
    if(strcmp(token,"var") == 0){
		nextToken();
        declaracao();
		nextToken();
        declaracoes();
    }
}

void declaracao(){
    if( id(token) == 1){			//verifica se o token pode ser um identificador
		strcpy(idGlobal,token);
		if(declarada(idGlobal) != 1){			//verifica se esse identificador ainda não foi declarado
			strcpy(variaveis[quantidade_variavel].palavras, token);		//insere o identificador na tabela de simbolos
	        nextToken();
	        if(strcmp(token,":") == 0){
	            nextToken();
	            if(strcmp(token,"int") == 0){				//insere o tipo do identificador na tabela de simbolos
					strcpy(variaveis[quantidade_variavel++].tag, token);
	                declaracao_inteiro();
	            }else if(strcmp(token,"float") == 0){
					strcpy(variaveis[quantidade_variavel++].tag, token);
	                declaracao_real();
	            }else if(strcmp(token,"string") == 0){
					strcpy(variaveis[quantidade_variavel++].tag, token);
	                declaracao_string();
	            }else{
					expectd("um tipo valido");
					printf(" na funcao declaracao");
					puts("");
	            }
	        }else{
	            expectd(":");
				printf(" na funcao declaracao");
				puts("");
			}
        }else{
			printf("erro: variavel já declarada\n" );
		}
    }else{
		error(token);
		printf(" na funcao declaracao");
		puts("");
    }
}

void declaracao_inteiro(){
    nextToken();
    if(strcmp(token,";") != 0){
		expectd(";");
		printf(" na funcao declaracao_inteiro");
		puts("");
    }
}

void declaracao_real(){
    nextToken();
    if(strcmp(token,";") != 0){
		expectd(";");
		printf(" na funcao declaracao_real");
		puts("");
    }
}

void declaracao_string(){
    nextToken();
    if(strcmp(token,";") != 0){
		expectd(";");
		printf(" na funcao declaracao_string");
		puts("");
    }
}

void bloco(){
    if(strcmp(token,"{") == 0){
		nextToken();
        comandos();
        if(strcmp(token,"}") != 0){
			expectd("}");
			printf(" na funcao bloco");
			puts("");
        }
    }else{
		expectd("{");
		printf(" na funcao bloco");
		puts("");
    }
}

void comandos(){
    if( (strcmp(token,"if") == 0) || (strcmp(token,"while") == 0) || (strcmp(token,"read") == 0) || (strcmp(token,"write") == 0) || (id(token) == 1) ){
        comando();
        comandos();
    }
}

void comando(){
    if(strcmp(token,"if") == 0){
		nextToken();
        comando_se_ou_senao();
    }else if(strcmp(token,"while") == 0){
		nextToken();
        comando_enquanto();
    }else if(strcmp(token,"read") == 0){
		nextToken();
        comando_leitura();
    }else if(strcmp(token,"write") == 0){
		nextToken();
        comando_escrita();
    }else if(id(token) == 1){
		strcpy(idGlobal,token);
		nextToken();
		comando_atribuicao();
	}
}

void comando_se_ou_senao(){
	char label0[MAXlABEL];
	char label1[MAXlABEL];
        if(strcmp(token,"(") == 0){
			nextToken();
            expressao_booleana();
            if(strcmp(token,")") == 0){
                nextToken();
                if(strcmp(token,"then") == 0){
					gera_label(label0);
					gera_label(label1);
					emit_code("\n");
					emit_code("\tpop rax\n");
					emit_code("\tcmp rax, 0\n");
					emit_code("\tjz ");
					emit_code(label0);
					emit_code("\n");
					nextToken();
                    bloco();
					emit_code("\n");
					emit_code("\tjmp ");
					emit_code(label1);
					emit_code("\n");
					emit_code(label0);
					emit_code(":\n");
                    nextToken();
                    if(strcmp(token,"else") == 0){
						nextToken();
                        bloco();
                        nextToken();
                    }
                    emit_code("\n");
					emit_code(label1);
					emit_code(":\n");
                }else{
					expectd("then");
					printf(" na funcao comando_se_ou_senao");
					puts("");
                }
            }else{
				expectd(")");
				printf(" na funcao comando_se_ou_senao");
				puts("");
            }
        }else{
			expectd("(");
			printf(" na funcao comando_se_ou_senao");
			puts("");
        }
}

void comando_enquanto(){
	char label2[MAXlABEL];
	char label3[MAXlABEL];
	gera_label(label2);
	gera_label(label3);
	emit_code("\n");
	emit_code(label2);
	emit_code(":\n");
    if(strcmp(token,"(") == 0){
		nextToken();
        expressao_booleana();
        if(strcmp(token,")") != 0){
			expectd(")");
			printf(" na funcao comando_se_ou_senao");
			puts("");
        }else{
            nextToken();
            if(strcmp(token,"do") != 0){
				expectd("do");
				printf(" na funcao comando_se_ou_senao");
				puts("");
            }else{
                emit_code("\n");
				emit_code("\tpop rax\n");
				emit_code("\tcmp rax, 0\n");
				emit_code("\tjz ");
				emit_code(label3);
				emit_code("\n");
				nextToken();
                bloco();
                nextToken();
                emit_code("\n");
				emit_code("\tjmp ");
				emit_code(label2);
				emit_code("\n");
				emit_code(label3);
				emit_code(":\n");
            }
        }
    }else{
		expectd("(");
		printf(" na funcao comando_se_ou_senao");
		puts("");
    }
}

void comando_atribuicao(){
	if(declarada(idGlobal) == 1){
	    if(strcmp(token,"=") != 0){
			expectd("=");
			printf(" na funcao comando_atribuicao");
			puts("");
	    }else{
			nextToken();
	        expressao_numerica();
			emit_code("\n");
			emit_code("\tpop rax\n");
			emit_code("\tmov [");
			emit_code(idGlobal);
			emit_code("],rax\n");
	        if(strcmp(token,";") != 0){
				expectd(";");
				printf(" na funcao comando_atribuicao");
				puts("");
	        }else{
				nextToken();
			}
	    }
	}else{
		puts("erro: variavel não declarada");
	}
}

void comando_leitura(){
	char aux[MAX];
	int i;
    if(id(token) == 1){
        strcpy(idGlobal,token);
        if(declarada(idGlobal) == 1){
    		nextToken();
            if( strcmp(token,";") != 0){
    			expectd(";");
    			printf(" na funcao comando_leitura");
    			puts("");
    		}else{
    			nextToken();

    			for(i = 0; i < quantidade_variavel; i++){
					if( (strcmp(variaveis[i].palavras,idGlobal) == 0) ) {
						strcpy(aux,variaveis[i].tag);
					}
				}
				if(strcmp(aux,"int") == 0){
	                emit_code("\n");
	                emit_code("\tmov rax,");
	                emit_code(idGlobal);
	                emit_code("\n");
	                emit_code("\tmov rdi, strin0\n");;
	                emit_code("\tmov rsi,rax\n");
	                emit_code("\tcall scanf\n");
	                emit_code("\n");
	            }else if(strcmp(aux,"string") == 0){
	                emit_code("\n");
	                emit_code("\tmov rax,");
	                emit_code(idGlobal);
	                emit_code("\n");
	                emit_code("\tmov rdi, strin1\n");;
	                emit_code("\tmov rsi,rax\n");
	                emit_code("\tcall scanf\n");
	                emit_code("\n");
	            }
    		}
        }else{
            puts("variavel não declarada");
        }
    }else{
		error(token);
		printf(" na funcao comando_leitura");
		puts("");
    }
}

void comando_escrita(){
	char aux[MAX];
	int i;
	if(id(token) == 1){
        strcpy(idGlobal,token);
        if(declarada(idGlobal) == 1){
    		nextToken();
    		if( strcmp(token,";") != 0){
    			expectd(";");
    			printf(" na funcao comando_escrita");
    			puts("");
    		}else{
    			nextToken();

    			for(i = 0; i < quantidade_variavel; i++){
					if( (strcmp(variaveis[i].palavras,idGlobal) == 0) ) {
						strcpy(aux,variaveis[i].tag);
					}
				}
				if(strcmp(aux,"int") == 0){
	                emit_code("\n");
	                emit_code("\tmov rdi, str0");
	                emit_code("\n");
	                emit_code("\tmov rsi,[");
	                emit_code(idGlobal);
	                emit_code("]\n");
	                emit_code("\tmov rax,0\n");
	                emit_code("\tcall printf\n");
	                emit_code("\n");
	            }else if(strcmp(aux,"string") == 0){
	                emit_code("\n");
	                emit_code("\tmov rdi, str1");
	                emit_code("\n");
	                emit_code("\tmov rsi,");
	                emit_code(idGlobal);
	                emit_code("\n");
	                emit_code("\tmov rax,0\n");
	                emit_code("\tcall printf\n");
	                emit_code("\n");
	            }
    		}
        }
	}else{
		error(token);
		printf(" na funcao comando_escrita");
		puts("");
	}
}

void expressao_booleana(){
	char label_aux[MAXlABEL];
	char label_aux1[MAXlABEL];
    if( id(token) == 1 ){
		strcpy(idGlobal,token);
		if(declarada(idGlobal) == 1){
			nextToken();
	        operador_relacional();
			nextToken();
	        expressao_numerica();
			emit_code("\n");
			if( (op == MAIOR) || (op == MENOR) || (op == MAIORIGUAL) || (op == MENORIGUAL) || (op == DIFERENTE)){
				gera_label(label_aux);
				gera_label(label_aux1);
                emit_code("\n");
				emit_code("\tpop rax\n");
				emit_code("\tmov rbx,[");
				emit_code(idGlobal);
				emit_code("]\n");
				emit_code("\tcmp rbx,rax\n");
				if(op == MAIOR){
					emit_code("\tjle ");
				}else if(op == MENOR){
					emit_code("\tjge ");
				}else if(op == MAIORIGUAL){
					emit_code("\tjb ");
				}else if(op == MENORIGUAL){
					emit_code("\tjg ");
				}else if(op == DIFERENTE){
					emit_code("\tje ");
				}
				emit_code(label_aux);
				emit_code("\n");
				emit_code("\tpush 1\n");
				emit_code("\tjmp ");
				emit_code(label_aux1);
				emit_code("\n");
				emit_code(label_aux);
				emit_code(":\n");
				emit_code("\tpush 0\n");
				emit_code(label_aux1);
				emit_code(":");
				emit_code("\n");
			}else if(op == IGUAL){
				gera_label(label_aux);
				gera_label(label_aux1);
				emit_code("\tpop rax\n");
				emit_code("\tmov rbx,[");
				emit_code(idGlobal);
				emit_code("]\n");
				emit_code("\tcmp rbx,rax\n");
				emit_code("\tje ");
				emit_code(label_aux);
				emit_code("\n");
				emit_code("\tpush 0\n");
				emit_code("\tjmp ");
				emit_code(label_aux1);
				emit_code("\n");
				emit_code(label_aux);
				emit_code(":\n");
				emit_code("\tpush 1\n");
				emit_code(label_aux1);
				emit_code(":");
				emit_code("\n");
			}else{
				expectd("um operador valido");
			}
		}else{
			printf("variavel não declarada\n" );
            printf(" na funcao expressao_booleana\n");
		}
    }else{
		error(token);
		printf(" na funcao expressao_booleana");
		puts("");
    }
}
//ainda não reconhece todos os operadores
void operador_relacional(){
	if(strcmp(token,">") == 0){
		op = MAIOR;
	}else if(strcmp(token,"<") == 0){
		op = MENOR;
	}else if(strcmp(token,">=") == 0){
		op = MAIORIGUAL;
	}else if(strcmp(token,"=<") == 0){
		op = MENORIGUAL;
	}else if(strcmp(token,"!=") == 0){
		op = DIFERENTE;
	}else if(strcmp(token,"==") == 0){
		op = IGUAL;
	}
}

void expressao_numerica(){
    fator();
	if (strcmp(token,"*") == 0){
		nextToken();
		fator();
		emit_code("\n");
		emit_code("\tpop rax");
		emit_code("\n");
		emit_code("\tpop rbx");
		emit_code("\n");
		emit_code("\timul rax,rbx");
		emit_code("\n");
		emit_code("\tpush rax");
		emit_code("\n");
	}else if(strcmp(token,"/") == 0) {
		nextToken();
		fator();
		emit_code("\n");
		emit_code("\tpop rax");
		emit_code("\n");
		emit_code("\tpop rbx");
		emit_code("\n");
		emit_code("\tidiv rbx,rax");
		emit_code("\n");
		emit_code("\tpush rbx");
		emit_code("\n");
    }
    expressao_numerica_r();
}

void expressao_numerica_r(){

    if( strcmp(token,"+") == 0 ){
		nextToken();
		expressao_numerica();
        expressao_numerica_r();
		emit_code("\n");
		emit_code("\tpop rax");
		emit_code("\n");
		emit_code("\tpop rbx");
		emit_code("\n");
		emit_code("\tadd rax,rbx");
		emit_code("\n");
		emit_code("\tpush rax");
		emit_code("\n");
	}else if (strcmp(token,"-") == 0) {
		nextToken();
		expressao_numerica();
        expressao_numerica_r();
		emit_code("\n");
		emit_code("\tpop rax");
		emit_code("\n");
		emit_code("\tpop rbx");
		emit_code("\n");
		emit_code("\tsub rbx,rax");
		emit_code("\n");
		emit_code("\tpush rbx");
		emit_code("\n");
    }
}

void termo(){
	char aux[MAX];
	if(num(token) == 1){
		strcpy(aux,token);
		emit_code("\n");
		emit_code("\tmov rax,");
		emit_code(aux);
		emit_code("\n");
		emit_code("\tpush rax");
		emit_code("\n");
	}else if(id(token) == 1){
		strcpy(aux,token);
		emit_code("\n");
		emit_code("\tmov rax,[");
		emit_code(aux);
		emit_code("]");
		emit_code("\n");
		emit_code("\tpush rax");
		emit_code("\n");
	}else{
		expectd("uma variavel ou um numero");
		printf(" na funcao termo");
		puts("");
	}
	nextToken();
}

void fator(){
   if(strcmp(token,"(") == 0){
	   	nextToken();
   		expressao_numerica();
		if( strcmp(token,")") != 0){
			expectd(")");
			printf(" na funcao fator");
			puts("");
		}else{
			nextToken();
		}
   }else{
	   	termo();
   }
}

void expectd(char *s){
	printf("erro : esperado '%s' antes  de '%s' ", s, token);
}

void emit_code(char *s){
	int n;
	n = strlen(s);
	memcpy(code+code_pos,s,n);
	code_pos +=n;
}

void emit_code_data(char *s){
	int n;
	n = strlen(s);
	memcpy(data+data_pos,s,n);
	data_pos +=n;
}

void writeFile(){
    int i = 0;
    while(i<data_pos){
        fputc(data[i],o);
        i++;
    }
    i = 0;
    while(i<code_pos){
        fputc(code[i],o);
        i++;
    }
}

void gera_label(char *s){
	char string[MAXlABEL];
	char numero[10];
	sprintf(numero,"%d",contLabel);
	strcpy(string,"label");
	strcat(string, numero);
	strcpy(s,string);
	contLabel++;
}

int declarada(char idGlobal[MAX]){
	int i;
	for(i = 0; i < quantidade_variavel; i++){
		if( (strcmp(variaveis[i].palavras,idGlobal) == 0) ) {
			return 1;
		}
	}
	return -1;
}

void error(char *s){
	printf("erro :'%s' não pode ser usado como identificador", s);
}
