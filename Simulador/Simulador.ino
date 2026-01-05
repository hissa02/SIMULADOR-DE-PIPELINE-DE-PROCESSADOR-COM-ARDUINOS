#include <Arduino.h>

//Configuração das portas de entrada--------------------------------------------------------
//Matriz[linhas][colunas]; ex: leds[0][0] = primeiro led
int leds[4][4] = {
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {8, 9, 10, 11},
    {12, 13, 19, 18}
};

//Portas do led RGB
int ledR = 17; //A3
int ledG = 16; //A2
int ledB = 15; //A1
//LED amarelo = vermelho + verde
//Porta lógica, não física

//Porta do botão de interação
int button = 14; //A0

//------------------------------------------------------------------------------------------
//Enumeração dos estados da simulação (máquina de estados)
enum PipelineState {
    NO_PIPELINE,
    PIPELINE_NORMAL,
    HAZARD_STRUCTURAL,
    HAZARD_DATA,
    HAZARD_CONTROL,
    STATIC_PREDICTION,
    DYNAMIC_PREDICTION
};

PipelineState currentState = NO_PIPELINE;

//Controle do botão
bool lastButtonState = LOW;

//------------------------------------------------------------------------------------------
void setup() {
    //Configuração das conexões de entrada e saída do arduíno:
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            pinMode(leds[i][j], OUTPUT);
        }
    }

    pinMode(ledR, OUTPUT);
    pinMode(ledB, OUTPUT);
    pinMode(ledG, OUTPUT);
    pinMode(button, INPUT);
}

//------------------------------------------------------------------------------------------
//Funções auxiliares

void clock() {
    delay(1000); //1 segundo por ciclo de clock
}

void clearAllLeds() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            digitalWrite(leds[i][j], LOW);
        }
    }
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, LOW);
    digitalWrite(ledB, LOW);
}

bool decisionWindow() {
    for (int i = 0; i < 3; i++) {

        // LED ON
        digitalWrite(ledG, HIGH);
        delay(500);

        // Se apertar, avança
        if (digitalRead(button) == HIGH) {
            digitalWrite(ledG, LOW);
            return true;
        }

        // LED OFF
        digitalWrite(ledG, LOW);
        delay(500);

        // Se apertar, avança
        if (digitalRead(button) == HIGH) {
            return true;
        }
    }

    // Se passou o tempo todo sem apertar
    return false;
}


//------------------------------------------------------------------------------------------
//Funções de simulação----------------------------------------------------------------------

