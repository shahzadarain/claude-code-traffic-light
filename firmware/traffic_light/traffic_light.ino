/*
 * traffic_light.ino — Claude Code Traffic Light firmware (ESP32)
 * -------------------------------------------------------------
 * A minimal Wi-Fi web server that switches three LEDs. Your computer's
 * light.sh script sends it requests like:
 *
 *     GET /set?color=red      -> red LED on,    others off
 *     GET /set?color=yellow   -> yellow LED on, others off
 *     GET /set?color=green    -> green LED on,  others off
 *     GET /set?color=off      -> all LEDs off
 *
 * GPIO mapping (see docs/wiring.md):
 *     pin 25 = red
 *     pin 26 = yellow
 *     pin 27 = green
 *
 * On boot the board prints its IP address to Serial at 115200 baud. Copy that
 * IP into LIGHT_IP at the top of scripts/light.sh.
 *
 * ---------------------------------------------------------------------------
 * ESP8266 note: this sketch targets the ESP32. To run it on an ESP8266,
 * swap the includes:
 *     #include <ESP8266WiFi.h>        // instead of <WiFi.h>
 *     #include <ESP8266WebServer.h>   // instead of <WebServer.h>
 * and use:  ESP8266WebServer server(80);
 * The rest of the code is the same (pick valid ESP8266 GPIO pins).
 * ---------------------------------------------------------------------------
 */

#include <WiFi.h>
#include <WebServer.h>

// >>> EDIT THESE <<<  Your Wi-Fi network name and password (placeholders).
const char* WIFI_SSID     = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// LED pin assignments. Change these if you wire to different GPIOs.
const int PIN_RED    = 25;
const int PIN_YELLOW = 26;
const int PIN_GREEN  = 27;

// Web server on the standard HTTP port.
WebServer server(80);

// Turn every LED off, then turn on just the one requested.
void setColor(const String& color) {
  digitalWrite(PIN_RED,    LOW);
  digitalWrite(PIN_YELLOW, LOW);
  digitalWrite(PIN_GREEN,  LOW);

  if (color == "red") {
    digitalWrite(PIN_RED, HIGH);
  } else if (color == "yellow") {
    digitalWrite(PIN_YELLOW, HIGH);
  } else if (color == "green") {
    digitalWrite(PIN_GREEN, HIGH);
  }
  // "off" (or anything unrecognized) leaves all LEDs off.
}

// Handler for: GET /set?color=<red|yellow|green|off>
void handleSet() {
  String color = server.arg("color");
  setColor(color);
  server.send(200, "text/plain", "OK");
}

// Friendly root page so visiting the IP in a browser isn't a 404.
void handleRoot() {
  server.send(200, "text/plain",
              "Claude Code Traffic Light. Use /set?color=red|yellow|green|off");
}

void setup() {
  Serial.begin(115200);

  // Configure the LED pins as outputs and start with everything off.
  pinMode(PIN_RED,    OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN,  OUTPUT);
  setColor("off");

  // Connect to Wi-Fi.
  Serial.println();
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected! Board IP address: ");
  Serial.println(WiFi.localIP());   // <-- copy this into scripts/light.sh
  Serial.println("Put this IP in LIGHT_IP at the top of scripts/light.sh");

  // Register routes and start serving.
  server.on("/",    handleRoot);
  server.on("/set", handleSet);
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
  server.handleClient();
}
