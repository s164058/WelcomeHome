
// Set MAC, UID and name to 0/empty
void clearAll() {
  BT_clearMAC();
  setZero();
  current.MAC_upp = 0;
  current.MAC_low = 0;
  current.UID_upp = 0;
  current.UID_low = 0;


  logEvent.MAC_upp = 0;
  logEvent.MAC_low = 0;
  logEvent.UID_upp = 0;
  logEvent.UID_low = 0;

  for (int i = 0; i < 7; i++) {
    logEvent.firstName[i] = " ";
    logEvent.lastName[i] = " ";
    current.firstName[i] = " ";
    current.lastName[i] = " ";
  }
}

// Function to set LED/Alarm output
void LED(boolean Red, boolean Green, boolean Blue, boolean Alarm) {
  digitalWrite(Red_PIN, Red);
  digitalWrite(Green_PIN, Green);
  digitalWrite(Blue_PIN, Blue);
  digitalWrite(Alarm_PIN, Alarm);
  digitalWrite(AlarmInv_PIN, !Alarm);
}

// Function to choose a random name
void randomName() {
  //Every name should be 8 char long!! (remember '/0')
  //align first to the rigth and last to the left
  char* first[] = {"    Red", "   Blue", "  Black", "  Green", "   Pink", "  White", " Yellow", " Orange", " Purple", "   Tiny", "    Big", "  Funky", "  Fancy"};
  char* last[] =  {"Bear   ", "Beaver ", "Swan   ", "Tiger  ", "Panda  ", "Lion   ", "Owl    ", "Goat   ", "Tuna   ", "Monkey ", "Snake  ", "Dolphin", "Spider " };
  int firstRnd = (random(0,10000)*db.count())%13;
  int lastRnd = (random(0,10000)*db.count())%13;
   for(int i = 0; i < 7; i++){
    current.firstName[i] = first[firstRnd][i];
    current.lastName[i] = last[lastRnd][i];
  }
}