//Simulação sem pipeline
void noPipeline(){
    // Status inicial: azul ligado
    digitalWrite(ledB, HIGH);

    // Para cada programa (linha)
    for(int prog = 0; prog < 4; prog++){

        // Busca
        digitalWrite(leds[prog][0], HIGH);
        clock();
        digitalWrite(leds[prog][0], LOW);

        // Decodifica
        digitalWrite(leds[prog][1], HIGH);
        clock();
        digitalWrite(leds[prog][1], LOW);

        // Executa
        digitalWrite(leds[prog][2], HIGH);
        clock();
        digitalWrite(leds[prog][2], LOW);

        // Grava
        digitalWrite(leds[prog][3], HIGH);
        clock();
        digitalWrite(leds[prog][3], LOW);
    }

    // Status final
    digitalWrite(ledB, LOW);
}
//Função de simulação de funcionamento normal da pipe line:
void normalStatus(){
    // Status inicial: pipeline saudável (LED azul ligado)
    digitalWrite(ledB, HIGH);

    // ------------------ CICLO 1 ------------------
    // P1: Busca
    digitalWrite(leds[0][0], HIGH);
    clock();
    digitalWrite(leds[0][0], LOW);

    // ------------------ CICLO 2 ------------------
    // P1: Decodifica | P2: Busca
    digitalWrite(leds[0][1], HIGH);
    digitalWrite(leds[1][0], HIGH);
    clock();
    digitalWrite(leds[0][1], LOW);
    digitalWrite(leds[1][0], LOW);

    // ------------------ CICLO 3 ------------------
    // P1: Executa | P2: Decodifica | P3: Busca
    digitalWrite(leds[0][2], HIGH);
    digitalWrite(leds[1][1], HIGH);
    digitalWrite(leds[2][0], HIGH);
    clock();
    digitalWrite(leds[0][2], LOW);
    digitalWrite(leds[1][1], LOW);
    digitalWrite(leds[2][0], LOW);

    // ------------------ CICLO 4 ------------------
    // P1: Grava | P2: Executa | P3: Decodifica | P4: Busca
    digitalWrite(leds[0][3], HIGH);
    digitalWrite(leds[1][2], HIGH);
    digitalWrite(leds[2][1], HIGH);
    digitalWrite(leds[3][0], HIGH);
    clock();
    digitalWrite(leds[0][3], LOW);
    digitalWrite(leds[1][2], LOW);
    digitalWrite(leds[2][1], LOW);
    digitalWrite(leds[3][0], LOW);

    // ------------------ CICLO 5 ------------------
    // P2: Grava | P3: Executa | P4: Decodifica
    digitalWrite(leds[1][3], HIGH);
    digitalWrite(leds[2][2], HIGH);
    digitalWrite(leds[3][1], HIGH);
    clock();
    digitalWrite(leds[1][3], LOW);
    digitalWrite(leds[2][2], LOW);
    digitalWrite(leds[3][1], LOW);

    // ------------------ CICLO 6 ------------------
    // P3: Grava | P4: Executa
    digitalWrite(leds[2][3], HIGH);
    digitalWrite(leds[3][2], HIGH);
    clock();
    digitalWrite(leds[2][3], LOW);
    digitalWrite(leds[3][2], LOW);

    // ------------------ CICLO 7 ------------------
    // P4: Grava
    digitalWrite(leds[3][3], HIGH);
    clock();
    digitalWrite(leds[3][3], LOW);

    // Status final: pipeline finalizado
    digitalWrite(ledB, LOW);
}
// Função de simulação do Hazard Estrutural
void HStructural(){

    // ---------------- STATUS INICIAL ----------------
    // Pipeline funcionando normalmente
    digitalWrite(ledB, HIGH); // azul = tudo ok

    // ---------------- CICLO 1 ----------------
    // P1: Busca
    digitalWrite(leds[0][0], HIGH);
    clock();
    digitalWrite(leds[0][0], LOW);

    // ---------------- CICLO 2 ----------------
    // P1: Decodifica | P2: Busca
    digitalWrite(leds[0][1], HIGH);
    digitalWrite(leds[1][0], HIGH);
    clock();
    digitalWrite(leds[0][1], LOW);
    digitalWrite(leds[1][0], LOW);

    // ---------------- CICLO 3 ----------------
    // P1: Executa | P2: Decodifica | P3: Busca
    digitalWrite(leds[0][2], HIGH);
    digitalWrite(leds[1][1], HIGH);
    digitalWrite(leds[2][0], HIGH);
    clock();
    digitalWrite(leds[0][2], LOW);
    digitalWrite(leds[1][1], LOW);
    digitalWrite(leds[2][0], LOW);

    // ---------------- CICLO 4 ----------------
    // P1: Write Back | P2: Executa | P3: Decodifica | P4: Busca
    digitalWrite(leds[0][3], HIGH);
    digitalWrite(leds[1][2], HIGH);
    digitalWrite(leds[2][1], HIGH);
    digitalWrite(leds[3][0], HIGH);
    clock();
    digitalWrite(leds[1][2], LOW);
    digitalWrite(leds[2][1], LOW);
    digitalWrite(leds[3][0], LOW);

    // ---------------- HAZARD ESTRUTURAL ----------------
    // Recurso ocupado no Write Back → pipeline inteiro em STALL
    digitalWrite(ledB, LOW); // sai do estado normal

    for(int i = 0; i < 3; i++){ // 3 ciclos de stall

        // P1 continua preso no Write Back
        digitalWrite(leds[0][3], HIGH);

        // LED amarelo piscando = perigo estrutural
        digitalWrite(ledR, HIGH);
        digitalWrite(ledG, HIGH);

        clock();

        // Pisca tudo
        digitalWrite(leds[0][3], LOW);
        digitalWrite(ledR, LOW);
        digitalWrite(ledG, LOW);

        clock();
    }

    // ---------------- PIPELINE RETOMA ----------------
    digitalWrite(ledB, HIGH); // azul = normal novamente

    // CICLO APÓS STALL
    // P2: Write Back | P3: Executa | P4: Decodifica
    digitalWrite(leds[1][3], HIGH);
    digitalWrite(leds[2][2], HIGH);
    digitalWrite(leds[3][1], HIGH);
    clock();
    digitalWrite(leds[1][3], LOW);
    digitalWrite(leds[2][2], LOW);
    digitalWrite(leds[3][1], LOW);

    // CICLO FINAL
    // P3: Write Back | P4: Executa
    digitalWrite(leds[2][3], HIGH);
    digitalWrite(leds[3][2], HIGH);
    clock();
    digitalWrite(leds[2][3], LOW);
    digitalWrite(leds[3][2], LOW);

    // Último
    digitalWrite(leds[3][3], HIGH);
    clock();
    digitalWrite(leds[3][3], LOW);

    // Status final
    digitalWrite(ledB, LOW);
}

