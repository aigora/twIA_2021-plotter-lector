import processing.serial.*;
Serial myPort;

PImage source;      // Source image
PImage destination; // Destination image
boolean hasSomething = false;
int ST1 = 2, ST2 = 5;
void setup() {
  /////Serial
  myPort = new Serial(this, "COM3", 9600);// cambia para tu pc 
  /////
  source = loadImage("panda2.jpg");
  destination = createImage(source.width, source.height, RGB);
  size(664,664);

  float threshold = 80;
  
  // We are going to look at both image's pixels
  source.loadPixels();
  destination.loadPixels();
  
  for (int x = 0; x < source.width; x++ ) {
    for (int y = 0; y < source.height; y++ ) {
      int loc = x + y*source.width;
      // Test the brightness against the threshold
      if (brightness(source.pixels[loc]) > threshold){
        destination.pixels[loc] = color(255); // White
      } else {
        destination.pixels[loc] = color(0);   // Black
      }
    }
  }
       destination.updatePixels();
  // Display the destination
      image(destination,0,0);
delay(5000);

          println("SETUP DONE");
  int drawline = 0,  stepsThisline = 0;
  for (int y = 0; y < destination.height; y+=2 ) {
   //println("STARTING Y LOOP" + y);
    for (int x = 0; x < destination.width ; x++ ) {
      //println("STARTING X LOOP" + x + " " + y);
      int steps = x + y*source.width;// va contanto de izq a dcha y esuna unica coord
      if(color(destination.pixels[steps]) == color(destination.pixels[steps+1]) &&  (x != (destination.width - 1)) && steps != destination.width -1 + (destination.height -1) * destination.width)
        {
          if(color(destination.pixels[steps]) == color(255))
            destination.pixels[steps] = color(255,0,0);
          if(color(destination.pixels[steps]) == color(0))
            hasSomething = true;
            destination.pixels[steps] = color(0,255,0);
            
          drawline ++;
          stepsThisline ++;
        }else if((color(destination.pixels[steps]) != color(destination.pixels[steps+1]) || (x == (destination.width - 1))) && hasSomething) 
        {
            
          if(color(destination.pixels[steps]) == color(255))
            {
              //drawline,0,0
              println(str(drawline * ST1) + ",0,0\0");
              myPort.write(str(drawline * ST1) + ",0,0,");
              delay(4 * drawline);

            }else
            {
              //drawline,0,1
              myPort.write(str(drawline * ST1) + ",0,1,");
              println((drawline * ST1) + ",0,1,");
            }
                    delay(4 * drawline* ST1);

          drawline = 0;
        }
    }
    if(hasSomething == false)// si no hay nada pintado solo avancza hoja y reset
  {
    stepsThisline = 0;
    drawline = 0;
  }else{
        hasSomething = false;

  }
   //avance de papel -stepsThisline,ST2,0
   println((str(-stepsThisline * ST1) + ',' + (-ST2) + ",0,"));
    myPort.write(str(-stepsThisline * ST1) + ',' + (-ST2) + ",0,");
                        delay(4 * stepsThisline* ST1);
          
   stepsThisline = 0;
  }
     destination.updatePixels();
  // Display the destination
      image(destination,0,0);
}
