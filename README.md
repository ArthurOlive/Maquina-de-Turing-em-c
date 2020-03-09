# Maquina de turing linearmente limitada:

</p>
O projeto a seguir contem 2 exemplo mtll1.c e mtll2.c, os arquivos da biblioteca são os arquivos turing.h e turing.c, abaixo segue um exemplo de chamada dos metodos e configuração:
</p>


~~~~c
#include <stdlib.h>
#include <stdio.h>
#include "turing.h"

int main(){
	//alfabeto da gramatica
	char alfabeto[] = {'a', 'b', 'c'};

	//alfabeto da fita
	char simbolosAux[] = {'X', 'Y', 'Z'};
	
	//tabela de transições
	transicao tq1 [] = {*ts('<','<',"q2", DIR)};
	transicao tq2 [] = {*ts('a', 'X', "q3", DIR)}; 
	transicao tq3 [] = {*ts('a', 'a', "q3", DIR), *ts('Y', 'Y', "q3", DIR), *ts('b', 'Y', "q4", DIR)}; 
	transicao tq4 [] = {*ts('b', 'b', "q4", DIR), *ts('c', 'Z', "q5", DIR), *ts('Z', 'Z', "q4", DIR)};
	transicao tq5 [] = {*ts('a', 'a', "q5", ESQ), *ts('b', 'b', "q5", ESQ), *ts('c', 'c', "q5", ESQ), *ts('Y', 'Y', "q5", ESQ),*ts('X', 'X', "q2", DIR), *ts('Z', 'Z', "q5", ESQ),*ts('>', '>', "qf", DIR)};
	transicao * tqf;
	
	//estados da maquina de turing
	estado * q1 = Estado(tq1, 1, "q1");
	estado * q2 = Estado(tq2, 1, "q2");
	estado * q3 = Estado(tq3, 3, "q3");
	estado * q4 = Estado(tq4, 3, "q4");
	estado * q5 = Estado(tq5, 7, "q5");
	estado * qf = Estado(tqf, 0, "qf");
	
	//array com os estados 
	estado estados[] = {*q1, *q2, *q3, *q4, *q5, *qf};
	
	//definicao da maquina
	turing * tr = Turing(alfabeto, simbolosAux, 3, estados, 6, '<', '>', q1, qf);

	//loop do programa
	int opc; 
	char cadeia[100];
	do{
		printf("O programa reconhece cadeias da gramatica (a^n b^n c^n)\n");
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

~~~~

Exemplo de execusão: 

<p align="center">
 <img src = https://github.com/ArthurOlive/maquina_turing_configuravel_c/blob/master/img/ex1.PNG/>
</p>

OBS: Execusão em prompt:
> gcc turing.c mtll1.c -o mtll1 
