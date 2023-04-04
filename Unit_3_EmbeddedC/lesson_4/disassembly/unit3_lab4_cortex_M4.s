
unit3_lab4_cortex_M4.elf:     file format elf32-littlearm


Disassembly of section .text:

00000000 <g_arr_p_2_f>:
   0:	20000400 	andcs	r0, r0, r0, lsl #8
   4:	00000011 	andeq	r0, r0, r1, lsl r0
   8:	000000c1 	andeq	r0, r0, r1, asr #1
   c:	000000c1 	andeq	r0, r0, r1, asr #1

00000010 <Reset_Handler>:
  10:	b580      	push	{r7, lr}
  12:	b086      	sub	sp, #24
  14:	af00      	add	r7, sp, #0
  16:	f240 0200 	movw	r2, #0
  1a:	f2c2 0200 	movt	r2, #8192	; 0x2000
  1e:	f240 0300 	movw	r3, #0
  22:	f2c2 0300 	movt	r3, #8192	; 0x2000
  26:	1ad3      	subs	r3, r2, r3
  28:	60bb      	str	r3, [r7, #8]
  2a:	f240 138c 	movw	r3, #396	; 0x18c
  2e:	f2c0 0300 	movt	r3, #0
  32:	617b      	str	r3, [r7, #20]
  34:	f240 0300 	movw	r3, #0
  38:	f2c2 0300 	movt	r3, #8192	; 0x2000
  3c:	613b      	str	r3, [r7, #16]
  3e:	f04f 0300 	mov.w	r3, #0
  42:	60fb      	str	r3, [r7, #12]
  44:	e00f      	b.n	66 <Reset_Handler+0x56>
  46:	697b      	ldr	r3, [r7, #20]
  48:	781a      	ldrb	r2, [r3, #0]
  4a:	693b      	ldr	r3, [r7, #16]
  4c:	701a      	strb	r2, [r3, #0]
  4e:	693b      	ldr	r3, [r7, #16]
  50:	f103 0301 	add.w	r3, r3, #1
  54:	613b      	str	r3, [r7, #16]
  56:	697b      	ldr	r3, [r7, #20]
  58:	f103 0301 	add.w	r3, r3, #1
  5c:	617b      	str	r3, [r7, #20]
  5e:	68fb      	ldr	r3, [r7, #12]
  60:	f103 0301 	add.w	r3, r3, #1
  64:	60fb      	str	r3, [r7, #12]
  66:	68fa      	ldr	r2, [r7, #12]
  68:	68bb      	ldr	r3, [r7, #8]
  6a:	429a      	cmp	r2, r3
  6c:	d3eb      	bcc.n	46 <Reset_Handler+0x36>
  6e:	f240 4200 	movw	r2, #1024	; 0x400
  72:	f2c2 0200 	movt	r2, #8192	; 0x2000
  76:	f240 0300 	movw	r3, #0
  7a:	f2c2 0300 	movt	r3, #8192	; 0x2000
  7e:	1ad3      	subs	r3, r2, r3
  80:	607b      	str	r3, [r7, #4]
  82:	f240 0300 	movw	r3, #0
  86:	f2c2 0300 	movt	r3, #8192	; 0x2000
  8a:	613b      	str	r3, [r7, #16]
  8c:	f04f 0300 	mov.w	r3, #0
  90:	60fb      	str	r3, [r7, #12]
  92:	e00b      	b.n	ac <Reset_Handler+0x9c>
  94:	693b      	ldr	r3, [r7, #16]
  96:	f04f 0200 	mov.w	r2, #0
  9a:	701a      	strb	r2, [r3, #0]
  9c:	693b      	ldr	r3, [r7, #16]
  9e:	f103 0301 	add.w	r3, r3, #1
  a2:	613b      	str	r3, [r7, #16]
  a4:	68fb      	ldr	r3, [r7, #12]
  a6:	f103 0301 	add.w	r3, r3, #1
  aa:	60fb      	str	r3, [r7, #12]
  ac:	68fa      	ldr	r2, [r7, #12]
  ae:	687b      	ldr	r3, [r7, #4]
  b0:	429a      	cmp	r2, r3
  b2:	d3ef      	bcc.n	94 <Reset_Handler+0x84>
  b4:	f000 f80a 	bl	cc <main>
  b8:	f107 0718 	add.w	r7, r7, #24
  bc:	46bd      	mov	sp, r7
  be:	bd80      	pop	{r7, pc}

000000c0 <Default_Handler>:
  c0:	b580      	push	{r7, lr}
  c2:	af00      	add	r7, sp, #0
  c4:	f7ff ffa4 	bl	10 <Reset_Handler>
  c8:	bd80      	pop	{r7, pc}
  ca:	bf00      	nop

000000cc <main>:
  cc:	b480      	push	{r7}
  ce:	b083      	sub	sp, #12
  d0:	af00      	add	r7, sp, #0
  d2:	f24e 1308 	movw	r3, #57608	; 0xe108
  d6:	f2c4 030f 	movt	r3, #16399	; 0x400f
  da:	f04f 0220 	mov.w	r2, #32
  de:	601a      	str	r2, [r3, #0]
  e0:	f04f 0300 	mov.w	r3, #0
  e4:	607b      	str	r3, [r7, #4]
  e6:	e00f      	b.n	108 <main+0x3c>
  e8:	f44f 43a8 	mov.w	r3, #21504	; 0x5400
  ec:	f2c4 0302 	movt	r3, #16386	; 0x4002
  f0:	f44f 42a8 	mov.w	r2, #21504	; 0x5400
  f4:	f2c4 0202 	movt	r2, #16386	; 0x4002
  f8:	6812      	ldr	r2, [r2, #0]
  fa:	f042 0208 	orr.w	r2, r2, #8
  fe:	601a      	str	r2, [r3, #0]
 100:	687b      	ldr	r3, [r7, #4]
 102:	f103 0301 	add.w	r3, r3, #1
 106:	607b      	str	r3, [r7, #4]
 108:	687b      	ldr	r3, [r7, #4]
 10a:	2bc7      	cmp	r3, #199	; 0xc7
 10c:	d9ec      	bls.n	e8 <main+0x1c>
 10e:	f245 531c 	movw	r3, #21788	; 0x551c
 112:	f2c4 0302 	movt	r3, #16386	; 0x4002
 116:	f245 521c 	movw	r2, #21788	; 0x551c
 11a:	f2c4 0202 	movt	r2, #16386	; 0x4002
 11e:	6812      	ldr	r2, [r2, #0]
 120:	f042 0208 	orr.w	r2, r2, #8
 124:	601a      	str	r2, [r3, #0]
 126:	f245 33fc 	movw	r3, #21500	; 0x53fc
 12a:	f2c4 0302 	movt	r3, #16386	; 0x4002
 12e:	f245 32fc 	movw	r2, #21500	; 0x53fc
 132:	f2c4 0202 	movt	r2, #16386	; 0x4002
 136:	6812      	ldr	r2, [r2, #0]
 138:	f042 0208 	orr.w	r2, r2, #8
 13c:	601a      	str	r2, [r3, #0]
 13e:	f04f 0300 	mov.w	r3, #0
 142:	607b      	str	r3, [r7, #4]
 144:	e003      	b.n	14e <main+0x82>
 146:	687b      	ldr	r3, [r7, #4]
 148:	f103 0301 	add.w	r3, r3, #1
 14c:	607b      	str	r3, [r7, #4]
 14e:	687a      	ldr	r2, [r7, #4]
 150:	f240 73cf 	movw	r3, #1999	; 0x7cf
 154:	429a      	cmp	r2, r3
 156:	d9f6      	bls.n	146 <main+0x7a>
 158:	f245 33fc 	movw	r3, #21500	; 0x53fc
 15c:	f2c4 0302 	movt	r3, #16386	; 0x4002
 160:	f245 32fc 	movw	r2, #21500	; 0x53fc
 164:	f2c4 0202 	movt	r2, #16386	; 0x4002
 168:	6812      	ldr	r2, [r2, #0]
 16a:	f022 0208 	bic.w	r2, r2, #8
 16e:	601a      	str	r2, [r3, #0]
 170:	f04f 0300 	mov.w	r3, #0
 174:	607b      	str	r3, [r7, #4]
 176:	e003      	b.n	180 <main+0xb4>
 178:	687b      	ldr	r3, [r7, #4]
 17a:	f103 0301 	add.w	r3, r3, #1
 17e:	607b      	str	r3, [r7, #4]
 180:	687a      	ldr	r2, [r7, #4]
 182:	f240 73cf 	movw	r3, #1999	; 0x7cf
 186:	429a      	cmp	r2, r3
 188:	d9f6      	bls.n	178 <main+0xac>
 18a:	e7cc      	b.n	126 <main+0x5a>

Disassembly of section .bss:

20000000 <_S_bss>:
	...

Disassembly of section .debug_info:

00000000 <.debug_info>:
   0:	00000155 	andeq	r0, r0, r5, asr r1
   4:	00000002 	andeq	r0, r0, r2
   8:	01040000 	mrseq	r0, (UNDEF: 4)
   c:	00000049 	andeq	r0, r0, r9, asr #32
  10:	00005f01 	andeq	r5, r0, r1, lsl #30
  14:	0000b000 	andeq	fp, r0, r0
  18:	00001000 	andeq	r1, r0, r0
  1c:	0000ca00 	andeq	ip, r0, r0, lsl #20
  20:	00000000 	andeq	r0, r0, r0
  24:	01170200 	tsteq	r7, r0, lsl #4
  28:	02010000 	andeq	r0, r1, #0
  2c:	00000030 	andeq	r0, r0, r0, lsr r0
  30:	18070403 	stmdane	r7, {r0, r1, sl}
  34:	04000000 	streq	r0, [r0], #-0
  38:	00000001 	andeq	r0, r0, r1
  3c:	01190100 	tsteq	r9, r0, lsl #2
  40:	00000010 	andeq	r0, r0, r0, lsl r0
  44:	000000c0 	andeq	r0, r0, r0, asr #1
  48:	00000000 	andeq	r0, r0, r0
  4c:	00009601 	andeq	r9, r0, r1, lsl #12
  50:	00550500 	subseq	r0, r5, r0, lsl #10
  54:	1c010000 	stcne	0, cr0, [r1], {-0}
  58:	00000025 	andeq	r0, r0, r5, lsr #32
  5c:	05689102 	strbeq	r9, [r8, #-258]!	; 0x102
  60:	0000008e 	andeq	r0, r0, lr, lsl #1
  64:	00961d01 	addseq	r1, r6, r1, lsl #26
  68:	91020000 	mrsls	r0, (UNDEF: 2)
  6c:	00710574 	rsbseq	r0, r1, r4, ror r5
  70:	1e010000 	cdpne	0, 0, cr0, cr1, cr0, {0}
  74:	00000096 	muleq	r0, r6, r0
  78:	06709102 	ldrbteq	r9, [r0], -r2, lsl #2
  7c:	1f010069 	svcne	0x00010069
  80:	000000a3 	andeq	r0, r0, r3, lsr #1
  84:	056c9102 	strbeq	r9, [ip, #-258]!	; 0x102
  88:	000000a7 	andeq	r0, r0, r7, lsr #1
  8c:	00252601 	eoreq	r2, r5, r1, lsl #12
  90:	91020000 	mrsls	r0, (UNDEF: 2)
  94:	04070064 	streq	r0, [r7], #-100	; 0x64
  98:	0000009c 	muleq	r0, ip, r0
  9c:	77080103 	strvc	r0, [r8, -r3, lsl #2]
  a0:	08000000 	stmdaeq	r0, {}	; <UNPREDICTABLE>
  a4:	6e690504 	cdpvs	5, 6, cr0, cr9, cr4, {0}
  a8:	01090074 	tsteq	r9, r4, ror r0
  ac:	00000039 	andeq	r0, r0, r9, lsr r0
  b0:	c0013201 	andgt	r3, r1, r1, lsl #4
  b4:	ca000000 	bgt	bc <Reset_Handler+0xac>
  b8:	38000000 	stmdacc	r0, {}	; <UNPREDICTABLE>
  bc:	01000000 	mrseq	r0, (UNDEF: 0)
  c0:	0000250a 	andeq	r2, r0, sl, lsl #10
  c4:	0000d000 	andeq	sp, r0, r0
  c8:	00d00b00 	sbcseq	r0, r0, r0, lsl #22
  cc:	00ff0000 	rscseq	r0, pc, r0
  d0:	85070403 	strhi	r0, [r7, #-1027]	; 0x403
  d4:	05000000 	streq	r0, [r0, #-0]
  d8:	0000000e 	andeq	r0, r0, lr
  dc:	00c00f01 	sbceq	r0, r0, r1, lsl #30
  e0:	03050000 	movweq	r0, #20480	; 0x5000
  e4:	20000000 	andcs	r0, r0, r0
  e8:	0000690c 	andeq	r6, r0, ip, lsl #18
  ec:	a3090100 	movwge	r0, #37120	; 0x9100
  f0:	01000000 	mrseq	r0, (UNDEF: 0)
  f4:	00310c01 	eorseq	r0, r1, r1, lsl #24
  f8:	0a010000 	beq	40100 <_E_text+0x3ff74>
  fc:	000000a3 	andeq	r0, r0, r3, lsr #1
 100:	020c0101 	andeq	r0, ip, #1073741824	; 0x40000000
 104:	01000001 	tsteq	r0, r1
 108:	0000a30b 	andeq	sl, r0, fp, lsl #6
 10c:	0c010100 	stfeqs	f0, [r1], {-0}
 110:	0000002a 	andeq	r0, r0, sl, lsr #32
 114:	00a30c01 	adceq	r0, r3, r1, lsl #24
 118:	01010000 	mrseq	r0, (UNDEF: 1)
 11c:	0000940c 	andeq	r9, r0, ip, lsl #8
 120:	a30d0100 	movwge	r0, #53504	; 0xd100
 124:	01000000 	mrseq	r0, (UNDEF: 0)
 128:	013b0a01 	teqeq	fp, r1, lsl #20
 12c:	01390000 	teqeq	r9, r0
 130:	d00b0000 	andle	r0, fp, r0
 134:	03000000 	movweq	r0, #0
 138:	07010d00 	streq	r0, [r1, -r0, lsl #26]
 13c:	00013904 	andeq	r3, r1, r4, lsl #18
 140:	009b0e00 	addseq	r0, fp, r0, lsl #28
 144:	11010000 	mrsne	r0, (UNDEF: 1)
 148:	00000153 	andeq	r0, r0, r3, asr r1
 14c:	00030501 	andeq	r0, r3, r1, lsl #10
 150:	0f000000 	svceq	0x00000000
 154:	00000129 	andeq	r0, r0, r9, lsr #2
 158:	00007400 	andeq	r7, r0, r0, lsl #8
 15c:	d2000200 	andle	r0, r0, #0, 4
 160:	04000000 	streq	r0, [r0], #-0
 164:	00004901 	andeq	r4, r0, r1, lsl #18
 168:	01200100 	teqeq	r0, r0, lsl #2
 16c:	00b00000 	adcseq	r0, r0, r0
 170:	00cc0000 	sbceq	r0, ip, r0
 174:	018c0000 	orreq	r0, ip, r0
 178:	00670000 	rsbeq	r0, r7, r0
 17c:	16020000 	strne	r0, [r2], -r0
 180:	01000001 	tsteq	r0, r1
 184:	00003002 	andeq	r3, r0, r2
 188:	00350300 	eorseq	r0, r5, r0, lsl #6
 18c:	04040000 	streq	r0, [r4], #-0
 190:	00001807 	andeq	r1, r0, r7, lsl #16
 194:	27010500 	strcs	r0, [r1, -r0, lsl #10]
 198:	01000001 	tsteq	r0, r1
 19c:	00690109 	rsbeq	r0, r9, r9, lsl #2
 1a0:	00cc0000 	sbceq	r0, ip, r0
 1a4:	018c0000 	orreq	r0, ip, r0
 1a8:	00640000 	rsbeq	r0, r4, r0
 1ac:	69010000 	stmdbvs	r1, {}	; <UNPREDICTABLE>
 1b0:	06000000 	streq	r0, [r0], -r0
 1b4:	0000010a 	andeq	r0, r0, sl, lsl #2
 1b8:	00700c01 	rsbseq	r0, r0, r1, lsl #24
 1bc:	91020000 	mrsls	r0, (UNDEF: 2)
 1c0:	04070074 	streq	r0, [r7], #-116	; 0x74
 1c4:	746e6905 	strbtvc	r6, [lr], #-2309	; 0x905
 1c8:	07040400 	streq	r0, [r4, -r0, lsl #8]
 1cc:	0000001d 	andeq	r0, r0, sp, lsl r0
	...

Disassembly of section .debug_abbrev:

00000000 <.debug_abbrev>:
   0:	25011101 	strcs	r1, [r1, #-257]	; 0x101
   4:	030b130e 	movweq	r1, #45838	; 0xb30e
   8:	110e1b0e 	tstne	lr, lr, lsl #22
   c:	10011201 	andne	r1, r1, r1, lsl #4
  10:	02000006 	andeq	r0, r0, #6
  14:	0e030016 	mcreq	0, 0, r0, cr3, cr6, {0}
  18:	0b3b0b3a 	bleq	ec2d08 <_E_text+0xec2b7c>
  1c:	00001349 	andeq	r1, r0, r9, asr #6
  20:	0b002403 	bleq	9034 <_E_text+0x8ea8>
  24:	030b3e0b 	movweq	r3, #48651	; 0xbe0b
  28:	0400000e 	streq	r0, [r0], #-14
  2c:	0c3f012e 	ldfeqs	f0, [pc], #-184	; ffffff7c <_E_bss+0xdffffb7c>
  30:	0b3a0e03 	bleq	e83844 <_E_text+0xe836b8>
  34:	0c270b3b 	stceq	11, cr0, [r7], #-236	; 0xffffff14
  38:	01120111 	tsteq	r2, r1, lsl r1
  3c:	42960640 	addsmi	r0, r6, #64, 12	; 0x4000000
  40:	0013010c 	andseq	r0, r3, ip, lsl #2
  44:	00340500 	eorseq	r0, r4, r0, lsl #10
  48:	0b3a0e03 	bleq	e8385c <_E_text+0xe836d0>
  4c:	13490b3b 	movtne	r0, #39739	; 0x9b3b
  50:	00000a02 	andeq	r0, r0, r2, lsl #20
  54:	03003406 	movweq	r3, #1030	; 0x406
  58:	3b0b3a08 	blcc	2ce880 <_E_text+0x2ce6f4>
  5c:	0213490b 	andseq	r4, r3, #180224	; 0x2c000
  60:	0700000a 	streq	r0, [r0, -sl]
  64:	0b0b000f 	bleq	2c00a8 <_E_text+0x2bff1c>
  68:	00001349 	andeq	r1, r0, r9, asr #6
  6c:	0b002408 	bleq	9094 <_E_text+0x8f08>
  70:	030b3e0b 	movweq	r3, #48651	; 0xbe0b
  74:	09000008 	stmdbeq	r0, {r3}
  78:	0c3f002e 	ldceq	0, cr0, [pc], #-184	; ffffffc8 <_E_bss+0xdffffbc8>
  7c:	0b3a0e03 	bleq	e83890 <_E_text+0xe83704>
  80:	0c270b3b 	stceq	11, cr0, [r7], #-236	; 0xffffff14
  84:	01120111 	tsteq	r2, r1, lsl r1
  88:	42960640 	addsmi	r0, r6, #64, 12	; 0x4000000
  8c:	0a00000c 	beq	c4 <Default_Handler+0x4>
  90:	13490101 	movtne	r0, #37121	; 0x9101
  94:	00001301 	andeq	r1, r0, r1, lsl #6
  98:	4900210b 	stmdbmi	r0, {r0, r1, r3, r8, sp}
  9c:	000b2f13 	andeq	r2, fp, r3, lsl pc
  a0:	00340c00 	eorseq	r0, r4, r0, lsl #24
  a4:	0b3a0e03 	bleq	e838b8 <_E_text+0xe8372c>
  a8:	13490b3b 	movtne	r0, #39739	; 0x9b3b
  ac:	0c3c0c3f 	ldceq	12, cr0, [ip], #-252	; 0xffffff04
  b0:	150d0000 	strne	r0, [sp, #-0]
  b4:	000c2700 	andeq	r2, ip, r0, lsl #14
  b8:	00340e00 	eorseq	r0, r4, r0, lsl #28
  bc:	0b3a0e03 	bleq	e838d0 <_E_text+0xe83744>
  c0:	13490b3b 	movtne	r0, #39739	; 0x9b3b
  c4:	0a020c3f 	beq	831c8 <_E_text+0x8303c>
  c8:	260f0000 	strcs	r0, [pc], -r0
  cc:	00134900 	andseq	r4, r3, r0, lsl #18
  d0:	11010000 	mrsne	r0, (UNDEF: 1)
  d4:	130e2501 	movwne	r2, #58625	; 0xe501
  d8:	1b0e030b 	blne	380d0c <_E_text+0x380b80>
  dc:	1201110e 	andne	r1, r1, #-2147483645	; 0x80000003
  e0:	00061001 	andeq	r1, r6, r1
  e4:	00160200 	andseq	r0, r6, r0, lsl #4
  e8:	0b3a0e03 	bleq	e838fc <_E_text+0xe83770>
  ec:	13490b3b 	movtne	r0, #39739	; 0x9b3b
  f0:	35030000 	strcc	r0, [r3, #-0]
  f4:	00134900 	andseq	r4, r3, r0, lsl #18
  f8:	00240400 	eoreq	r0, r4, r0, lsl #8
  fc:	0b3e0b0b 	bleq	f82d30 <_E_text+0xf82ba4>
 100:	00000e03 	andeq	r0, r0, r3, lsl #28
 104:	3f012e05 	svccc	0x00012e05
 108:	3a0e030c 	bcc	380d40 <_E_text+0x380bb4>
 10c:	270b3b0b 	strcs	r3, [fp, -fp, lsl #22]
 110:	1113490c 	tstne	r3, ip, lsl #18
 114:	40011201 	andmi	r1, r1, r1, lsl #4
 118:	0c429706 	mcrreq	7, 0, r9, r2, cr6
 11c:	00001301 	andeq	r1, r0, r1, lsl #6
 120:	03003406 	movweq	r3, #1030	; 0x406
 124:	3b0b3a0e 	blcc	2ce964 <_E_text+0x2ce7d8>
 128:	0213490b 	andseq	r4, r3, #180224	; 0x2c000
 12c:	0700000a 	streq	r0, [r0, -sl]
 130:	0b0b0024 	bleq	2c01c8 <_E_text+0x2c003c>
 134:	08030b3e 	stmdaeq	r3, {r1, r2, r3, r4, r5, r8, r9, fp}
 138:	Address 0x00000138 is out of bounds.


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
  68:	00000002 	andeq	r0, r0, r2
  6c:	007d0002 	rsbseq	r0, sp, r2
  70:	00000002 	andeq	r0, r0, r2
  74:	00000004 	andeq	r0, r0, r4
  78:	047d0002 	ldrbteq	r0, [sp], #-2
  7c:	00000004 	andeq	r0, r0, r4
  80:	00000006 	andeq	r0, r0, r6
  84:	107d0002 	rsbsne	r0, sp, r2
  88:	00000006 	andeq	r0, r0, r6
  8c:	000000c0 	andeq	r0, r0, r0, asr #1
  90:	10770002 	rsbsne	r0, r7, r2
	...

Disassembly of section .debug_aranges:

00000000 <.debug_aranges>:
   0:	0000001c 	andeq	r0, r0, ip, lsl r0
   4:	00000002 	andeq	r0, r0, r2
   8:	00040000 	andeq	r0, r4, r0
   c:	00000000 	andeq	r0, r0, r0
  10:	00000010 	andeq	r0, r0, r0, lsl r0
  14:	000000ba 	strheq	r0, [r0], -sl
	...
  20:	0000001c 	andeq	r0, r0, ip, lsl r0
  24:	01590002 	cmpeq	r9, r2
  28:	00040000 	andeq	r0, r4, r0
  2c:	00000000 	andeq	r0, r0, r0
  30:	000000cc 	andeq	r0, r0, ip, asr #1
  34:	000000c0 	andeq	r0, r0, r0, asr #1
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
  2c:	00001002 	andeq	r1, r0, r2
  30:	01190300 	tsteq	r9, r0, lsl #6
  34:	5a599f3e 	bpl	1667d34 <_E_text+0x1667ba8>
  38:	02040200 	andeq	r0, r4, #0, 4
  3c:	0402004c 	streq	r0, [r2], #-76	; 0x4c
  40:	0200b802 	andeq	fp, r0, #131072	; 0x20000
  44:	4a060104 	bmi	18045c <_E_text+0x1802d0>
  48:	5a9f5006 	bpl	fe7d4068 <_E_bss+0xde7d3c68>
  4c:	02040200 	andeq	r0, r4, #0, 4
  50:	0402004c 	streq	r0, [r2], #-76	; 0x4c
  54:	02008002 	andeq	r8, r0, #2
  58:	4a060104 	bmi	180470 <_E_text+0x1802e4>
  5c:	4d2f5006 	stcmi	0, cr5, [pc, #-24]!	; 4c <Reset_Handler+0x3c>
  60:	01022f2f 	tsteq	r2, pc, lsr #30
  64:	63010100 	movwvs	r0, #4352	; 0x1100
  68:	02000000 	andeq	r0, r0, #0
  6c:	00001d00 	andeq	r1, r0, r0, lsl #26
  70:	fb010200 	blx	4087a <_E_text+0x406ee>
  74:	01000d0e 	tsteq	r0, lr, lsl #26
  78:	00010101 	andeq	r0, r1, r1, lsl #2
  7c:	00010000 	andeq	r0, r1, r0
  80:	6d000100 	stfvss	f0, [r0, #-0]
  84:	2e6e6961 	cdpcs	9, 6, cr6, cr14, cr1, {3}
  88:	00000063 	andeq	r0, r0, r3, rrx
  8c:	05000000 	streq	r0, [r0, #-0]
  90:	0000cc02 	andeq	ip, r0, r2, lsl #24
  94:	01090300 	mrseq	r0, (UNDEF: 57)
  98:	0200763d 	andeq	r7, r0, #63963136	; 0x3d00000
  9c:	004b0204 	subeq	r0, fp, r4, lsl #4
  a0:	b9020402 	stmdblt	r2, {r1, sl}
  a4:	01040200 	mrseq	r0, R12_usr
  a8:	3e064a06 	vmlacc.f32	s8, s12, s12
  ac:	0200bbbd 	andeq	fp, r0, #193536	; 0x2f400
  b0:	4a060204 	bmi	1808c8 <_E_text+0x18073c>
  b4:	01040200 	mrseq	r0, R12_usr
  b8:	bb59064a 	bllt	16419e8 <_E_text+0x164185c>
  bc:	02040200 	andeq	r0, r4, #0, 4
  c0:	02004a06 	andeq	r4, r0, #24576	; 0x6000
  c4:	064a0104 	strbeq	r0, [sl], -r4, lsl #2
  c8:	00010259 	andeq	r0, r1, r9, asr r2
  cc:	Address 0x000000cc is out of bounds.


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
  54:	74616400 	strbtvc	r6, [r1], #-1024	; 0x400
  58:	69735f61 	ldmdbvs	r3!, {r0, r5, r6, r8, r9, sl, fp, ip, lr}^
  5c:	7300657a 	movwvc	r6, #1402	; 0x57a
  60:	74726174 	ldrbtvc	r6, [r2], #-372	; 0x174
  64:	632e7075 	teqvs	lr, #117	; 0x75
  68:	5f455f00 	svcpl	0x00455f00
  6c:	74786574 	ldrbtvc	r6, [r8], #-1396	; 0x574
  70:	645f7000 	ldrbvs	r7, [pc], #-0	; 78 <Reset_Handler+0x68>
  74:	75007473 	strvc	r7, [r0, #-1139]	; 0x473
  78:	6769736e 	strbvs	r7, [r9, -lr, ror #6]!
  7c:	2064656e 	rsbcs	r6, r4, lr, ror #10
  80:	72616863 	rsbvc	r6, r1, #6488064	; 0x630000
  84:	7a697300 	bvc	1a5cc8c <_E_text+0x1a5cb00>
  88:	70797465 	rsbsvc	r7, r9, r5, ror #8
  8c:	5f700065 	svcpl	0x00700065
  90:	00637273 	rsbeq	r7, r3, r3, ror r2
  94:	625f455f 	subsvs	r4, pc, #398458880	; 0x17c00000
  98:	67007373 	smlsdxvs	r0, r3, r3, r7
  9c:	7272615f 	rsbsvc	r6, r2, #-1073741801	; 0xc0000017
  a0:	325f705f 	subscc	r7, pc, #95	; 0x5f
  a4:	6200665f 	andvs	r6, r0, #99614720	; 0x5f00000
  a8:	735f7373 	cmpvc	pc, #-872415231	; 0xcc000001
  ac:	00657a69 	rsbeq	r7, r5, r9, ror #20
  b0:	735c3a44 	cmpvc	ip, #68, 20	; 0x44000
  b4:	7774666f 	ldrbvc	r6, [r4, -pc, ror #12]!
  b8:	5c657261 	sfmpl	f7, 2, [r5], #-388	; 0xfffffe7c
  bc:	7261654c 	rsbvc	r6, r1, #76, 10	; 0x13000000
  c0:	6e495f6e 	cdpvs	15, 4, cr5, cr9, cr14, {3}
  c4:	7065445f 	rsbvc	r4, r5, pc, asr r4
  c8:	6d5c6874 	ldclvs	8, cr6, [ip, #-464]	; 0xfffffe30
  cc:	6f635f79 	svcvs	0x00635f79
  d0:	5c736564 	cfldr64pl	mvdx6, [r3], #-400	; 0xfffffe70
  d4:	74696e55 	strbtvc	r6, [r9], #-3669	; 0xe55
  d8:	655f335f 	ldrbvs	r3, [pc, #-863]	; fffffd81 <_E_bss+0xdffff981>
  dc:	6465626d 	strbtvs	r6, [r5], #-621	; 0x26d
  e0:	20646564 	rsbcs	r6, r4, r4, ror #10
  e4:	6c5c435f 	mrrcvs	3, 5, r4, ip, cr15
  e8:	6f737365 	svcvs	0x00737365
  ec:	5c345f6e 	ldcpl	15, cr5, [r4], #-440	; 0xfffffe48
  f0:	65646f63 	strbvs	r6, [r4, #-3939]!	; 0xf63
  f4:	6e615f73 	mcrvs	15, 3, r5, cr1, cr3, {3}
  f8:	63735f64 	cmnvs	r3, #100, 30	; 0x190
  fc:	74706972 	ldrbtvc	r6, [r0], #-2418	; 0x972
 100:	455f0073 	ldrbmi	r0, [pc, #-115]	; 95 <Reset_Handler+0x85>
 104:	7461645f 	strbtvc	r6, [r1], #-1119	; 0x45f
 108:	65640061 	strbvs	r0, [r4, #-97]!	; 0x61
 10c:	5f79616c 	svcpl	0x0079616c
 110:	6e756f63 	cdpvs	15, 7, cr6, cr5, cr3, {3}
 114:	75760074 	ldrbvc	r0, [r6, #-116]!	; 0x74
 118:	33746e69 	cmncc	r4, #1680	; 0x690
 11c:	00745f32 	rsbseq	r5, r4, r2, lsr pc
 120:	6e69616d 	powvsez	f6, f1, #5.0
 124:	6d00632e 	stcvs	3, cr6, [r0, #-184]	; 0xffffff48
 128:	006e6961 	rsbeq	r6, lr, r1, ror #18

Disassembly of section .comment:

00000000 <.comment>:
   0:	3a434347 	bcc	10d0d24 <_E_text+0x10d0b98>
   4:	4e472820 	cdpmi	8, 4, cr2, cr7, cr0, {1}
   8:	34202955 	strtcc	r2, [r0], #-2389	; 0x955
   c:	322e372e 	eorcc	r3, lr, #12058624	; 0xb80000
	...

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
  14:	00000000 	andeq	r0, r0, r0
  18:	00000010 	andeq	r0, r0, r0, lsl r0
  1c:	000000b0 	strheq	r0, [r0], -r0	; <UNPREDICTABLE>
  20:	87080e41 	strhi	r0, [r8, -r1, asr #28]
  24:	41018e02 	tstmi	r1, r2, lsl #28
  28:	0d41200e 	stcleq	0, cr2, [r1, #-56]	; 0xffffffc8
  2c:	00000007 	andeq	r0, r0, r7
  30:	00000018 	andeq	r0, r0, r8, lsl r0
  34:	00000000 	andeq	r0, r0, r0
  38:	000000c0 	andeq	r0, r0, r0, asr #1
  3c:	0000000a 	andeq	r0, r0, sl
  40:	87080e41 	strhi	r0, [r8, -r1, asr #28]
  44:	41018e02 	tstmi	r1, r2, lsl #28
  48:	0000070d 	andeq	r0, r0, sp, lsl #14
  4c:	0000000c 	andeq	r0, r0, ip
  50:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
  54:	7c020001 	stcvc	0, cr0, [r2], {1}
  58:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  5c:	00000018 	andeq	r0, r0, r8, lsl r0
  60:	0000004c 	andeq	r0, r0, ip, asr #32
  64:	000000cc 	andeq	r0, r0, ip, asr #1
  68:	000000c0 	andeq	r0, r0, r0, asr #1
  6c:	87040e41 	strhi	r0, [r4, -r1, asr #28]
  70:	100e4101 	andne	r4, lr, r1, lsl #2
  74:	00070d41 	andeq	r0, r7, r1, asr #26
