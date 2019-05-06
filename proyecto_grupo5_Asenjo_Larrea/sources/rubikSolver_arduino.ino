#include <Servo.h>
#define PRINCIPAL_IZQUIERDA 8
#define PRINCIPAL_ARRIBA 9
#define PRINCIPAL_DERECHA 10
#define PRINCIPAL_ABAJO 11
#define AUXILIAR_IZQUIERDA 3
#define AUXILIAR_ARRIBA 5
#define AUXILIAR_DERECHA 6
#define AUXILIAR_ABAJO 7

#define DERECHA0 600
#define DERECHA90 1550
#define DERECHA180 2500
#define ARRIBA0 400
#define ARRIBA90 1400
#define ARRIBA180 2400
#define IZQUIERDA0 600
#define IZQUIERDA90 1550
#define IZQUIERDA180 2500
#define ABAJO0 400
#define ABAJO90 1400
#define ABAJO180 2400

#define INCREMENTO_INICIAL 1
#define INCREMENTO_FINAL 1

int dutycycle = 500;
int period = 20000;
short incremento = 2;
short posiciones[4] = {1500, 1500, 1500, 1500}; /* Las posiciones son izquierda, arriba, derecha y abajo */
short limites0[4] = {IZQUIERDA0, ARRIBA0, DERECHA0, ABAJO0};
short limites90[4] = {IZQUIERDA90, ARRIBA90, DERECHA90, ABAJO90};
short limites180[4] = {IZQUIERDA180, ARRIBA180, DERECHA180, ABAJO180};
String recepcionSerial = "";

Servo auxiliarIzquierdo;
Servo auxiliarDerecho, auxiliarArriba, auxiliarAbajo;

void initServo(int numServo){
  short posicionServos;

  for (posicionServos = 500; posicionServos <= 2500; posicionServos+=1)
  {
    digitalWrite(numServo, HIGH);
    delayMicroseconds(posicionServos);
    digitalWrite(numServo, LOW);
    delayMicroseconds(period - posicionServos);
  }
  delay(200);
  
  for (posicionServos = 2500; posicionServos>= 1500; posicionServos-=1)
  {
    digitalWrite(numServo, HIGH);
    delayMicroseconds(posicionServos);
    digitalWrite(numServo, LOW);
    delayMicroseconds(period - posicionServos);
  }
  delay(200);

  posiciones[numServo-8] = 1500;
}

void retraerAbajo(){
  auxiliarAbajo.write(0);
  delay(100);
}

void extenderAbajo(){
  auxiliarAbajo.write(100);
  delay(100);
}

void extenderArriba(){
  auxiliarArriba.write(85);
  delay(100);
}

void retraerArriba(){
  auxiliarArriba.write(0);
  delay(100);
}

void extenderIzquierda(){
  auxiliarIzquierdo.write(105);
  delay(100);
}

void retraerIzquierda(){
  auxiliarIzquierdo.write(15);
  delay(100);
}

void extenderDerecha(){
  auxiliarDerecho.write(95);
  delay(100);
}

void retraerDerecha(){
  auxiliarDerecho.write(0);
  delay(100);
}

void servoPrincipal0grados(int numServo){
  int i = 0;
  for(i=0; i<50; i++){
    digitalWrite(numServo, HIGH);
    delayMicroseconds(limites0[numServo-8]);
    digitalWrite(numServo, LOW);
    delayMicroseconds(period - limites0[numServo-8]);
  }
  posiciones[numServo-8] = limites0[numServo-8];
}

void horizontales0grados(){
  // Ponemos la derecha a 0 grados y la izquierda a 180 grados
  for(; posiciones[2]>= limites0[2]; posiciones[2]-=4){
    digitalWrite(PRINCIPAL_DERECHA, HIGH);
    digitalWrite(PRINCIPAL_IZQUIERDA, HIGH);
    delayMicroseconds(posiciones[2]);
    digitalWrite(PRINCIPAL_DERECHA, LOW);
    delayMicroseconds(posiciones[0]-posiciones[2]);
    digitalWrite(PRINCIPAL_IZQUIERDA, LOW);
    delayMicroseconds(period - posiciones[0]);
    posiciones[0] += 4;
  }
  posiciones[0] = limites180[0];
  posiciones[2] = limites0[2];
}

