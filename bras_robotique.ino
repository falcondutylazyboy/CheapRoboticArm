#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "ESP32_Robot_Control";
const char* password = "password123";

Servo brasServo;
Servo pinceServo;

// Variables de position actuelle et cible
int posBras = 0;
int posPince = 0;
int cibleBras = 0;
int ciblePince = 0;

unsigned long dernierMouvement = 0;
const int vitesseServo = 20; // Plus c'est bas, plus c'est rapide (ms)

WebServer server(80);

const char index_html[] = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { text-align: center; font-family: sans-serif; }
    button { padding: 30px 50px; font-size: 24px; margin: 10px; touch-action: manipulation; }
  </style>
</head>
<body>
  <h2>Controle Robot</h2>
  <p>Bras: 
    <button onmousedown="start('bras', 'up')" onmouseup="stop()" ontouchstart="start('bras', 'up')" ontouchend="stop()">+</button>
    <button onmousedown="start('bras', 'down')" onmouseup="stop()" ontouchstart="start('bras', 'down')" ontouchend="stop()">-</button>
  </p>
  <p>Pince: 
    <button onmousedown="start('pince', 'up')" onmouseup="stop()" ontouchstart="start('pince', 'up')" ontouchend="stop()">+</button>
    <button onmousedown="start('pince', 'down')" onmouseup="stop()" ontouchstart="start('pince', 'down')" ontouchend="stop()">-</button>
  </p>
  <script>
    let timer;
    function start(servo, dir) {
      timer = setInterval(() => { fetch('/action?servo=' + servo + '&dir=' + dir); }, 100);
    }
    function stop() { clearInterval(timer); }
  </script>
</body></html>)rawliteral";

void handleRoot() { server.send(200, "text/html", index_html); }

void handleAction() {
  String servo = server.arg("servo");
  String dir = server.arg("dir");

  if (servo == "bras") {
    if (dir == "up" && cibleBras < 180) cibleBras += 2;
    else if (dir == "down" && cibleBras > 0) cibleBras -= 2;
  } else if (servo == "pince") {
    if (dir == "up" && ciblePince < 180) ciblePince += 2;
    else if (dir == "down" && ciblePince > 0) ciblePince -= 2;
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  brasServo.attach(10, 500, 2400);
  pinceServo.attach(9, 500, 2400);
  
  // Position initiale 0
  brasServo.write(posBras);
  pinceServo.write(posPince);

  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.on("/action", handleAction);
  server.begin();
}

void loop() {
  server.handleClient();

  // Mouvement fluide : met à jour la position réelle vers la cible
  if (millis() - dernierMouvement > vitesseServo) {
    if (posBras != cibleBras) {
      posBras += (cibleBras > posBras) ? 1 : -1;
      brasServo.write(posBras);
    }
    if (posPince != ciblePince) {
      posPince += (ciblePince > posPince) ? 1 : -1;
      pinceServo.write(posPince);
    }
    dernierMouvement = millis();
  }
}