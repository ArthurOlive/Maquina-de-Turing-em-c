#include "turing.h"

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

transicao * ts(char lido, char escrito, char * estado, int movimento){
	transicao * ts = calloc(1, sizeof(transicao));

	ts->caractereLido = lido;
	ts->caractereEscrito = escrito;
	ts->estadoDestino = estado;
	ts->movimento = movimento;
	
	return ts;
}

estado * Estado(transicao * transicoes, int tam, char * id){
	estado * est = calloc(1, sizeof(estado));
	est->transicaoEstado = transicoes;
	est->quant = tam;
	est->idEstado = id;
	
	return est;
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
	ntr->fita = NULL;
	
	return ntr;
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


void printFita(fita * ft){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    
	if (ft != NULL){
		int tam = ft->tam;
		int cont = 0;
		while(tam){
			if (ft->fita[cont].pos == ft->blocoAtual->pos){
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				printf("%c ", ft->fita[cont].conteudo);
				SetConsoleTextAttribute(hConsole, saved_attributes);	
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

void moverPosFita(fita * ft, int movimento){
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

void printTrans(transicao * ts){
	printf("%c %c %s %d\n", ts->caractereLido, ts->caractereEscrito, ts->estadoDestino, ts->movimento);
	
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

void aceita(turing * tr, char * cadeia){
	
	if (tr->fita != NULL){
		free(tr->fita);
		tr->fita = iniciarFita(cadeia, tr->caractereInicial, tr->caractereFinal);	
	} else {
		tr->fita = iniciarFita(cadeia, tr->caractereInicial, tr->caractereFinal);
	}
	
	int resp = 0;
    printf("==================================================================\n");
	while(tr->estadoAtual->idEstado != tr->estadoFinal->idEstado && resp == 0){
        printf("\t");
		printFita(tr->fita);
		resp = processar(tr);
	}
	printf("==================================================================\n");
	printf(" Estado final : %s\n", tr->estadoAtual->idEstado);
	
	if (testarFita(tr->fita, tr->caractereInicial, tr->caractereFinal, tr->alfabetoFita) != 0){
		printf(" Rejeita a cadeia %s\n", tr->fita->cadeia);
	} else if (tr->estadoAtual->idEstado != tr->estadoFinal->idEstado){
		printf(" Rejeita a cadeia %s\n", tr->fita->cadeia);
	} else {
		printf(" Aceita a cadeia %s\n\n", tr->fita->cadeia);
	}
	
	//reserta o estado da maquina
	tr->estadoAtual = tr->estadoInicial;
}

int processar(turing * tr){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
	int i = 0;

	while (i < tr->estadoAtual->quant){
		if (tr->estadoAtual->transicaoEstado[i].caractereLido == tr->fita->blocoAtual->conteudo){
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            printf("F: ");
            SetConsoleTextAttribute(hConsole, saved_attributes);	

            printf("%c -> %c ",tr->fita->blocoAtual->conteudo, tr->estadoAtual->transicaoEstado[i].caractereEscrito);
			tr->fita->blocoAtual->conteudo = tr->estadoAtual->transicaoEstado[i].caractereEscrito;
			moverPosFita(tr->fita, tr->estadoAtual->transicaoEstado[i].movimento);

            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            printf("Q: ");
            SetConsoleTextAttribute(hConsole, saved_attributes);

            printf("%s -> ", tr->estadoAtual->idEstado);
			tr->estadoAtual = buscarEstado(tr, tr->estadoAtual->transicaoEstado[i].estadoDestino);
            printf("%s\n", tr->estadoAtual->idEstado);
			return 0;
		}
		i++;
	}
	return 1;
}



int testarFita(fita * ft, char inicial, char  final, char * alfaFita){
	if (ft != NULL){
		int cont = 0;
		int i = 0;
		int c = 0;
		while(cont < ft->tam){
			c = 0;
			if (ft->fita[cont].conteudo != inicial && ft->fita[cont].conteudo != final){
				i = 0;
				while(i < strlen(alfaFita)){
					if (ft->fita[cont].conteudo == alfaFita[i]){
						c = 1;
						i = strlen(alfaFita);
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
