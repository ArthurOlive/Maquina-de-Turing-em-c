#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DIR 1
#define ESQ 0

typedef struct bloco{
	int pos;					//contem a posicao do bloco
	char conteudo;				//contem o caractere do bloco
} bloco;

typedef struct fita{
	char * cadeia;
	int tam;
	bloco * fita;				//contem n blocos
	bloco * blocoAtual;			//bloco atual da fita
}fita;

typedef struct transicao{
	char caractereLido;			//caractere que sera lido na fita
	char caractereEscrito;		//caractere que será escrito na fita
	char * estadoDestino;		//indentificado do estado
	int movimento; 				//true = direita, false = esquerda 
} transicao;

typedef struct estado{
	transicao * transicaoEstado;//contem um conjunto de estados
	int quant;
	char * idEstado;			//contem o nome do estado para a indentificaçao
} estado;

typedef struct turing{
	char * alfabeto;			//alfabeto da cadeia
	char * alfabetoFita;		//alfabeto da fita
	estado * estados;			//contem todos os estados 
	fita * fita;				//contem a fita 
	int quantEstados; 			//quantidade de estados
	int quantAlfa;				//tamanho do alfabeto
	int quantAlfaFita;			//tamanho do alfabeto da fita
	estado * estadoAtual;		//contem o estado atual
	char caractereInicial;		//caractere do inicio da fita
	char caractereFinal;		//caractere do final da fita
	estado * estadoInicial; 	//ponteiro para o estado inicial da maquina
	estado * estadoFinal;		//ponteiro para o estado final da maquina 
} turing;

turing * Turing(char * alfabeto, char * alfabetoFita, estado * estados, int quant, char caractereInicial, char caractereFinal, estado * estadoInicial, estado * estadoFinal);
estado * Estado(transicao * transicoes, int tam, char * id);
void printTrans(transicao * ts);
void printEstado(estado * est);
transicao * ts(char lido, char escrito, char * estado, int movimento); 
fita * iniciarFita(char * cadeia, char inicial, char final);
void listarFita(fita * ft);
void moverFita(fita * ft, int movimento);
void aceita(turing * tr, char * cadeia);
int processar(turing * tr);
estado * buscarEstado(turing * tr, char * id);
int aceitaFita(fita * ft, char inicial, char final, char * alfaFita, int tam);

int main(){
	char alfabeto[] = {'a', 'b', 'c'};
	char alfabetoFita[] = {'X', 'Y', 'Z'};
	
	transicao tq1 [] = {*ts('<','<',"q2", DIR)};
	transicao tq2 [] = {*ts('a', 'X', "q3", DIR)}; 
	transicao tq3 [] = {*ts('a', 'a', "q3", DIR), *ts('Y', 'Y', "q3", DIR), *ts('b', 'Y', "q4", DIR)}; 
	transicao tq4 [] = {*ts('b', 'b', "q4", DIR), *ts('c', 'Z', "q5", DIR), *ts('Z', 'Z', "q4", DIR)};
	transicao tq5 [] = {*ts('a', 'a', "q5", ESQ), *ts('b', 'b', "q5", ESQ), *ts('c', 'c', "q5", ESQ), *ts('Y', 'Y', "q5", ESQ),*ts('X', 'X', "q2", DIR), *ts('Z', 'Z', "q5", ESQ),*ts('>', '>', "qf", DIR)};
	transicao * tqf;
	
	estado * q1 = Estado(tq1, 1, "q1");
	estado * q2 = Estado(tq2, 1, "q2");
	estado * q3 = Estado(tq3, 3, "q3");
	estado * q4 = Estado(tq4, 3, "q4");
	estado * q5 = Estado(tq5, 7, "q5");
	estado * qf = Estado(tqf, 0, "qf");
	
	estado estados[] = {*q1, *q2, *q3, *q4, *q5, *qf};
	
	turing * tr = Turing(alfabeto, alfabetoFita, estados, 6, '<', '>', q1, qf);

	aceita(tr, "aaabbbccc");
	system("pause");
	system("cls");
	
	aceita(tr, "aabbccc");
	system("pause");
	system("cls");
	
	aceita(tr, "aaabbccc");
	system("pause");
	system("cls");
	
	system("pause");
	return 0;
}

fita * iniciarFita(char * cadeia, char inicial, char final){
	int tam = strlen(cadeia) + 2;
	int cont = 1;
	
	fita * nwFita = calloc (1, sizeof(fita));
	nwFita->fita = calloc(tam, sizeof(bloco));
	nwFita->cadeia = cadeia;
	
	nwFita->fita[0].conteudo = inicial;
	nwFita->fita[0].pos = 0;
	
	while(cont < (tam - 1)){
		nwFita->fita[cont].conteudo = cadeia[cont - 1];
		nwFita->fita[cont].pos = cont;
		cont ++;
	}
	
	nwFita->fita[(tam - 1)].conteudo = final;
	nwFita->fita[(tam - 1)].pos = (tam - 1);
	
	nwFita->blocoAtual = &nwFita->fita[0];
	
	nwFita->tam = tam;
	
	return nwFita;
}

