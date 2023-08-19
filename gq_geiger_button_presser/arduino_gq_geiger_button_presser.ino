
// Works for the "Walfront 4 Key Keyboard Module" (ASIN B07PFK5Z7L)
// Buttons are common cathode

const int PIN_K1 = 3;
const int PIN_K2 = 4;
const int PIN_K3 = 5;
const int PIN_K4 = 6;

void setup(void)
{
    const int baudRate = 115200;

    Serial.begin(baudRate);

    pinMode(PIN_K1, INPUT_PULLUP);
    pinMode(PIN_K2, INPUT_PULLUP);
    pinMode(PIN_K3, INPUT_PULLUP);
    pinMode(PIN_K4, INPUT_PULLUP);
}

void loop(void)
{

    // TODO: Add debouncing

    if (!digitalRead(PIN_K1))
    {
        // Serial.println("K1 pressed");
        Serial.write("<KEY0>>");
    }

    else if (!digitalRead(PIN_K2))
    {
        // Serial.println("K2 pressed");
        Serial.write("<KEY1>>");
    }

    else if (!digitalRead(PIN_K3))
    {
        // Serial.println("K3 pressed");
        Serial.write("<KEY2>>");
    }

    else if (!digitalRead(PIN_K4))
    {
        // Serial.println("K4 pressed");
        Serial.write("<KEY3>>");
    }

    delay(200);
}