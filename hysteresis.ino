#include <TimerOne.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define TERM_PIN A0
#define RELAY_PELTIER 5
#define RELAY_FAN 6

float Tamb = 0;   
float Tsup = 0;   
float consigna = 0; 
float dT1 = 0;
float dT2 = 0;

bool peltierON = false;
bool fanON = false; // control manual desde Processing

volatile bool flagSerial = false; // bandera para imprimir Serial

// ---- ISR del Timer1 ----
void intu() {
  flagSerial = true; // activa la impresión de datos
}

// ---- Setup ----
void setup() {
  Serial.begin(9600);
  dht.begin();
  
  pinMode(RELAY_PELTIER, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  
  digitalWrite(RELAY_PELTIER, LOW);
  digitalWrite(RELAY_FAN, LOW);    

  Timer1.initialize(1000000);     // 1 segundo
  Timer1.attachInterrupt(intu);   // llama a intu() cada segundo
}

// ---- Loop principal ----
void loop() {
  // Leer sensores
  Tamb = dht.readTemperature();
  Tsup = leerTermistor();

  // Histéresis Peltier (solo si consigna >0)
  if(consigna > 0){
    if (peltierON) {
      if (Tsup <= consigna - dT2) peltierON = false;
      else if (Tsup >= consigna + dT1) peltierON = true;
    } else {
      if (Tsup >= consigna + dT1) peltierON = true;
    }
  }

  // Control de relés
  digitalWrite(RELAY_PELTIER, peltierON ? HIGH : LOW);
  digitalWrite(RELAY_FAN, fanON ? HIGH : LOW);

  // ---- Serial cada 1 segundo usando bandera ----
  if (flagSerial) {
    flagSerial = false;
    Serial.print(Tamb,2); Serial.print(",");
    Serial.print(Tsup,2); Serial.print(",");
    Serial.print(peltierON ? "1" : "0"); Serial.print(",");
    Serial.println(fanON ? "1" : "0");
  }

  // ---- Comandos desde Processing ----
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd.startsWith("SET")) {
      int idx1 = cmd.indexOf(',');
      int idx2 = cmd.indexOf(',', idx1 + 1);
      int idx3 = cmd.indexOf(',', idx2 + 1);
      if (idx1 > 0 && idx2 > 0 && idx3 > 0){
        consigna = cmd.substring(idx1 + 1, idx2).toFloat();
        dT1 = cmd.substring(idx2 + 1, idx3).toFloat();
        dT2 = cmd.substring(idx3 + 1).toFloat();
        peltierON = true; // activar Peltier al iniciar ensayo
      }
    } else if (cmd.startsWith("FAN_ON")) fanON = true;
    else if (cmd.startsWith("FAN_OFF")) fanON = false;
  }
}

// ---- Función termistor ajustada ----
float leerTermistor() {
  int val = analogRead(TERM_PIN);
  float V = (val * 5.0) / 1023.0;
  // Polinomio original (puedes ajustar según tu sensor)
return -0.1572*V*V*V*V*V + 2.1731*V*V*V*V - 13.09*V*V*V + 42.653*V*V - 93.647*V + 127.54;

}