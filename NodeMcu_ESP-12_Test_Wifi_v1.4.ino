/*********************************************************************/
  #define autor       "Caio Elizio - caioelizio@gmail.com 62 98223-9516"
  #define programa    " Test Wifi Display Nokia 5110"
  #define Version     "v1.3"
  #define dataversion "03/03/2021"
  #define placa       "NodeMcu ESP-12"
/*********************************************************************/
/*Lista de Peças: 
  1 NodeMcu ESP-12
  1 Fonte 5v Powerbanck
  1 Display Nokia
*/
//Prototypes
void iniDisplay();
void clickEvent(void);
void doubleClickEvent(void);
void holdEvent(void);
void longHoldEvent(void);

//import------------------------------------------------
#include "config.h"
#include "funcoes_sis.h"
#include "JSON.h"
#include "DisplayNokia.h"
#include "WifiScan.h"

//Inicialização----------------------------------------------------
void setup() {
  initOutput(); //Define a porta status de saida e entrada / *depois de ini a serial
  initSerial();
  iniDisplay();

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(500);         //Espera 1 segundo 
}

int delayTime = 1000;
unsigned long lastTime = millis();
//*Repetição programa principal---------------------------------------------
void loop() {
  // Aguarda o tempo defino em delayTime para executar 
  if ((millis() - lastTime) > delayTime) {
    f_WifiScan();
    lastTime = millis();
  }

  int b = checkButton();
   if (b == 1) clickEvent();
   if (b == 2) doubleClickEvent();
   if (b == 3) holdEvent();
   if (b == 4) longHoldEvent();
}
