//declaramos pin sensor referencia
const int sensorJefe = 2;
// declaramos pines de las notas
const int sensorDo = 3;
const int sensorRe = 4;
const int sensorMi = 5;
const int sensorfa = 6;
const int sensorSol = 7;
const int sensorLa = 8;
const int sensorSi = 9;
// pin buzzer
const int buzzer = 10;
bool duplicate = true;
//frecuencias notas
#define DO 261.626
#define RE 293.665
#define MI 329.628
#define FA 349.228
#define SOL 391.995
#define LA 440
#define SI 493.883
//definimos duracion en ms
#define DURACION 300
void setup()
{
  Serial.begin(9600);
  //ponemos los pines de los sensores en input
  for (int i = 3; i < 10; i++)
  {
    pinMode(i, INPUT);
  }
  pinMode(buzzer, OUTPUT);

}

void loop()
{
  int value = 0;
  if ( digitalRead(sensorJefe) == HIGH && duplicate == true) //si el jefe esta activado
  {
    //leemos el resto
    for (int i = 3; i < 10; i++)
    {
      if (digitalRead(i) == HIGH)
      {
        duplicate = false;
        value = i;
        break;
      }
    }
  }
  switch (value)
  {
    case 3:
      Serial.println("1000000");

      tone(buzzer, DO, DURACION);

      break;
    case 4:
      tone(buzzer, RE, DURACION);
      Serial.println("0100000");

      break;
    case 5:
      tone(buzzer, MI, DURACION);
      Serial.println("0010000");

      break;
    case 6:
      tone(buzzer, FA, DURACION);
      Serial.println("0001000");

      break;
    case 7:
      tone(buzzer, SOL, DURACION);
      Serial.println("0000100");

      break;
    case 8:
      tone(buzzer, LA, DURACION);
      Serial.println("0000010");

      break;
    case 9:
      tone(buzzer, SI, DURACION);
      Serial.println("0000001");

      break;
  }
  if (digitalRead(sensorJefe) != HIGH)
  {
    duplicate = true;
  }
}
