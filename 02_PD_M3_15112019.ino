// Variables para el motor
int m3_enA = 28;
int m3_enB = 29;
int m3_out = 3;

//Variables del robot
float theta3;

// Referencia para articulaciones
float theta3_d = 0.0;

//Variables para el cálculo del control
float actual_e3;
float past_e3;
float kp3 = 20;
float kd3 = 2;
bool fl = true;
float dot_e3;

//Variable del controlador
float u3;

void paro_M3();
void giro_M3_A();
void giro_M3_B();

unsigned long actualTime;
float deltaTime = 0.05;
unsigned long pastTime;




void setup() {
  pinMode(m3_enA,OUTPUT);
  pinMode(m3_enB,OUTPUT);
  pinMode(m3_out,OUTPUT);
  
  Serial.begin(9600);
  pastTime = 0;
}

void loop() {
  actualTime = millis();
  theta3 = (float(analogRead(A3)-650))*90/280;
  Serial.print("Theta_3: "); Serial.print(theta3);


  actual_e3 = theta3_d - theta3;
  Serial.print("   e3: "); Serial.print(actual_e3);

  dot_e3 =  (actual_e3 - past_e3)/deltaTime;

  u3 = -kp3*actual_e3 - kd3*dot_e3;

  
  Serial.print("   u3: "); Serial.print(u3);

  if (u3<0)
    giro_M3_B();    
  else
    giro_M3_A();

  u3 = abs(u3);
  if (u3 > 255)
    u3 = 250;

  analogWrite(m3_out,int(u3));
  deltaTime = float(actualTime - pastTime)/1000;

  Serial.print("   DeltaTime: "); Serial.println(deltaTime);
  pastTime = actualTime;
  past_e3 = actual_e3;
  

  


}
void paro_M3(){
  Serial.println("Paro M3");
  digitalWrite(m3_enA,0);
  digitalWrite(m3_enB,0);
}

void giro_M3_A(){
  //Serial.println("Girando M3 A");
  digitalWrite(m3_enA,1);
  digitalWrite(m3_enB,0);
}

void giro_M3_B(){
  //Serial.println("Girando M3 B");
  digitalWrite(m3_enA,0);
  digitalWrite(m3_enB,1);
}
