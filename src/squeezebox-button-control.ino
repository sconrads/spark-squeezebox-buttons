// This #include statement was automatically added by the Spark IDE.
#include "HttpClient.h"

int button = 0;
int buttonOff = 0;
int led = D7; // This one is the built-in tiny one to the right of the USB jack
int ekstraLed = D0;

int buttonPressed = 0;
int buttonOffPressed = 0;
int channel = 0;
int power = 0;

String responseBody;
int responseStatus = 0;

HttpClient http;

// Headers currently need to be set at init, useful for API keys etc.
http_header_t headers[] = {
    { "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t request;
http_response_t response;

//http://10.0.1.42:9000/status.html?p0=play&player=00:04:20:17:92:0a&uid=1417950431000
//https://api.spark.io/v1/devices/53ff6a066667574821402567/status?access_token=e515e98469950739c58ebcb4e4bcd86a2e8c8dca
//http://tutoriels.domotique-store.fr/content/54/95/fr/api-logitech-squeezebox-server-_-player-http.html

void setup()
{
    Serial.begin(9600);
    pinMode(D1, INPUT);
    pinMode(D2, INPUT);
    pinMode(led, OUTPUT);
    pinMode(ekstraLed, OUTPUT);
    digitalWrite(led, LOW);
    digitalWrite(ekstraLed, LOW);
}
void loop()
{
  button = digitalRead(D1);
  buttonOff = digitalRead(D2);

  if(button == 1)
  {
    if (buttonPressed == 0) {
        digitalWrite(led, HIGH);
        Serial.println(WiFi.localIP());

        Serial.print("Core IP: ");
        Serial.println(WiFi.localIP());
        Serial.print("Gateway: ");
        Serial.println(WiFi.gatewayIP());
        Serial.print("Mask: ");
        Serial.println(WiFi.subnetMask());

        // Request path and body can be set at runtime or at setup.
        IPAddress remoteIP(10,0,1,42);
        request.ip = remoteIP;
        request.port = 9000;

        if (channel == 0) {
            //NRK P1
            request.path = "/plugins/Favorites/index.html?action=play&index=3&player=00:04:20:17:92:0a";
            channel = 1;
        } else if (channel == 1) {
            //NRK p3
            request.path = "/plugins/Favorites/index.html?action=play&index=4&player=00:04:20:17:92:0a";
            channel = 2;
        } else {
            //Julesanger
            digitalWrite(ekstraLed, HIGH);
            request.path = "/plugins/Favorites/index.html?action=play&index=7&player=00:04:20:17:92:0a";
            delay(1000);
            digitalWrite(ekstraLed, LOW);
            channel = 0;
        }

        // Get request
        http.get(request, response, headers);
        Serial.print("Application>\tResponse status: ");
        Serial.println(response.status);

        Serial.print("Application>\tHTTP Response Body: ");
        Serial.println(response.body);

        if (response.status == 200)
        {
            delay(1000);
            digitalWrite(led, LOW);
            delay(1000);
            digitalWrite(led, HIGH);
            delay(1000);
            digitalWrite(led, LOW);
        } else
        {
            digitalWrite(ekstraLed, HIGH);
            delay(1000);
            digitalWrite(ekstraLed, LOW);
            delay(1000);
            digitalWrite(ekstraLed, HIGH);
            delay(1000);
            digitalWrite(ekstraLed, LOW);
        }
    }
    buttonPressed = 1;
  } else
  {
    buttonPressed = 0;
  }

  if(buttonOff == 1)
  {
    if (buttonOffPressed == 0) {
        digitalWrite(led, HIGH);
        Serial.println(WiFi.localIP());

        Serial.print("Core IP: ");
        Serial.println(WiFi.localIP());
        Serial.print("Gateway: ");
        Serial.println(WiFi.gatewayIP());
        Serial.print("Mask: ");
        Serial.println(WiFi.subnetMask());

        // Request path and body can be set at runtime or at setup.
        IPAddress remoteIP(10,0,1,42);
        request.ip = remoteIP;
        request.port = 9000;

        if (power == 0) {
            request.path = "/status.txt?p0=button&p1=power_off&player=00:04:20:17:92:0a";
            power = 1;
        } else {
            request.path = "/status.txt?p0=play&player=00:04:20:17:92:0a";
            power = 0;
        }

        // Get request
        http.get(request, response, headers);
        Serial.print("Application>\tResponse status: ");
        Serial.println(response.status);

        Serial.print("Application>\tHTTP Response Body: ");
        Serial.println(response.body);

        if (response.status == 200)
        {
            delay(1000);
            digitalWrite(led, LOW);
            delay(1000);
            digitalWrite(led, HIGH);
            delay(1000);
            digitalWrite(led, LOW);
        } else
        {
            digitalWrite(ekstraLed, HIGH);
            delay(1000);
            digitalWrite(ekstraLed, LOW);
            delay(1000);
            digitalWrite(ekstraLed, HIGH);
            delay(1000);
            digitalWrite(ekstraLed, LOW);
        }
    }
    buttonOffPressed = 1;
  } else
  {
    buttonOffPressed = 0;
  }

}
