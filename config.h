/* Author: Caio Elizio - caioelizio@gmail.com 62 98223-9516"
 * Date: 25/11/20
 * Settings / Configurações
 * Versao 1.0 
 */ 
//defines - mapeamento de pinos do NodeMCU
  #define D0    16
  #define D1    5  //* 3.3v
  #define D2    4  //*
  #define D3    0  //scl
  #define D4    2  //sda
  #define D5    14 //*
  #define D6    12 //*
  #define D7    13 //*
  #define D8    15
  #define D9    3
  #define D10   1  //*/


//Pinagem--------------------------------------------------
  #define pinLedonboard LED_BUILTIN //ou BUILTIN_LED
  #define pinButton     D0

//Display LCD Nokia 5110 - ESP
#include <SPI.h> // Software SPI (slower updates, more flexible pin options):
//#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
  const int8_t RST_PIN = D2;  //LCD reset (RST)           D3 
  const int8_t CE_PIN  = D1;  //LCD chip select (CS)      D4 
  const int8_t DC_PIN  = D6;  //Data/Command select (D/C) D5
  const int8_t DIN_PIN = D7;  //Serial data out (DIN)     D6
  const int8_t CLK_PIN = D5;  //Serial clock out (SCLK)   D7
//  const int8_t BL_PIN  = D0;  //ou liga pino direto no 3.3v

  //Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN, DIN_PIN, CLK_PIN);
  Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);
  #define NUMFLAKES 10
  #define XPOS 0
  #define YPOS 1
  #define DELTAY 2
  //*/
 
//Rf433
 int x,startbit,ctr,dataok,t1,larpulso,larpulso1,larpulso2,larpulso3,larpulso4,bt1,bt2,antcode=0;    
 unsigned long _data = 0;  //DATA recebi codigo do HT6p20 28 BITS, 22 do codigo +2 dos botões +4 do anti-codigo;
 unsigned long _dur,_dur1; //Duração do Pulso    
 int liga_desliga = 1;     //variável para saber se o led/alarme está ligado ou desligado    
 int resultado    = 0;     //resultado do módulo (%) da divisão, se restar ele é 1, se não restar é 0    



//Variáveis e objetos globais--------------------------------------
  #define ON  1
  #define OFF 0
  boolean b_debug  = false;
  //boolean b_debug  = true;
//
  int iStatusLedOnboard = 0;
  boolean bsomteclas    = false;
  int iStatusR1         = 0;
  int iStatusR2         = 0;
//  char* cStatusR1       = "OFF";
//  char* cStatusR2       = "OFF";
//Sensor PIR
  int iSensorPIR      = 0;  //Variavel para guardar valor do sensor
  int i_ttl_movimento = 0;
  boolean movimento   = false;
//f_tempo
  int t_seg   = 0;
  int t_i_seg = 0;
  int t_min   = 0;
  int t_i_min = 1;
  int t_horas = 0;
  int t_valor = 4825;
  unsigned long t_temp1;
//  long lastMsg = 0;
  char msg[50];
  int value = 0;
//f_timeClock
  int iTime        = 1; //1 inicia ligado
  int i_segAtivo   = 0;
  int i_minAtivo   = 0;
  int i_horasAtivo = 0;
  int i_valor      = 4825;
  long lastMsg = 0;
  int i_minutos   = 1;
  int i_horas     = 0;
  int i_minutos2  = 99;
  int i_horas2    = 99;
  boolean bBreak  = false;
  int iIDrede = 0;

#include <EEPROM.h>

#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
  IPAddress ipLocal;
//  IPAddress ip(192,168,15,50);        //IP FIXO (ALTERE PARA FAIXA DE IP DISPONÍVEL DO SEU ROTEADOR. EX: 192.168.1.110)
  IPAddress ip(192,168,2,50);        //IP FIXO (ALTERE PARA FAIXA DE IP DISPONÍVEL DO SEU ROTEADOR. EX: 192.168.1.110)
//  IPAddress gateway(192,168,15,1);     //GATEWAY DE CONEXÃO (ALTERE PARA O GATEWAY DO SEU ROTEADOR)
  IPAddress gateway(192,168,2,1);     //GATEWAY DE CONEXÃO (ALTERE PARA O GATEWAY DO SEU ROTEADOR)
  IPAddress subnet(255,255,255,0);     //MASCARA DE REDE
  IPAddress apIP(192,168,4,1);         //IP FIXO Web Server Wifi ESP

  WiFiClient espClient;
//  WiFiServer server(80); //CASO OCORRA PROBLEMAS COM A PORTA 80, UTILIZE OUTRA (EX:8082,8089) E A CHAMADA DA URL FICARÁ IP:PORTA(EX: 192.168.0.15:8082)

#include <ESP8266WebServer.h>
  const byte  WEBSERVER_PORT = 80;         //Porta Servidor Web
  ESP8266WebServer server(WEBSERVER_PORT); //Server on port 80
  void initOTA();
  void initWiFi();
  void reconectWiFi(); 
  char ID_esp[30];      // Identificação do dispositivo
  const char* WEBSERVER_HEADER_KEYS[] = {ID_esp}; //Headers do Servidor Web
  char ssid[30];        // Rede WiFi
  char pw[30];          // Senha da Rede WiFi
  char IPfixo[15];
  char hostnameOTA[30]; // Rede WiFi
  String wifi_id;
  long l_rssi;
  word bootCount;       //Número de inicializações
  String sSSID;
  String sRSSI;

#include <FS.h>
#include <ArduinoJson.h>
//test  const size_t JSON_SIZE = JSON_OBJECT_SIZE(5) + 500; //Tamanho do Objeto JSON
  const size_t JSON_SIZE = JSON_OBJECT_SIZE(5) + 1500; //Tamanho do Objeto JSON

#include <TimeLib.h>
  