void HData() {

    // STATUS NORMAL
    digitalWrite(ledB, HIGH);

    // Tempo 1: P1 Busca
    digitalWrite(leds[0][0], HIGH);
    clock();
    digitalWrite(leds[0][0], LOW);

    // Tempo 2: P1 Decodifica | P2 Busca
    digitalWrite(leds[0][1], HIGH);
    digitalWrite(leds[1][0], HIGH);
    clock();
    digitalWrite(leds[0][1], LOW);
    digitalWrite(leds[1][0], LOW);

    // Tempo 3: P1 Executa | P2 Decodifica
    digitalWrite(leds[0][2], HIGH);
    digitalWrite(leds[1][1], HIGH);
    clock();
    digitalWrite(leds[0][2], LOW);
    digitalWrite(leds[1][1], LOW);

    // Tempo 4: P1 Write Back | P2 Executa (AQUI NASCE O HAZARD)
    digitalWrite(ledB, LOW);      // sai do normal
    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, HIGH);     // atenção

    for (int i = 0; i < 3; i++) { // 3 ciclos de STALL

        // Pisca os LEDs problemáticos
        digitalWrite(leds[0][3], HIGH); // P1 em Write Back
        digitalWrite(leds[1][2], HIGH); // P2 em Execução
        digitalWrite(ledR, HIGH);
        digitalWrite(ledG, HIGH);

        clock();

        digitalWrite(leds[0][3], LOW);
        digitalWrite(leds[1][2], LOW);
        digitalWrite(ledR, LOW);
        digitalWrite(ledG, LOW);

        clock();
    }

    // Hazard resolvido
    digitalWrite(ledB, HIGH);

    // Continuação normal do pipeline
    digitalWrite(leds[1][2], LOW); // libera execução do P2
    digitalWrite(leds[1][3], HIGH); // P2 Write Back
    clock();
    digitalWrite(leds[1][3], LOW);

    digitalWrite(ledB, LOW);
}

