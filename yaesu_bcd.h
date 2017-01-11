// yaesu_bcd.h

if (analogRead(A6) > 409) {BCD1=1;}else{BCD1=0;}; // BCD1 > 409 = 2V = HIGH
if (analogRead(A5) > 409) {BCD2=1;}else{BCD2=0;}; // BCD2
if (analogRead(A4) > 409) {BCD3=1;}else{BCD3=0;}; // BCD3
if (analogRead(A3) > 409) {BCD4=1;}else{BCD4=0;}; // BCD4

boolean BCDmatrix[4][15] = { /*

=======[ Input BCD ]====================================================================

          BCD 1 --> */ { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0 }, /*
          BCD 2 --> */ { 0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  1 }, /*
          BCD 3 --> */ { 0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  1,  1,  1 }, /*
          BCD 4 --> */ { 0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1 }, /*
                         |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
                         V   V   V   V   V   V   V   V   V   V   V   V   V   V   V
-------------------------------------------------------------------------------------
Band # in matrix table   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
Yaesu BCD                   160 80  40  30  20  17  15  12  10  6m  <--- free --->     FT-1000MP ?
-------------------------------------------------------------------------------------

========================================================================================


*/};

for (bandBCD=0; bandBCD<15; bandBCD++){ 
      if (BCDmatrix[0][bandBCD]==BCD1 && BCDmatrix[1][bandBCD]==BCD2 && BCDmatrix[2][bandBCD]==BCD3 && BCDmatrix[3][bandBCD]==BCD4){
            BAND=bandBCD;
      }
}
bandSET();                         // set outputs
#if defined(REMOTE_RELAY)
    remoteRelay();
    previous3 = millis();     // set time mark
#endif
#if defined(SERIAL_echo)
    serialEcho();
#endif
delay(1000);

