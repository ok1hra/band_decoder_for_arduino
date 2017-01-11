// icom_civ.h

#ifdef REQUEST
    timeout2 = millis()-previous2;                  // check timeout
    if (timeout2>(watchdog2)){
        txCIV(3, 0, CIV_ADRESS);                    // ([command], [freq]) 3=read  ** Hardware not ready yet **
        previous2 = millis();                       // set time mark
    }
#endif

#if defined(ICOM_CIV)
    if (Serial.available() > 0) {
        incomingByte = Serial.read();
        icomSM(incomingByte);
        rdIS="";
        if(rdI[10]==0xFD){                    // state machine end
            for (int i=9; i>=5; i-- ){
                if (rdI[i] < 10) {                                                         // leading zero
                    rdIS = rdIS + 0;
                }
                rdIS = rdIS + String(rdI[i], HEX);                                           // append BCD digit from HEX variable to string
            }
            freq = rdIS.toInt();
        
            //=====[ Frequency (Hz) to Band rules ]======================================
            //                                        you can expand rules up to 14 Bands
            
                 if (freq >=   1810000 && freq <=   2000000 )  {BAND=1;}  // 160m
            else if (freq >=   3500000 && freq <=   3800000 )  {BAND=2;}  //  80m
            else if (freq >=   7000000 && freq <=   7200000 )  {BAND=3;}  //  40m
            else if (freq >=  10100000 && freq <=  10150000 )  {BAND=4;}  //  30m
            else if (freq >=  14000000 && freq <=  14350000 )  {BAND=5;}  //  20m
            else if (freq >=  18068000 && freq <=  18168000 )  {BAND=6;}  //  17m
            else if (freq >=  21000000 && freq <=  21450000 )  {BAND=7;}  //  15m
            else if (freq >=  24890000 && freq <=  24990000 )  {BAND=8;}  //  12m
            else if (freq >=  28000000 && freq <=  29700000 )  {BAND=9;}  //  10m
            else if (freq >=  50000000 && freq <=  52000000 ) {BAND=10;}  //   6m
            else if (freq >= 144000000 && freq <= 146000000 ) {BAND=11;}  //   2m
            else {BAND=0;}                                                // out of range
            //===========================================================================
            
            bandSET();                                                                // set outputs relay
        
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
#endif

#if defined(WATCHDOG)
    watchDog();
#endif
