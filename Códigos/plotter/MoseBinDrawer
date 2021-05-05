boolean bin = false;

void setup()
{
  String[] lines = loadStrings("list.txt");
  noSmooth();

  int[] size;
  size(960, 540);
  size = calculateLen(lines);
  drawData(size, lines);
}


void drawData(int[] size, String[] lines)
{
  PImage canvas;
  int off = 0;
  canvas = createImage(size[0], size[1], RGB);

  for (int i = 0; i < canvas.height; i+= 2 ) {
    off = 0;

    if (bin)// si es binario(o notas) se pone el sistema de referencia
    {
            int loc =  i*canvas.width + canvas.width - 1;
            canvas.pixels[loc] = color(0); // dot

    }
    for (int j = 0; j < lines[i/2].length(); j++ ) {

      int loc = j + i*canvas.width + off;
      if (lines[i/2].charAt(j) == '.')
      {
        canvas.pixels[loc] = color(0); // dot
        canvas.pixels[loc + 1] = color(255); // dot
        off+= 1;
      } else if (lines[i/2].charAt(j) == '-')
      {
        canvas.pixels[loc] = color(0); // line = 3 dots
        canvas.pixels[loc + 1] = color(0); // line = 3 dots
        canvas.pixels[loc + 2] = color(0); // line = 3 dots
        canvas.pixels[loc + 3] = color(255); // dot

        off+=3;
      } else if (lines[i/2].charAt(j) == '/')
      {
        canvas.pixels[loc] = color(255);
        canvas.pixels[loc + 1] = color(255);
        canvas.pixels[loc + 2] = color(255); 
        canvas.pixels[loc + 3] = color(255); 
        canvas.pixels[loc + 4] = color(255); 
        off+=4;
      }else if (lines[i/2].charAt(j) == ' ')
      {
        canvas.pixels[loc] = color(255);
        canvas.pixels[loc + 1] = color(255);
        canvas.pixels[loc + 2] = color(255); 
        off+=2;
      } else if (lines[i/2].charAt(j) == '1')
      {
        canvas.pixels[loc] = color(0);
      }
    }
  }

  // rellenar los vacios de blanco
  for (int i = 0; i< canvas.height; i++)
  {
    for (int j = 0; j < canvas.width; j++ ) 
    {
      int loc = j + i*canvas.width;
      if ((canvas.pixels[loc]) != color(0))
      {
        canvas.pixels[loc] = color(255);
      }
    }
  }
  canvas.updatePixels();
  //canvas.resize(800, 0);
  image(canvas, 0, 0, displayWidth/2, (displayWidth/4) * canvas.height/canvas.width);
  canvas.save("Output.jpg");
}

int[] calculateLen(String[] lines) {
  int out[] = {0, 0}, len = 0, max = 0;
  for (int i = 0; i < lines.length; i++) {
    len = 0;
    for (int j = 0; j < lines[i].length(); j++) {
      if (lines[i].charAt(j) == '.')
      {
        len += 2;
      } else if (lines[i].charAt(j) == '-')
      {
        len += 4;
      } else if (lines[i].charAt(j) == ' ')
      {
        len += 5;
      } else if (lines[i].charAt(j) == '0' || lines[i].charAt(j) == '1')
      {
        len ++;
        bin = true;
        println("BINARIO ON");
      }
    }
    if (len > max)
    {
      max = len;
    }
  }
  if (bin == true)
  {
    max ++;
  }
  out[0] = max;
  out[1] = lines.length * 2;
  return out;
}
