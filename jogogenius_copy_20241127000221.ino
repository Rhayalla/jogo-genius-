// pinos dos LEDs 
int leds[4] = {9,8,7,6};
// pinos dos botoes
int botoes[4] = {2,3,4,5};
//Pinos do display 
int leds_display[7]={10,11,12,13,A0,A1,A2};
// variáveis do jogo
int sequencia[10];
int nivel = 0;
int estadoBotao;
int comparaSequencia = 0;
int estadoPartida = true;
bool jogadorPerdeu = false;

void setup(){
//definindo que os pinos dos leds são saídas
  pinMode(leds[3],OUTPUT);
  pinMode(leds[2],OUTPUT);
  pinMode(leds[1],OUTPUT);
  pinMode(leds[0],OUTPUT); 
//definindo que os pinos dos botoes são entradas
  pinMode(botoes[3],INPUT_PULLUP);
  pinMode(botoes[2],INPUT_PULLUP);
  pinMode(botoes[1],INPUT_PULLUP);
  pinMode(botoes[0],INPUT_PULLUP);
  
  
  inicioJogo();
  
  Serial.begin(9600);
}
void loop(){
  
  proximoNivel();
  reproduzirSequencia();
  jogador();
  delay(1000);
  
  if(jogadorPerdeu == true){
    sequencia[10]={};
    nivel = 0;
    jogadorPerdeu = false;
  }
  
  delay(1000);
}  
//criterio 2: ascender e apagar em ordem especifica
 void inicioJogo() {

  for(int i=0; i<3; i++) 
  {
    digitalWrite(9,HIGH);
    digitalWrite(8,LOW);
    digitalWrite(7,LOW);
    digitalWrite(6,LOW);
    delay(300);
    
    digitalWrite(9,LOW);
    digitalWrite(8,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(6,LOW);
    delay(300);
    
    digitalWrite(9,LOW);
    digitalWrite(8,LOW);
    digitalWrite(7,HIGH);
    digitalWrite(6,LOW);
    delay(300);
    
    digitalWrite(9,LOW);
    digitalWrite(8,LOW);
    digitalWrite(7,LOW);
    digitalWrite(6,HIGH);
    delay(300);
    digitalWrite(6,LOW);
  }
  delay(1000);
 }
//gerar o nivel do jogo e progredi-lo  
void proximoNivel() 
{
  if(nivel <= sequencia[10]){
    int numAleatorio = random(4);
    sequencia[nivel] = numAleatorio;
    nivel = nivel + 1;
  }
}
//acender os leds de acordo com o nivel
 void reproduzirSequencia()
  {
    for(int i=0; i < nivel; i++){
      digitalWrite(leds[sequencia[i]],HIGH);
      delay(500);
      digitalWrite(leds[sequencia[i]],LOW);
      delay(500);
    }
  }
//confere se o jogador realizou alguma ação 
 bool jogador() {
  for (int i = 0; i < nivel; i++) {
    bool jogou = false;
   	 while (!jogou) {
      for (int i = 0; i < 4; i++) {
        if (digitalRead(botoes[i]) == HIGH) {
          estadoBotao = i;
           if(botoes[estadoBotao] == sequencia[i])
           {
            digitalWrite(leds[i], HIGH);
          	delay(500);
          	digitalWrite(leds[i], LOW);
          	delay(500);
         }
          
          jogou = false;
        }
      }
    }
    if (sequencia[comparaSequencia] != estadoBotao) {
      estadoPartida = false;
      break;
    }
    comparaSequencia++;
  }
  comparaSequencia = 0;
  return estadoPartida;
}
  
