/* Author: Caio Elizio - caioelizio@gmail.com 62 98223-9516"
 * Date: 25/11/20
 * Display Nokia
 * Versao 1.0 
 */
//Prototypes
void iniDisplay();
void setupDisplay();

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
