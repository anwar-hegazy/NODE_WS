
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

#include <Servo.h>

/* Set these to your desired credentials. */
const char *ssid = "NODE_WS";
const char *password = "";

ESP8266WebServer server(80);


Servo myservo1;  // create servo object to control a servo

Servo myservo2;  // create servo object to control a servo



String cmd = "1";

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  cmd = server.arg("cmd");
  // get cmd parameter from url :  http://192.168.4.1/?cmd=1
  checkcommand();

  server.send(200, "text/html", "<h1>You are connected</h1>" + cmd);
}



void setup() {
  Serial.begin(9600);
  delay(100);

  myservo1.attach(D1);  // rigth ext pin D1
  myservo2.attach(D2);  // right int pin D2

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
  delay(10);
}

void forward()
{

  myservo1.write(110);
  delay(10);
}

void back()
{
  myservo2.write(50);
  delay(10);
}

void Stop()
{
  myservo1.write(90);
  myservo2.write(90);
  delay(10);
}



void checkcommand()
{

  int cm = cmd.toInt();
  switch (cm) {
    //UP
    case 1:

      forward();


      break;

    //DOWN
    case 2:


      back();

      break;


    //STOP
    case 5:
      Stop();
      break;
    }
  }
