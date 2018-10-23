#include<at89x52.h>
#define Tea P0_1
#define Coffee P0_2
#define Glass P1
const LIGADO = 1;
const DESLIGADO = 0;

void delay(unsigned int time_ms){
	unsigned int i, j;
	for (i = 0; i < time_ms; i++){
		for (j = 0; j < 12750; j++){
		}
	}
}
void coinInterrupt() interrupt 0 { // S�ra chamada quando a moeda for colocado, ou seja a porta da interrup��o P3_2;
	if((Tea == LIGADO) && (Coffee == DESLIGADO)){
			delay(800); 					// pequeno tempo para a m�quina identificar o que ser� feito;
			Glass = LIGADO; 		 // O copo � ligado para encher;
			delay(4000); 				//tempo em que o copo enche;
			Glass = DESLIGADO; //Copo cheio;
			Tea = DESLIGADO; 	//Desliga o pino do Ch�;
			P3_2 = 1;        //Volta ao estado inicial para esperar outra moeda;
		}
		else if((Coffee == LIGADO) && (Tea == DESLIGADO)){
			delay(800); 							// pequeno tempo para a m�quina identificar o que ser� feito;
			Glass = LIGADO;					 // O copo � ligado para encher;
			delay(4000); 						//tempo em que o copo enche;
			Glass = DESLIGADO; 		 //Copo cheio;
			Coffee = DESLIGADO; 	//Desliga o pino do caf�;
			P3_2 = 1;						 //Volta ao estado inicial para esperar outra moeda;
		}
}

int main(){
		EA = 1;  //habilita a chave geral das interrup��es;
		EX0 = 1; //habilita a interrup��o 0;
		P0 = DESLIGADO;
		P1 = DESLIGADO;
		while(1){
		 //Esperando moeda;
		}
}