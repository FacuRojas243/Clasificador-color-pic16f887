MEDIR_FRECUENCIA:
    CLRF    TMR1H
    CLRF    TMR1L               
    MOVLW   B'00000111'         
    MOVWF   T1CON
    CALL    DELAY_20MS          
    CLRF    T1CON               
    MOVF    TMR1L, W            
    RETURN
