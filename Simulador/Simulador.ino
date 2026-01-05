//c++ code
#include <Arduino.h>
#include <ArduinoJson.h>

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
//Portas do botão de interação
int button = 14; //A0

// Variáveis para controle
int currentCycle = 0;
String currentMode = "noPipeline";
int ledMatrix[4][4] = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
};
String rgbColor = "#0EA5E9"; // Azul padrão
boolean status = 0;

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
    
    Serial.begin(9600); // Comunicação serial
}

//Funções de simulação----------------------------------------------------------------------
//Função de exemplo para clock:
void clock(){
    delay(1000); // 1 segundo
}

//Função para enviar dados em JSON
void sendJSON() {
    StaticJsonDocument<512> doc;
    
    doc["cycle"] = currentCycle;
    doc["mode"] = currentMode;
    doc["rgb"] = rgbColor;
    
    // Adiciona a matriz de LEDs
    JsonArray matrix = doc.createNestedArray("ledMatrix");
    for(int i = 0; i < 4; i++) {
        JsonArray row = matrix.createNestedArray();
        for(int j = 0; j < 4; j++) {
            row.add(ledMatrix[i][j]);
        }
    }
    
    // Adiciona métricas simples
    JsonObject metrics = doc.createNestedObject("metrics");
    metrics["cpi"] = 1.0 + (currentCycle * 0.1);
    metrics["totalCycles"] = currentCycle;
    metrics["stalls"] = 0;
    
    // Serializa e envia
    serializeJson(doc, Serial);
    Serial.println();
}

//Função de simulação do processamento sem pipeline:
void noPipeline(){
    //Status inicial:
    digitalWrite(ledB, HIGH); //liga led azul, status normal;

    //Primeiro programa (linha 1):-----------------------------------------------
    digitalWrite(leds[0][0], HIGH); //liga led
    clock();
    digitalWrite(leds[0][0], LOW); //desliga led

    digitalWrite(leds[0][1], HIGH); //liga led
    clock();
    digitalWrite(leds[0][1], LOW); //desliga led

    digitalWrite(leds[0][2], HIGH); //liga led
    clock();
    digitalWrite(leds[0][2], LOW); //desliga led

    digitalWrite(leds[0][3], HIGH); //liga led
    clock();
    digitalWrite(leds[0][3], LOW); //desliga led

    //Segundo programa (linha 2):-----------------------------------------------
    digitalWrite(leds[1][0], HIGH); //liga led
    clock();
    digitalWrite(leds[1][0], LOW); //desliga led

    digitalWrite(leds[1][1], HIGH); //liga led
    clock();
    digitalWrite(leds[1][1], LOW); //desliga led

    digitalWrite(leds[1][2], HIGH); //liga led
    clock();
    digitalWrite(leds[1][2], LOW); //desliga led

    digitalWrite(leds[1][3], HIGH); //liga led
    clock();
    digitalWrite(leds[1][3], LOW); //desliga led

    //Terceiro programa (linha 3):-----------------------------------------------
    digitalWrite(leds[2][0], HIGH); //liga led
    clock();
    digitalWrite(leds[2][0], LOW); //desliga led

    digitalWrite(leds[2][1], HIGH); //liga led
    clock();
    digitalWrite(leds[2][1], LOW); //desliga led

    digitalWrite(leds[2][2], HIGH); //liga led
    clock();
    digitalWrite(leds[2][2], LOW); //desliga led

    digitalWrite(leds[2][3], HIGH); //liga led
    clock();
    digitalWrite(leds[2][3], LOW); //desliga led

    //Quarto programa (linha 4):-----------------------------------------------
    digitalWrite(leds[3][0], HIGH); //liga led
    clock();
    digitalWrite(leds[3][0], LOW); //desliga led

    digitalWrite(leds[3][1], HIGH); //liga led
    clock();
    digitalWrite(leds[3][1], LOW); //desliga led

    digitalWrite(leds[3][2], HIGH); //liga led
    clock();
    digitalWrite(leds[3][2], LOW); //desliga led

    digitalWrite(leds[3][3], HIGH); //liga led
    clock();
    digitalWrite(leds[3][3], LOW); //desliga led
    
    //Status final:
    digitalWrite(ledB, LOW); //desliga led azul
}

