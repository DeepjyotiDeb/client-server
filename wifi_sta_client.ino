#include<ESP8266WiFi.h>

char *ssid="YourNetworkName";
char *pass="123456789";
char *host="192.168.4.1";
int i=1;

void setup()
{ 
//  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,pass);
//  IPAddress ip(192,168,1,15);   
//  IPAddress gateway(192,168,4,1);   
//  IPAddress subnet(255,255,255,0);   
//  WiFi.config(ip, gateway, subnet);
  
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.gatewayIP());
  Serial.println("connected : ");
  Serial.print(host);
  Serial.println("value  ");
  Serial.print(i);
  delay(10);
//else{ Serial.println("failed");}
}

void loop(){
  WiFiClient client;
 // const int tport=80;
  if(client.connect(host,80)) 
  {
    i++;
    String url = "/update?value=";
    url += String(i);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host +  "\r\n" + "Connection: close\r\n\r\n"); // minimum set of required URL headers
    Serial.println(i);
    delay(10);
    // Read all the lines of the response and print them to Serial
    Serial.println("Response: ");
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
      //client.stop();
      }
  }
}