void verticales0grados(){
  // Ponemos arriba a 0 grados y abajo a 180
  // Suponemos que los motores estan colocados en 90 (ambos) uno gradualmente lo movemos de cinco en cinco hasta 0 y el otro de cinco en cinco hasta 180
  for(; posiciones[1]>=limites0[1]; posiciones[1]-=4){ // Vamos decrementando arriba de 1500 a 500
    digitalWrite(PRINCIPAL_ARRIBA, HIGH);
    digitalWrite(PRINCIPAL_ABAJO, HIGH);
    delayMicroseconds(posiciones[1]);
    digitalWrite(PRINCIPAL_ARRIBA, LOW);
    delayMicroseconds(posiciones[3] - posiciones[1]);
    digitalWrite(PRINCIPAL_ABAJO, LOW);
    delayMicroseconds(period - posiciones[3]);
    posiciones[3] += 4; // Incrementamos abajo de 1500 a 2500
  }
  posiciones[1] = limites0[1];
  posiciones[3] = limites180[3];
}

void servoPrincipal180grados(int numServo){
  int i = 0;
  for(i=0; i<50; i++){
    digitalWrite(numServo, HIGH);
    delayMicroseconds(limites180[numServo-8]);
    digitalWrite(numServo, LOW);
    delayMicroseconds(period - limites180[numServo-8]);
  }
  posiciones[numServo-8] = limites180[numServo-8];
}


void horizontales180grados(){
  for(; posiciones[2] <= limites180[2]; posiciones[2]+=4){
    // Ponemos la derecha a 180 grados y la izquierda a 0 grados
    digitalWrite(PRINCIPAL_DERECHA, HIGH);
    digitalWrite(PRINCIPAL_IZQUIERDA, HIGH);
    delayMicroseconds(posiciones[0]);
    digitalWrite(PRINCIPAL_IZQUIERDA, LOW);
    delayMicroseconds(posiciones[2] - posiciones[0]);
    digitalWrite(PRINCIPAL_DERECHA, LOW);
    delayMicroseconds(period - posiciones[2]);
    posiciones[0] -= 4;
  }
  posiciones[0] = limites0[0];
  posiciones[2] = limites180[2];
}

void verticales180grados(){
  for(; posiciones[1]<=limites180[1]; posiciones[1]+=4){
    // Ponemos arriba a 180 grados y abajo a cero grados
    digitalWrite(PRINCIPAL_ARRIBA, HIGH);
    digitalWrite(PRINCIPAL_ABAJO, HIGH);
    delayMicroseconds(posiciones[3]);
    digitalWrite(PRINCIPAL_ABAJO, LOW);
    delayMicroseconds(posiciones[1]-posiciones[3]);
    digitalWrite(PRINCIPAL_ARRIBA , LOW);
    delayMicroseconds(period - posiciones[1]);
    posiciones[3] -= 4;
  }
  posiciones[1] = limites180[1];
  posiciones[3] = limites0[3];
}

void servoPrincipal90grados(int numServo){
  int i = 0;
  for(i=0; i<50; i++){
    digitalWrite(numServo, HIGH);
    delayMicroseconds(limites90[numServo-8]);
    digitalWrite(numServo, LOW);
    delayMicroseconds(period - limites90[numServo-8]);
  }
  posiciones[numServo-8] = limites90[numServo-8];
}

