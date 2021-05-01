

void setup(){
 size(600,600);
  background(200);
}

  

void draw(){
  int  x=1000;
  int  y=1000 ;
  char [][]matrizn = new char [x][y];
  char  [][]matrizb = new char [x][y];
  int i, j;
  //Inicializa la matriz blanca
  for(i=0; (i<500); i++){ 
  for(j=0; (j<500); j++){  
 //Llena de izquierda a derecha los elementos de una fila con el valor 255 y luego pasa a la siguiente y vuelve a llenar...
  matrizb[j][i]=255;

  }
  }
  
  
  
  for(i=0; (i<500); i++){ 
  for(j=0; (j<500); j++){  
   
     if(matrizn[j][i]==0){
      matrizb[j][i]=0;
     }
     
      else{
      matrizb[j][i]=255;
     }
  }
  }

 
 
   //Imprime matriz
  for(i=0; (i<500); i++){
  for(j=0; (j<500); j++){

    fill(matrizn[j][i]);
    noStroke();
    
    rect(j,i,1,1);
    }
    }
  
  
     if (mousePressed==true){
      
    matrizn[mouseX][mouseY]=0;
    fill(matrizn[mouseX][mouseY]); noStroke();
    rect(mouseX,mouseY,1,1);
  }
  
  
  
  
}//Fin
