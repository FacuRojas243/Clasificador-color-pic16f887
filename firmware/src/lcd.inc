LCD_INIT:
    CALL    DELAY_20MS
    MOVLW   0x38                
    CALL    LCD_COMANDO
    MOVLW   0x0C                
    CALL    LCD_COMANDO
    CALL    LCD_CLEAR
    RETURN

LCD_CLEAR:
    MOVLW   0x01                
    CALL    LCD_COMANDO
    RETURN

LCD_COMANDO:
    MOVWF   PORTD               
    BCF     LCD_RS              
    BSF     LCD_E               
    NOP
    BCF     LCD_E               
    CALL    DELAY_5MS
    RETURN

LCD_DATOS:
    MOVWF   PORTD               
    BSF     LCD_RS              
    BSF     LCD_E
    NOP
    BCF     LCD_E
    CALL    DELAY_5MS
    RETURN

MOSTRAR_LISTO:
    MOVLW   0x80
    CALL    LCD_COMANDO
    MOVLW   'S'
    CALL    LCD_DATOS
    MOVLW   'I'
    CALL    LCD_DATOS
    MOVLW   'S'
    CALL    LCD_DATOS
    MOVLW   'T'
    CALL    LCD_DATOS
    MOVLW   'E'
    CALL    LCD_DATOS
    MOVLW   'M'
    CALL    LCD_DATOS
    MOVLW   'A'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   'L'
    CALL    LCD_DATOS
    MOVLW   'I'
    CALL    LCD_DATOS
    MOVLW   'S'
    CALL    LCD_DATOS
    MOVLW   'T'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    RETURN

TXT_LCD_VACIO:
    MOVLW   0x80
    CALL    LCD_COMANDO
    MOVLW   'S'
    CALL    LCD_DATOS
    MOVLW   'I'
    CALL    LCD_DATOS
    MOVLW   'N'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   'B'
    CALL    LCD_DATOS
    MOVLW   'J'
    CALL    LCD_DATOS
    MOVLW   'E'
    CALL    LCD_DATOS
    MOVLW   'T'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    
    MOVLW   0xC0
    CALL    LCD_COMANDO
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    RETURN

TXT_LCD_ROJO:
    MOVLW   0x80
    CALL    LCD_COMANDO
    MOVLW   'C'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   'L'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   'R'
    CALL    LCD_DATOS
    MOVLW   ':'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   'R'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   'J'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    
    MOVLW   0xC0            
    CALL    LCD_COMANDO
    MOVLW   'A'
    CALL    LCD_DATOS
    MOVLW   'N'
    CALL    LCD_DATOS
    MOVLW   'G'
    CALL    LCD_DATOS
    MOVLW   'U'
    CALL    LCD_DATOS
    MOVLW   'L'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   ':'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   '0'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   'G'
    CALL    LCD_DATOS
    MOVLW   'R'
    CALL    LCD_DATOS
    MOVLW   'A'
    CALL    LCD_DATOS
    MOVLW   'D'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   'S'
    CALL    LCD_DATOS
    RETURN

TXT_LCD_VERDE:
    MOVLW   0x80
    CALL    LCD_COMANDO
    MOVLW   'C'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   'L'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   'R'
    CALL    LCD_DATOS
    MOVLW   ':'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   'V'
    CALL    LCD_DATOS
    MOVLW   'E'
    CALL    LCD_DATOS
    MOVLW   'R'
    CALL    LCD_DATOS
    MOVLW   'D'
    CALL    LCD_DATOS
    MOVLW   'E'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    
    MOVLW   0xC0            
    CALL    LCD_COMANDO
    MOVLW   'A'
    CALL    LCD_DATOS
    MOVLW   'N'
    CALL    LCD_DATOS
    MOVLW   'G'
    CALL    LCD_DATOS
    MOVLW   'U'
    CALL    LCD_DATOS
    MOVLW   'L'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   ':'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   '9'
    CALL    LCD_DATOS
    MOVLW   '0'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   'G'
    CALL    LCD_DATOS
    MOVLW   'R'
    CALL    LCD_DATOS
    MOVLW   'A'
    CALL    LCD_DATOS
    MOVLW   'D'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   'S'
    CALL    LCD_DATOS
    RETURN

TXT_LCD_AZUL:
    MOVLW   0x80
    CALL    LCD_COMANDO
    MOVLW   'C'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   'L'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   'R'
    CALL    LCD_DATOS
    MOVLW   ':'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   'A'
    CALL    LCD_DATOS
    MOVLW   'Z'
    CALL    LCD_DATOS
    MOVLW   'U'
    CALL    LCD_DATOS
    MOVLW   'L'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    
    MOVLW   0xC0            
    CALL    LCD_COMANDO
    MOVLW   'A'
    CALL    LCD_DATOS
    MOVLW   'N'
    CALL    LCD_DATOS
    MOVLW   'G'
    CALL    LCD_DATOS
    MOVLW   'U'
    CALL    LCD_DATOS
    MOVLW   'L'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   ':'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   '1'
    CALL    LCD_DATOS
    MOVLW   '8'
    CALL    LCD_DATOS
    MOVLW   '0'
    CALL    LCD_DATOS
    MOVLW   ' '
    CALL    LCD_DATOS
    MOVLW   'G'
    CALL    LCD_DATOS
    MOVLW   'R'
    CALL    LCD_DATOS
    MOVLW   'A'
    CALL    LCD_DATOS
    MOVLW   'D'
    CALL    LCD_DATOS
    MOVLW   'O'
    CALL    LCD_DATOS
    MOVLW   'S'
    CALL    LCD_DATOS
    RETURN
