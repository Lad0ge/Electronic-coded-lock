#include <Keypad.h> // библиотека клавиатуры
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // библиотека  жки дисплея

#define ld_gr 9 // зеленый светодиод
#define ld_red 11 // красный светодиод
#define relay 8 // реле

# define amount 6 // количество символов в коде

char marks;
char parole[amount] = {'*','*','*','*','*','*'}; // установленный пароль
char cliks[amount]; // нажатые клавиши

int t = 0; // счётчик нажатий
int x = 0; // счётчик совпадений

const byte rows = 4; // количество строк
const byte cols = 4; // количество столбцов

char sign[rows][cols] = {
    {'1','2','3','A'},

    {'4','5','6','B'},

    {'7','8','9','C'},

    {'*','0','#','D'}

}; //знаки клавиатуры

byte rows_pins[rows] = {0,1,2,3}; // пины для строк
byte cols_pins[cols] = {4,5,6,7}; // пины для столбцов

LiquidCrystal_I2C LCD(0x27,16,2); // присваиваем имя LCD для дисплея

Keypad board = Keypad(makeKeymap(marks), rows_pins, cols_pins, rows, cols); // сама клавиатура(как объект)

void setup(){
  LCD.init(); // инициализация LCD дисплея
  LCD.backlight(); // включение подсветки дисплея
   
  LCD.setCursor(1, 0);     // ставим курсор на 1 символ первой строки
  LCD.print("Write ur code");     // печатаем сообщение на первой строке
  
  LCD.setCursor(1, 1);
  LCD.print("Ur code: ");
   
  pinMode(ld_gr, OUTPUT); // обозначаем пин для зелёноного светодиода
  pinMode(ld_red, OUTPUT); // обозначаем пин для красного светодиода
  pinMode(relay, OUTPUT); // обозначаем пин для реле

  
}
void loop(){
  marks = board.getKey(); // опрос клавиатуры на наличие нажатых кнопок
  if (marks!=NO_KEY){
    cliks[t]=marks;
    LCD.setCursor(9+t, 1);
    LCD.print(cliks[t]);
    t++; // если есть кнопка, то добавляем её в массив и увеличиваем т на единицу
    if (t == amount){
      for ( uint8_t i = 0; i < amount; i++){
        if(cliks[i]==parole[i]){
          x++; // ищем совпадения, если есть, то увеличиваем x на единицу
        }
      }
      if (x==amount){
        LCD.setCursor(0,0);
        LCD.print(" Right Answer ");
        digitalWrite(relay, HIGH);
        digitalWrite(ld_gr, HIGH);
        delay (5000);
        digitalWrite(ld_gr, LOW);
        digitalWrite(relay, LOW);
        LCD.setCursor(1, 0);     // ставим курсор на 1 символ первой строки
        LCD.print("Write ur code");     // печатаем сообщение на первой строке
        t=0;
        x=0;
      }
      else{
        LCD.setCursor(0,0);
        LCD.print(" Wrong Answer ");
        digitalWrite(ld_red, HIGH);
        delay(3000);
        digitalWrite(ld_red, LOW);
        LCD.setCursor(1, 0);     // ставим курсор на 1 символ первой строки
        LCD.print("Write ur code");     // печатаем сообщение на первой строке
        t=0;
        x=0;
      }
    }
  }
}