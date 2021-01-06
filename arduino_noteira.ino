

// DEFINIÇÕES
#define pinNoteiro 2
#define pinMoedas 3
#define pinSaida 8

// DECLARAÇÃO DE VARIÁVEIS GLOBAIS
int creditoInserido = 0;
int contador_pulso = 0;
int resto_contador = 0;
unsigned long espera_rodar_noteira=3000;
unsigned long tempoAtual = millis();
unsigned long tempoInicial =0;
///////////////VARIÁVEIS
void setup() {
  Serial.begin(9600); 
  pinMode(pinNoteiro, INPUT);
  pinMode (pinMoedas, INPUT_PULLUP);
  pinMode(pinSaida, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pinNoteiro), leituraNoteiro, RISING);
  attachInterrupt(digitalPinToInterrupt(pinMoedas), leituraMoedinhas, RISING);
}
//*****************SETUP***********//

void leituraNoteiro()
{
  contador_pulso++;
  tempoInicial = millis();
  Serial.println("a interrupção funcionou! "); //APAGAR NO PROGRAMA EM PRODUÇÃO
  Serial.println (tempoInicial);
}

void leituraMoedinhas()
{
   Serial.println("MOEDINHAS EM HIGH, é para estar em LOW"); //APAGAR NO PROGRAMA EM PRODUÇÃO
   contador_pulso++;
   tempoInicial = millis();
   delay(700);
}
void loop (){
  //delay (5000);
  if(millis() - tempoInicial  > espera_rodar_noteira)
 { Serial.println ( tempoInicial);
   Serial.println (millis());
   tempoInicial = millis();
  if (contador_pulso > 1)
  {
    resto_contador = contador_pulso % 2;
    if (resto_contador ==0)
      {
       delay (100);
       for  ( int i = 0; i < contador_pulso/2; i = i+1) 
       {  
          digitalWrite(pinSaida, HIGH);
          Serial.println("5 REAIS COMPUTADOS");
          delay(500);
          Serial.println("agora é para desligar o led");
          digitalWrite(pinSaida, LOW);
          delay (500);
          resto_contador=0;
       }
       Serial.println("CONTADOR DE PULSO =0");  
       contador_pulso=0;
      }
    if (resto_contador >0)
      {
         delay (100);
         for  ( int i = 0; i < contador_pulso/2; i = i+1) 
        { 
         digitalWrite(pinSaida, HIGH);
         Serial.println("CREDITOU MOEDINHAS");
         delay(500);
         Serial.println("agora é para desligar o led");
         digitalWrite(pinSaida, LOW);
         delay (500);
         resto_contador = 0;
       }
     delay (500);
     contador_pulso = 1;
       Serial.println ("saiu do delay de 5 Segundos ");
      }
      
  }
 // tempoInicial = millis();
  }
  /*while (digitalRead(pinNoteiro) == LOW )
   { 
     Serial.println("NOTEIRA em LOW");
     contador_pulso++;
     delay(11);
   }
   */
if 

   
}




/*
void loop() {

  if( ((millis() - controleLeitura) > esperaLeitura) && (creditoInserido > 2) ){ // Aqui é o contador de crédito
    Serial.print("Credito inserido: ");
    Serial.println(creditoInserido);
    creditoInserido = 0;
  }
  delay(10);
  digitalWrite(pinSaida, !digitalRead(pinNoteiro));
}


void leituraNoteiro() {
  creditoInserido++;
  controleLeitura = millis();
}
*/