//Função de simulação de funcionamento normal da pipeline:
void normalStatus(){
    //Status inicial:
    digitalWrite(ledB, HIGH); //liga led azul, status normal;

    //Tempo 1: Programa 1 - Busca:
    digitalWrite(leds[0][0], HIGH); //liga led
    clock();
    digitalWrite(leds[0][0], LOW); //desliga led

    //Tempo 2: Programa 1 - Decodifica | Programa 2 - Busca:
    digitalWrite(leds[0][1], HIGH); //liga led
    digitalWrite(leds[1][0], HIGH); //liga led
    clock();
    digitalWrite(leds[0][1], LOW); //desliga led
    digitalWrite(leds[1][0], LOW); //desliga led

    //Tempo 3: Programa 1 - Executa | Programa 2 - Decodifica | Programa 3 - Busca:
    digitalWrite(leds[0][2], HIGH); //liga led
    digitalWrite(leds[1][1], HIGH); //liga led
    digitalWrite(leds[2][0], HIGH); //liga led
    clock();
    digitalWrite(leds[0][2], LOW); //desliga led
    digitalWrite(leds[1][1], LOW); //desliga led
    digitalWrite(leds[2][0], LOW); //desliga led

    //Tempo 4: Programa 1 - Grava | Programa 2 - Executa | Programa 3 - Decodifica | Programa 4 - Busca:
    digitalWrite(leds[0][3], HIGH); //liga led
    digitalWrite(leds[1][2], HIGH); //liga led
    digitalWrite(leds[2][1], HIGH); //liga led
    digitalWrite(leds[3][0], HIGH); //liga led
    clock();
    digitalWrite(leds[0][3], LOW); //desliga led
    digitalWrite(leds[1][2], LOW); //desliga led
    digitalWrite(leds[2][1], LOW); //desliga led
    digitalWrite(leds[3][0], LOW); //desliga led

    //Tempo 5: Programa 1 - Fim | Programa 2 - Grava | Programa 3 - Executa | Programa 4 - Decodifica:
    digitalWrite(leds[1][3], HIGH);
    digitalWrite(leds[2][2], HIGH);
    digitalWrite(leds[3][1], HIGH);
    clock();
    digitalWrite(leds[1][3], LOW);
    digitalWrite(leds[2][2], LOW);
    digitalWrite(leds[3][1], LOW);

    //Tempo 6: Programa 1 - Fim | Programa 2 - Fim | Programa 3 - Grava | Programa 4 - Executa:
    digitalWrite(leds[2][3], HIGH);
    digitalWrite(leds[3][2], HIGH);
    clock();
    digitalWrite(leds[2][3], LOW);
    digitalWrite(leds[3][2], LOW);

    //Tempo 7: Programa 1 - Fim | Programa 2 - Fim | Programa 3 - Fim | Programa 4 - Grava:
    digitalWrite(leds[3][3], HIGH);
    clock();
    digitalWrite(leds[3][3], LOW);

    //Status final:
    digitalWrite(ledB, LOW);
}

//Função de simulação do Hazard estrutural:
void HStructural(){
    //Tempo 1: P1 Busca
    digitalWrite(leds[0][0], HIGH);
    clock();
    digitalWrite(leds[0][0], LOW);

    //Tempo 2: P1 Decodifica | P2 Busca
    digitalWrite(leds[0][1], HIGH);
    digitalWrite(leds[1][0], HIGH);
    clock();
    digitalWrite(leds[1][0], LOW);

    //Tempo 3: Stall — conflito de recurso
    digitalWrite(leds[0][1], HIGH);
    digitalWrite(ledR, HIGH); //LED vermelho indicando STALL
    clock();
    digitalWrite(ledR, LOW);

    //Tempo 4: Agora o recurso liberou
    digitalWrite(leds[0][1], LOW);
    digitalWrite(leds[0][2], HIGH); //P1 Executa
    digitalWrite(leds[1][1], HIGH); //P2 Decodifica
    clock();
    digitalWrite(leds[0][2], LOW);
    digitalWrite(leds[1][1], LOW);
}

//Função de simulação do Hazard de controle:
void HControl(){
    //Tempo 1: P1 Busca
    digitalWrite(leds[0][0], HIGH);
    clock();
    digitalWrite(leds[0][0], LOW);

    //Tempo 2: P1 Decodifica | P2 Busca
    digitalWrite(leds[0][1], HIGH);
    digitalWrite(leds[1][0], HIGH);
    clock();
    digitalWrite(leds[1][0], LOW);

    //Tempo 3: Branch detectado!
    digitalWrite(ledR, HIGH); //Vermelho piscando pra indicar o drama
    clock();
    digitalWrite(ledR, LOW);

    //Flush: descartando as instruções P2
    digitalWrite(leds[1][0], LOW);
    digitalWrite(leds[0][1], LOW);

    //Tempo 4: Recarrega a pipeline no caminho correto
    digitalWrite(leds[0][2], HIGH);
    clock();
    digitalWrite(leds[0][2], LOW);
}

