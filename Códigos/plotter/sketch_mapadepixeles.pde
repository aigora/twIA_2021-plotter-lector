/*ATENCIÓN: 
-Click izquierdo: pintar negro.
-Click derecho: borrar.
-Rueda arriba: aumentar el tamaño del pinzel.
-Rueda abajo: disminuir el tamaño del pinzel

-Para cambiar el tamaño de la ventana modificad los valores de las variables "x", "y" junto con los valores de size(a,b) de manera que a=x y b=y.
  De no hacerlo de esa manera, puede pasar que: 
  1. Al introducir un valor en size mayor que en x o y: al guardar la imagen saldrá parte del fondo con un color gris como indica "background(200)" en la función setup.
  2. Al introducir un valor en size menor que en x o y: se usa más memoria de la necesaria.

-Para cambiar el nombre del archivo de guardado ir a la función keyPressed() e introducir en la variable el nombre y el formato de la siguiente manera: save(" nombre.formato "). 
 Las comillas son necesarias.  
*/


int x=700, y=700;

int [][]matriz = new int [x][y];
int i, j, radio=1, d;

void setup() {
  size(500, 500);
  background(200);
  noStroke();
  ellipseMode(RADIUS); 



  for (i=0; (i<y); i++) { 
    for (j=0; (j<x); j++) {  
      matriz[j][i]=1;
    }
  }
}


void draw() { 
 //Programa principal:
 if (mousePressed==true) {
    pincel_matriz();//Imprime matriz en la ventana
    imatriz();
  }
  KeyPressed();//Guardado de la imagen
  
  
  //Consola: coordenadas y radio del pincel
  printlcoord();
}

//Guardado
//Cambiar el nombre del archivo: save("nombrearchivo.formato")
void KeyPressed(){
  if(key=='s' ||key=='S'){
  save("Dibujo.png");
  }
  
}




//Relaciona el mouse con la matriz: 
void pincel_matriz(){

    for (i=0; (i<y); i++) { 
      for (j=0; (j<x); j++) {
        d=(int)dist(mouseX, mouseY, j, i);
        if ( mouseButton == LEFT  &&d<=radio) {
          matriz[j][i]=0;
        }
        if ( mouseButton == RIGHT  &&d<=radio) {
          matriz[j][i]=1;
        }
      }
    }
    
    /*Funcionamiento: al hacer click mide la distancia de todas las posiciones (j,i) con la del ratón,
    si la distancia es menor o igual al radio modifica el valor de los elementos matriz[i][i] que cumplan el requisito.
    Los subindices[j][i] de cada elemento de la matriz están relacionados con su posición (j,i) en el plano.
    */
}

//Controla el radio del pincel:
void mouseWheel(MouseEvent event) {
  int e = event.getCount();

  if (radio>0) {
    radio=radio-e;
  }
  if (radio<1) {
    radio=1;
  }
}

//Imprime matriz en la ventana:
void imatriz() {
 
  for (i=0; (i<y); i++) {
    for (j=0; (j<x); j++) {
      if (matriz[j][i]==1) {//blanco
        fill(255);
        rect(j, i, 1, 1);
      }
      if (matriz[j][i]==0) {//negro
        fill(0);

        rect(j, i, 1, 1);
      }
    }
  }
}


//Consola:
//Imprime las coordenadas y el radio del pincel
void printlcoord() {

  if (mouseX>x) {
    print("X!");
  }
    
  if (mouseY>y) {
    print("Y!");
  }
  println("r:", radio, "|mX:", mouseX, "|mY:", mouseY);
}
