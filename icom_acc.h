// icom_acc.h

VALUE = analogRead(AD); 
if (counter == 5) {
    VOLTAGE = float(VALUE) * 5.0 / 1023.0;

    //=====[ Icom ACC voltage range ]===========================================================

    if (VOLTAGE > 0.73 && VOLTAGE < 1.00 ) {BAND=10;}  //   6m   * * * * * * * * * * * * * * * * 
    if (VOLTAGE > 1.00 && VOLTAGE < 1.09 ) {BAND=9;}   //  10m   *           Need              *
    if (VOLTAGE > 1.09 && VOLTAGE < 1.32 ) {BAND=8;}   //  12m   *    calibrated to your       *
    if (VOLTAGE > 1.32 && VOLTAGE < 1.55 ) {BAND=7;}   //  15m   *         own ICOM            *
    if (VOLTAGE > 1.55 && VOLTAGE < 1.77 ) {BAND=6;}   //  17m   *     ----------------        *
    if (VOLTAGE > 1.77 && VOLTAGE < 2.24 ) {BAND=5;}   //  20m   *    (These values have       *
    if (VOLTAGE > 0.10 && VOLTAGE < 0.50 ) {BAND=4;}   //  30m   *   been measured by any)     *
    if (VOLTAGE > 2.24 && VOLTAGE < 2.73 ) {BAND=3;}   //  40m   *          ic-746             *
    if (VOLTAGE > 2.73 && VOLTAGE < 2.99 ) {BAND=2;}   //  80m   *                             *
    if (VOLTAGE > 2.99 && VOLTAGE < 4.00 ) {BAND=1;}   // 160m   * * * * * * * * * * * * * * * * 
    if (VOLTAGE > 0.00 && VOLTAGE < 0.10 ) {BAND=0;}   // parking

    //==========================================================================================
    
    bandSET();                                // set outputs
    delay (20);
}else{
    if (abs(prevVALUE-VALUE)>10) {            // average
        //means change or spurious number 
        prevVALUE=VALUE;
    }else {
        counter++; 
        prevVALUE=VALUE;
    }
}
#if defined(REMOTE_RELAY)
    remoteRelay();
    previous3 = millis();     // set time mark
#endif
#if defined(SERIAL_echo)
    serialEcho();
    Serial.print(VOLTAGE);
    Serial.println(" V");
    Serial.flush();
#endif

delay(500);                                   // refresh time