void horizontales90grados(){
  if (posiciones[0] > posiciones[2]){ // La izquierda esta a 180 y la derecha a 0
    for(; posiciones[0] >= limites90[0]; posiciones[0]-=4){
      digitalWrite(PRINCIPAL_DERECHA, HIGH);
      digitalWrite(PRINCIPAL_IZQUIERDA, HIGH);
      delayMicroseconds(posiciones[2]);
      digitalWrite(PRINCIPAL_DERECHA, LOW);
      delayMicroseconds(posiciones[0] - posiciones[2]);
      digitalWrite(PRINCIPAL_IZQUIERDA, LOW);
      delayMicroseconds(period-posiciones[0]);
      posiciones[2] += 4;
    }
  } else if (posiciones[0] < posiciones[2]){ // La derecha esta a 180 y la izquierda a 0
    for(; posiciones[0] <= limites90[0]; posiciones[0]+=4){
      digitalWrite(PRINCIPAL_DERECHA, HIGH);
      digitalWrite(PRINCIPAL_IZQUIERDA, HIGH);
      delayMicroseconds(posiciones[0]);
      digitalWrite(PRINCIPAL_IZQUIERDA, LOW);
      delayMicroseconds(posiciones[2]-posiciones[0]);
      digitalWrite(PRINCIPAL_DERECHA, LOW);
      delayMicroseconds(period-posiciones[2]);
      posiciones[2] -= 4;
    } 
  } // Si no entra en ninguno de los dos los servos ya estan a 90

  posiciones[0] = limites90[0];
  posiciones[2] = limites90[2];
}

void verticales90grados(){
  if (posiciones[1] > posiciones[3]){ // Arriba esta a 180 y abajo a 0
    for(; posiciones[1]>= limites90[1]; posiciones[1]-=4){
      digitalWrite(PRINCIPAL_ARRIBA, HIGH);
      digitalWrite(PRINCIPAL_ABAJO, HIGH);
      delayMicroseconds(posiciones[3]);
      digitalWrite(PRINCIPAL_ABAJO, LOW);
      delayMicroseconds(posiciones[1] - posiciones[3]);
      digitalWrite(PRINCIPAL_ARRIBA, LOW);
      delayMicroseconds(period - posiciones[1]);
      posiciones[3] += 4;
    }
  } else if (posiciones[1] < posiciones[3]){ // Arriba esta a 0 y abajo a 180
    for(; posiciones[1] <= limites90[1]; posiciones[1]+=4){
      digitalWrite(PRINCIPAL_ARRIBA, HIGH);
      digitalWrite(PRINCIPAL_ABAJO, HIGH);
      delayMicroseconds(posiciones[1]);
      digitalWrite(PRINCIPAL_ARRIBA, LOW);
      delayMicroseconds(posiciones[3]-posiciones[1]);
      digitalWrite(PRINCIPAL_ABAJO, LOW);
      delayMicroseconds(period - posiciones[3]);
      posiciones[3] -= 4;
    }
  } // Si no entra en ninguna de las dos es que estan las dos en el medio
  posiciones[3] = limites90[3];
  posiciones[1] = limites90[1];
}

void getNext(){
  recepcionSerial = Serial.readString();
  while(recepcionSerial != "NEXT"){
    recepcionSerial = Serial.readString();
  }
}


