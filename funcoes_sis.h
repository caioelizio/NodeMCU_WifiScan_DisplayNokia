/* Author: Caio Elizio - caioelizio@gmail.com 62 98223-9516"
 * Date: 25/11/20
 * Functions System / funções do Sistema
 * Versao 1.0 
 */
//Prototypes
void initOutput(void);
void initSerial();
void f_Serial_Sistema();
void f_ledonboard(boolean b_valor);
int  EEPROM_Read(int i_end_EEPROM);
void EEPROM_Write(int end_EEPROM_w,int i_valor);
void EEPROM_Clear();
void f_timeClock();
void f_Serial_TempoAtivo();
void sendNTPpacket(IPAddress &address);
void log(String s);
String softwareStr();
String longTimeStr();
String hexStr();
String ipStr();
String deviceID();

void initOutput(void) {
  pinMode(pinLedonboard, OUTPUT);
  pinMode(pinButton,     INPUT);
  
  digitalWrite(pinLedonboard, ON);
}
void initSerial() {
  Serial.begin(115200); //9600 da erro, caindo conexao...
  delay(10);
  Serial.println();
  Serial.println(F("Iniciando Serial..."));  
  Serial.println();
  Serial.println(F("Definindo pinos como INPUT ou OUTPUT..."));
  Serial.println(F("<---------Definindo pinos como ON ou OFF---------->"));
  Serial.print  (F("pinLedonboard "));   Serial.println(F(" OFF"));
//
  Serial.println(F("<------------------------------------------------->"));
}
void f_Serial_Sistema(){
  Serial.println();
  Serial.println(F("<----------------Informações Sistema-------------->"));
  Serial.print(F("Autor:   "));         Serial.println(autor);
  Serial.print(F("Sistema: "));         Serial.print(ID_esp); Serial.print(F(" - ")); Serial.println(Version);
  Serial.print(F("Data Versao: "));     Serial.println(dataversion);
  Serial.print(F("Número de Reset: ")); Serial.println(bootCount); //Número de inicializações
//  Serial.print(F("Tempo Ativo: "));   Serial.println(longTimeStr(millis() / 1000)); //tempo desde o ultimo reset
  f_Serial_TempoAtivo(); //ok
  Serial.print(F("Websever: http://")); Serial.print(ipLocal);   Serial.println(F("/"));
  //Serial.print("Websever: http://" + ipStr(WiFi.softAPIP()));  Serial.println(F("/"));
  //Serial.print(F("WiFi AP: "));            Serial.println(String(ID_esp));
  Serial.println(F("<------------------------------------------------->"));
}

//Funções Genéricas--------------------------------------
void log(String s) {
  // Gera log na Serial
  Serial.println(s);
}
String softwareStr() {
  // Retorna nome do software
  return String(__FILE__).substring(String(__FILE__).lastIndexOf("\\") + 1);
}
String longTimeStr(const time_t &t){
  // Retorna segundos como "d:hh:mm:ss"
  String s = String(t / SECS_PER_DAY) + ":";
  if (hour(t) < 10) {   s += "0"; }
  s += String(hour(t)) + ":";
  if (minute(t) < 10) { s += "0"; }
  s += String(minute(t)) + ":";
  if (second(t) < 10) { s += "0"; }
  s += String(second(t));
  return s;
}
String hexStr(const unsigned long &h, const byte &l = 8) {
  // Retorna valor em formato hexadecimal
  String s;
  s= String(h, HEX);
  s.toUpperCase();
  s = ("00000000" + s).substring(s.length() + 8 - l);
  return s;
}
String ipStr(const IPAddress &ip) {
  // Retorna IPAddress em formato "n.n.n.n"
  String sFn = "";
  for (byte bFn = 0; bFn < 3; bFn++) {
    sFn += String((ip >> (8 * bFn)) & 0xFF) + ".";
  }
  sFn += String(((ip >> 8 * 3)) & 0xFF);
  return sFn;
}
String deviceID(){ // Retorna ID padrão
//  return ID_esp;
  return hostnameOTA;
}

//Função: leitura da memoria da ESP
int EEPROM_Read(int i_end_EEPROM){
  byte b_value = EEPROM.read(i_end_EEPROM);  //read a byte from the current address 0-511
  if (b_debug == true){
//    Serial.println();
    Serial.print(F("Endereco memoria EEPROM: "));  Serial.print(i_end_EEPROM);
    Serial.print(F("\t")); //espaço
    Serial.print(F(" Valor read: "));  Serial.print(b_value, DEC);
    Serial.println();
  }
  if (i_end_EEPROM >= 512){ //EEPROM_Read(0-511)
    Serial.print(F("Erro endereco de memoria! Valor maior que 512"));
    return 512;
  }
  //delay(500);
  return b_value;
}
void EEPROM_Write(int end_EEPROM_w,int i_valor){ //EEPROM_Write(0-511,0-511)
  //write the value to the appropriate byte of the EEPROM.
  //these values will remain there when the board is turned off.
  EEPROM.write(end_EEPROM_w, i_valor);
  if (b_debug == true){
    Serial.println();
    Serial.print(F("Endereco memoria: ")); Serial.print(end_EEPROM_w);
    Serial.print(F("\t")); //espaço
    Serial.print(F("Valor write: "));      Serial.println(i_valor, DEC);
  }
  if (i_valor >= 512){
    Serial.print(F("Valor maior que 512, erro endereco de memoria!"));
  }else{
    EEPROM.commit();
  };
  if (EEPROM.commit()) {
//    Serial.println(F("EEPROM sucMsgessfully committed"));
  } else {
    Serial.println(F("ERROR! EEPROM commit failed"));
  }
  //delay(100);
}
void EEPROM_Clear(){ // write a 0 to all 512 bytes of the EEPROM
  EEPROM.begin(512);
    for (int i = 0; i < 512; i++) EEPROM.write(i, 0);
  EEPROM.end();
}

void f_ledonboard(boolean b_valor){ //acende e apaga o led da ESP
  if (b_valor == ON) {
    digitalWrite(pinLedonboard, ON);  //LED 
    Serial.print("Led ESP "); Serial.println("ON");
  } else {
    digitalWrite(pinLedonboard, OFF); //LED 
    Serial.print("Led ESP "); Serial.println("OFF");  
  }
}

void f_timeClock(){
  i_valor = millis()/1000;
  i_segAtivo   = i_valor % 60;
  i_valor = i_valor / 60;
  i_minAtivo   = i_valor % 60;
  i_valor = i_valor / 60;
  i_horasAtivo = i_valor;
}
void f_Serial_TempoAtivo(){
//  Serial.print(F("Tempo Ativo: ")); Serial.println(longTimeStr(millis() / 1000)); //tempo desde o ultimo reset
//erro  Serial.println();
  Serial.print(F("Tempo Ativo:  "));
  if (i_horasAtivo < 10){ Serial.print(F("0")); } Serial.print(i_horasAtivo); Serial.print(F(":"));
  if (i_minAtivo   < 10){ Serial.print(F("0")); } Serial.print(i_minAtivo);   Serial.print(F(":"));
  if (i_segAtivo   < 10){ Serial.print(F("0")); } Serial.println(i_segAtivo);
}
