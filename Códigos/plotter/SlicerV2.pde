PImage source;      // Source image
PImage destination; // Destination image
PImage finalimg;
int totalPixels;
boolean isActive = true;
int pos = 0, lineLenght = 1;
///SERIAL
import processing.serial.*;
Serial myPort;
////
float DELAY = 3.25;
int SCALE = 3;
void setup() {

  /////Serial
  myPort = new Serial(this, "COM3", 9600);// cambia para tu pc 
  /////

  frameRate(60);
  source = loadImage("panda2.jpg");// la imagen con la que se trabaja
  destination = createImage(source.width, source.height, RGB);
  finalimg = createImage(source.width, source.height, RGB);

  size(1920, 1080);

  float threshold = 169;

  blackAndWhite(threshold);// CONVERTIMOS A BLANCO Y NEGRO LA IMAGEN INICIAL
  totalPixels = source.width * source.height;
  delay(3000);
}

void draw()
{
  if (isActive)
  {
    slicer();// LA PROCESAMOS PARA PODERLA DIBUJAR, esta en draw para que se vea el efecto
  }
}