void detectarCubo(){
  extenderArriba();
  Serial.println("OK"); // Ya esta la cara amarilla preparada para la foto
  recepcionSerial = Serial.readString();
  getNext();
  // Giramos el cubo verticalmente en sentido antihorario
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  retraerArriba();
  retraerAbajo();
  delay(1000);
  horizontales180grados();
  Serial.println("OK"); // Ya esta la cara roja preparada para la foto
  getNext();
  servoPrincipal90grados(PRINCIPAL_ARRIBA);
  servoPrincipal90grados(PRINCIPAL_ABAJO);
  delay(1000);
  extenderAbajo();
  extenderArriba();
  delay(1000);
  retraerIzquierda();
  retraerDerecha();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_DERECHA);
  servoPrincipal90grados(PRINCIPAL_IZQUIERDA);
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  retraerArriba();
  retraerAbajo();
  delay(1000);
  horizontales180grados();
  Serial.println("OK"); // Ya esta la cara blanca preparada para la foto
  getNext();
  delay(1000);
  extenderAbajo();
  extenderArriba();
  delay(1000);
  retraerIzquierda();
  retraerDerecha();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_DERECHA);
  servoPrincipal90grados(PRINCIPAL_IZQUIERDA);
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  retraerArriba();
  retraerAbajo();
  delay(1000);
  horizontales180grados();
  Serial.println("OK"); // Ya esta la cara naranja preparada para la foto
  getNext();
  delay(1000);
  extenderAbajo();
  extenderArriba();
  delay(1000);
  retraerIzquierda();
  retraerDerecha();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_DERECHA);
  servoPrincipal90grados(PRINCIPAL_IZQUIERDA);
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  retraerArriba();
  retraerAbajo();
  delay(1000);
  horizontales180grados();
  delay(1000);
  extenderAbajo();
  extenderArriba();
  delay(1000);
  retraerIzquierda();
  retraerDerecha();
  delay(1000);
  verticales0grados();
  Serial.println("OK"); //Ya esta la cara verde preparada para la foto
  getNext();
  verticales90grados();
  delay(1000);
  verticales180grados();
  Serial.println("OK"); // Ya esta la cara azul preparada para la foto, una vez la recibamos lo ponemos listo para empezar
  getNext();
  verticales90grados();
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  retraerArriba();
  retraerAbajo();
  delay(1000);
  horizontales90grados();
  delay(1000);
  extenderAbajo();
  extenderArriba();
  delay(1000);
  Serial.println("OK"); // Estamos listos para empezar
}

void f(){
  retraerArriba();
  retraerAbajo();
  delay(1000);
  verticales180grados();
  delay(1000);
  extenderArriba();
  extenderAbajo();
  delay(1000);
  retraerIzquierda();
  retraerDerecha();
  delay(1000);
  verticales90grados();
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  servoPrincipal180grados(PRINCIPAL_DERECHA);
  delay(1000);
  retraerDerecha();
  retraerIzquierda();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_DERECHA);
  verticales180grados();
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  retraerArriba();
  retraerAbajo();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_ARRIBA);
  servoPrincipal90grados(PRINCIPAL_ABAJO);
  delay(1000);
  extenderArriba();
  extenderAbajo();
  delay(1000);
}

void fprima(){
  retraerArriba();
  retraerAbajo();
  delay(1000);
  verticales180grados();
  delay(1000);
  extenderArriba();
  extenderAbajo();
  delay(1000);
  retraerIzquierda();
  retraerDerecha();
  delay(1000);
  verticales90grados();
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  servoPrincipal0grados(PRINCIPAL_DERECHA);
  delay(1000);
  retraerDerecha();
  retraerIzquierda();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_DERECHA);
  verticales180grados();
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  retraerArriba();
  retraerAbajo();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_ARRIBA);
  servoPrincipal90grados(PRINCIPAL_ABAJO);
  delay(1000);
  extenderArriba();
  extenderAbajo();
  delay(1000);
}

void b(){
  retraerArriba();
  retraerAbajo();
  delay(1000);
  verticales0grados();
  delay(1000);
  extenderArriba();
  extenderAbajo();
  delay(1000);
  retraerIzquierda();
  retraerDerecha();
  delay(1000);
  verticales90grados();
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  servoPrincipal180grados(PRINCIPAL_DERECHA);
  delay(1000);
  retraerDerecha();
  retraerIzquierda();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_DERECHA);
  verticales0grados();
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  retraerArriba();
  retraerAbajo();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_ARRIBA);
  servoPrincipal90grados(PRINCIPAL_ABAJO);
  delay(1000);
  extenderArriba();
  extenderAbajo();
  delay(1000);
}

