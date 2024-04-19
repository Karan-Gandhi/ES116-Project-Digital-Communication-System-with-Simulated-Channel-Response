#define COMM A0
#define THRESHOLD 100

int SPEED = 20;
bool preambleMode = true;

void setup() {
  Serial.begin(9600);
}

int read() {
  int p = analogRead(COMM) > THRESHOLD;
  delay(SPEED);
  return p;
}

void loop() {
  while (preambleMode) {
    int p = (analogRead(COMM) > THRESHOLD);
    if (p == 1) {
      break;
    }
  }

  int count = 0;
  while (preambleMode) {
    int p1 = read();
    int p2 = read();
    int p3 = read();
    int p4 = read();
    preambleMode = false;
    count += 4;

    if (p1 == p2 && p2 == 1) {
    } else if (p2 == p3 && p3 == 1) {
      int p = read();
    } else if (p3 == p4 && p4 == 1) {
      int p = read();
      p = read();
    } else {
      preambleMode = true;
    }
  }

  int message_size = 0;
  for (int i = 0; i < 5; i++) {
    int bit = read();
    message_size += (1 << (5 - i - 1)) * bit;
  }

  for (int i = 0; i < message_size; i++) {
    int val = 0;
    for (int j = 0; j < 7; j++) {
      int bit = read();
      if (bit == 1) {
        val += bit * (1 << (7 - 1 - j));
      }
    }
    Serial.print(char(val));
  }
  Serial.println("");
  preambleMode = true;
  delay(9000);
}
