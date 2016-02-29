
/* ############################################################ 
 *  By: Vittaysak Rujivorakul
 *  Android App for Controller:  https://play.google.com/store/apps/details?id=com.br3.udpctl&hl=th
 *  My Demo Clip VDO: https://www.youtube.com/watch?v=E85RfNlRmHU 
 *  Hardware Micro Controller: NodeMCU V2 (ESP8266-12) found at http://www.nodemcu.com/
 *  Enjoy your kids
 *########################################################### */
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "BQ8";
const char *password = "";

ESP8266WebServer server(80);


int pin1_motor_R = D1;   ///E2
int pin2_motor_R = D2;
int pin1_motor_L = D3;   // E1
int pin2_motor_L = D4;
int pin1_motor_C = D7;   // E1
int pin2_motor_C = D8;
 


String cmd="1";

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  cmd=server.arg("cmd");
  // get cmd parameter from url :  http://192.168.4.1/?cmd=1
  checkcommand();
  
  server.send(200, "text/html", "<h1>You are connected</h1>" + cmd);
}



void setup() {
  delay(1000);
  Serial.begin(9600);

   pinMode(pin1_motor_R , OUTPUT);
   pinMode(pin2_motor_R, OUTPUT);
   pinMode(pin1_motor_L, OUTPUT);
   pinMode(pin2_motor_L, OUTPUT);

 
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
   
  server.handleClient();
}



void forward()
 {
   delay(10);
 //  Serial.println("forward");
   
 
   digitalWrite(pin1_motor_R, HIGH);
   digitalWrite(pin2_motor_R, LOW);
   
   digitalWrite(pin1_motor_L, HIGH);
   digitalWrite(pin2_motor_L, LOW);
   
 }


 void back()
 {
   delay(10);
  // Serial.println("back");
 
   digitalWrite(pin1_motor_R, LOW);
   digitalWrite(pin2_motor_R, HIGH);
   
   digitalWrite(pin1_motor_L, LOW);
   digitalWrite(pin2_motor_L, HIGH);
 }



 void left()
 {
  delay(10);
 // Serial.println("left");
 
  digitalWrite(pin1_motor_R, LOW);
  digitalWrite(pin2_motor_R, LOW);
   
   digitalWrite(pin1_motor_L, HIGH);
   digitalWrite(pin2_motor_L, LOW);
 }

 
 void right()
 {
  delay(10);
 // Serial.println("Right");
 
   digitalWrite(pin1_motor_R, HIGH);
  digitalWrite(pin2_motor_R, LOW);
   
   digitalWrite(pin1_motor_L, LOW);
   digitalWrite(pin2_motor_L, LOW);
 }

void Stop()
 {
  delay(10);
 // Serial.println("Right");
 
   digitalWrite(pin1_motor_R, LOW);
  digitalWrite(pin2_motor_R, LOW);
   
   digitalWrite(pin1_motor_L, LOW);
   digitalWrite(pin2_motor_L, LOW);
 }

 void checkcommand()
 {
    
   int cm = cmd.toInt();
   switch(cm){
  //UP
    case 1:     forward();      
    break;
    
  //DOWN
    case 2:      back();      
    break;


 //STOP
    case 5:  Stop();                              
    break;


  //LEFT
    case 3:  left();    
    break;

  //RIGH
    case 4:  right();   
    break;

    }

 }