//Função de simulação do Hazard de dados:
void HData(){
    //Tempo 1: P1 Busca
    digitalWrite(leds[0][0], HIGH);
    clock();
    digitalWrite(leds[0][0], LOW);

    //Tempo 2: P1 Decodifica | P2 Busca
    digitalWrite(leds[0][1], HIGH);
    digitalWrite(leds[1][0], HIGH);
    clock();
    digitalWrite(leds[1][0], LOW);

    //Tempo 3: P1 Executa | P2 Decodifica (detecta dependência!)
    digitalWrite(leds[0][2], HIGH);
    digitalWrite(leds[1][1], HIGH);
    clock();

    //Tempo 4: Stall — P2 trava no decode
    digitalWrite(ledR, HIGH); //vermelho avisando
    digitalWrite(leds[1][1], HIGH);
    clock();
    digitalWrite(ledR, LOW);

    //Tempo 5: Forward Resolve
    digitalWrite(leds[1][1], LOW);
    digitalWrite(leds[0][2], LOW);
    digitalWrite(leds[0][3], HIGH); //P1 grava
    digitalWrite(leds[1][2], HIGH); //P2 executa
    clock();
    digitalWrite(leds[0][3], LOW);
    digitalWrite(leds[1][2], LOW);
}

//Função para simulação de uma Branch Prediction estática:
void staticPrediction(){
    //Status inicial:
    digitalWrite(ledB, HIGH); //liga led azul, predição estática ativa

    //Tempo 1: P1 Busca
    digitalWrite(leds[0][0], HIGH);
    clock();
    digitalWrite(leds[0][0], LOW);

    //Tempo 2: P1 Decodifica | P2 Busca
    digitalWrite(leds[0][1], HIGH);
    digitalWrite(leds[1][0], HIGH);
    clock();
    digitalWrite(leds[0][1], LOW);
    digitalWrite(leds[1][0], LOW);

    //Tempo 3: P1 Executa | P2 Decodifica | P3 Busca
    digitalWrite(leds[0][2], HIGH);
    digitalWrite(leds[1][1], HIGH);
    digitalWrite(leds[2][0], HIGH);
    clock();
    digitalWrite(leds[0][2], LOW);
    digitalWrite(leds[1][1], LOW);
    digitalWrite(leds[2][0], LOW);

    //Tempo 4: Predição ACERTA!
    digitalWrite(ledG, HIGH); //LED verde = acertou!
    digitalWrite(leds[0][3], HIGH);
    digitalWrite(leds[1][2], HIGH);
    digitalWrite(leds[2][1], HIGH);
    digitalWrite(leds[3][0], HIGH);
    clock();
    digitalWrite(leds[0][3], LOW);
    digitalWrite(leds[1][2], LOW);
    digitalWrite(leds[2][1], LOW);
    digitalWrite(leds[3][0], LOW);
    digitalWrite(ledG, LOW);

    //Tempo 5: Acertou novamente
    digitalWrite(ledG, HIGH);
    digitalWrite(leds[0][3], HIGH);
    digitalWrite(leds[1][3], HIGH);
    digitalWrite(leds[2][2], HIGH);
    digitalWrite(leds[3][1], HIGH);
    clock();
    digitalWrite(leds[0][3], LOW);
    digitalWrite(leds[1][3], LOW);
    digitalWrite(leds[2][2], LOW);
    digitalWrite(leds[3][1], LOW);
    digitalWrite(ledG, LOW);

    //Tempo 6: PREDIÇÃO ERRA!
    digitalWrite(ledR, HIGH); //LED vermelho = ERROU!
    clock();
    digitalWrite(ledR, LOW);

    //Flush
    digitalWrite(leds[1][2], LOW);
    digitalWrite(leds[2][1], LOW);
    digitalWrite(leds[3][0], LOW);

    //Tempo 7: Recuperação
    digitalWrite(leds[0][3], HIGH);
    clock();
    digitalWrite(leds[0][3], LOW);

    //Status final:
    digitalWrite(ledB, LOW);
}

