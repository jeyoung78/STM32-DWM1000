#include <WiFi.h>
#include <HardwareSerial.h>

HardwareSerial mySerial(1);

// WiFi credentials
const char* ssid = "Jeyoung";
const char* password = "hello0602";

// Task handles
TaskHandle_t Task1;
TaskHandle_t Task2;

// Server object
WiFiServer server(80);

void setup() {
  // Start the serial communication with the Arduino Nano
  mySerial.begin(9600, SERIAL_8N1, 16, 17);
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();

  // Create tasks
  xTaskCreate(taskServer, "TaskServer", 10000, NULL, 1, &Task1);
  xTaskCreate(taskOther, "TaskOther", 10000, NULL, 1, &Task2);
}

void loop() {
  // Nothing to do here, tasks are running in parallel
}

// Task for handling the web server
void taskServer(void *pvParameters) {
  for (;;) {
    WiFiClient client = server.available(); // Check for incoming client connections
    if (client) { // If a client has connected
      String currentLine = "";
      String header = "";
      bool isPost = false;
      int num1 = 0, num2 = 0, num3 = 0;

      while (client.connected()) { // While the client is still connected
        if (client.available()) { // If there are bytes to read from the client
          char c = client.read(); // Read a byte from the client
          header += c; // Append the byte to the header string
          if (c == '\n' && currentLine.length() == 0) { // End of headers
            if (header.startsWith("POST")) { // Check if the request is a POST request
              isPost = true; // Set the flag to true if it is a POST request
            }
            break; // Exit the loop as the end of the headers has been reached
          }
          if (c == '\n') {
            currentLine = ""; // Reset currentLine if a newline character is encountered
          } else if (c != '\r') {
            currentLine += c; // Append the character to currentLine if it is not a carriage return
          }
        }
      }

      if (isPost) {
        String body = "";
        while (client.available()) {
          char c = client.read();
          body += c;
        }
        int pos1 = body.indexOf("num1=");
        int pos2 = body.indexOf("&num2=");
        int pos3 = body.indexOf("&num3=");
        if (pos1 != -1 && pos2 != -1 && pos3 != -1) {
          num1 = body.substring(pos1 + 5, pos2).toInt();
          num2 = body.substring(pos2 + 6, pos3).toInt();
          num3 = body.substring(pos3 + 6).toInt();
        }
      }

      // Output HTML form
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type:text/html");
      client.println();
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("<form action=\"/\" method=\"POST\">");
      client.println("Number 1: <input type=\"number\" name=\"num1\"><br>");
      client.println("Number 2: <input type=\"number\" name=\"num2\"><br>");
      client.println("Number 3: <input type=\"number\" name=\"num3\"><br>");
      client.println("<input type=\"submit\" value=\"Submit\">");
      client.println("</form>");

      // Print the numbers if form was submitted
      if (isPost) {
        Serial.print("Number 1: ");
        Serial.println(num1);
        Serial.print("Number 2: ");
        Serial.println(num2);
        Serial.print("Number 3: ");
        Serial.println(num3);
        client.println("<p>Numbers received. Check Serial Monitor for values.</p>");
        mySerial.print(num1);
        mySerial.print(",");
        mySerial.print(num2);
        mySerial.print(",");
        mySerial.println(num3);
      }

      client.println("</html>");
      client.stop();
    }
  }
}

// Task for performing another task (e.g., printing a message)
void taskOther(void *pvParameters) {
  for (;;) {
    //Serial.println("Running TaskOther");
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
  }
}
