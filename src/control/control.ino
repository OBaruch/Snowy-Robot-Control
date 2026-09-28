#include <Servo.h>
#include <WiFi.h>
#include "time.h"
#include<ArduinoJson.h>
#include "SoundData.h"
#include "XT_DAC_Audio.h"

#define ledVerde 23

String ClientRequest;
String mensajeJSON = "";


/////////////////////////////////Audio Objetos
XT_DAC_Audio_Class DacAudio(25,0);          

XT_Wav_Class bellsD(bells_wav);       //b
XT_Wav_Class navidadD(navidad_wav);   //n
XT_Wav_Class faltanD(faltan_wav);     //f
XT_Wav_Class paraD(para_wav);         //p
XT_Wav_Class semanasD(semanas_wav);   //s
XT_Wav_Class unaD(una_wav);           //1
XT_Wav_Class dosD(dos_wav);           //2
XT_Wav_Class tresD(tres_wav);         //3
XT_Wav_Class cuatroD(cuatro_wav);     //4
XT_Wav_Class cincoD(cinco_wav);       //5  
 
XT_Sequence_Class Sequence;              




///////////////////////////////Imprimir la hora local////////////////////////
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
//  int hora ;
//  hora = timeinfo.tm_hour;
//  byte horamodificada;
//  horamodificada = hora - 7;
//  
  Serial.print(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////ESTABLECER IP
IPAddress staticIP(192, 168, 43, 158); //http://192.168.43.211
IPAddress gateway(192, 168, 3, 255);
IPAddress subnet(255, 255, 255, 0);
WiFiServer server(80);
WiFiClient client;
String myresultat;
///////////////////////////////////////////////////////////////////////////////////////////////////////VARIABLES DE SERVOS
static const int servosPins[3] = {18, 19, 21}; 
Servo servos[3];
///////////////////////////////////////////////////////////////////////////////////////////////////////FUNCIONES

void setServos(int degrees,int s) {
  servos[s].write((degrees + (35 * s)) % 180);  
}


String ReadIncomingRequest()
{
  while (client.available())
  {
    ClientRequest = (client.readStringUntil('\r'));
    if ((ClientRequest.indexOf("HTTP/1.1") > 0))
      myresultat = ClientRequest;
  }
  return myresultat;
}




void PlayNumber(char const *Number)
{  
  int NumChars=strlen(Number);              
  Sequence.RemoveAllPlayItems();            
  for(int i=0;i<NumChars;i++)
    AddNumberToSequence(Number[i]);         
  DacAudio.Play(&Sequence);        
  Serial.println(Number);         
}

void AddNumberToSequence(char TheNumber)
{
  switch(TheNumber)
  {
    case 'b' : Sequence.AddPlayItem(&bellsD);break;
    case 'n' : Sequence.AddPlayItem(&navidadD);break;
    case 'f' : Sequence.AddPlayItem(&faltanD);break;
    case 'p' : Sequence.AddPlayItem(&paraD);break;
    case 's' : Sequence.AddPlayItem(&semanasD);break;
    case '1' : Sequence.AddPlayItem(&unaD);break;
    case '2' : Sequence.AddPlayItem(&dosD);break;
    case '3' : Sequence.AddPlayItem(&tresD);break;
    case '4' : Sequence.AddPlayItem(&cuatroD);break;
    case '5' : Sequence.AddPlayItem(&cincoD);break;
  }
}




void setup()
{
  Serial.begin(115200);
  ClientRequest = "";
  pinMode(ledVerde, OUTPUT);
  Serial.begin(115200);
  delay(10);
  mensajeJSON.reserve(100);
///////////////////////////////////////////////////////////////////////////////////////////////////////CONECTAR A WIFI
  Serial.println("START");
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println("ATT_Internet_En_Casa_1937");
  WiFi.begin("virus", "123123123");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
 
/////////////////////////init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
/////////////////////////////////////////////////////////////


 // WiFi.config(staticIP, gateway, subnet);  
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
///////////////////////////////////////////////////////////////////////////////////////////////////////INICIALIZAR SERVIDOR
  server.begin();
///////////////////////////////////////////////////////////////////////////////////////////////////////CONEXION DE SERVOS
      for(int i = 0; i < 3; ++i) {
        if(!servos[i].attach(servosPins[i])) {
            Serial.print("Servo ");
            Serial.print(i); 
            Serial.println("attach error");
        }
    }
}






void loop()
{
  DacAudio.FillBuffer();    
///////////////////////////////////////////////////////////////////////////////////////////////////////BUSCAR CLIENTE EN EL SERVIDOR
  //obtém cliente
  client = server.available();
  if (!client)
    return;
  while (!client.available())
    delay(1);
///////////////////////////////////////////////////////////////////////////////////////////////////////LEER URL
  ClientRequest = (ReadIncomingRequest());

  Serial.println(ClientRequest);


  ClientRequest.remove(0, 5);
  ClientRequest.remove(ClientRequest.length() - 9, 9);
  String mensajeJSON = ClientRequest;
  mensajeJSON.replace("%22", "\"");
  mensajeJSON.replace("%7D", "}");
  mensajeJSON.replace("%7B", "{");
  
  Serial.println(mensajeJSON);
  
     StaticJsonBuffer<100> bufferJSON;
      //mensajeJSON es una variable String
      //bufferJSON es una variable string para la biblioteca ArduinoJSON
      //objetoJSON es una variable que si es valida, tiene el formato JSON
     
     JsonObject& objetoJSON = bufferJSON.parseObject(mensajeJSON);

     //Averiguar si el objeto JSON es valido
     if(objetoJSON.success()){
              
                  String hora = objetoJSON["hora"]; 
                  float clima = objetoJSON["clima"];
                  String hola = objetoJSON["hola"];
                  String luces = objetoJSON["luces"];
                  String baila = objetoJSON["baila"];
                  String no = objetoJSON["no"];
                  String si = objetoJSON["si"];
                  String musica = objetoJSON["musica"];
                  Serial.println(musica);
                  String cuantofaltaparanavidad = objetoJSON["cuantofaltaparanavidad"];
                  String selfie = objetoJSON["selfie"];




                  //////////////////////////////////////////variables
          
              if (hora == "hora")
              {
                //mostrar en lcd
              
              }
              if (selfie == "selfie")
              {
                //girar360
              
              }
              if (clima >= 0 || clima <=0 )
              {
                //mostrar en lcd
              
              }
              if (hola == "hola")
              {
                //saludar
              }
              if (no == "no")
              {
                //mover la cabeza
              }
              if (si == "si")
              {
                //mover laa cabeza
              }
             if (luces == "luces")
              {
                //secuencias
              }
              if (musica == "musica")
              {
              PlayNumber("b");      
              }
              if (cuantofaltaparanavidad== "cuantofaltaparanavidad")
              {
                //digitalWrite(ledVerde,HIGH);
              }
              if (baila == "baila")
              {

                int pos =0;
                while (int pos <= 180) {
                setServos(pos,1);
                delay(20);
                Serial.println(pos);
                if(pos==180)
                  break
                pos=pos+20;  
                }    
                int posD = 180;
                while (posD >= 0) {
                setServos(posD,1);
                Serial.println(posD);
                delay(20);
                if(pos==0)
                  break
                posD=posD-20;
                }
              }
  }
     else
     {
     Serial.print("El comando no tiene el formato JSON");
     }
  
///////////////////////////////////////////////////////////////////////////////////////////////////////COMANDOS


  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("");
  client.println("");
  client.println("OK");
  client.println("");
  client.flush();
  client.stop();
  delay(50);
  
}
