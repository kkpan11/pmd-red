@ File generated by m4a2s Song-Module
	.include "MPlayDef.s"

	.equ	seq_631_grp, bank_026
	.equ	seq_631_pri, 127
	.equ	seq_631_rev, 0
	.equ	seq_631_mvl, 127
	.equ	seq_631_key, 0

	.section .rodata
	.global	seq_631
	.align	2

@*********************** Track 01 ***********************@

seq_631_0:
	.byte	KEYSH , seq_631_key+0
	.byte	TEMPO , 190/2
	.byte		VOICE , 12
	.byte		VOL   , 120*seq_631_mvl/mxv
	.byte		PAN   , c_v+0
	.byte	W01
	.byte		MOD   , 60
	.byte		MODT  , mod_pan
	.byte	W01
	.byte		N06   , Ds2 , v120
	.byte	W06
	.byte		        Gn3 
	.byte	W05
	.byte		VOICE , 13
	.byte	W01
	.byte		N03   , Cs2 
	.byte	W03
	.byte		N06   , As2 
	.byte	W06
	.byte		        As2 , v040
	.byte	W06
	.byte		        As2 , v020
	.byte	W06
	.byte	FINE

@******************************************************@

	.align	2

seq_631:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	seq_631_pri	@ Priority
	.byte	seq_631_rev	@ Reverb

	.word	seq_631_grp

	.word	seq_631_0

	.end