#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include<WiFiClient.h>

char *ssid="YourNetworkName";
char *pass="123456789";
int value=6;

ESP8266WebServer server(80);
//WiFiServer server1(200);

void root1();
void Update1();
void safety();

void setup()
{ 
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,pass,1);
  
//  IPAddress ip(192,168,1,15);   
//  IPAddress gateway(192,168,1,254);   
//  IPAddress subnet(255,255,255,0);
//  WiFi.softAPConfig(ip, gateway, subnet);
  
  Serial.begin(115200);
  delay(10);
  Serial.println("starting");
  Serial.println("IP  :");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.softAPIP());
  server.on("/", root1);
  server.on("/update", Update1);
  server.on("/safe", safety);
  server.begin();
  Serial.println("server started");
}
void loop(void)
{
  server.handleClient();
}
void root1()
{
  server.send(200, "text/plain", String(value));
}
void Update1()
{
  value=server.arg("value").toInt();
  Serial.println(value);
  Serial.println("test");
  server.send(200, "text/plain", "updated");
  //write oled code
}
void safety()
{
  if(value>=10)
  {
    Serial.println("not safe");
    server.send(200, "text/plain", "1");
  }
  else
  {
    Serial.println("safe");
    server.send(200, "text/plain", "0");
  }
}
