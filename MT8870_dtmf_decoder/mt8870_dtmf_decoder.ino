
//// ----- Pin names ----- ////
const int PIN_Q1 = 3;
const int PIN_Q2 = 4;
const int PIN_Q3 = 5;
const int PIN_Q4 = 6;
//// Delayed Steering output - called 'STD' in Datasheet
const int PIN_STQ = 7;

void setup()
{
    Serial.begin(9600);
    pinMode(PIN_Q1, INPUT);
    pinMode(PIN_Q2, INPUT);
    pinMode(PIN_Q3, INPUT);
    pinMode(PIN_Q4, INPUT);
    pinMode(PIN_STQ, INPUT);
}

void loop()
{
    uint8_t number;

    const bool output_signal = digitalRead(PIN_STQ);

    if (output_signal == HIGH) /*When DTMF tone is detected, STQ will read HIGH for the duration of the tone*/
    {
        delay(100);

        number = (0x00 | (digitalRead(3) << 0) | (digitalRead(4) << 1) | (digitalRead(5) << 2) | (digitalRead(6) << 3));

        switch (number)
        { // Comes from Table 1 - Functional Decode Table
        case 0x01:
            Serial.print("1");
            break;
        case 0x02:
            Serial.print("2");
            break;
        case 0x03:
            Serial.print("3");
            break;
        case 0x04:
            Serial.print("4");
            break;
        case 0x05:
            Serial.print("5");
            break;
        case 0x06:
            Serial.print("6");
            break;
        case 7:
            Serial.print("7");
            break;
        case 0x08:
            Serial.print("8");
            break;
        case 0x09:
            Serial.print("9");
            break;
        case 0x0A:
            Serial.print("0");
            break;
        case 0x0B:
            Serial.print("*");
            break;
        case 0x0C:
            Serial.print("#");
            break;
        case 0x0D:
            Serial.print("A");
            break;
        case 0x0E:
            Serial.print("B");
            break;
        case 0x0F:
            Serial.print("C");
            break;
        case 0x00:
            Serial.print("D");
            break;
        }
    }
}
