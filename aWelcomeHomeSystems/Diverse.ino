void LED(boolean Red, boolean Green, boolean Blue, boolean Alarm) {
  digitalWrite(Redpin, Red);
  digitalWrite(Greenpin, Green);
  digitalWrite(Bluepin, Blue);
  digitalWrite(Alarmpin, Alarm);
  digitalWrite(AlarmpinInv, !Alarm);
}
