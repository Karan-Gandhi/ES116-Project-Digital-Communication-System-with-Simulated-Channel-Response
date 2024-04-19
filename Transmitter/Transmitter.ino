#define OUT 7
String MESSAGE = "Hello world!";
int HEADER_COUNT = 0;
int MESSAGE_LENGTH = 0;
int SPEED = 20;

void setup() {
  pinMode(OUT, OUTPUT);
//  PREMBLE - 1 byte
//  HEADER Start - 5 bits
//  HEADER - 5 bits is the header size
//  PAYLOAD - just the message

  MESSAGE_LENGTH = MESSAGE.length();
  Serial.begin(9600);
}

void send(int val) {
  digitalWrite(OUT, val);
  delay(SPEED);
}

void loop() {
  // This is the preamble
  for (int i = 0; i < 4; i++) {
    send(HIGH);
    send(LOW);
  }

  Serial.println("Preamble done");
  // Message Start sequence
  send(LOW);
  send(HIGH);
  send(HIGH);
  send(LOW);
  send(LOW);

  // Header
  for (int i = 0; i < 5; i++) {
    byte current_bit = bitRead(MESSAGE_LENGTH, 5 - i - 1);
    send(current_bit);
  }

  // Payload
  for (int i = 0; i < MESSAGE.length(); i++) {
    int current_character = int(MESSAGE[i]);

    for (int i = 0; i < 7; i++) {
      byte current_bit = bitRead(current_character, 7 - i - 1);
      send(current_bit);
      Serial.println(current_bit);
    }
  }
  send(LOW);
  delay(10000);
}
