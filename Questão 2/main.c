#include <at89x52.h>
#define Esteira_produto P1_0
#define Esteira_caixa P1_6
#define AndaEsteira_caixa P1_7
#define ParaEsteira_produto P1_1
const LIGADO = 1;
const DESLIGADO = 0;
int contador = 0;

void caixaCheiaInterrupt() interrupt 1{
	TR0 = 0; //pausa timer para recarregar (Timer Stop)
	TH0 = 0x3C; //recarrega o timer com o valor inicial de 
	TL0 = 0xAF; //15.535 
	TR0 = 1; //ativa timer para contar (Timer RUN)
	contador++;
	if(contador == 2500){ //Quando o contador for igual a 600, a caixa estará cheia então ocorre a parada da Esteira_Produto
		ParaEsteira_produto = LIGADO; // Esteira do produto para, para a Esteira da caixa andar e a caixa trocar
		AndaEsteira_caixa = LIGADO; // Esteira da caixa anda para trocar a caixa
		Esteira_produto = DESLIGADO; //Pino sinalizador da esteira produto em movimento é desligado;
		Esteira_caixa = DESLIGADO; //Pino sinalizador da esteira caixa parada é desligado;
	}else if(contador == 5000){
		ParaEsteira_produto = DESLIGADO; // Agora que a caixa já andou e a Esteira do produto pode andar, desligamos esse pino;
		AndaEsteira_caixa = DESLIGADO; // Agora que a caixa já andou desligamos esse pino;
		Esteira_produto = LIGADO; // Pino sinalizador de Esteira produto em movimento é ligado novamente;
		Esteira_caixa = LIGADO; // Pino sinalizador de Esteira da caixa parada é ligado;
		contador = 0; //zerando o contador para reiniciar a contagem de produtos na caixa;
	}
}

int main(){
		EA = 1; 
		ET0 = 1;
		TMOD = 1; 
		TR0 = 1;
		P1 = DESLIGADO; //Desligando todos os pinos da porta P1, para ficar visivel a operação nas portas;
		Esteira_produto = LIGADO; //Pino Sinalizador de esteira produto em movimento é ativado;
		Esteira_caixa   = LIGADO; //Pino Sinalizador de esteira caixa parada é ativado;
		while(1){
		}
}