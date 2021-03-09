/* Author: Caio Elizio - caioelizio@gmail.com 62 98223-9516"
 * Date: 25/11/20
 * Display Nokia
 * Versao 1.0 
 */
//Prototypes
void iniDisplay();
void setupDisplay();
void f_display_WifiScan();
void f_display_WifiScan_v2();

void iniDisplay() {
  Serial.println("Iniciando display");
  display.begin();
  display.setContrast(60);  //0-100 padrao 60
  display.clearDisplay();  // clears the screen and buffer
  display.setTextSize(0);
  display.setTextColor(BLACK, WHITE);
  display.print(F("--------------")); //13 linhas
  display.print("Iniciando");
  display.println();
  display.print("display");
  display.println();
  display.print(F("--------------")); //13 linhas
  display.display();
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