//Função de simulação de uma Branch Prediction dinâmica com Perceptron:
void dinamicPrediction(){
    //Status inicial:
    digitalWrite(ledB, HIGH); //liga led azul, predição dinâmica ativa

    //Tempo 1: P1 Busca
    digitalWrite(leds[0][0], HIGH);
    clock();
    digitalWrite(leds[0][0], LOW);

    //Tempo 2: P1 Decodifica | P2 Busca
    digitalWrite(leds[0][1], HIGH);
    digitalWrite(leds[1][0], HIGH);
    clock();
    digitalWrite(leds[0][1], LOW);
    digitalWrite(leds[1][0], LOW);

    //Tempo 3: P1 Executa | P2 Decodifica | P3 Busca
    digitalWrite(leds[0][2], HIGH);
    digitalWrite(leds[1][1], HIGH);
    digitalWrite(leds[2][0], HIGH);
    clock();
    digitalWrite(leds[0][2], LOW);
    digitalWrite(leds[1][1], LOW);
    digitalWrite(leds[2][0], LOW);

    //Tempo 4: Predição ACERTA! Perceptron aprendeu
    digitalWrite(ledG, HIGH); //LED verde = acertou!
    digitalWrite(leds[0][3], HIGH);
    digitalWrite(leds[1][2], HIGH);
    digitalWrite(leds[2][1], HIGH);
    digitalWrite(leds[3][0], HIGH);
    clock();
    digitalWrite(leds[0][3], LOW);
    digitalWrite(leds[1][2], LOW);
    digitalWrite(leds[2][1], LOW);
    digitalWrite(leds[3][0], LOW);

    //Tempo 5: Acerta DE NOVO!
    digitalWrite(leds[0][3], HIGH);
    digitalWrite(leds[1][3], HIGH);
    digitalWrite(leds[2][2], HIGH);
    digitalWrite(leds[3][1], HIGH);
    clock();
    digitalWrite(leds[0][3], LOW);
    digitalWrite(leds[1][3], LOW);
    digitalWrite(leds[2][2], LOW);
    digitalWrite(leds[3][1], LOW);

    //Tempo 6: ACERTA MAIS UMA VEZ!
    digitalWrite(leds[1][3], HIGH);
    digitalWrite(leds[2][3], HIGH);
    digitalWrite(leds[3][2], HIGH);
    clock();
    digitalWrite(leds[1][3], LOW);
    digitalWrite(leds[2][3], LOW);
    digitalWrite(leds[3][2], LOW);

    //Tempo 7: Exceção! Perceptron erra
    digitalWrite(ledR, HIGH); //LED vermelho = ERROU (mas é raro!)
    clock();
    digitalWrite(ledR, LOW);

    //Flush
    digitalWrite(leds[2][2], LOW);
    digitalWrite(leds[3][1], LOW);

    //Tempo 8: Recuperação
    digitalWrite(leds[0][3], HIGH);
    clock();
    digitalWrite(leds[0][3], LOW);

    //Tempo 9: Perceptron se ajusta
    digitalWrite(ledG, HIGH); //Verde = aprendeu!
    clock();
    digitalWrite(ledG, LOW);

    //Status final:
    digitalWrite(ledB, LOW);
}

//------------------------------------------------------------------------------------------
void loop(){
    // MODO 1: Sem Pipeline
    currentMode = "noPipeline";
    rgbColor = "#0EA5E9";
    currentCycle = 0;
    status = 0;
    while(!status){
        noPipeline();
        sendJSON();
        currentCycle++;
        status = digitalRead(button);
    }

    // MODO 2: Normal
    currentMode = "normal";
    rgbColor = "#0EA5E9";
    currentCycle = 0;
    status = 0;
    while(!status){
        normalStatus();
        sendJSON();
        currentCycle++;
        status = digitalRead(button);
    }

    // MODO 3: Hazard Estrutural
    currentMode = "structuralHazard";
    rgbColor = "#FCD34D";
    currentCycle = 0;
    status = 0;
    while(!status){
        HStructural();
        sendJSON();
        currentCycle++;
        status = digitalRead(button);
    }

    // MODO 4: Hazard de Dados
    currentMode = "dataHazard";
    rgbColor = "#FCD34D";
    currentCycle = 0;
    status = 0;
    while(!status){
        HData();
        sendJSON();
        currentCycle++;
        status = digitalRead(button);
    }

    // MODO 5: Hazard de Controle
    currentMode = "controlHazard";
    rgbColor = "#EF4444";
    currentCycle = 0;
    status = 0;
    while(!status){
        HControl();
        sendJSON();
        currentCycle++;
        status = digitalRead(button);
    }

    // MODO 6: Predição Estática
    currentMode = "staticPrediction";
    rgbColor = "#3B82F6";
    currentCycle = 0;
    status = 0;
    while(!status){
        staticPrediction();
        sendJSON();
        currentCycle++;
        status = digitalRead(button);
    }

    // MODO 7: Predição Dinâmica
    currentMode = "dynamicPrediction";
    rgbColor = "#3B82F6";
    currentCycle = 0;
    status = 0;
    while(!status){
        dinamicPrediction();
        sendJSON();
        currentCycle++;
        status = digitalRead(button);
    }
}
