

// DEFINIÇÕES
#define pinNoteiro 2 // pino de interrupção do noteiro
#define pinMoedas 3 // pino de interrupção das moedas
#define pinSaida 8 // pino de saída que dá os créditos.
#define inputAudio 7 // define o pino que recebe se há sinal de audio saindo do computador
#define outputAudio 5 // Define o pino que dá o sinal de alto quando há saída de som do computador

// DECLARAÇÃO DE VARIÁVEIS GLOBAIS
int creditoInserido = 0;
int contador_pulso = 0;
int resto_contador = 0;
int val=0;
unsigned long espera_rodar_noteira=3000; //Espera 3 segundo após o início da noteira
unsigned long tempoAtual = millis();
unsigned long tempoInicial =0; // cronômetro utilizado no programa que faz a contagem das moedas
unsigned long cronometro_audio = millis();
unsigned long espera_tempo_audio = 6000; // espera 6 segundos após acabar o sinal de áudio
///////////////VARIÁVEIS
void setup() {
  Serial.begin(9600); 
  pinMode(pinNoteiro, INPUT);
  pinMode (pinMoedas, INPUT_PULLUP);
  pinMode(pinSaida, OUTPUT);
  pinMode ( inputAudio,INPUT);
  pinMode (outputAudio,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pinNoteiro), leituraNoteiro, RISING);
  attachInterrupt(digitalPinToInterrupt(pinMoedas), leituraMoedinhas, RISING);
}
//*****************SETUP***********//

void leituraNoteiro()
{
  contador_pulso++;
  tempoInicial = millis();
  Serial.println("a interrupção funcionou! "); //APAGAR NO PROGRAMA EM PRODUÇÃO
  Serial.println (tempoInicial); // APAGAR NO PROGRAMA EM PRODUÇÃO
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
  val= digitalRead (inputAudio);
  if ( val == HIGH)
  {
    digitalWrite (outputAudio, HIGH);
    cronometro_audio = millis();
    Serial.println ("Saída audio em high");    
  }
  
  if (millis() - cronometro_audio > espera_tempo_audio)
  {
    digitalWrite (outputAudio, LOW);
    Serial.println ("Saída audio em LOOOW");
  }
  
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

  }


}


