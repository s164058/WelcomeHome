

// State definitions
#define STATE_1 1
#define STATE_2 2
#define STATE_3 3

int currentState;
int nextState;
unsigned long startTime;
unsigned long timeElapsed;

void setup() { // This code runs once, on startup

  Serial.begin(9600);
  currentState = STATE_1;
  nextState = STATE_1;
  // Save starting time
  startTime = millis();

}

void loop() {
  //Next state?
  if (nextState != currentState) {
    startTime = millis();
    currentState = nextState;
  }
  timeElapsed = millis() - startTime;

  // State Logic
  switch (currentState) {
    case STATE_1:
      Serial.println("Im in state 1");

      if (timeElapsed > 1000) {
        nextState = STATE_2;
      }
      break;
    case STATE_2:
      Serial.println("Im in state 2");
      if (timeElapsed > 1000) {
        nextState = STATE_3;
      }
      break;
    case STATE_3:
      Serial.println("Im in state 3");
      if (timeElapsed > 1000) {
        nextState = STATE_1;
      }
      break;
    default:
      Serial.println("Unknown state!");
      nextState = STATE_1;
      break;
  }

  delay(5);
}
