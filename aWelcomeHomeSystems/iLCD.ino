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
  for(int i = 0: i < 8; i++){
    lcd.write(i);
    lcd.print(" ");
  }
  
}



