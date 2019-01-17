void LCD_setup()
{
  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, bell);
  lcd.createChar(1, note);
  lcd.createChar(2, clock);
  lcd.createChar(3, heart);
  lcd.createChar(4, duck);
  lcd.createChar(5, check);
  lcd.createChar(6, cross);
  lcd.createChar(7, retarrow);
  lcd.home();

  lcd.print("LCD setup . . .");
  lcd.setCursor(0, 1);
  for (int i = 0 ; i < 8; i++) {
    lcd.write(i);
    lcd.print(" ");
  }
}
void LCD_welcome() {
  lcd.clear();
  lcd.home();

  lcd.write(3);
  lcd.print("Welcome Home!!!");

  lcd.setCursor(0, 1);
//  lcd.write(1);
//  lcd.print(__DATE__);
//  lcd.print(" ");
  lcd.write(2);
  lcd.print(__TIME__);
}
void LCD_wrong() {
  lcd.clear();
  lcd.home();
  lcd.write(6);
  lcd.print(" Go away ");
  lcd.write(6);
}
void LCD_BT() {
  lcd.clear();
  lcd.home();
  lcd.print(" BT ");
}
void LCD_NFC() {
  lcd.clear();
  lcd.home();
  lcd.print(" NFC ");
}


