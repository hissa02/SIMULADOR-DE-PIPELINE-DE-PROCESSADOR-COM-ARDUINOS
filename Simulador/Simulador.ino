//c++ code
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
    delay(2000);
}
//Função de simulação de funcionamento normal da pipe line:
void normalStatus(){
    
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
void loop(){
    //Chamar as funções em tempos específicos com base na sequência de apresentação:
    //Implementar botão para alternar interagir sobre a seleção das funções de forma prática;
    //sequencia: normal > HStructural > HData > HControl > staticPrediction > dinamicPrediction

    while(button == 0){ //ideia de aplicação do botão
        normalStatus();
    }
    button = 0;
    while(button == 0){ //ideia de aplicação do botão
        HStructural();
    }
    button = 0;
    while(button == 0){ //ideia de aplicação do botão
        HData();
    }
    button = 0;
    while(button == 0){ //ideia de aplicação do botão
        HControl();
    }
    button = 0;
    while(button == 0){ //ideia de aplicação do botão
        staticPrediction();
    }
    button = 0; 
    while(button == 0){ //ideia de aplicação do botão
        dinamicPrediction();
    }    
}