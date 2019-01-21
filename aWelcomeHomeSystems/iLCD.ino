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
void LCD_WELCOME_NAME() {
  lcd.clear();
  lcd.home();

  lcd.write(3);
  lcd.print("Welcome Home!!!");

  lcd.setCursor(0, 1);
  lcd.print(current.firstName);
  lcd.print(current.lastName);
}
void LCD_WELCOME_DATA() {
  lcd.clear();
  lcd.home();
  
  lcd.print("Temp: ");
  lcd.setCursor(7, 0);
  lcd.print(temp);
  lcd.print((char)223);
  lcd.print("C    ");
  
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.setCursor(7, 0);
  lcd.print(hum);
  lcd.print("%     ");
}
void LCD_WRONG() {
  lcd.clear();
  lcd.home();
  lcd.write(6);
  lcd.print(" Go away ");
  lcd.write(6);
}
void LCD_BT() {
  lcd.clear();
  lcd.home();
  lcd.print(" BT             ");
}
void LCD_NFC() {
  lcd.clear();
  lcd.home();
  lcd.print("            NFC ");
}
void LCD_WAIT() {
  lcd.clear();
  lcd.print("      WAIT      ");
}
void LCD_MASTER() {
  lcd.clear();
  lcd.home();
  lcd.print(" Scan masterkey ");

}
void LCD_NEW() {
  lcd.clear();
  lcd.home();
  lcd.print(" Scan new key   ");

}
void LCD_USER() {
  lcd.clear();
  lcd.home();
  lcd.print("Creating user...");
}
