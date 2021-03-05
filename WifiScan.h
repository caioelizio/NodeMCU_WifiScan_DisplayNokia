/* Author: Caio Elizio - caioelizio@gmail.com 62 98223-9516"
 * Date: 08/08/20
 * WifiScan
 * Version 1.0 
 */
//Prototypes
void f_WifiScan();
void f_display_WifiScan(int i,int n);
void f_display_WifiScan_v2(int i,int n);

void f_WifiScan() {
  Serial.println("scan start");
  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("Nenhuma rede localizada");
  } else {
    Serial.print("Total redes: "); Serial.println(n);
    display.clearDisplay();  // clears the screen and buffer
    for (int i = 0; i < n; ++i) {
/*      if (i == 3){
        Serial.println("quebra linha");
        display.setCursor(0,0);
//        display.clearDisplay();  // clears the screen and buffer
      }//*/

      sSSID = WiFi.SSID(i);
      sRSSI = String( WiFi.RSSI(i)+100) ;
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print("-"); Serial.print(n); Serial.print(": ");
      Serial.print(sSSID);
      Serial.print(" ("); Serial.print(sRSSI); Serial.print(")");
//      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");

      f_display_WifiScan(i,n);
//      f_display_WifiScan_v2(i,n);

      JsonWifiScan_Save();

      display.display();
    }
  }
  Serial.println();
}

void f_display_WifiScan(int i,int n) {
    display.clearDisplay();  // clears the screen and buffer
    display.setTextSize(0); //tamanho font 0 peq / 1 media / 2 grande / 3 gigante
    display.setTextColor(BLACK, WHITE);
        display.print(String(i + 1));
        display.print("-"); display.print(n); display.print(": ");
        display.print(WiFi.RSSI(i)+100);
        display.println();
        display.print(WiFi.SSID(i));
        display.println();
    display.display();
}
void f_display_WifiScan_v2(int i,int n) {
    display.setTextSize(0); //tamanho font 0 peq / 1 media / 2 grande / 3 gigante
    display.setTextColor(BLACK, WHITE);
        display.print(WiFi.SSID(i));
        display.println(":");
        display.print(WiFi.RSSI(i)+100);
        display.println();
//        display.print("Forca sinal:"); display.print(WiFi.RSSI(i)+100);
//        display.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
//    display.display();
}
