#include "zpallo.h"

// Variables Globales
// Parametro a 
byte TRES[NEDS] = {0x03}; // 3 
byte UNO[NEDS] = {0x01};  // 1
byte a[NEDS]; // Calculo en Setup
// Cantidad de Test
#define CANT_TEST 10

void setup() {
  // Habilita comunicacion serial a 115200
  Serial.begin(115200);
  randomSeed(analogRead(0));

  // Agregado  Inicial a la comunicacion Serial (Start)
  Serial.print("ECC ");Serial.println(NEDS*8);
  Serial.print("Numero de bloques 8bit : ");
  Serial.println(NEDS);
  //Serial.println("Parametros Iniciales");
  /*
  Serial.print("P :");
  print_datoln(get_curve_p());
  Serial.print("N :");
  print_datoln(get_curve_n());
  Serial.print("Gx:");
  print_datoln(get_curve_g().x);
  Serial.print("Gy:");
  print_datoln(get_curve_g().y);
  vli_modSub(a,get_curve_p(),TRES,get_curve_p()); // a = -3
  Serial.print("a: ");
  print_datoln(a);
  Serial.print("b :");
  print_datoln(get_curve_b());*/
}

void loop() {
  int rp;
  byte DX[NEDS],DY[NEDS],DZ[NEDS],k[NEDS];
  rp=random(10);
  for(rp=0;rp<10;rp+=1){
    generateK(k); //ponla afuera para que sea un K fijo.
    JA_left_to_right(DX,DY,DZ,get_points_test()[rp].x,get_points_test()[rp].y,UNO,k);
    Serial.print("ITERACION: ");Serial.println(rp+1);
    //Serial.print("Cant. Adiciones: ");Serial.println(sumas);
    Serial.print("K: ");print_datoln(k);
    Serial.print("DX: ");print_datoln(DX);
    Serial.print("DY: ");print_datoln(DY);  
    Serial.print("DZ: ");print_datoln(DZ);
  }
  delay(7000);
}
