;
; File generated by cc65 v 2.16 - Git 4156538
;
	.fopt		compiler,"cc65 v 2.16 - Git 4156538"
	.setcpu		"6502"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.forceimport	__STARTUP__
	.export		_loadPalette
	.export		_loadText
	.export		_resetScroll
	.export		_i
	.export		_NMI_flag
	.export		_Frame_Count
	.export		_text_pos
	.export		_TEXT
	.export		_PALETTE
	.export		_main

.segment	"RODATA"

_TEXT:
	.byte	$48,$65,$6C,$6C,$6F,$20,$4E,$45,$53,$21,$00
_PALETTE:
	.byte	$1F
	.byte	$00
	.byte	$10
	.byte	$20

.segment	"BSS"

.segment	"BSS"
_i:
	.res	1,$00
.segment	"BSS"
_NMI_flag:
	.res	1,$00
.segment	"BSS"
_Frame_Count:
	.res	1,$00
.segment	"BSS"
_text_pos:
	.res	1,$00

; ---------------------------------------------------------------
; void __near__ loadPalette (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_loadPalette: near

.segment	"CODE"

;
; PPU_ADDRESS = 0x3f; 
;
	lda     #$3F
	sta     $2006
;
; PPU_ADDRESS = 0x00;
;
	lda     #$00
	sta     $2006
;
; for(i = 0; i < sizeof(PALETTE); ++i) {
;
	sta     _i
L006D:	lda     _i
	cmp     #$04
	bcs     L002D
;
; PPU_DATA = PALETTE[i]; //Loads our palatte colors into memory
;
	ldy     _i
	lda     _PALETTE,y
	sta     $2007
;
; for(i = 0; i < sizeof(PALETTE); ++i) {
;
	inc     _i
	jmp     L006D
;
; }
;
L002D:	rts

.endproc

; ---------------------------------------------------------------
; void __near__ loadText (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_loadText: near

.segment	"CODE"

;
; if(text_pos < sizeof(TEXT)) {
;
	lda     _text_pos
	cmp     #$0B
	bcs     L006E
;
; PPU_ADDRESS = 0x21;
;
	lda     #$21
	sta     $2006
;
; PPU_ADDRESS = 0xca + text_pos;
;
	lda     _text_pos
	clc
	adc     #$CA
	sta     $2006
;
; PPU_DATA = TEXT[text_pos];
;
	ldy     _text_pos
	lda     _TEXT,y
	sta     $2007
;
; ++text_pos;
;
	inc     _text_pos
;
; } else {
;
	rts
;
; text_pos = 0;
;
L006E:	lda     #$00
	sta     _text_pos
;
; PPU_ADDRESS = 0x21;
;
	lda     #$21
	sta     $2006
;
; PPU_ADDRESS = 0xca;
;
	lda     #$CA
	sta     $2006
;
; for(i = 0; i < sizeof(TEXT); ++i) {
;
	lda     #$00
	sta     _i
L006F:	lda     _i
	cmp     #$0B
	bcs     L0062
;
; PPU_DATA = 0; //Clear the text by writing tile 0 (blank) in it's place
;
	lda     #$00
	sta     $2007
;
; for(i = 0; i < sizeof(TEXT); ++i) {
;
	inc     _i
	jmp     L006F
;
; }
;
L0062:	rts

.endproc

; ---------------------------------------------------------------
; void __near__ resetScroll (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_resetScroll: near

.segment	"CODE"

;
; PPU_ADDRESS = 0;
;
	lda     #$00
	sta     $2006
;
; PPU_ADDRESS = 0;
;
	sta     $2006
;
; SCROLL = 0;
;
	sta     $2005
;
; SCROLL = 0;
;
	sta     $2005
;
; }
;
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ main (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

.segment	"CODE"

;
; PPU_CTRL = 0;
;
	lda     #$00
	sta     $2000
;
; PPU_MASK = 0;
;
	sta     $2001
;
; loadPalette();
;
	jsr     _loadPalette
;
; resetScroll();
;
	jsr     _resetScroll
;
; PPU_CTRL = 0x90; //NMI on
;
	lda     #$90
	sta     $2000
;
; PPU_MASK = 0x1e; //screen on
;
	lda     #$1E
	sta     $2001
;
; while(NMI_flag == 0); //NMI_flag is set in reset.s
;
L0070:	lda     _NMI_flag
	beq     L0070
;
; NMI_flag = 0;
;
	lda     #$00
	sta     _NMI_flag
;
; if(Frame_Count == 15) {
;
	lda     _Frame_Count
	cmp     #$0F
	bne     L0070
;
; loadText();
;
	jsr     _loadText
;
; resetScroll();
;
	jsr     _resetScroll
;
; Frame_Count = 0;
;
	lda     #$00
	sta     _Frame_Count
;
; while(1) {
;
	jmp     L0070

.endproc

