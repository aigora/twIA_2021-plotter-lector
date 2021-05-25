//[OPERATIVO]
//a esta fecha Hace homing inicial y se mueve al recibir comandos
// de la forma XX,XX,A, donde XX son los pasos a mover, el carro y el papel,
//respectivamente y a es 1 o 0, 0 no pinta, 1 sí

#include <Servo.h>

//definicion de pins de motores paso a paso

int motor[] = {4, 5, 6, 7};
int motor2[] = {8, 9, 10, 11};

//definicion variables
int stepCounter = 0;     // contador para los pasos
int stepsPerRev = 2048;  // pasos para una vuelta completa
//secuencia 2-fases
const int numSteps = 4;
const int stepsLookup[4] = { B1100, B0110, B0011, B1001 };
const int off[1] = { B0000 };

const int StopButtonPin = 12;
int buttonsPin = 1;// button state, when pressed = 0
bool isHomed = false;
int steps = 0;
// definicion servo Actuador
Servo lapiz;
void setup()
{
  Serial.begin(9600);
  lapiz.attach(3);
  //declarar pines como salida
  pinMode(motor[0], OUTPUT);
  pinMode(motor[1], OUTPUT);
  pinMode(motor[2], OUTPUT);
  pinMode(motor[3], OUTPUT);
  pinMode(motor2[0], OUTPUT);
  pinMode(motor2[1], OUTPUT);
  pinMode(motor2[2], OUTPUT);
  pinMode(motor2[3], OUTPUT);

  // ir a origen
  void homing();
}

void loop()
{
  if (Serial.available() && isHomed) {
    // leer serial
    int *st1, *st2, *servo;
    readSerial( st1,  st2,  servo);

    //Servo
    moveServo(*servo);
    //segundo motor
    if (*st2 != 0)
    {
      moveMotor(motor2, *st2);
      apagar();
    }
    //primer motor
    if (*st1 != 0)
    {
      moveMotor(motor, *st1);
      apagar();
    }
  }
}
// mueve el servo que sube y baja el lapiz para que pinte o deje de pintar
void moveServo(int servo)
{
  if (servo == 1)
  {
    lapiz.write(90);
  } else
  {
    lapiz.write(45);
  }
}
//funcion que controla el bucle de movimiento de los motores de los ejes
void moveMotor(int motor[], int st)
{
  if (st > 0)
  {
    for (int i = 0; i < st; i++)
    {
      steps++;
      clockwise(motor);
      delay(3);
    }
  } else
  {
    for (int i = 0; i > st; i--)
    {
      steps--;
      anticlockwise(motor);
      delay(3);
    }
  }
}
// se ejecuta al inicio mueve el cabezal hasta que pulsa el boton para conocer la posicion inicial
// una vez ejecutado se maneja a traves de los pasos del motor
void homing()
{
  lapiz.write(45);
  for (int i = 0; i < 500; i++)
  {
    anticlockwise(motor2);
    delay(3);
  }
  apagar();
  while (digitalRead(StopButtonPin) == HIGH) // que se hacerque al home
  {
    anticlockwise(motor);
    delay(3);
    isHomed = true;
    lapiz.write(0);
  }
  while (digitalRead(StopButtonPin) == LOW) //  que se aleje lo justo para dejar de pulsar el boton
  {
    clockwise(motor);
    delay(3);
    lapiz.write(45);
  }
  steps = 0; // inicializamos los steps a 0
  apagar();
}

void readSerial(int *st1, int *st2, int *servo)
{
  String first  = Serial.readStringUntil(',');
  Serial.read(); //next character is comma, so skip it using this
  String second = Serial.readStringUntil(',');
  Serial.read();
  String third  = Serial.readStringUntil(',');
  * st1 = first.toInt();
  * st2 = second.toInt();
  * servo = third.toInt();

}
void apagar()
{
  //apagar para evitar sobre calentar porque no hace falta fuerza para mantener pos
  digitalWrite(motor[0], bitRead(off[1], 0));
  digitalWrite(motor[1], bitRead(off[1], 0));
  digitalWrite(motor[2], bitRead(off[1], 0));
  digitalWrite(motor[3], bitRead(off[1], 0));
}
void clockwise(int motorvc[])//  secuencia en sentido reloj
{
  stepCounter++;
  if (stepCounter >= numSteps) stepCounter = 0;
  setOutput(stepCounter, motorvc);
}

void anticlockwise(int motorva[])//  secuencia en sentido anti-horario
{
  stepCounter--;
  if (stepCounter < 0) stepCounter = numSteps - 1;
  setOutput(stepCounter, motorva);
}

void setOutput(int step, int motorVar[])// manda la señal para encender las bobinas que corresponden al motor
{
  digitalWrite(motorVar[0], bitRead(stepsLookup[step], 0));
  digitalWrite(motorVar[1], bitRead(stepsLookup[step], 1));
  digitalWrite(motorVar[2], bitRead(stepsLookup[step], 2));
  digitalWrite(motorVar[3], bitRead(stepsLookup[step], 3));
}
