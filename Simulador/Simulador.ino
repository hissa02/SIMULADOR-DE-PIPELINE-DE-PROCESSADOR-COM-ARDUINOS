//c++ code
#include <Arduino.h>

//Configuração das portas de entrada--------------------------------------------------------
//Matriz[linhas][colunas]; ex: leds[1][1] = led na porta 0;
int leds[4][4] = {
    {0,1,2,3},
    {4,5,6,7},
    {8,9,10,11},
    {12,13,19,18}
};
//Portas do led RGB
int ledR = 17; //A3
int ledB = 16; //A2
int ledG = 15; //A1
//Portas do botal de interação
int button = 14; //A0

void setup(){
    //Configuração das conecções de entrada e saída do arduíno:
    for(int i = 0 ;i<4; i++){
        for(int j = 0; j<4; j++){
            pinMode(leds[i][j], OUTPUT);
        }
    }
    pinMode(ledR, OUTPUT);
    pinMode(ledB, OUTPUT);
    pinMode(ledG, OUTPUT); 
    pinMode(button, INPUT);
}
//Funções de simulação----------------------------------------------------------------------
//Função de exemplo para clock:
void clock(){
    delay(1000); // 1 segundo
}
//Função de simulação do processamento sem pipeline:
void noPipeline(){
    //Status inicial:
    digitalWrite(ledB, HIGH); //liga led azul, staus normal;

    //Primeiro programa (linha 1):-----------------------------------------------
    digitalWrite(leds[1][1], HIGH); //liga led
    clock();
    digitalWrite(leds[1][1], LOW); //desliga led

    digitalWrite(leds[1][2], HIGH); //liga led
    clock();
    digitalWrite(leds[1][2], LOW); //desliga led

    digitalWrite(leds[1][3], HIGH); //liga led
    clock();
    digitalWrite(leds[1][3], LOW); //desliga led

    digitalWrite(leds[1][4], HIGH); //liga led
    clock();
    digitalWrite(leds[1][4], LOW); //desliga led

    //Segundo programa (linha 2):-----------------------------------------------
    digitalWrite(leds[2][1], HIGH); //liga led
    clock();
    digitalWrite(leds[2][1], LOW); //desliga led

    digitalWrite(leds[2][2], HIGH); //liga led
    clock();
    digitalWrite(leds[2][2], LOW); //desliga led

    digitalWrite(leds[2][3], HIGH); //liga led
    clock();
    digitalWrite(leds[2][3], LOW); //desliga led

    digitalWrite(leds[2][4], HIGH); //liga led
    clock();
    digitalWrite(leds[2][4], LOW); //desliga led

    //Terceiro programa (linha 3):-----------------------------------------------
    digitalWrite(leds[3][1], HIGH); //liga led
    clock();
    digitalWrite(leds[3][1], LOW); //desliga led

    digitalWrite(leds[3][2], HIGH); //liga led
    clock();
    digitalWrite(leds[3][2], LOW); //desliga led

    digitalWrite(leds[3][3], HIGH); //liga led
    clock();
    digitalWrite(leds[3][3], LOW); //desliga led

    digitalWrite(leds[3][4], HIGH); //liga led
    clock();
    digitalWrite(leds[3][4], LOW); //desliga led

    //Quarto programa (linha 4):-----------------------------------------------
    digitalWrite(leds[4][1], HIGH); //liga led
    clock();
    digitalWrite(leds[4][1], LOW); //desliga led

    digitalWrite(leds[4][2], HIGH); //liga led
    clock();
    digitalWrite(leds[4][2], LOW); //desliga led

    digitalWrite(leds[4][3], HIGH); //liga led
    clock();
    digitalWrite(leds[4][3], LOW); //desliga led

    digitalWrite(leds[4][4], HIGH); //liga led
    clock();
    digitalWrite(leds[4][4], LOW); //desliga led
    
    //Status final:
    digitalWrite(ledB, LOW); //desliga led azul

}
//Função de simulação de funcionamento normal da pipe line:
void normalStatus(){
    //Status inicial:
    digitalWrite(ledB, HIGH); //liga led azul, status normal;

    //Tempo 1: Programa 1 - Busca:
    digitalWrite(leds[1][1], HIGH); //liga led
    clock();
    digitalWrite(leds[1][1], LOW); //desliga led

    //Tempo 2: Programa 1 - Decodifica | Programa 2 - Busca:
    digitalWrite(leds[1][2], HIGH); //liga led
    digitalWrite(leds[2][1], HIGH); //liga led
    clock();
    digitalWrite(leds[1][2], LOW); //desliga led
    digitalWrite(leds[2][1], LOW); //desliga led

    //Tempo 3: Programa 1 - Executa | Programa 2 - Decodifica | Programa 3 - Busca:
    digitalWrite(leds[1][3], HIGH); //liga led
    digitalWrite(leds[2][2], HIGH); //liga led
    digitalWrite(leds[3][1], HIGH); //liga led
    clock();
    digitalWrite(leds[1][3], LOW); //desliga led
    digitalWrite(leds[2][2], LOW); //desliga led
    digitalWrite(leds[3][1], LOW); //desliga led

    //Tempo 4: Programa 1 - Grava | Programa 2 - Executa | Programa 3 - Decodifica | Programa 4 - Busca:
    digitalWrite(leds[1][4], HIGH); //liga led
    digitalWrite(leds[2][3], HIGH); //liga led
    digitalWrite(leds[3][2], HIGH); //liga led
    digitalWrite(leds[4][1], HIGH); //liga led
    clock();
    digitalWrite(leds[1][4], LOW); //desliga led
    digitalWrite(leds[2][3], LOW); //desliga led
    digitalWrite(leds[3][2], LOW); //desliga led
    digitalWrite(leds[4][1], LOW); //desliga led

    //Tempo 5: Programa 1 - Fim | Programa 2 - Grava | Programa 3 - Executa | Programa 4 - Decodifica:
    digitalWrite(leds[2][3], HIGH);
    digitalWrite(leds[3][2], HIGH);
    digitalWrite(leds[4][1], HIGH);
    clock();
    digitalWrite(leds[2][3], LOW);
    digitalWrite(leds[3][2], LOW);
    digitalWrite(leds[4][1], LOW);

    //Tempo 6: Programa 1 - Fim | Programa 2 - Fim | Programa 3 - Grava | Programa 4 - Executa:
    digitalWrite(leds[3][3], HIGH);
    digitalWrite(leds[4][2], HIGH);
    clock();
    digitalWrite(leds[3][3], LOW);
    digitalWrite(leds[4][2], LOW);

    //Tempo 7: Programa 1 - Fim | Programa 2 - Fim | Programa 3 - Fim | Programa 4 - Grava:
    digitalWrite(leds[4][3], HIGH);
    clock();
    digitalWrite(leds[4][3], LOW);

    //Status final:
    digitalWrite(ledB, LOW);
}
//Função de simulação do Hazard estrutural:
void HStructural(){
    
}
//Função de simulação do Hazard de controle:
void HControl(){
    
}
//Função de simulação do Hazard de dados:
void HData(){
    
}
//Função para simulação de uma Branch Prediction estática:
void staticPrediction(){

}
//Função de simulação de uma Branch Prediction dinâmica com Percéptron:
void dinamicPrediction(){
    
}
//------------------------------------------------------------------------------------------
boolean status = 0;
void loop(){
    //Chamar as funções em tempos específicos com base na sequência de apresentação:
    //Implementar botão para alternar interagir sobre a seleção das funções de forma prática;
    //sequencia: normal > HStructural > HData > HControl > staticPrediction > dinamicPrediction

    while(!status){ //ideia de aplicação do botão
        noPipeline();
        status = digitalRead(button);
    }

    while(!status){ //ideia de aplicação do botão
        normalStatus();
        status = digitalRead(button);
    }

    status = 0;
    while(!status){ 
        HStructural();
        status = digitalRead(button);
    }

    status = 0;
    while(!status){
        HData();
        status = digitalRead(button);
    }

    status = 0;
    while(!status){
        HControl();
        status = digitalRead(button);
    }

    status = 0;
    while(!status){
        staticPrediction();
        status = digitalRead(button);
    }

    status = 0; 
    while(!status){
        dinamicPrediction();
        status = digitalRead(button);
    }

    return;
}