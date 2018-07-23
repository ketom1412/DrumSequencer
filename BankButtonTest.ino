//Testing Bank Button and LED
const int BankButton = 3;
const int BankLED = 18;
int ButtonState = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(BankButton, INPUT);
    pinMode(BankLED, OUTPUT);
}

void loop()
{
    ButtonState = digitalRead(BankButton);
    Serial.println(ButtonState);
    if(ButtonState == HIGH)
    {
        digitalWrite(BankLED, HIGH);
    }
    else
    {
        digitalWrite(BankLED, LOW);
    }
}