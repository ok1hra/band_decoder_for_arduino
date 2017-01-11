// serial.h

while (Serial.available() > 0) {
    BAND = Serial.parseInt();
    freq = Serial.parseInt();
    if (Serial.read() == '\n') {
        bandSET();
        #if defined(REMOTE_RELAY)
            remoteRelay();
            previous3 = millis();     // set time mark
        #endif
        #if defined(SERIAL_echo)
            serialEcho();
        #endif
        #if defined(WATCHDOG)
            previous = millis();                   // set time mark
        #endif
    }
}
#if defined(WATCHDOG)
    watchDog();
#endif

