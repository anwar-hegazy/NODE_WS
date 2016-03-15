/**
 * Basic Web_Server for NodeMCU
 *
 *  - Anita de Prado -
 *
 *     Crea un servidor web local accesible en: http://172.16.34.155
 *          (dirección concreta para esta plaquita NodeMCU)
 *
 */

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Wifi
const char* ssid = "BQ_CORP";
const char* password = "%&Th3_M4Tr1X1234!=";

const char* webLocalDir = "http://172.16.34.155"; //(dirección concreta para esta plaquita NodeMCU)

ESP8266WebServer server(80); //Create a Web server

static String buttonState = "OFF";



void setup(void){

  Serial.begin(9600);

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  server.on("/", handleRoot);

  server.on("/tolili", [](){
    server.send(200, "text/plain", "Tonto el que lo lea :D");
  });

  server.on("/boton", botoncicosPag);

  server.on("/paracliente", [](){
    server.send(200, "text/html", buttonState);
  });

  //Si no encuentra dirección
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}

void loop(void){
  server.handleClient();

  delay(1000);

}



/*-------------------------------------------------------
**------- FUNCIONEEEES ----------------------------------
---------------------------------------------------------*/

void handleRoot() {

    //Enviar el código HTML de la portada al server:
    //  En este caso es accesible desde: http://172.16.34.155
    String htmlCode = "";

    htmlCode += "<!DOCTYPE html>";
    htmlCode += "<html style=\"background-image: url(http://i.stack.imgur.com/7YKUD.jpg); background-repeat: repeat;\">\n";
    htmlCode += "<head><title>Hacker!</title></head>";
    htmlCode += "    <body> \n <br><br>";
    htmlCode += "        <h1 style= \"text-align:center; color:#CEF6CE; font-family: monospace; font-size:200%;\" >Hello from Anita's NodeMCU! \n \n \n</h1>&nbsp;";
    htmlCode += "        <center><img src=\"http://fs01.androidpit.info/a/b7/60/zowi-app-b760e4-w240.png\" alt=\"Zowiwi\" ></center>\n"; //p:  style=\"text-align:center;\"
    htmlCode += "        <p style= \"text-align:center; color:#CEF6CE; font-family: monospace;\"> <i>ESP8266 inside</i> </p><br>";
    htmlCode += "        <h2 style= \"color:#CEF6CE; font-family: monospace;\" >Please Try:</h2>";
    htmlCode += "        <a href=\"http://172.16.34.155/tolili\" style=\"margin-left: 30px; color:#00C3FF;\">http://172.16.34.155/tolili</a><br>";
    htmlCode += "        <a href=\"http://172.16.34.155/boton\" style=\"margin-left: 30px; color:#00C3FF;\">http://172.16.34.155/boton </a><br>";
    htmlCode += "        <a href=\"https://c1.staticflickr.com/1/5/5040260_a2c426a753.jpg\" style=\"margin-left: 30px; color:#FFE100;\"><b>Banana</b></a><br>";
    htmlCode += "        <br><br><h4 style= \"color:#CEF6CE; font-family: monospace;\" >Gracias a Bea por su cargador ^^</h4>";
    htmlCode += "    </body>";
    htmlCode += " </html>";

   server.send(200, "text/html", htmlCode); //indexHtmlCode


}

void handleNotFound(){

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri(); //Mostrar dirección que no funciona
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; //Mostrando argumentos
  }
  server.send(404, "text/plain", message);

}


//Página botoncicos. En este caso es accesible desde: http://172.16.34.155/boton
void botoncicosPag(){

  buttonState = server.arg("pin"); //Actualizo buttonState con el valor actual del argumento "pin"

  String htmlCode = "";

  htmlCode += "<!DOCTYPE html>\n";
  htmlCode += "<html style=\"background-image: url(http://i.stack.imgur.com/7YKUD.jpg); background-repeat: repeat;\">\n";  //OTRA CHACHI: https://s-media-cache-ak0.pinimg.com/736x/e7/d3/66/e7d36669c822b2e4bae251b77e0660ce.jpg
  htmlCode += "<head><title>Hacker Control!</title></head>\n";
  htmlCode += "    <body>\n <br><br>";
  htmlCode += "        <h1 style= \"text-align:center; color:#CEF6CE; font-family: monospace; font-size:200%;\" ><b>Botoncicos!</b></h1>\n";  // align='center'
  htmlCode += "        <p style=\"align:center; text-align:center; \">\n"; //margin-left: 20px
  htmlCode += "                <a href=\"?pin=ON\" style=\"align:center;\"><img src=\"http://bit.ly/1QR2UiB\" alt=\"botonON\"></a>&nbsp;";   //Otro: http://bit.ly/1nC7BUY
  htmlCode += "                <a href=\"?pin=OFF\" style=\"align:center;\"><img src=\"http://bit.ly/1P3oHRN\" alt=\"botonOFF\"></a>&nbsp;";
  //htmlCode += "                <button onClick=location.href='?pin=ON\' style='margin:auto;background-color: #CEF6CE;color: black;padding: 20px;border: 2px solid #3F7CFF;width:85px;'> ON </button>\n";
  //htmlCode += "                <button onClick=location.href='?pin=OFF\' style='margin:auto;background-color: #F5A9A9;color: black;padding: 20px;border: 2px solid #3F7CFF;width:85px;'> OFF </button>\n";
  htmlCode += "        </p>\n";
  htmlCode += "        <p style= \"color:#CEF6CE;\" >  Segunda plaquita NodeCMU (cliente) recibe: ";
  htmlCode += buttonState;
  htmlCode += "        </p>\n &nbsp;";
  htmlCode += "    </body>\n";
  htmlCode += "</html>";

  server.send(200, "text/html", htmlCode);

}
