void blackAndWhite(float threshold)
{
  source.loadPixels();
  destination.loadPixels();

  for (int x = 0; x < source.width; x++ ) {
    for (int y = 0; y < source.height; y++ ) {
      int loc = x + y*source.width;
      // Test the brightness against the threshold
      if (brightness(source.pixels[loc]) > threshold) {
        destination.pixels[loc] = color(255); // White
      } else {
        destination.pixels[loc] = color(0);   // Black
      }
    }
  }
  destination.updatePixels();
  // Display the destination
  image(destination, (1920 - destination.width) /2, (1080 - destination.height) /2);// set image in the centre of the screen
}

void slicer()
{
  int[] xSteps ={}, servoSteps = {};
  int servoState = 0, layerSteps = 0;
  if (pos < totalPixels - destination.width) 
  {
    pos+= destination.width;
  } else
  {
    isActive = false;
  }
  //reset linelenght each different line
  lineLenght = 1;
  layerSteps = 1;
  for (int x = 0; x < destination.width; x++)
  {
    // vemos el color para ver si hay que pintar o no
    if (color(destination.pixels[pos + x]) == color(255))// si es el blanco
    {
      servoState = 0;// estado no pintar
    } 
     else// si es negro
    {
      servoState = 1;// pintar
    }

    if (x != destination.width - 1) //  salvo la ultima columna compara con el de la dcha
    {
      if (color(destination.pixels[pos + x + 1]) == color(destination.pixels[pos + x]))// mismo color
      {
        lineLenght ++;
        layerSteps ++;

        if (color(destination.pixels[pos + x]) == color(255))// si es el blanco
        {
          finalimg.pixels[pos + x] = color(0, 0, 255);
        } else
        {
          finalimg.pixels[pos + x] = color(0, 0, 0);
        }
      } else // distinto color
      {
        //enviar
        xSteps = append(xSteps, lineLenght);
        servoSteps = append(servoSteps, servoState);
        finalimg.pixels[pos + x] = color(0, 255, 0);
        lineLenght = 1;
        layerSteps++;
      }
    } 
     else// ultima columna compara con el anterior
    {
      if (color(destination.pixels[pos + x]) == color(255) && color(destination.pixels[pos + x]) == color(destination.pixels[pos + x -1]))// si es el blanco
      {
        layerSteps ++;
        lineLenght ++;
        //amarillo la parte que ignoro
        ignore(pos - 1, lineLenght -1);
        //avanzo el papel
        sendData(-(layerSteps -lineLenght ), -1, 0);//vuelve al origen
        //println("LINEA VACIA");
      } else
      {
        xSteps = append(xSteps, lineLenght);
        servoSteps = append(servoSteps, servoState);
        lineLenght ++;
        layerSteps ++;
        finalimg.pixels[pos + x] = color(0, 255, 0);
      }
    }
  }
  printDraw(xSteps, servoSteps);//imprimo los valores

  finalimg.updatePixels();
  image(finalimg, (1920 - destination.width) /2, (1080 - destination.height) /2);//coloco en el centro
}
void waitForMachine(int steps)
{
  if (abs(steps * DELAY) < 150)
  {
      delay(150);

  } else
  {
      delay(int(abs(steps * DELAY)));

  }
}
void sendData(int x, int y, int servo)
{
  x *= SCALE;
  y *= 8;

  println(str(x) + "," + str(-y) + "," + str(servo) + ",");
  //send serial
  myPort.write(str(x) + "," + str(y) + "," + str(servo) + ",");
  waitForMachine(x+y);
}
void ignore(int pos, int lenght)
{
  for (int i = 0; i < lenght; i++)
  {
    if (i == lenght -1)
    {
      finalimg.pixels[pos - i] = color(255, 0, 0);
    } else
    {
      finalimg.pixels[pos - i] = color(255, 233, 0);
    }
  }
}
void printDraw(int[] x, int[] servo)
{
  for (int i = 0; i< x.length; i++)
  {
    sendData(x[i], 0, servo[i]);
    //print(x[i] + "/" + servo[i] + "///");
  }
}
