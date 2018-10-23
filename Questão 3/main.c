#include <at89x52.h>

#define camera1 P1_0
#define camera2 P1_1
#define camera3 P1_2
#define camera4 P1_3
#define sala1 P0_0
#define sala2 P0_1
#define sala3 P0_2
#define sala4 P0_3
 
const LIGADO = 1;
const DESLIGADO = 0;
int contador = 0;

void alarme() interrupt 0{
	if(sala1 == 1 || sala2 == 1 || sala3 == 1 || sala4 == 1 ){
			P3_1 = ~P3_1;
			P3_3 = ~P3_3;
			P3_3 = ~P3_4;
			P3_5 = ~P3_5;
			P3_6 = ~P3_6;
			P3_7 = ~P3_7;
	}
}

void pauseVCR(){
	while(sala1 == 0 && sala2 == 0 && sala3 == 0 && sala4 == 0){ //verifica se existe alguém em alguma das alas;
		camera1 = DESLIGADO;
		camera2 = DESLIGADO;
		camera3 = DESLIGADO;
		camera4 = DESLIGADO;
		contador = 0;
		if(sala1 == 1 && sala2 == 0 && sala3 == 0 && sala4 == 0){
			contador = 60;	//alguém foi detectado na camera 1, pule para la;
			break;
		}
		else if(sala1 == 0 && sala2 == 1 && sala3 == 0 && sala4 == 0){
			contador = 120; //alguém foi detectado na camera 2, pule para la;
			break;
		}
		else if(sala1 == 0 && sala2 == 0 && sala3 == 1 && sala4 == 0){
			contador = 180; //alguém foi detectado na camera 3, pule para la;
			break;
		}
		else if(sala1 == 0 && sala2 == 0 && sala3 == 0 && sala4 == 1){
			contador = 220; //alguém foi detectado na camera 4, pule para la;
			break;
		}
	}
}

void caixaCheiaInterrupt() interrupt 1{
	TR0 = 0; //pausa timer para recarregar (Timer Stop)
	TH0 = 0x3C; //recarrega o timer com o valor inicial de 
	TL0 = 0xAF; //15.535 
	TR0 = 1; //ativa timer para contar (Timer RUN)
	
	if(contador == 60){ //se passou 50ms x 60 = 3 segundos
		camera1 = LIGADO; //Liga a camera um e desliga as outras
		camera2 = DESLIGADO;
		camera3 = DESLIGADO;
		camera4 = DESLIGADO;
		
	}else if(contador == 120){ //se passou 50ms x 120 = 6 segundos
		camera2 = LIGADO; //liga camera dois e desliga as outras
		camera1 = DESLIGADO;
		camera3 = DESLIGADO;
		camera4 = DESLIGADO;
	} else if(contador == 180){ //se passou 50ms x 180 = 9 segundos
		camera3 = LIGADO; //liga a camera tres e desliga as outras
		camera1 = DESLIGADO;
		camera2 = DESLIGADO;
		camera4 = DESLIGADO;
	}else if(contador == 240){ //se passou 50ms x 240 = 12 segundos
		camera4 = LIGADO; //liga a camera quatro e desliga as outras
		camera1 = DESLIGADO;
		camera2 = DESLIGADO;
		camera3 = DESLIGADO;
		contador = 0;
	}
	contador++;
	//verificação se há alguém ou não na sala
	pauseVCR();
}

int main(){
		EA = 1;
		EX0 = 1;
		ET0 = 1;
		TMOD = 1; 
		TR0 = 1;
		P1 = DESLIGADO;
		while(1){
		}
		
}