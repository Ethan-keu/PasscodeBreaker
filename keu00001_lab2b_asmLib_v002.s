.include "xc.inc"

.text                       

.global _write_0_1, _write_1_1,_write_0_2, _write_1_2,_write_0_3, _write_1_3,_write_0_4, _write_1_4, _keu_wait_100us, _keu_wait_1ms

 
_write_0_1:
    inc LATA  
    repeat #3
    nop
    
    clr LATA
    repeat #5
    nop
    
    return
    
_write_1_1:
    inc LATA         
    repeat #7
    nop
    
    clr LATA 
    repeat #1
    nop
    return
    
_write_0_2:
    mov #4, w0 
    mov w0, LATA  
    repeat #3
    nop
    
    clr LATA
    repeat #5
    nop
    
    return
    
_write_1_2:
    mov #4, w0
    mov w0, LATA         
    repeat #7
    nop
    
    clr LATA 
    repeat #1
    nop
    return
    
_write_0_3:
    mov #8, w0 
    mov w0, LATA  
    repeat #3
    nop
    
    clr LATA
    repeat #5
    nop
    
    return
    
_write_1_3:
    mov #8, w0
    mov w0, LATA         
    repeat #7
    nop
    
    clr LATA 
    repeat #1
    nop
    return
    
_write_0_4:
    mov #16, w0 
    mov w0, LATA  
    repeat #3
    nop
    
    clr LATA
    repeat #5
    nop
    
    return
    
_write_1_4:
    mov #16, w0
    mov w0, LATA         
    repeat #7
    nop
    
    clr LATA 
    repeat #1
    nop
    return
    
_keu_wait_100us:
    repeat #1364
    nop
    return
    
_keu_wait_1ms:
    repeat #9999
    nop
    repeat #5763
    nop
    return


