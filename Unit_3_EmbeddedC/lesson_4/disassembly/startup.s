
startup.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <Reset_Handler>:
   0:	b580      	push	{r7, lr}
   2:	b086      	sub	sp, #24
   4:	af00      	add	r7, sp, #0
   6:	f240 0200 	movw	r2, #0
   a:	f2c0 0200 	movt	r2, #0
   e:	f240 0300 	movw	r3, #0
  12:	f2c0 0300 	movt	r3, #0
  16:	1ad3      	subs	r3, r2, r3
  18:	60bb      	str	r3, [r7, #8]
  1a:	f240 0300 	movw	r3, #0
  1e:	f2c0 0300 	movt	r3, #0
  22:	617b      	str	r3, [r7, #20]
  24:	f240 0300 	movw	r3, #0
  28:	f2c0 0300 	movt	r3, #0
  2c:	613b      	str	r3, [r7, #16]
  2e:	f04f 0300 	mov.w	r3, #0
  32:	60fb      	str	r3, [r7, #12]
  34:	e00f      	b.n	56 <Reset_Handler+0x56>
  36:	697b      	ldr	r3, [r7, #20]
  38:	781a      	ldrb	r2, [r3, #0]
  3a:	693b      	ldr	r3, [r7, #16]
  3c:	701a      	strb	r2, [r3, #0]
  3e:	693b      	ldr	r3, [r7, #16]
  40:	f103 0301 	add.w	r3, r3, #1
  44:	613b      	str	r3, [r7, #16]
  46:	697b      	ldr	r3, [r7, #20]
  48:	f103 0301 	add.w	r3, r3, #1
  4c:	617b      	str	r3, [r7, #20]
  4e:	68fb      	ldr	r3, [r7, #12]
  50:	f103 0301 	add.w	r3, r3, #1
  54:	60fb      	str	r3, [r7, #12]
  56:	68fa      	ldr	r2, [r7, #12]
  58:	68bb      	ldr	r3, [r7, #8]
  5a:	429a      	cmp	r2, r3
  5c:	d3eb      	bcc.n	36 <Reset_Handler+0x36>
  5e:	f240 0200 	movw	r2, #0
  62:	f2c0 0200 	movt	r2, #0
  66:	f240 0300 	movw	r3, #0
  6a:	f2c0 0300 	movt	r3, #0
  6e:	1ad3      	subs	r3, r2, r3
  70:	607b      	str	r3, [r7, #4]
  72:	f240 0300 	movw	r3, #0
  76:	f2c0 0300 	movt	r3, #0
  7a:	613b      	str	r3, [r7, #16]
  7c:	f04f 0300 	mov.w	r3, #0
  80:	60fb      	str	r3, [r7, #12]
  82:	e00b      	b.n	9c <Reset_Handler+0x9c>
  84:	693b      	ldr	r3, [r7, #16]
  86:	f04f 0200 	mov.w	r2, #0
  8a:	701a      	strb	r2, [r3, #0]
  8c:	693b      	ldr	r3, [r7, #16]
  8e:	f103 0301 	add.w	r3, r3, #1
  92:	613b      	str	r3, [r7, #16]
  94:	68fb      	ldr	r3, [r7, #12]
  96:	f103 0301 	add.w	r3, r3, #1
  9a:	60fb      	str	r3, [r7, #12]
  9c:	68fa      	ldr	r2, [r7, #12]
  9e:	687b      	ldr	r3, [r7, #4]
  a0:	429a      	cmp	r2, r3
  a2:	d3ef      	bcc.n	84 <Reset_Handler+0x84>
  a4:	f7ff fffe 	bl	0 <main>
  a8:	f107 0718 	add.w	r7, r7, #24
  ac:	46bd      	mov	sp, r7
  ae:	bd80      	pop	{r7, pc}

000000b0 <Default_Handler>:
  b0:	b580      	push	{r7, lr}
  b2:	af00      	add	r7, sp, #0
  b4:	f7ff fffe 	bl	0 <Reset_Handler>
  b8:	bd80      	pop	{r7, pc}
  ba:	bf00      	nop

Disassembly of section .bss:

00000000 <stack_top>:
	...

Disassembly of section .vectors:

00000000 <g_arr_p_2_f>:
   0:	00000400 	andeq	r0, r0, r0, lsl #8
	...

Disassembly of section .debug_info:

00000000 <.debug_info>:
   0:	00000155 	andeq	r0, r0, r5, asr r1
   4:	00000002 	andeq	r0, r0, r2
   8:	01040000 	mrseq	r0, (UNDEF: 4)
   c:	00000049 	andeq	r0, r0, r9, asr #32
  10:	00006801 	andeq	r6, r0, r1, lsl #16
  14:	0000b900 	andeq	fp, r0, r0, lsl #18
  18:	00000000 	andeq	r0, r0, r0
  1c:	0000ba00 	andeq	fp, r0, r0, lsl #20
  20:	00000000 	andeq	r0, r0, r0
  24:	00550200 	subseq	r0, r5, r0, lsl #4
  28:	02010000 	andeq	r0, r1, #0
  2c:	00000030 	andeq	r0, r0, r0, lsr r0
  30:	18070403 	stmdane	r7, {r0, r1, sl}
  34:	04000000 	streq	r0, [r0], #-0
  38:	00000001 	andeq	r0, r0, r1
  3c:	01190100 	tsteq	r9, r0, lsl #2
  40:	00000000 	andeq	r0, r0, r0
  44:	000000b0 	strheq	r0, [r0], -r0	; <UNPREDICTABLE>
  48:	00000000 	andeq	r0, r0, r0
  4c:	00009601 	andeq	r9, r0, r1, lsl #12
  50:	005e0500 	subseq	r0, lr, r0, lsl #10
  54:	1c010000 	stcne	0, cr0, [r1], {-0}
  58:	00000025 	andeq	r0, r0, r5, lsr #32
  5c:	05689102 	strbeq	r9, [r8, #-258]!	; 0x102
  60:	00000097 	muleq	r0, r7, r0
  64:	00961d01 	addseq	r1, r6, r1, lsl #26
  68:	91020000 	mrsls	r0, (UNDEF: 2)
  6c:	007a0574 	rsbseq	r0, sl, r4, ror r5
  70:	1e010000 	cdpne	0, 0, cr0, cr1, cr0, {0}
  74:	00000096 	muleq	r0, r6, r0
  78:	06709102 	ldrbteq	r9, [r0], -r2, lsl #2
  7c:	1f010069 	svcne	0x00010069
  80:	000000a3 	andeq	r0, r0, r3, lsr #1
  84:	056c9102 	strbeq	r9, [ip, #-258]!	; 0x102
  88:	000000b0 	strheq	r0, [r0], -r0	; <UNPREDICTABLE>
  8c:	00252601 	eoreq	r2, r5, r1, lsl #12
  90:	91020000 	mrsls	r0, (UNDEF: 2)
  94:	04070064 	streq	r0, [r7], #-100	; 0x64
  98:	0000009c 	muleq	r0, ip, r0
  9c:	80080103 	andhi	r0, r8, r3, lsl #2
  a0:	08000000 	stmdaeq	r0, {}	; <UNPREDICTABLE>
  a4:	6e690504 	cdpvs	5, 6, cr0, cr9, cr4, {0}
  a8:	01090074 	tsteq	r9, r4, ror r0
  ac:	00000039 	andeq	r0, r0, r9, lsr r0
  b0:	b0013201 	andlt	r3, r1, r1, lsl #4
  b4:	ba000000 	blt	8 <.debug_info+0x8>
  b8:	38000000 	stmdacc	r0, {}	; <UNPREDICTABLE>
  bc:	01000000 	mrseq	r0, (UNDEF: 0)
  c0:	0000250a 	andeq	r2, r0, sl, lsl #10
  c4:	0000d000 	andeq	sp, r0, r0
  c8:	00d00b00 	sbcseq	r0, r0, r0, lsl #22
  cc:	00ff0000 	rscseq	r0, pc, r0
  d0:	8e070403 	cdphi	4, 0, cr0, cr7, cr3, {0}
  d4:	05000000 	streq	r0, [r0, #-0]
  d8:	0000000e 	andeq	r0, r0, lr
  dc:	00c00f01 	sbceq	r0, r0, r1, lsl #30
  e0:	03050000 	movweq	r0, #20480	; 0x5000
  e4:	00000000 	andeq	r0, r0, r0
  e8:	0000720c 	andeq	r7, r0, ip, lsl #4
  ec:	a3090100 	movwge	r0, #37120	; 0x9100
  f0:	01000000 	mrseq	r0, (UNDEF: 0)
  f4:	00310c01 	eorseq	r0, r1, r1, lsl #24
  f8:	0a010000 	beq	40100 <Default_Handler+0x40050>
  fc:	000000a3 	andeq	r0, r0, r3, lsr #1
 100:	0b0c0101 	bleq	30040c <Default_Handler+0x30035c>
 104:	01000001 	tsteq	r0, r1
 108:	0000a30b 	andeq	sl, r0, fp, lsl #6
 10c:	0c010100 	stfeqs	f0, [r1], {-0}
 110:	0000002a 	andeq	r0, r0, sl, lsr #32
 114:	00a30c01 	adceq	r0, r3, r1, lsl #24
 118:	01010000 	mrseq	r0, (UNDEF: 1)
 11c:	00009d0c 	andeq	r9, r0, ip, lsl #26
 120:	a30d0100 	movwge	r0, #53504	; 0xd100
 124:	01000000 	mrseq	r0, (UNDEF: 0)
 128:	013b0a01 	teqeq	fp, r1, lsl #20
 12c:	01390000 	teqeq	r9, r0
 130:	d00b0000 	andle	r0, fp, r0
 134:	03000000 	movweq	r0, #0
 138:	07010d00 	streq	r0, [r1, -r0, lsl #26]
 13c:	00013904 	andeq	r3, r1, r4, lsl #18
 140:	00a40e00 	adceq	r0, r4, r0, lsl #28
 144:	11010000 	mrsne	r0, (UNDEF: 1)
 148:	00000153 	andeq	r0, r0, r3, asr r1
 14c:	00030501 	andeq	r0, r3, r1, lsl #10
 150:	0f000000 	svceq	0x00000000
 154:	00000129 	andeq	r0, r0, r9, lsr #2
	...

Disassembly of section .debug_abbrev:

00000000 <.debug_abbrev>:
   0:	25011101 	strcs	r1, [r1, #-257]	; 0x101
   4:	030b130e 	movweq	r1, #45838	; 0xb30e
   8:	110e1b0e 	tstne	lr, lr, lsl #22
   c:	10011201 	andne	r1, r1, r1, lsl #4
  10:	02000006 	andeq	r0, r0, #6
  14:	0e030016 	mcreq	0, 0, r0, cr3, cr6, {0}
  18:	0b3b0b3a 	bleq	ec2d08 <Default_Handler+0xec2c58>
  1c:	00001349 	andeq	r1, r0, r9, asr #6
  20:	0b002403 	bleq	9034 <Default_Handler+0x8f84>
  24:	030b3e0b 	movweq	r3, #48651	; 0xbe0b
  28:	0400000e 	streq	r0, [r0], #-14
  2c:	0c3f012e 	ldfeqs	f0, [pc], #-184	; ffffff7c <Default_Handler+0xfffffecc>
  30:	0b3a0e03 	bleq	e83844 <Default_Handler+0xe83794>
  34:	0c270b3b 	stceq	11, cr0, [r7], #-236	; 0xffffff14
  38:	01120111 	tsteq	r2, r1, lsl r1
  3c:	42960640 	addsmi	r0, r6, #64, 12	; 0x4000000
  40:	0013010c 	andseq	r0, r3, ip, lsl #2
  44:	00340500 	eorseq	r0, r4, r0, lsl #10
  48:	0b3a0e03 	bleq	e8385c <Default_Handler+0xe837ac>
  4c:	13490b3b 	movtne	r0, #39739	; 0x9b3b
  50:	00000a02 	andeq	r0, r0, r2, lsl #20
  54:	03003406 	movweq	r3, #1030	; 0x406
  58:	3b0b3a08 	blcc	2ce880 <Default_Handler+0x2ce7d0>
  5c:	0213490b 	andseq	r4, r3, #180224	; 0x2c000
  60:	0700000a 	streq	r0, [r0, -sl]
  64:	0b0b000f 	bleq	2c00a8 <Default_Handler+0x2bfff8>
  68:	00001349 	andeq	r1, r0, r9, asr #6
  6c:	0b002408 	bleq	9094 <Default_Handler+0x8fe4>
  70:	030b3e0b 	movweq	r3, #48651	; 0xbe0b
  74:	09000008 	stmdbeq	r0, {r3}
  78:	0c3f002e 	ldceq	0, cr0, [pc], #-184	; ffffffc8 <Default_Handler+0xffffff18>
  7c:	0b3a0e03 	bleq	e83890 <Default_Handler+0xe837e0>
  80:	0c270b3b 	stceq	11, cr0, [r7], #-236	; 0xffffff14
  84:	01120111 	tsteq	r2, r1, lsl r1
  88:	42960640 	addsmi	r0, r6, #64, 12	; 0x4000000
  8c:	0a00000c 	beq	c4 <.debug_abbrev+0xc4>
  90:	13490101 	movtne	r0, #37121	; 0x9101
  94:	00001301 	andeq	r1, r0, r1, lsl #6
  98:	4900210b 	stmdbmi	r0, {r0, r1, r3, r8, sp}
  9c:	000b2f13 	andeq	r2, fp, r3, lsl pc
  a0:	00340c00 	eorseq	r0, r4, r0, lsl #24
  a4:	0b3a0e03 	bleq	e838b8 <Default_Handler+0xe83808>
  a8:	13490b3b 	movtne	r0, #39739	; 0x9b3b
  ac:	0c3c0c3f 	ldceq	12, cr0, [ip], #-252	; 0xffffff04
  b0:	150d0000 	strne	r0, [sp, #-0]
  b4:	000c2700 	andeq	r2, ip, r0, lsl #14
  b8:	00340e00 	eorseq	r0, r4, r0, lsl #28
  bc:	0b3a0e03 	bleq	e838d0 <Default_Handler+0xe83820>
  c0:	13490b3b 	movtne	r0, #39739	; 0x9b3b
  c4:	0a020c3f 	beq	831c8 <Default_Handler+0x83118>
  c8:	260f0000 	strcs	r0, [pc], -r0
  cc:	00134900 	andseq	r4, r3, r0, lsl #18
	...

Disassembly of section .debug_loc:

00000000 <.debug_loc>:
   0:	00000000 	andeq	r0, r0, r0
   4:	00000002 	andeq	r0, r0, r2
   8:	007d0002 	rsbseq	r0, sp, r2
   c:	00000002 	andeq	r0, r0, r2
  10:	00000004 	andeq	r0, r0, r4
  14:	087d0002 	ldmdaeq	sp!, {r1}^
  18:	00000004 	andeq	r0, r0, r4
  1c:	00000006 	andeq	r0, r0, r6
  20:	207d0002 	rsbscs	r0, sp, r2
  24:	00000006 	andeq	r0, r0, r6
  28:	000000b0 	strheq	r0, [r0], -r0	; <UNPREDICTABLE>
  2c:	20770002 	rsbscs	r0, r7, r2
	...
  38:	000000b0 	strheq	r0, [r0], -r0	; <UNPREDICTABLE>
  3c:	000000b2 	strheq	r0, [r0], -r2
  40:	007d0002 	rsbseq	r0, sp, r2
  44:	000000b2 	strheq	r0, [r0], -r2
  48:	000000b4 	strheq	r0, [r0], -r4
  4c:	087d0002 	ldmdaeq	sp!, {r1}^
  50:	000000b4 	strheq	r0, [r0], -r4
  54:	000000ba 	strheq	r0, [r0], -sl
  58:	08770002 	ldmdaeq	r7!, {r1}^
	...

Disassembly of section .debug_aranges:

00000000 <.debug_aranges>:
   0:	0000001c 	andeq	r0, r0, ip, lsl r0
   4:	00000002 	andeq	r0, r0, r2
   8:	00040000 	andeq	r0, r4, r0
	...
  14:	000000ba 	strheq	r0, [r0], -sl
	...

Disassembly of section .debug_line:

00000000 <.debug_line>:
   0:	00000063 	andeq	r0, r0, r3, rrx
   4:	00200002 	eoreq	r0, r0, r2
   8:	01020000 	mrseq	r0, (UNDEF: 2)
   c:	000d0efb 	strdeq	r0, [sp], -fp
  10:	01010101 	tsteq	r1, r1, lsl #2
  14:	01000000 	mrseq	r0, (UNDEF: 0)
  18:	00010000 	andeq	r0, r1, r0
  1c:	72617473 	rsbvc	r7, r1, #1929379840	; 0x73000000
  20:	2e707574 	mrccs	5, 3, r7, cr0, cr4, {3}
  24:	00000063 	andeq	r0, r0, r3, rrx
  28:	05000000 	streq	r0, [r0, #-0]
  2c:	00000002 	andeq	r0, r0, r2
  30:	01190300 	tsteq	r9, r0, lsl #6
  34:	5a599f3e 	bpl	1667d34 <Default_Handler+0x1667c84>
  38:	02040200 	andeq	r0, r4, #0, 4
  3c:	0402004c 	streq	r0, [r2], #-76	; 0x4c
  40:	0200b802 	andeq	fp, r0, #131072	; 0x20000
  44:	4a060104 	bmi	18045c <Default_Handler+0x1803ac>
  48:	5a9f5006 	bpl	fe7d4068 <Default_Handler+0xfe7d3fb8>
  4c:	02040200 	andeq	r0, r4, #0, 4
  50:	0402004c 	streq	r0, [r2], #-76	; 0x4c
  54:	02008002 	andeq	r8, r0, #2
  58:	4a060104 	bmi	180470 <Default_Handler+0x1803c0>
  5c:	4d2f5006 	stcmi	0, cr5, [pc, #-24]!	; 4c <.debug_line+0x4c>
  60:	01022f2f 	tsteq	r2, pc, lsr #30
  64:	Address 0x00000064 is out of bounds.


Disassembly of section .debug_str:

00000000 <.debug_str>:
   0:	65736552 	ldrbvs	r6, [r3, #-1362]!	; 0x552
   4:	61485f74 	hvcvs	34292	; 0x85f4
   8:	656c646e 	strbvs	r6, [ip, #-1134]!	; 0x46e
   c:	74730072 	ldrbtvc	r0, [r3], #-114	; 0x72
  10:	5f6b6361 	svcpl	0x006b6361
  14:	00706f74 	rsbseq	r6, r0, r4, ror pc
  18:	676e6f6c 	strbvs	r6, [lr, -ip, ror #30]!
  1c:	736e7520 	cmnvc	lr, #32, 10	; 0x8000000
  20:	656e6769 	strbvs	r6, [lr, #-1897]!	; 0x769
  24:	6e692064 	cdpvs	0, 6, cr2, cr9, cr4, {3}
  28:	535f0074 	cmppl	pc, #116	; 0x74
  2c:	7373625f 	cmnvc	r3, #-268435451	; 0xf0000005
  30:	5f535f00 	svcpl	0x00535f00
  34:	61746164 	cmnvs	r4, r4, ror #2
  38:	66654400 	strbtvs	r4, [r5], -r0, lsl #8
  3c:	746c7561 	strbtvc	r7, [ip], #-1377	; 0x561
  40:	6e61485f 	mcrvs	8, 3, r4, cr1, cr15, {2}
  44:	72656c64 	rsbvc	r6, r5, #100, 24	; 0x6400
  48:	554e4700 	strbpl	r4, [lr, #-1792]	; 0x700
  4c:	34204320 	strtcc	r4, [r0], #-800	; 0x320
  50:	322e372e 	eorcc	r3, lr, #12058624	; 0xb80000
  54:	6e697500 	cdpvs	5, 6, cr7, cr9, cr0, {0}
  58:	5f323374 	svcpl	0x00323374
  5c:	61640074 	smcvs	16388	; 0x4004
  60:	735f6174 	cmpvc	pc, #116, 2
  64:	00657a69 	rsbeq	r7, r5, r9, ror #20
  68:	72617473 	rsbvc	r7, r1, #1929379840	; 0x73000000
  6c:	2e707574 	mrccs	5, 3, r7, cr0, cr4, {3}
  70:	455f0063 	ldrbmi	r0, [pc, #-99]	; 15 <.debug_str+0x15>
  74:	7865745f 	stmdavc	r5!, {r0, r1, r2, r3, r4, r6, sl, ip, sp, lr}^
  78:	5f700074 	svcpl	0x00700074
  7c:	00747364 	rsbseq	r7, r4, r4, ror #6
  80:	69736e75 	ldmdbvs	r3!, {r0, r2, r4, r5, r6, r9, sl, fp, sp, lr}^
  84:	64656e67 	strbtvs	r6, [r5], #-3687	; 0xe67
  88:	61686320 	cmnvs	r8, r0, lsr #6
  8c:	69730072 	ldmdbvs	r3!, {r1, r4, r5, r6}^
  90:	7974657a 	ldmdbvc	r4!, {r1, r3, r4, r5, r6, r8, sl, sp, lr}^
  94:	70006570 	andvc	r6, r0, r0, ror r5
  98:	6372735f 	cmnvs	r2, #2080374785	; 0x7c000001
  9c:	5f455f00 	svcpl	0x00455f00
  a0:	00737362 	rsbseq	r7, r3, r2, ror #6
  a4:	72615f67 	rsbvc	r5, r1, #412	; 0x19c
  a8:	5f705f72 	svcpl	0x00705f72
  ac:	00665f32 	rsbeq	r5, r6, r2, lsr pc
  b0:	5f737362 	svcpl	0x00737362
  b4:	657a6973 	ldrbvs	r6, [sl, #-2419]!	; 0x973
  b8:	5c3a4400 	cfldrspl	mvf4, [sl], #-0
  bc:	74666f73 	strbtvc	r6, [r6], #-3955	; 0xf73
  c0:	65726177 	ldrbvs	r6, [r2, #-375]!	; 0x177
  c4:	61654c5c 	cmnvs	r5, ip, asr ip
  c8:	495f6e72 	ldmdbmi	pc, {r1, r4, r5, r6, r9, sl, fp, sp, lr}^	; <UNPREDICTABLE>
  cc:	65445f6e 	strbvs	r5, [r4, #-3950]	; 0xf6e
  d0:	5c687470 	cfstrdpl	mvd7, [r8], #-448	; 0xfffffe40
  d4:	635f796d 	cmpvs	pc, #1785856	; 0x1b4000
  d8:	7365646f 	cmnvc	r5, #1862270976	; 0x6f000000
  dc:	696e555c 	stmdbvs	lr!, {r2, r3, r4, r6, r8, sl, ip, lr}^
  e0:	5f335f74 	svcpl	0x00335f74
  e4:	65626d65 	strbvs	r6, [r2, #-3429]!	; 0xd65
  e8:	64656464 	strbtvs	r6, [r5], #-1124	; 0x464
  ec:	5c435f20 	mcrrpl	15, 2, r5, r3, cr0
  f0:	7373656c 	cmnvc	r3, #108, 10	; 0x1b000000
  f4:	345f6e6f 	ldrbcc	r6, [pc], #-3695	; fc <.debug_str+0xfc>
  f8:	646f635c 	strbtvs	r6, [pc], #-860	; 100 <.debug_str+0x100>
  fc:	615f7365 	cmpvs	pc, r5, ror #6
 100:	735f646e 	cmpvc	pc, #1845493760	; 0x6e000000
 104:	70697263 	rsbvc	r7, r9, r3, ror #4
 108:	5f007374 	svcpl	0x00007374
 10c:	61645f45 	cmnvs	r4, r5, asr #30
 110:	Address 0x00000110 is out of bounds.


Disassembly of section .comment:

00000000 <.comment>:
   0:	43434700 	movtmi	r4, #14080	; 0x3700
   4:	4728203a 			; <UNDEFINED> instruction: 0x4728203a
   8:	2029554e 	eorcs	r5, r9, lr, asr #10
   c:	2e372e34 	mrccs	14, 1, r2, cr7, cr4, {1}
  10:	Address 0x00000010 is out of bounds.


Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00003241 	andeq	r3, r0, r1, asr #4
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000028 	andeq	r0, r0, r8, lsr #32
  10:	726f4305 	rsbvc	r4, pc, #335544320	; 0x14000000
  14:	2d786574 	cfldr64cs	mvdx6, [r8, #-464]!	; 0xfffffe30
  18:	0600344d 	streq	r3, [r0], -sp, asr #8
  1c:	094d070d 	stmdbeq	sp, {r0, r2, r3, r8, r9, sl}^
  20:	14041202 	strne	r1, [r4], #-514	; 0x202
  24:	17011501 	strne	r1, [r1, -r1, lsl #10]
  28:	19011803 	stmdbne	r1, {r0, r1, fp, ip}
  2c:	1e011a01 	vmlane.f32	s2, s2, s2
  30:	Address 0x00000030 is out of bounds.


Disassembly of section .debug_frame:

00000000 <.debug_frame>:
   0:	0000000c 	andeq	r0, r0, ip
   4:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
   8:	7c020001 	stcvc	0, cr0, [r2], {1}
   c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  10:	0000001c 	andeq	r0, r0, ip, lsl r0
	...
  1c:	000000b0 	strheq	r0, [r0], -r0	; <UNPREDICTABLE>
  20:	87080e41 	strhi	r0, [r8, -r1, asr #28]
  24:	41018e02 	tstmi	r1, r2, lsl #28
  28:	0d41200e 	stcleq	0, cr2, [r1, #-56]	; 0xffffffc8
  2c:	00000007 	andeq	r0, r0, r7
  30:	00000018 	andeq	r0, r0, r8, lsl r0
  34:	00000000 	andeq	r0, r0, r0
  38:	000000b0 	strheq	r0, [r0], -r0	; <UNPREDICTABLE>
  3c:	0000000a 	andeq	r0, r0, sl
  40:	87080e41 	strhi	r0, [r8, -r1, asr #28]
  44:	41018e02 	tstmi	r1, r2, lsl #28
  48:	0000070d 	andeq	r0, r0, sp, lsl #14