void bprima(){
  retraerArriba();
  retraerAbajo();
  delay(1000);
  verticales0grados();
  delay(1000);
  extenderArriba();
  extenderAbajo();
  delay(1000);
  retraerIzquierda();
  retraerDerecha();
  delay(1000);
  verticales90grados();
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  servoPrincipal0grados(PRINCIPAL_DERECHA);
  delay(1000);
  retraerDerecha();
  retraerIzquierda();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_DERECHA);
  verticales0grados();
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  retraerArriba();
  retraerAbajo();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_ARRIBA);
  servoPrincipal90grados(PRINCIPAL_ABAJO);
  delay(1000);
  extenderArriba();
  extenderAbajo();
  delay(1000);
}

void r(){
  servoPrincipal180grados(PRINCIPAL_DERECHA);
  delay(1000);
  retraerDerecha();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_DERECHA);
  delay(1000);
  extenderDerecha();
  delay(1000);
}


void rprima(){
  servoPrincipal0grados(PRINCIPAL_DERECHA);
  delay(1000);
  retraerDerecha();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_DERECHA);
  delay(1000);
  extenderDerecha();
  delay(1000);
}

void u(){
  servoPrincipal180grados(PRINCIPAL_ARRIBA);
  delay(1000);
  retraerArriba();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_ARRIBA);
  delay(1000);
  extenderArriba();
  delay(1000);
}

void uprima(){
  servoPrincipal0grados(PRINCIPAL_ARRIBA);
  delay(1000);
  retraerArriba();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_ARRIBA);
  delay(1000);
  extenderArriba();
  delay(1000);
}

void l(){
  servoPrincipal180grados(PRINCIPAL_IZQUIERDA);
  delay(1000);
  retraerIzquierda();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_IZQUIERDA);
  delay(1000);
  extenderIzquierda();
  delay(1000);
}

void lprima(){
  servoPrincipal0grados(PRINCIPAL_IZQUIERDA);
  delay(1000);
  retraerIzquierda();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_IZQUIERDA);
  delay(1000);
  extenderIzquierda();
  delay(1000);
}

void d(){
  retraerArriba();
  delay(1000);
  servoPrincipal180grados(PRINCIPAL_ABAJO);
  delay(1000);
  retraerAbajo();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_ABAJO);
  delay(1000);
  extenderAbajo();
  extenderArriba();
  delay(1000);
}

void dprima(){
  retraerArriba();
  delay(1000);
  servoPrincipal0grados(PRINCIPAL_ABAJO);
  delay(1000);
  retraerAbajo();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_ABAJO);
  delay(1000);
  extenderAbajo();
  extenderArriba();
  delay(1000);
}

void f2(){
  retraerArriba();
  retraerAbajo();
  delay(1000);
  verticales180grados();
  delay(1000);
  extenderArriba();
  extenderAbajo();
  delay(1000);
  retraerIzquierda();
  retraerDerecha();
  delay(1000);
  verticales90grados();
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  servoPrincipal180grados(PRINCIPAL_DERECHA);
  delay(1000);
  retraerDerecha();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_DERECHA);
  delay(1000);
  extenderDerecha();
  delay(1000);
  servoPrincipal180grados(PRINCIPAL_DERECHA);
  delay(1000);
  retraerDerecha();
  retraerIzquierda();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_DERECHA);
  verticales180grados();
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  retraerArriba();
  retraerAbajo();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_ARRIBA);
  servoPrincipal90grados(PRINCIPAL_ABAJO);
  delay(1000);
  extenderArriba();
  extenderAbajo();
  delay(1000);
}

void b2(){
  retraerArriba();
  retraerAbajo();
  delay(1000);
  verticales0grados();
  delay(1000);
  extenderArriba();
  extenderAbajo();
  delay(1000);
  retraerIzquierda();
  retraerDerecha();
  delay(1000);
  verticales90grados();
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  servoPrincipal180grados(PRINCIPAL_DERECHA);
  delay(1000);
  retraerDerecha();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_DERECHA);
  delay(1000);
  extenderDerecha();
  delay(1000);
  servoPrincipal180grados(PRINCIPAL_DERECHA);
  delay(1000);
  retraerDerecha();
  retraerIzquierda();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_DERECHA);
  verticales0grados();
  delay(1000);
  extenderDerecha();
  extenderIzquierda();
  delay(1000);
  retraerArriba();
  retraerAbajo();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_ARRIBA);
  servoPrincipal90grados(PRINCIPAL_ABAJO);
  delay(1000);
  extenderArriba();
  extenderAbajo();
  delay(1000);
}