void HControl() {

    // ================= PIPELINE NORMAL ATÉ P3 EXEC =================
    digitalWrite(ledB, HIGH); // status azul

    // Ciclo 1
    digitalWrite(leds[0][0], HIGH); // P1 IF
    clock();
    digitalWrite(leds[0][0], LOW);

    // Ciclo 2
    digitalWrite(leds[0][1], HIGH); // P1 ID
    digitalWrite(leds[1][0], HIGH); // P2 IF
    clock();
    digitalWrite(leds[0][1], LOW);
    digitalWrite(leds[1][0], LOW);

    // Ciclo 3
    digitalWrite(leds[0][2], HIGH); // P1 EX
    digitalWrite(leds[1][1], HIGH); // P2 ID
    digitalWrite(leds[2][0], HIGH); // P3 IF
    clock();
    digitalWrite(leds[0][2], LOW);
    digitalWrite(leds[1][1], LOW);
    digitalWrite(leds[2][0], LOW);

    // Ciclo 4
    digitalWrite(leds[0][3], HIGH); // P1 WB
    digitalWrite(leds[1][2], HIGH); // P2 EX
    digitalWrite(leds[2][1], HIGH); // P3 ID
    digitalWrite(leds[3][0], HIGH); // P4 IF
    clock();
    digitalWrite(leds[0][3], LOW); // P1 finalizou
    digitalWrite(leds[1][2], LOW);
    digitalWrite(leds[2][1], LOW);
    digitalWrite(leds[3][0], LOW);

    // ================= HAZARD DE CONTROLE =================
    // Situação congelada:
    // P2 em WB
    // P3 em EX (branch)
    // P4 em ID

    digitalWrite(ledB, LOW); // sai do normal

    digitalWrite(leds[1][3], HIGH); // P2 WB
    digitalWrite(leds[3][1], HIGH); // P4 ID

    for (int i = 0; i < 3; i++) {
        // P3 EXEC piscando
        digitalWrite(leds[2][2], HIGH);

        // STATUS AMARELO
        digitalWrite(ledR, HIGH);
        digitalWrite(ledG, HIGH);

        clock();

        digitalWrite(leds[2][2], LOW);
        digitalWrite(ledR, LOW);
        digitalWrite(ledG, LOW);

        clock();
    }

    // ================= BRANCH ERRADO =================
    // P3 vai para WB
    // P4 fica esperando em EXEC

    digitalWrite(leds[1][3], LOW); // P2 finaliza
    digitalWrite(leds[3][1], LOW);

    digitalWrite(leds[3][2], HIGH); // P4 EX

    for (int i = 0; i < 3; i++) {
        digitalWrite(leds[2][3], HIGH); // P3 WB
        digitalWrite(ledR, HIGH);       // status vermelho

        clock();

        digitalWrite(leds[2][3], LOW);
        digitalWrite(ledR, LOW);

        clock();
    }

    digitalWrite(leds[3][2], LOW);

    // ================= FLUSH =================
    for (int p = 0; p < 4; p++) {
        for (int e = 0; e < 4; e++) {
            digitalWrite(leds[p][e], HIGH);
        }
    }
    clock();

    for (int p = 0; p < 4; p++) {
        for (int e = 0; e < 4; e++) {
            digitalWrite(leds[p][e], LOW);
        }
    }

    // ================= PIPELINE NORMAL NOVAMENTE =================
    digitalWrite(ledB, HIGH);

    digitalWrite(leds[0][0], HIGH);
    clock();
    digitalWrite(leds[0][0], LOW);digitalWrite(ledB, HIGH);

    // ------------------ CICLO 1 ------------------
    // P1: Busca
    digitalWrite(leds[0][0], HIGH);
    clock();
    digitalWrite(leds[0][0], LOW);

    // ------------------ CICLO 2 ------------------
    // P1: Decodifica | P2: Busca
    digitalWrite(leds[0][1], HIGH);
    digitalWrite(leds[1][0], HIGH);
    clock();
    digitalWrite(leds[0][1], LOW);
    digitalWrite(leds[1][0], LOW);

    // ------------------ CICLO 3 ------------------
    // P1: Executa | P2: Decodifica | P3: Busca
    digitalWrite(leds[0][2], HIGH);
    digitalWrite(leds[1][1], HIGH);
    digitalWrite(leds[2][0], HIGH);
    clock();
    digitalWrite(leds[0][2], LOW);
    digitalWrite(leds[1][1], LOW);
    digitalWrite(leds[2][0], LOW);

    // ------------------ CICLO 4 ------------------
    // P1: Grava | P2: Executa | P3: Decodifica | P4: Busca
    digitalWrite(leds[0][3], HIGH);
    digitalWrite(leds[1][2], HIGH);
    digitalWrite(leds[2][1], HIGH);
    digitalWrite(leds[3][0], HIGH);
    clock();
    digitalWrite(leds[0][3], LOW);
    digitalWrite(leds[1][2], LOW);
    digitalWrite(leds[2][1], LOW);
    digitalWrite(leds[3][0], LOW);

    // ------------------ CICLO 5 ------------------
    // P2: Grava | P3: Executa | P4: Decodifica
    digitalWrite(leds[1][3], HIGH);
    digitalWrite(leds[2][2], HIGH);
    digitalWrite(leds[3][1], HIGH);
    clock();
    digitalWrite(leds[1][3], LOW);
    digitalWrite(leds[2][2], LOW);
    digitalWrite(leds[3][1], LOW);

    // ------------------ CICLO 6 ------------------
    // P3: Grava | P4: Executa
    digitalWrite(leds[2][3], HIGH);
    digitalWrite(leds[3][2], HIGH);
    clock();
    digitalWrite(leds[2][3], LOW);
    digitalWrite(leds[3][2], LOW);

    // ------------------ CICLO 7 ------------------
    // P4: Grava
    digitalWrite(leds[3][3], HIGH);
    clock();
    digitalWrite(leds[3][3], LOW);

    // Status final: pipeline finalizado
    digitalWrite(ledB, LOW);
}

//Função para simulação de uma Branch Prediction estática:
void staticPrediction(){

}
//Função de simulação de uma Branch Prediction dinâmica com Percéptron:
void dinamicPrediction(){
    
}

//------------------------------------------------------------------------------------------
void loop() {
    bool buttonState = digitalRead(button);

    //Detecção de borda de subida (clique)
    if (decisionWindow()) {
        currentState = (PipelineState)((currentState + 1) % 7);
        clearAllLeds();
    }

    lastButtonState = buttonState;

    //Executa o estado atual
    switch (currentState) {
        case NO_PIPELINE:
            noPipeline();
            break;

        case PIPELINE_NORMAL:
            normalStatus();
            break;

        case HAZARD_STRUCTURAL:
            HStructural();
            break;

        case HAZARD_DATA:
            HData();
            break;

        case HAZARD_CONTROL:
            HControl();
            break;

        case STATIC_PREDICTION:
            staticPrediction();
            break;

        case DYNAMIC_PREDICTION:
            dinamicPrediction();
            break;
    }
}
