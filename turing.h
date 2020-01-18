#ifndef TURING_H  
#define TURING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define DIR 1
#define ESQ 0

typedef struct bloco{
	int pos;					//contem a posicao do bloco
	char conteudo;				//contem o caractere do bloco
} bloco;

typedef struct fita{
	int tam;					//contem o tamanho da fita
	char * cadeia;				//contem a cadeia 
	bloco * fita;				//contem n blocos
	bloco * blocoAtual;			//bloco atual da fita
}fita;

typedef struct transicao{
	int movimento; 				//true = direita, false = esquerda 
	char caractereLido;			//caractere que sera lido na fita
	char caractereEscrito;		//caractere que sera escrito na fita
	char * estadoDestino;		//indentificado do estado
} transicao;

typedef struct estado{
	int quant;					//quantidade de estados
	char * idEstado;			//contem o nome do estado para a indentificacao
	transicao * transicaoEstado;//contem um conjunto de estados
} estado;

typedef struct turing{
	char * alfabeto;			//alfabeto da cadeia
	char * alfabetoFita;		//alfabeto da fita
	int quantEstados; 			//quantidade de estados
	char caractereInicial;		//caractere do inicio da fita
	char caractereFinal;		//caractere do final da fita
	estado * estados;			//contem todos os estados 
	fita * fita;				//contem a fita 
	estado * estadoAtual;		//contem o estado atual
	estado * estadoInicial; 	//ponteiro para o estado inicial da maquina
	estado * estadoFinal;		//ponteiro para o estado final da maquina 
} turing;

turing * Turing(char * alfabeto, char * alfabetoFita, estado * estados, int quant, char caractereInicial, char caractereFinal, estado * estadoInicial, estado * estadoFinal);
estado * Estado(transicao * transicoes, int tam, char * id);
transicao * ts(char lido, char escrito, char * estado, int movimento); 
fita * iniciarFita(char * cadeia, char inicial, char final);

void printTrans(transicao * ts);
void printEstado(estado * est);
void printFita(fita * ft);

void moverPosFita(fita * ft, int movimento);
void aceita(turing * tr, char * cadeia);
int processar(turing * tr);
estado * buscarEstado(turing * tr, char * id);
int testarFita(fita * ft, char inicial, char final, char * alfaFita);

#endif
