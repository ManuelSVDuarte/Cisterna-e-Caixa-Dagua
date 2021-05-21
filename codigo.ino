// Variaveis definindo os pinos para os leds que vão indicar os parametros
int caixaVazia = 2;
int caixaCheia = 3;

int bomba = 7;
int valvula = 8;

int nivelCaixa = 0; // 0 = vazia; 1 = cheia; 
int nivelCisterna = 3; // 3 = baixo; 2 = medio; 1 = cheio
int ligado = 0;



void setup()
{
  Serial.begin(9600);
  pinMode(caixaVazia, OUTPUT); // Led pino 2
  pinMode(caixaCheia, OUTPUT); // Led pino 3
  pinMode(bomba, OUTPUT); // Led pino 7
  pinMode(valvula, OUTPUT); // Led pino 8
  // Sensores Cisterna
  pinMode(4, OUTPUT); // Indicação do nivel 3
  pinMode(5, OUTPUT); // Indicação do nivel 2
  pinMode(6, OUTPUT); // Indicação do nivel 1
  // Botoes
  pinMode(9, INPUT_PULLUP); // Nivel 1
  pinMode(10, INPUT_PULLUP); // Nivel 2
  pinMode(11, INPUT_PULLUP); // Nivel 3
  pinMode(12, INPUT_PULLUP); // Esvaziar Caixa 
}

void nivel(int x)
{
  	for(int x = 4; x <= 6; x++)
   		digitalWrite(x, LOW);
  	if(nivelCaixa)
    {
		digitalWrite(caixaCheia, HIGH);
		digitalWrite(caixaVazia, LOW);
    }
  	else
    {
		digitalWrite(caixaCheia, LOW);
		digitalWrite(caixaVazia, HIGH);
    }
  
	switch(x)
    {
    	case 3: //cisterna com pouca agua
        {
          	digitalWrite(4, HIGH);
        	digitalWrite(valvula, HIGH); //ligar valvula
          	digitalWrite(bomba, LOW); // desligar a bomba
          	delay(500);
          	Serial.println("Enchendo cisterna...");
          	delay(500);
          	digitalWrite(4, LOW);
          	digitalWrite(5, HIGH);
          	delay(500);
          	nivelCisterna = 2;
          	Serial.println("A cisterna agora esta no nivel 2.");
        	break;
        }
      	case 2: 
        {
          	digitalWrite(5, HIGH);
        	digitalWrite(valvula, HIGH); //ligar valvula
          	if(nivelCaixa)
            {
              	Serial.println("Caixa dagua cheia.");
            	digitalWrite(bomba, LOW);
            }
	        else
            {
            	Serial.println("Caixa dagua vazia.");
              	delay(500);
              	Serial.println("Enchendo cisterna e caixa dagua simultaneamente.");
              	digitalWrite(bomba, HIGH);
            }
          	delay(500);
          	digitalWrite(6, HIGH);
          	digitalWrite(5, LOW);
          	nivelCaixa = 1;
          	digitalWrite(caixaCheia, HIGH);
          	digitalWrite(caixaVazia, LOW);
          	Serial.println("A cisterna esta no nivel 1 e a caixa esta cheia.");
        	break;
        }
        case 1: 
        {
          	digitalWrite(6, HIGH);
        	digitalWrite(valvula, LOW); //ligar valvula
          	Serial.println("A cisterna está cheia.");
          	delay(500);
          	if(nivelCaixa)
            {
          		digitalWrite(bomba, LOW); // desligar a bomba
              	Serial.println("A caixa dagua está cheia.");
            }
          	else
            {
              	Serial.println("Enchendo a caixa dagua...");
              	delay(500);
              	digitalWrite(caixaCheia, HIGH);
              	Serial.println("Caixa dagua cheia.");
            }
        	break;
        }
    }
}
void loop()
{
  for(int x = 9; x <= 12; x++)
  {
  	if(digitalRead(x) == 0) // se um botao for pressionado
    {
      if(x == 12)
      {
      	nivelCaixa = 0;
      	digitalWrite(caixaCheia, LOW);
      	digitalWrite(caixaVazia, HIGH);
        Serial.println("Caixa dagua vazia.");
      }
      else
	  	nivel(x - 8);
    }
  }
}
