#include<OneWire.h>
        #include<DS18B20.h>
        #include"SparkFunTMP102.h"
        #include<Wire.h>
        int analogowyPin=A5;
        float temperaturaC;
        const byte ONEWIRE_PIN=8;
        byte sensorAddress[8]={0x28,0x6A,0x26,0xC1,0x8,0x0,0x0,0xE5};
        OneWire onewire(ONEWIRE_PIN);
        DS18B20 sensors(&onewire);
        const int ALERT_PIN=A3;
        TMP102 sensor0(0x48);


        void setup()
        {
        Serial1.begin(9600);
        Serial.begin(9600);
        sensors.begin();
        pinMode(ALERT_PIN,INPUT);
        sensor0.begin();
        sensor0.setFault(0);
        sensor0.setAlertPolarity(1);
        sensor0.setAlertMode(0);
        sensor0.setConversionRate(2);
        sensor0.setExtendedMode(0);
        sensor0.setHighTempC(29.4);
        sensor0.setLowTempC(26.67);


        }

        void loop()
        {
        int odczyt=analogRead(analogowyPin);

        float napiecie1=odczyt*5.0;
        float napiecie2=napiecie1/1023.0;

        // print out the voltage
        //Serial.print(napiecie2); Serial.println(" = napiecie");

        // now print out the temperature
        float temperaturaC=(napiecie2-0.5)*100;

        //Serial.print(temperaturaC); Serial.println(" stopni C");

        sensors.request(sensorAddress);

        float temperature=sensors.readTemperature(sensorAddress);

        float sparkfuntemperature;
        boolean alertPinState,alertRegisterState;
        sensor0.wakeup();
        sparkfuntemperature=sensor0.readTempC();
        alertPinState=digitalRead(ALERT_PIN);
        alertRegisterState=sensor0.alert();
        sensor0.sleep();


        Serial.print(("TMP36GT9Z analogowy= "));
        Serial.print(temperaturaC);
        Serial.print((" 'C"));
        Serial.println((""));
        Serial.print(("DS18B20 one wire = "));
        Serial.print(temperature);
        Serial.print((" 'C"));
        Serial.println((""));
        Serial.print(("TMP102 SparkFun = "));
        Serial.print(sparkfuntemperature);
        Serial.print((" 'C"));
        Serial.println((""));


        Serial1.print(temperaturaC);
        Serial1.print(temperature);
        Serial1.print(sparkfuntemperature);
        delay(3000);
        temperaturaC=0;
        temperature=0;
        sparkfuntemperature=0;

        delay(1000);
        }