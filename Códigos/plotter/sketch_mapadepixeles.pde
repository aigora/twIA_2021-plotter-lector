int x=500;
int y=500 ;
int [][]matriz = new int [x][y];
int i, j, radio=1;
int mXP, mXN, mYN, mYP, d;
//0 negro, 1 blanco. 

void setup() {
  size(600, 600);
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
  //Input click del ratón
  
  mainn();
  

  printlcoord();
}


void mainn(){
if (mousePressed==true) {
    //if()
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
    // if(mouseButton == LEFT){matriz[mouseX][mouseY]=0;}
    //if(mouseButton == RIGHT){matriz[mouseX][mouseY]=1;}
    imatriz();
  }
}
  
void mouseWheel(MouseEvent event) {
  int e = event.getCount();

  if (radio>0) {
    radio=radio-e;
  }
  if (radio==0) {
    radio=1;
  }
}

void imatriz() {

  //Imprime matriz
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


void printlcoord() {

  if (mouseX>x) {
    print("X!");
  }
  if (mouseY>y) {
    print("Y!");
  }
  println("r:", radio, "|mX:", mouseX, "|mY:", mouseY);
  //int mXP=mouseX+radio, mXN=mouseX-radio, mYN=mouseY+radio, mYP=mouseY-radio;
}
