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
      sRSSI = String( WiFi.RSSI(i)+100);
      if (bBreak){
        Serial.print("Sinal sRSSI:");
        Serial.print(" ("); Serial.print(sRSSI); Serial.println(")");
        f_display_WifiScan(i,n);
        break;
      }
      sSSID = WiFi.SSID(i);
//      sRSSI = String( WiFi.RSSI(i)+100);
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print("-"); Serial.print(n); Serial.print(": ");
      Serial.print(sSSID);
      Serial.print(" ("); Serial.print(sRSSI); Serial.println(")");
//      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");

      f_display_WifiScan(i,n);
//      f_display_WifiScan_v2(i,n);



      JsonWifiScan_Save();
      display.display();
    }
  }
  Serial.println();
  Serial.print("bBreak "); Serial.println(bBreak);
}