void l2(){
  l();
  l();
}

void r2(){
  r();
  r();
}

void u2(){
  u();
  u();
}

void d2(){
  d();
  d();
}
/*void servoPrincipal0grados(int numServo){
  Serial.println("Se ha entrado en la funcion servo principal 0 grados con servo");
  incremento = INCREMENTO_INICIAL; 
  short posicionInicial = posiciones[numServo-8];
  for(; posiciones[numServo-8]>500;posiciones[numServo-8]-=incremento){
    if (posiciones[numServo-8] == posicionInicial-10){
      incremento = INCREMENTO_FINAL;  
    }
    digitalWrite(numServo, HIGH);
    delayMicroseconds(posiciones[numServo-8]);
    digitalWrite(numServo, LOW);
    delayMicroseconds(period - posiciones[numServo-8]);
  }

  posiciones[numServo-8] = 500; // Saturamos la posicion a cero grados
  delay(10);
}*/

/*void servoPrincipal180grados(int numServo){
  Serial.println("Se ha entrado en la funcion servo principal 180 grados con servo");
  incremento = INCREMENTO_INICIAL; 
  short posicionInicial = posiciones[numServo-8];
  for(; posiciones[numServo-8]<2500;posiciones[numServo-8]+=incremento){
    if (posiciones[numServo-8] == posicionInicial+10){
      incremento = INCREMENTO_FINAL;  
    }
    digitalWrite(numServo, HIGH);
    delayMicroseconds(posiciones[numServo-8]);
    digitalWrite(numServo, LOW);
    delayMicroseconds(period - posiciones[numServo-8]);
  }

  posiciones[numServo-8] = 2500; // Saturamos la posicion a cero grados
  delay(10);
}*/

/*void servoPrincipal90grados(int numServo)
{
  Serial.println("Se ha entrado en la funcion servo principal 90 grados con servo");

  short posicionInicial = posiciones[numServo-8];

  if (posicionInicial < 1500){
    incremento = INCREMENTO_INICIAL;
    for(; posiciones[numServo-8]<1500;posiciones[numServo-8]+=incremento){
      if (posiciones[numServo-8] == posicionInicial+10){
        incremento = INCREMENTO_FINAL;  
      }
      digitalWrite(numServo, HIGH);
      delayMicroseconds(posiciones[numServo-8]);
      digitalWrite(numServo, LOW);
      delayMicroseconds(period - posiciones[numServo-8]);
    }
    posiciones[numServo-8] = 1500;
    delay(10);
  } else if (posicionInicial > 1500){
     incremento = INCREMENTO_INICIAL;
     for(; posiciones[numServo-8]>1500;posiciones[numServo-8]-=incremento){
      if (posiciones[numServo-8] == posicionInicial-10){
        incremento = INCREMENTO_FINAL;  
      }
      digitalWrite(numServo, HIGH);
      delayMicroseconds(posiciones[numServo-8]);
      digitalWrite(numServo, LOW);
      delayMicroseconds(period - posiciones[numServo-8]);
    }
    posiciones[numServo-8] = 1500;
    delay(10);
  }
}*/

void posicionEsperaCubo(){
  verticales0grados();
  extenderAbajo();
}

