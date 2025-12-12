char data;
bool blinkState = false;

void setup()
{
    Serial.begin(9600);
    pinMode(8, OUTPUT);
}

void loop()
{
    if (Serial.available())
    {
        data = Serial.read();
    }

    if (data == '1')
    {
        blinkState = true;
    }

    if (data == '0')
    {
        blinkState = false;
        digitalWrite(8, LOW);
    }

    if (blinkState)
    {
        digitalWrite(8, HIGH);
        delay(300);
        digitalWrite(8, LOW);
        delay(300);
    }
}
