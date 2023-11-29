// LIBRARIES
//#include <SPI.h>
#include <Ethernet.h>
//#include <SD.h>

// VARIABLES
byte mac[] = { 0x2C, 0xF7, 0xF1, 0x08, 0x33, 0x4D }; //0xA8, 0x61, 0x0A, 0xAE, 0x3A, 0xC4 }; //0x93, 0xDB, 0x9F, 0x47, 0x63, 0x0C }; //0x2C, 0xF7, 0xF1, 0x08, 0x33, 0x95 };
EthernetServer server(80);

char * webPage; // char varible with pointer so we can type out HTML code as a string

void setup()
{
  Ethernet.begin(mac); // reads the mac address of the device (Arduino)
  server.begin();
  Serial.begin(9600);

  Serial.println(Ethernet.localIP());// prints out the IP address of the device
}

void loop()
{
  // connection to the ethernet client (client is the web browser)
  EthernetClient client = server.available(); // checks if the device is connected to the internet
  if (client) {
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); // read the IP address
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();


          // reads from the micro sd card
          //          const char *webPage = "<h2>Hey Look It's a Web Page From an Arduino!!</h2>"
          //                    "<p>hello welcome to my web page served from an arduino!!</p> "
          //                    "<p>here is a list:</p>"
          //                    "<ul>"
          //                        "<li>One</li>"
          //                        "<li>Two</li>"
          //                        "<li>Three</li>"
          //                    "</ul>";
          HTMLcode();
          if (webPage) {
            client.write(webPage); // tells your web browser to read the file we have identified as our html file
          }
          break;
        }

        // finishes off the process of connection and uploading to your web browser
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
  }
}



String HTMLcode() {
  webPage = "<h2>Hey Look It's a Web Page From an Arduino!!</h2>"
            "<p>hello welcome to my web page served from an arduino!!</p> "
            "<p>here is a list:</p>"
            "<ul>"
            "<li>One</li>"
            "<li>Two</li>"
            "<li>Three</li>"
            "</ul>";
  return webPage;
}
