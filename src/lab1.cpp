// Подключение библиотеки
#include "i7188.h" // Подключение библиотеки от производителя
// Объявление переменных
int quit = 0;       // Переменная для остановки выполнения и выхода из программы
int LedMode = 0;    // Переменная проецирующая текущее состояние индикатора
int data;           // Переменная символа(его номера char), введенной с клавиатуры.
unsigned long time; // Переменная для работы с таймером
// Начало работы функции

int main(void) // Главная (мейн) функция
{
    // Инициализация таймера (TimerOpen());
    TimerOpen();       // Использование встроенного таймера. Функция от производителя
    StopWatchStart(0); // Обнуление таймера.
    LedOff();          // Обнуление (выключение) индикатора.
    // Начало цикла;
    while (!quit)
    {
        // Зацикливание до тех пор, пока не поступит команда и остановки (quit = 1)
        // Чтение значения счетчика (StopWatchReadValue());
        StopWatchReadValue(0, &time); // Чтение значения счетчика
        // В этот промежуток счетчик считает время и момент когда он будет равен 5 //секундам произойдет переключение индикатора.
        /*Если счетчик на отметке 10000мс(10 секунд) – переключение индикатора, в зависимости от текущего состояния.*/
        if (time >= 10000)
        {                       // как только значение равно 5 секундам
            StopWatchStart(0);  // обнуление счетчика
            LedMode = !LedMode; // здесь важно понимать, что “!LedMode” это обращение к функции библиотеки устройства, которое вернет значение false если индикатор выключении или true если он включен.
            if (LedMode)
                LedOn(); // включение/выключение в зависимости от положения
            else
                LedOff();
        }
        
        if (Kbhit())
        {                   // если был произведен ввод с клавиатуры
            data = Getch(); // считывание символа с клавиатуры в переменную data
            if (data == 'q' || data == 'Q')
                quit = 1; // выход
            else
            {
                Putch(data);

                if (data == '\r')
                    Putch('\n');
            }
        }
    }
    TimerClose(); // Прекращение использования встроенного счетчика
}
