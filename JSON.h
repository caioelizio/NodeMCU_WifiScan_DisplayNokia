/* Author: Caio Elizio - caioelizio@gmail.com 62 98223-9516"
 * Date: 27/02/21
 * JSON
 * Version 1.0
 */
//Prototypes
boolean JsonWifiScan_Read();
boolean JsonWifiScan_Save();

boolean JsonWifiScan_Read() {
  log(F("Lê configuração JSON"));
  StaticJsonDocument<JSON_SIZE> jsonDHT;

  File file = SPIFFS.open(F("/WifiScan.json"), "r");
  if (deserializeJson(jsonDHT, file)) {
    log(F("Falha lendo dht.json, assumindo valores padrão."));
//    configReset();
    return false;
  } else {
    log(F("Sucesso na leitura da configuração JSON "));
//    f_temp   = jsonDHT["SSID"]   | 0;
//    f_temp   = jsonDHT["RSSI"]   | 0;
//  datahora = jsonDHT["datahora"] | 0;

    file.close();
    log(F("\nLendo configuração WifiScan.json"));
    serializeJsonPretty(jsonDHT, Serial);
    log("");
    return true;
  }
}

boolean JsonWifiScan_Save() { //Grava configuração
  StaticJsonDocument<JSON_SIZE> jsonDHT;
  File file = SPIFFS.open(F("/WifiScan.json"), "w+");
  if (file) {
    // Atribui valores ao JSON e grava
    jsonDHT["SSID"]     = sSSID;
    jsonDHT["RSSI"]     = sRSSI;
    jsonDHT["datahora"] = "";
    serializeJsonPretty(jsonDHT, file);
    file.close();

    log(F("\nGravando WifiScan.json"));
    serializeJsonPretty(jsonDHT, Serial);
//    log("");
    return true;
  }
  return false;
}