void initServos(){
  retraerIzquierda();
  delay(1000);
  retraerArriba();
  delay(1000);
  retraerDerecha();
  delay(1000);
  retraerAbajo();
  delay(1000);
  servoPrincipal90grados(PRINCIPAL_IZQUIERDA);
  delay(500);
  servoPrincipal90grados(PRINCIPAL_ARRIBA);
  delay(500);
  servoPrincipal90grados(PRINCIPAL_DERECHA);
  delay(500);
  servoPrincipal90grados(PRINCIPAL_ABAJO);
  delay(500);
  /*initServo(PRINCIPAL_IZQUIERDA);
  delay(200);
  initServo(PRINCIPAL_ARRIBA);
  delay(200);
  initServo(PRINCIPAL_DERECHA);
  delay(200);
  initServo(PRINCIPAL_ABAJO);
  delay(200);*/
  // La posicion de espera al cubo parte de la posicion final de inicializacion,
  // con todos los motores retraidos y en 90 grados
  posicionEsperaCubo();
}

void setup() {
  // put your setup code here, to run once:
  //myservo.attach(9);
  pinMode(PRINCIPAL_ARRIBA, OUTPUT);
  pinMode(PRINCIPAL_ABAJO, OUTPUT);
  pinMode(PRINCIPAL_DERECHA, OUTPUT);
  pinMode(PRINCIPAL_IZQUIERDA, OUTPUT);
  auxiliarIzquierdo.attach(AUXILIAR_IZQUIERDA);
  auxiliarDerecho.attach(AUXILIAR_DERECHA);
  auxiliarArriba.attach(AUXILIAR_ARRIBA);
  auxiliarAbajo.attach(AUXILIAR_ABAJO);

  recepcionSerial.reserve(200);
  Serial.begin(9600);
  initServos();
}

