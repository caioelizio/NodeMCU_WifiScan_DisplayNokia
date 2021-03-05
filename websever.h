/* Author: Caio Elizio - caioelizio@gmail.com 62 98223-9516"
 * Date: 27/02/21
 * Websever
 * Version 1.0
 */
//Prototypes
void iniWebsever();
void handleDashboard();

void iniWebsever() {
  if (!SPIFFS.begin()) {
    Serial.println(F("SPIFFS ERRO"));
    while (true);
  }
//  Serial.println(F("WebServer Pronto"));
}

//Requisições Web --------------------------------------
void handleDashboard() {
  File file = SPIFFS.open("/dashboard.html", "r");
  if (file) {
    file.setTimeout(100);
    String s = file.readString();
    file.close();
    Serial.println(F("\nAtualiza conteúdo dinâmico dashboard.html"));
//    s.replace("#ID_esp#"        , ID_esp);
//    s.replace("#cSensor#"       , cSensor);

//    server.send(200, "text/html", s); //Send data //Envia dados
//    Serial.println("Dashboard: " + ipStr(server.client().remoteIP()));  
  } else {
//    server.send(500, "text/plain", "Dashboard - ERROR 500");
//    Serial.println(F("Dashboard - ERRO lendo arquivo"));
  }
}  
