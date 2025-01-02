void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
      String message = Serial.readStringUntil('\n');
      String newMessage = "";
      bool lastCharWasSpace = false;
      for (int i = 0; i < message.length(); i++) {
          char c = message[i];
          
          if (c != ' ') {
              newMessage += c;
              newMessage += ' ';
              lastCharWasSpace = false;
          } else if (!lastCharWasSpace) {
              newMessage += ' ';
              lastCharWasSpace = true;
          }
      }
      newMessage.trim();
      Serial.print("Changed message: ");
      Serial.println(newMessage);
  }
}