void loop() {
  if(Serial.available()){
    recepcionSerial = Serial.readString();
    if (recepcionSerial == "U0\n"){
      servoPrincipal0grados(PRINCIPAL_ARRIBA);
    } else if (recepcionSerial == "I\n"){
      Serial.println("Ha entrado en la funcion");
      extenderArriba();
      delay(1000);
      verticales90grados();
      delay(1000);
      extenderDerecha();
      extenderIzquierda();
      delay(1000);
    } else if (recepcionSerial == "F"){
      f();
      Serial.println("OK");
    } else if (recepcionSerial == "F'"){
      fprima();
      Serial.println("OK");
    } else if (recepcionSerial == "F2"){
      f2();
      Serial.println("OK");
    }else if (recepcionSerial == "B"){
      b();
      Serial.println("OK");
    } else if (recepcionSerial == "B'"){
      bprima();
      Serial.println("OK");
    } else if (recepcionSerial == "B2"){
      b2();
      Serial.println("OK");
    } else if (recepcionSerial == "U"){
      u();
      Serial.println("OK");
    } else if (recepcionSerial == "U'"){
      uprima();
      Serial.println("OK");
    } else if (recepcionSerial == "U2"){
      u2();
      Serial.println("OK");
    }  else if (recepcionSerial == "D"){
      d();
      Serial.println("OK");
    } else if (recepcionSerial == "D'"){
      dprima();
      Serial.println("OK");
    } else if (recepcionSerial == "D2"){
      d2();
      Serial.println("OK");
    } else if (recepcionSerial == "R"){
      r();
      Serial.println("OK");
    } else if (recepcionSerial == "R'"){
      rprima();
      Serial.println("OK");
    } else if (recepcionSerial == "R2"){
      r2();
      Serial.println("OK");
    } else if (recepcionSerial == "L"){
      l();
      Serial.println("OK");
    } else if (recepcionSerial == "L'"){
      lprima();
      Serial.println("OK");
    } else if (recepcionSerial == "L2"){
      l2();
      Serial.println("OK");
    } else if (recepcionSerial == "E"){
      retraerIzquierda();
      retraerDerecha();
      delay(1000);
      verticales0grados();
      delay(1000);
      retraerArriba();
    }
    else if (recepcionSerial == "U90\n"){
      servoPrincipal90grados(PRINCIPAL_ARRIBA);
    } else if (recepcionSerial == "U180\n"){
      servoPrincipal180grados(PRINCIPAL_ARRIBA);
    } else if (recepcionSerial == "L0\n"){
      servoPrincipal0grados(PRINCIPAL_IZQUIERDA);
    } else if (recepcionSerial == "L90\n"){
      servoPrincipal90grados(PRINCIPAL_IZQUIERDA);
    } else if (recepcionSerial == "L180\n"){
      servoPrincipal180grados(PRINCIPAL_IZQUIERDA);
    } else if (recepcionSerial == "D0\n"){
      servoPrincipal0grados(PRINCIPAL_ABAJO);
    } else if (recepcionSerial == "D90\n"){
      servoPrincipal90grados(PRINCIPAL_ABAJO);
    } else if (recepcionSerial == "D180\n"){
      servoPrincipal180grados(PRINCIPAL_ABAJO);
    } else if (recepcionSerial == "R0\n"){
      servoPrincipal0grados(PRINCIPAL_DERECHA);
    } else if (recepcionSerial == "R90\n"){
      servoPrincipal90grados(PRINCIPAL_DERECHA);
    } else if (recepcionSerial == "R180\n"){
      servoPrincipal180grados(PRINCIPAL_DERECHA);
    } else if (recepcionSerial == "START\n"){
      horizontales90grados();
      delay(1000);
      extenderDerecha();
      extenderIzquierda();
      delay(1000);
    } else if (recepcionSerial == "R\n"){
      // Rotamos la cara de la derecha en sentido horario
      servoPrincipal180grados(PRINCIPAL_DERECHA);
      delay(1000);
      retraerDerecha();
      delay(1000);
      servoPrincipal90grados(PRINCIPAL_DERECHA);
      delay(1000);
      extenderDerecha();
      delay(1000);
    } else if (recepcionSerial == "DETECTAR"){
      detectarCubo();
    }else if (recepcionSerial == "V0\n"){
      verticales0grados();
    } else if (recepcionSerial == "V90\n"){
      verticales90grados();
    } else if (recepcionSerial == "V180\n"){
      verticales180grados();
    } else if (recepcionSerial == "H0\n"){
      horizontales0grados();
    } else if (recepcionSerial == "H90\n"){
      horizontales90grados();
    } else if (recepcionSerial == "H180\n"){
      horizontales180grados();
    }
  }
  // put your main code here, to run repeatedly:
  /*for(dutycycle = 500; dutycycle <= 2500; dutycycle+=incremento)
  {
    if (dutycycle == 550){
      incremento = 5;
    }
    digitalWrite(pin, HIGH);
    delayMicroseconds(dutycycle);
    digitalWrite(pin, LOW);
    delayMicroseconds(period - dutycycle);
  }

  incremento = 2;
  delay(1000);
  for(dutycycle = 2500; dutycycle >= 500; dutycycle-=incremento)
  {
    if (dutycycle == 2450){
      incremento = 5;
    }
    digitalWrite(pin, HIGH);
    delayMicroseconds(dutycycle);
    digitalWrite(pin, LOW);
    delayMicroseconds(period - dutycycle);
  }*/

  /*incremento = 2;
  delay(1000);*/
  

  /*int i = 0;
  for(i = 0; i < 500; i++){
      digitalWrite(pin, HIGH);
    delayMicroseconds(2500);
    digitalWrite(pin, LOW);
    delayMicroseconds(period-2500);
  }

  delay(2000);
  for (i=0; i< 500; i++)
  {
      digitalWrite(pin, HIGH);
    delayMicroseconds(500);
    digitalWrite(pin, LOW);
    delayMicroseconds(period-500);
  }*/
  

  

  /*for (pos = 0; pos <= 180; pos+=2){
    myservo.write(pos);
    delay(15);
  }

  delay(2000);

  for (pos = 180; pos >= 0; pos-=2){
    myservo.write(pos);
    delay(15);
  }

  delay (2000);*/
}
