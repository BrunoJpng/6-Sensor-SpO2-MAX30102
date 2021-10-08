#ifndef LCD_H
#define LCD_H

class LCD {
  public:
    void LCD_Character(unsigned char data_00);
    void LCD_Commandgiver(unsigned char command);
    void LCD_Initializer(void);
    void LCD_String(char *string_00);
    void LCD_Clear();
    void LCD_String_xy(char row_1, char position, char *string_00);
};

#endif