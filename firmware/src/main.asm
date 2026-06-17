LIST p=16F887
    #include "p16f887.inc"

    __CONFIG _CONFIG1, _FOSC_XT & _WDTE_OFF & _PWRTE_ON & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_ON & _IESO_OFF & _FCMEN_OFF & _LVP_OFF
    __CONFIG _CONFIG2, _BOR4V_BOR40V & _WRT_OFF
    
D1              EQU 0x20        
D2              EQU 0x21
D3              EQU 0x22
D4              EQU 0x23
INDEX           EQU 0x24
W_TEMP          EQU 0x25        
STATUS_TEMP     EQU 0x26
BANDERAS        EQU 0x27        
VALOR_ADC       EQU 0x28        
CONT_ROJO       EQU 0x29        
CONT_VERDE      EQU 0x2A
CONT_AZUL       EQU 0x2B
SERVO_PULSOS    EQU 0x2C        
DEL_REG1        EQU 0x2D        
DEL_REG2        EQU 0x2E
CENTENAS        EQU 0x2F
DECENAS         EQU 0x30
UNIDADES        EQU 0x31
NUM_TEMP        EQU 0x32

#DEFINE FLAG_ESCANEAR BANDERAS,0  
#DEFINE LCD_RS        PORTE,0    
#DEFINE LCD_E         PORTE,1    
#DEFINE S2            PORTB,1    
#DEFINE S3            PORTB,2    
#DEFINE SERVO_PIN     PORTC,2    

    ORG  0X00          
    GOTO INICIO

    ; Rutina de atención a interrupciones
    ORG  0X04
ISR:
    MOVWF   W_TEMP      
    SWAPF   STATUS, 0
    MOVWF   STATUS_TEMP
    
    BTFSS   INTCON, INTF 
    GOTO    FIN_ISR
    
    BSF     FLAG_ESCANEAR
    BCF     INTCON, INTE  
    BCF     INTCON, INTF        
    
FIN_ISR:
    SWAPF   STATUS_TEMP, 0 
    MOVWF   STATUS
    SWAPF   W_TEMP, 1
    SWAPF   W_TEMP, 0
    RETFIE

    ; Configuración inicial de puertos y registros
INICIO:
    BSF     STATUS, RP1  
    BSF     STATUS, RP0         
    CLRF    ANSEL               
    CLRF    ANSELH              
    BSF     ANSEL, 0            

    BCF     STATUS, RP1         
    CLRF    TRISD               
    BCF     TRISE, 0            
    BCF     TRISE, 1            
    BSF     TRISA, 0            
    
    MOVLW   B'00000001'         
    MOVWF   TRISB
    
    MOVLW   B'10000001'         
    MOVWF   TRISC

    MOVLW   B'00000000'         
    MOVWF   OPTION_REG
    
    MOVLW   D'25'               
    MOVWF   SPBRG
    BSF     TXSTA, BRGH        
    BSF     TXSTA, TXEN        
    
    MOVLW   B'00000000'         
    MOVWF   ADCON1

    BCF     STATUS, RP0         
    BCF     STATUS, RP1
    
    CLRF    PORTD
    CLRF    PORTC
    CLRF    BANDERAS
    
    BSF     RCSTA, SPEN         
    BSF     RCSTA, CREN         
    
    MOVLW   B'01000001'         
    MOVWF   ADCON0

    BSF     INTCON, INTE        
    BSF     INTCON, GIE         

    CALL    LCD_INIT

    ; Bucle principal de supervisión
LOOP:
    BSF     ADCON0, GO          
ESPERA_ADC:
    BTFSC   ADCON0, GO          
    GOTO    ESPERA_ADC
    MOVF    ADRESH, W
    MOVWF   VALOR_ADC           

    CALL    MOSTRAR_LISTO

    BTFSS   FLAG_ESCANEAR       
    GOTO    LOOP                

    ; Proceso de medición y clasificación
    BCF     FLAG_ESCANEAR       
    CALL    LCD_CLEAR

    BCF     S2                  
    BCF     S3                  
    CALL    MEDIR_FRECUENCIA
    MOVWF   CONT_ROJO           

    BSF     S2                  
    BSF     S3                  
    CALL    MEDIR_FRECUENCIA
    MOVWF   CONT_VERDE          

    BCF     S2                  
    BSF     S3                  
    CALL    MEDIR_FRECUENCIA
    MOVWF   CONT_AZUL           

    CALL    UART_ENVIA_ESTADISTICAS
    
    MOVF    VALOR_ADC, W        
    SUBWF   CONT_VERDE, W       
    BTFSS   STATUS, C           
    GOTO    ACCION_VACIO        

    MOVF    CONT_VERDE, W       
    SUBWF   CONT_ROJO, W        
    BTFSS   STATUS, C           
    GOTO    VERDE_MAYOR

ROJO_MAYOR:
    MOVF    CONT_AZUL, W
    SUBWF   CONT_ROJO, W        
    BTFSS   STATUS, C
    GOTO    ACCION_AZUL
    GOTO    ACCION_ROJO

VERDE_MAYOR:
    MOVF    CONT_AZUL, W
    SUBWF   CONT_VERDE, W       
    BTFSS   STATUS, C
    GOTO    ACCION_AZUL
    GOTO    ACCION_VERDE

    ; Rutinas de acción según el color detectado
ACCION_VACIO:
    CALL    LCD_CLEAR
    CALL    TXT_LCD_VACIO
    CALL    UART_ENVIA_VACIO
    GOTO    FIN_PROCESO

ACCION_ROJO:
    CALL    LCD_CLEAR
    CALL    TXT_LCD_ROJO        
    CALL    UART_ENVIA_R        
    CALL    SERVO_0_DEG         
    GOTO    FIN_PROCESO         

ACCION_VERDE:
    CALL    LCD_CLEAR
    CALL    TXT_LCD_VERDE       
    CALL    UART_ENVIA_V        
    CALL    SERVO_90_DEG        
    GOTO    FIN_PROCESO

ACCION_AZUL:
    CALL    LCD_CLEAR
    CALL    TXT_LCD_AZUL        
    CALL    UART_ENVIA_A        
    CALL    SERVO_180_DEG       
    GOTO    FIN_PROCESO

    ; Finalización y retorno al inicio
FIN_PROCESO:
ESPERA_SOLTAR:
    BTFSS   PORTB, 0            
    GOTO    ESPERA_SOLTAR       
    CALL    DELAY_20MS          
    BCF     INTCON, INTF        
    BSF     INTCON, INTE        
    GOTO    LOOP
    
    #include "delays.inc"
    #include "lcd.inc"
    #include "uart.inc"
    #include "servo.inc"
    #include "sensor.inc"

    END
