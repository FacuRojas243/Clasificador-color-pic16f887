SERVO_0_DEG:
    MOVLW   D'50'               
    MOVWF   SERVO_PULSOS
S_0_LP:
    BSF     SERVO_PIN           
    CALL    DELAY_0_5MS         
    BCF     SERVO_PIN           
    CALL    DELAY_19MS          
    CALL    DELAY_0_5MS         
    DECFSZ  SERVO_PULSOS, F
    GOTO    S_0_LP
    RETURN
SERVO_90_DEG:
    MOVLW   D'50'
    MOVWF   SERVO_PULSOS
S_90_LP:
    BSF     SERVO_PIN
    CALL    DELAY_1MS
    CALL    DELAY_0_5MS         
    BCF     SERVO_PIN
    CALL    DELAY_18_5MS        
    DECFSZ  SERVO_PULSOS, F
    GOTO    S_90_LP
    RETURN
SERVO_180_DEG:
    MOVLW   D'50'
    MOVWF   SERVO_PULSOS
S_180_LP:
    BSF     SERVO_PIN
    CALL    DELAY_2MS           
    CALL    DELAY_0_5MS         
    BCF     SERVO_PIN
    CALL    DELAY_5MS           
    CALL    DELAY_5MS           
    CALL    DELAY_5MS           
    CALL    DELAY_2MS           
    CALL    DELAY_0_5MS         
    DECFSZ  SERVO_PULSOS, F
    GOTO    S_180_LP
    RETURN
