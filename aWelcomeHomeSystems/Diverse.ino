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

void LED(boolean Red, boolean Green, boolean Blue, boolean Alarm) {
  digitalWrite(Redpin, Red);
  digitalWrite(Greenpin, Green);
  digitalWrite(Bluepin, Blue);
  digitalWrite(Alarmpin, Alarm);
  digitalWrite(AlarmpinInv, !Alarm);
}

void randomName() {
  //Every name should be 8 char long!! (remember '/0')
  //align first to the rigth and last to the left
  char* first[] = {"    Red", "   Blue", "  Black", "  Green", "   Pink", "  White", " Yellow", " Orange", " Purple"};
  char* last[] =  {"Bear   ", "Beaver ", "Swan   ", "Tiger  ", "Panda  ", "Lion   ", "Owl    ", "Goat   ", "Tuna   "};
  int firstRnd = (random(0,2000)*db.count())%9;
  int lastRnd = (random(0,2000)*db.count())%9;
   for(int i = 0; i < 7; i++){
    current.firstName[i] = first[firstRnd][i];
    current.lastName[i] = last[lastRnd][i];
  }
}
