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
int analogPin = A0; // Define a leitura analógica
int analogPin2 = A1; // Define a leitura analógica do botão começa 
int valor_analogico = 0;
int valor_analogico_botao_comeca = 1000;
int logica_or_para_funcionamento_micro_A = 0;
int logica_or_para_funcionamento_micro_B = 0;
int logica_or_para_funcionamento_micro_C = 0;



int valor_analogico_setado_para_trigar = 150;// AQUI ESTÁ A VOLTAGEM PARA MUDAR O TRIGGER DO ARDUINO



unsigned long espera_rodar_noteira=1000; //Espera 1 segundo após o início da noteira
unsigned long tempoAtual = millis();
unsigned long tempoInicial =0; // cronômetro utilizado no programa que faz a contagem das moedas
unsigned long cronometro_audio = millis();
unsigned long cronometro_microfone_credito = millis ();
unsigned long espera_tempo_audio = 120000; // espera 6 segundos após acabar o sinal de áudio
unsigned long espera_tempo_cronometro_microfone_credito = 120000;// tempo que o microfone fica aberto após colocar crédito.

///////////////VARIÁVEIS
void setup() {
  Serial.begin(9600); 
  pinMode(pinNoteiro, INPUT);
  pinMode (pinMoedas, INPUT_PULLUP);
  pinMode(pinSaida, OUTPUT);
  pinMode ( inputAudio,INPUT);
  pinMode (outputAudio,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pinNoteiro), leituraNoteiro, RISING);
  attachInterrupt(digitalPinToInterrupt(pinMoedas), leituraMoedinhas, FALLING);
}
//*****************SETUP***********//

void leituraNoteiro()
{
  contador_pulso++;
  tempoInicial = millis();
  Serial.println("a interrupção funcionou! "); //APAGAR NO PROGRAMA EM PRODUÇÃO
  //Serial.println (tempoInicial); // APAGAR NO PROGRAMA EM PRODUÇÃO
}

void leituraMoedinhas()
{
   static unsigned long last_interrupt_time = 0; //gambiarra para evitar erro de boucing
   unsigned long interrupt_time = millis(); // continuação da gambi para o erro de bouncing
   Serial.println ("entrou na interrupção");
   if (interrupt_time - last_interrupt_time > 400)
   {
   Serial.println("MOEDINHAS EM HIGH, é para estar em LOW"); //APAGAR NO PROGRAMA EM PRODUÇÃO
   contador_pulso++;
   tempoInicial = millis();
   last_interrupt_time = interrupt_time;
   }
   
}
void loop (){
  //delay (5000);
  valor_analogico=0;
  valor_analogico_botao_comeca = 1000;
  valor_analogico_botao_comeca = analogRead(analogPin2);
  valor_analogico = analogRead (analogPin);
  Serial.println(valor_analogico_botao_comeca);
  
 // val= digitalRead (inputAudio);
  if ( valor_analogico > valor_analogico_setado_para_trigar) //aqui tá lendo o valor de áudio da saída do PC.
     {
     logica_or_para_funcionamento_micro_B = 1;
   logica_or_para_funcionamento_micro_C =0;
    digitalWrite (outputAudio, LOW);
    cronometro_audio = millis();
   Serial.println ("Saída audio em high"); 
   valor_analogico = 0;    
      }
      //$$$$$$$$$$$$$$AQUI VEM A PARTE ADICIONADA DE CÓDIGO
  if ( valor_analogico_botao_comeca < 900) // Aqui vê se o botão "começa" atinge o limite
     {
     logica_or_para_funcionamento_micro_C = 1;
    //digitalWrite (outputAudio, HIGH);
    //cronometro_audio = millis();
   Serial.println ("APERTOU BOTÃO COMEÇA"); 
   valor_analogico_botao_comeca = 1000;    
      }  
    
// Aqui vem a gambiarra que faz funcionar o microfone só quando coloca crédito, por 20 segundos
if (millis () - cronometro_microfone_credito > espera_tempo_cronometro_microfone_credito)
{
   // digitalWrite (outputAudio, LOW);
    logica_or_para_funcionamento_micro_A = 0;
  logica_or_para_funcionamento_micro_C = 0;
  valor_analogico_botao_comeca = 10000; // aqui também reseta o botão começa
    Serial.println ("saída de áudio low por causa das moedas");
    valor_analogico = 0;  
}

//Esse aqui é para deixar em 0V depois que acaba a música.  
 if (millis() - cronometro_audio > espera_tempo_audio)
  {
    
    //digitalWrite (outputAudio, LOW);
    logica_or_para_funcionamento_micro_B=0;
    Serial.println ("Saída audio em LOOOW");
    valor_analogico = 0;  
  }
//aqui vem a lógica para funcionar o áudio tanto quando colocar crédito, quanto quando a música começar
  if ((logica_or_para_funcionamento_micro_A * logica_or_para_funcionamento_micro_C == 1) || (logica_or_para_funcionamento_micro_B == 1))
  {
    digitalWrite(outputAudio,LOW);
    Serial.println( "estou aqui na lógica OR COM O MICRO LIGADO");
  }
  else
  {
  digitalWrite (outputAudio,HIGH);
  Serial.println("entrei no Else da lógica OR");
  }
  
 
  if(millis() - tempoInicial  > espera_rodar_noteira)
 { //Serial.println ( tempoInicial);
   //Serial.println (millis());
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
          Serial.println("número de créditos impar computado");
          delay(100);
          Serial.println("agora é para desligar o led");
          digitalWrite(pinSaida, LOW);
          delay (100);
          resto_contador=0;
          // *******************AQUI VEM A GAMBIARRA PARA FUNCIONAR O ÁUDIO DO PC via créditos
          //digitalWrite (outputAudio, HIGH); precisa desabilitar, porque se não a lógica "or" não funciona
          logica_or_para_funcionamento_micro_A = 1;
          cronometro_microfone_credito = millis();
         // cronometro_audio = millis(); // Não colocar Precisa colocar isso aquim se não vai disparar o cronômetro do áudio
          Serial.println ("aqui estou ligando o microfone, porque inseriram créditos impar");
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
         delay(100);
         Serial.println("agora é para desligar o led");
         digitalWrite(pinSaida, LOW);
         delay (100);
         resto_contador = 0;
         // **********************AQUI VEM A GAMBIARRA PARA FUNCIONAR O ÁUDIO DO PC via créditos
          logica_or_para_funcionamento_micro_A = 1;
          //digitalWrite (outputAudio, HIGH); precisa desabilitar, porque se não a lógica "or" não funciona
          cronometro_microfone_credito = millis();
          Serial.println ("aqui estou ligando o microfone, porque inseriram MOEDITAS");
       }
     delay (100);
     contador_pulso = 1;
       Serial.println ("saiu do delay de 5 Segundos ");
      }  
      
  }

  }


}
