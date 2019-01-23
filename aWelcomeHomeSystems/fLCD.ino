//This document contains functions for updating the LCD display
void LCD_setup()
{
  lcd.begin();
  lcd.backlight();

  lcd.createChar(2, clock);
  lcd.createChar(3, heart);
  lcd.createChar(6, cross);

  lcd.home();
  lcd.clear();
  lcd.print("  Setup . . .   ");
}
void LCD_WELCOME_NAME() {
  lcd.home();
  lcd.write(3);
  lcd.print(" Welcome Home ");
  lcd.write(3);

  lcd.setCursor(0, 1);
  lcd.print(logEvent.firstName);
  lcd.print(" ");
  lcd.print(logEvent.lastName);
  lcd.print(" ");
}
void LCD_WELCOME_NEW_CREATED() {
  lcd.home();
  lcd.print("    New user    ");

  lcd.setCursor(0, 1);
  lcd.print("    created     ");
}
void LCD_WELCOME_NEW_NAME() {
  lcd.home();
  lcd.print("Your codename is");
  lcd.setCursor(0, 1);
  lcd.print(current.firstName);
  lcd.print(" ");
  lcd.print(current.lastName);
  lcd.print(" ");

}
void LCD_WELCOME_DATA() {
  lcd.home();

  lcd.print("Temp:   ");
  lcd.setCursor(7, 0);
  lcd.print(temp);
  lcd.print((char)223);
  lcd.print("C    ");

  lcd.setCursor(0, 1);
  lcd.print("Hum:   ");
  lcd.setCursor(7, 1);
  lcd.print(hum);
  lcd.print("%     ");
}
void LCD_WRONG() {
  lcd.home();
  lcd.write(6);
  lcd.print(" Unauthorized ");
  lcd.write(6);
  lcd.setCursor(0, 1);
  lcd.print("                ");
}
void LCD_BT() {
  lcd.home();
  lcd.print("    Scanning    ");
  lcd.setCursor(0, 1);
  lcd.print(".-.-.-.-.-.-.-.-");
}
void LCD_NFC() {
  lcd.home();
  lcd.print("    Scanning    ");
  lcd.setCursor(0, 1);
  lcd.print("-.-.-.-.-.-.-.-.");
}
void LCD_WAIT() {
  lcd.clear();
}
void LCD_MASTER() {
  lcd.home();
  lcd.print(" Scan masterkey ");
  lcd.setCursor(0, 1);
  lcd.print("                ");

}
void LCD_NEW() {
  lcd.home();
  lcd.print("  Scan new key  ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}
