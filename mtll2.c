#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "turing.h"

int main(){
	//alfabeto da gramatica
	char alfabeto[] = {'a', 'b', 'c', 'd'};

	//alfabeto da fita
	char alfabetoFita[] = {'X', 'Y', 'Z', 'W'};
	
	//tabela de transições
	transicao tq1 [] = {*ts('<','<',"q2", DIR)};
	transicao tq2 [] = {*ts('a', 'X', "q3", DIR)}; 
	transicao tq3 [] = {*ts('a', 'a', "q3", DIR), *ts('Y', 'Y', "q3", DIR),  *ts('Z', 'Z', "q3", DIR), *ts('b', 'Y', "q4", DIR)}; 
	transicao tq4 [] = {*ts('c', 'Z', "q5", DIR)};
	transicao tq5 [] = {*ts('b', 'b', "q6", DIR), *ts('W', 'W', "q5", DIR), *ts('d', 'W', "q8", DIR)};
	transicao tq6 [] = {*ts('c','c',"q5", DIR)};
	transicao tq7 [] = {*ts('a', 'a', "q7", ESQ), *ts('b', 'b', "q7", ESQ), *ts('c', 'c', "q7", ESQ), *ts('d', 'd', "q7", ESQ), *ts('W', 'W', "q7", ESQ),*ts('Y', 'Y', "q7", ESQ),*ts('X', 'X', "q2", DIR), *ts('Z', 'Z', "q7", ESQ),*ts('>', '>', "qf", DIR)};
	transicao tq8 [] = {*ts('d', 'W', "q7", DIR)};
	transicao * tqf;

	//estados da maquina de turing
	estado * q1 = Estado(tq1, 1, "q1");
	estado * q2 = Estado(tq2, 1, "q2");
	estado * q3 = Estado(tq3, 4, "q3");
	estado * q4 = Estado(tq4, 1, "q4");
	estado * q5 = Estado(tq5, 3, "q5");
 	estado * q6 = Estado(tq6, 1, "q6");
	estado * q7 = Estado(tq7, 9, "q7");
	estado * q8 = Estado(tq8, 1, "q8");
	estado * qf = Estado(tqf, 0, "qf");
	
	//array com os estados 
	estado estados[] = {*q1, *q2, *q3, *q4, *q5, *q6, *q7, *q8, *qf};
	
	//definicao da maquina
	turing * tr = Turing(alfabeto, alfabetoFita, estados, 9, '<', '>', q1, qf);

	//loop do programa
	int opc;
	char cadeia[100];
	do{
		printf("O programa reconhece cadeias da gramatica (a^n (bc)^n d^2n)\n");
		printf("1 - digitar uma cadeia\n");
		printf("0 - sair\n");
		printf("opcao: ");
		scanf("%d", &opc);

		if(opc){
			printf("Digite uma cadeia: ");
			scanf("%s", cadeia);
			aceita(tr, cadeia);
			system("pause");
			system("cls");
		}
	} while(opc);


	system("pause");
	return 0;
}