void listarFita(fita * ft){
	
    
	if (ft != NULL){
		int tam = ft->tam;
		int cont = 0;
		while(tam){
			if (ft->fita[cont].pos == ft->blocoAtual->pos){
				printf("|%c|", ft->fita[cont].conteudo);	
			} else {
				printf("%c ", ft->fita[cont].conteudo);
			}
			cont++;
			tam--;
		}
	} else {
		printf("Fita vazia!!!\n");
	}

}

void moverFita(fita * ft, int movimento){
	if (movimento){
		if ((ft->blocoAtual->pos + 1) < ft->tam){
			ft->blocoAtual = &ft->fita[(ft->blocoAtual->pos + 1)];
		} 
	} else {
		if ((ft->blocoAtual->pos - 1) > 0){
			ft->blocoAtual = &ft->fita[(ft->blocoAtual->pos - 1)];
		} 
	}
}

transicao * ts(char lido, char escrito, char * estado, int movimento){
	transicao * ts = calloc(1, sizeof(transicao));
	ts->caractereLido = lido;
	ts->caractereEscrito = escrito;
	ts->estadoDestino = estado;
	ts->movimento = movimento;
	
	return ts;
}

void printTrans(transicao * ts){
	printf("%c %c %s %d\n", ts->caractereLido, ts->caractereEscrito, ts->estadoDestino, ts->movimento);
	
}
   
estado * Estado(transicao * transicoes, int tam, char * id){
	estado * est = calloc(1, sizeof(estado));
	est->transicaoEstado = transicoes;
	est->quant = tam;
	est->idEstado = id;
	
	return est;
}

void printEstado(estado * est){
	printf("estado : %s\n", est->idEstado);
	int tam = est->quant;
	int cont = 0;
	while (cont < tam){
		printTrans(&est->transicaoEstado[cont]);
		cont ++;
	}
}

turing * Turing(char * alfabeto, char * alfabetoFita, estado * estados, int quant, char caractereInicial, char caractereFinal, estado * estadoInicial, estado * estadoFinal){
	turing * ntr = calloc (1, sizeof(turing));
	ntr->alfabeto = alfabeto;
	ntr->alfabetoFita = alfabetoFita;
	ntr->caractereInicial = caractereInicial;
	ntr->caractereFinal = caractereFinal;
	ntr->estadoInicial = estadoInicial;
	ntr->estadoFinal = estadoFinal;
	ntr->quantEstados = quant;
	ntr->estados = estados;
	ntr->estadoAtual = ntr->estadoInicial;
	ntr->quantAlfa = strlen(alfabeto);
	ntr->quantAlfaFita = strlen(alfabetoFita);
	ntr->fita = NULL;
	
	return ntr;
}

void aceita(turing * tr, char * cadeia){
	
	if (tr->fita != NULL){
		free(tr->fita);
		tr->fita = iniciarFita(cadeia, tr->caractereInicial, tr->caractereFinal);	
	} else {
		tr->fita = iniciarFita(cadeia, tr->caractereInicial, tr->caractereFinal);
	}
	
	int resp = 0;
	
	while(tr->estadoAtual->idEstado != tr->estadoFinal->idEstado && resp == 0){
		listarFita(tr->fita);
		resp = processar(tr);
	}
	printf("Estado final : %s\n", tr->estadoAtual->idEstado);

	if (aceitaFita(tr->fita, tr->caractereInicial, tr->caractereFinal, tr->alfabetoFita, tr->quantAlfaFita) != 0){
		printf("Rejeita a cadeia %s\n", tr->fita->cadeia);
	} else if (tr->estadoAtual->idEstado != tr->estadoFinal->idEstado){
		printf("Rejeita a cadeia %s\n", tr->fita->cadeia);
	} else {
		printf("Aceita a cadeia %s\n", tr->fita->cadeia);
	}
	//reserta o estado da maquina
	tr->estadoAtual = tr->estadoInicial;
}

int processar(turing * tr){
	int i = 0;
	printf("Estado: %s \n", tr->estadoAtual->idEstado);
	while (i < tr->estadoAtual->quant){
		if (tr->estadoAtual->transicaoEstado[i].caractereLido == tr->fita->blocoAtual->conteudo){
			tr->fita->blocoAtual->conteudo = tr->estadoAtual->transicaoEstado[i].caractereEscrito;
			moverFita(tr->fita, tr->estadoAtual->transicaoEstado[i].movimento);
			tr->estadoAtual = buscarEstado(tr, tr->estadoAtual->transicaoEstado[i].estadoDestino);
			i = tr->estadoAtual->quant;
			return 0;
		}
		i++;
	}
	return 1;
}

estado * buscarEstado(turing * tr, char * id){
	int tam = tr->quantEstados;
	int cont = 0;
	while (cont < tam){
		if(strcmp(id, tr->estados[cont].idEstado) == 0){
			return &tr->estados[cont];
		}
		cont ++;
	}
	return NULL;
}

int aceitaFita(fita * ft, char inicial, char  final, char * alfaFita, int tam){
	if (ft != NULL){
		int cont = 0;
		int i = 0;
		int c = 0;
		while(cont < ft->tam){
			c = 0;
			if (ft->fita[cont].conteudo != inicial && ft->fita[cont].conteudo != final){
				i = 0;
				while(i < tam){
					if (ft->fita[cont].conteudo == alfaFita[i]){
						c = 1;
						i = tam;
					}
					i++;
				}
				if (c == 0){
					return 1;
				}
			}
			cont++;
		}
	} 
	return 0;
}
