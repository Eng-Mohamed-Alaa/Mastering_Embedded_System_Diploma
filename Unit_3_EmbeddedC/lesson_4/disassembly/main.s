
main.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <main>:
   0:	b480      	push	{r7}
   2:	b083      	sub	sp, #12
   4:	af00      	add	r7, sp, #0
   6:	f24e 1308 	movw	r3, #57608	; 0xe108
   a:	f2c4 030f 	movt	r3, #16399	; 0x400f
   e:	f04f 0220 	mov.w	r2, #32
  12:	601a      	str	r2, [r3, #0]
  14:	f04f 0300 	mov.w	r3, #0
  18:	607b      	str	r3, [r7, #4]
  1a:	e00f      	b.n	3c <main+0x3c>
  1c:	f44f 43a8 	mov.w	r3, #21504	; 0x5400
  20:	f2c4 0302 	movt	r3, #16386	; 0x4002
  24:	f44f 42a8 	mov.w	r2, #21504	; 0x5400
  28:	f2c4 0202 	movt	r2, #16386	; 0x4002
  2c:	6812      	ldr	r2, [r2, #0]
  2e:	f042 0208 	orr.w	r2, r2, #8
  32:	601a      	str	r2, [r3, #0]
  34:	687b      	ldr	r3, [r7, #4]
  36:	f103 0301 	add.w	r3, r3, #1
  3a:	607b      	str	r3, [r7, #4]
  3c:	687b      	ldr	r3, [r7, #4]
  3e:	2bc7      	cmp	r3, #199	; 0xc7
  40:	d9ec      	bls.n	1c <main+0x1c>
  42:	f245 531c 	movw	r3, #21788	; 0x551c
  46:	f2c4 0302 	movt	r3, #16386	; 0x4002
  4a:	f245 521c 	movw	r2, #21788	; 0x551c
  4e:	f2c4 0202 	movt	r2, #16386	; 0x4002
  52:	6812      	ldr	r2, [r2, #0]
  54:	f042 0208 	orr.w	r2, r2, #8
  58:	601a      	str	r2, [r3, #0]
  5a:	f245 33fc 	movw	r3, #21500	; 0x53fc
  5e:	f2c4 0302 	movt	r3, #16386	; 0x4002
  62:	f245 32fc 	movw	r2, #21500	; 0x53fc
  66:	f2c4 0202 	movt	r2, #16386	; 0x4002
  6a:	6812      	ldr	r2, [r2, #0]
  6c:	f042 0208 	orr.w	r2, r2, #8
  70:	601a      	str	r2, [r3, #0]
  72:	f04f 0300 	mov.w	r3, #0
  76:	607b      	str	r3, [r7, #4]
  78:	e003      	b.n	82 <main+0x82>
  7a:	687b      	ldr	r3, [r7, #4]
  7c:	f103 0301 	add.w	r3, r3, #1
  80:	607b      	str	r3, [r7, #4]
  82:	687a      	ldr	r2, [r7, #4]
  84:	f240 73cf 	movw	r3, #1999	; 0x7cf
  88:	429a      	cmp	r2, r3
  8a:	d9f6      	bls.n	7a <main+0x7a>
  8c:	f245 33fc 	movw	r3, #21500	; 0x53fc
  90:	f2c4 0302 	movt	r3, #16386	; 0x4002
  94:	f245 32fc 	movw	r2, #21500	; 0x53fc
  98:	f2c4 0202 	movt	r2, #16386	; 0x4002
  9c:	6812      	ldr	r2, [r2, #0]
  9e:	f022 0208 	bic.w	r2, r2, #8
  a2:	601a      	str	r2, [r3, #0]
  a4:	f04f 0300 	mov.w	r3, #0
  a8:	607b      	str	r3, [r7, #4]
  aa:	e003      	b.n	b4 <main+0xb4>
  ac:	687b      	ldr	r3, [r7, #4]
  ae:	f103 0301 	add.w	r3, r3, #1
  b2:	607b      	str	r3, [r7, #4]
  b4:	687a      	ldr	r2, [r7, #4]
  b6:	f240 73cf 	movw	r3, #1999	; 0x7cf
  ba:	429a      	cmp	r2, r3
  bc:	d9f6      	bls.n	ac <main+0xac>
  be:	e7cc      	b.n	5a <main+0x5a>

Disassembly of section .debug_info:

00000000 <.debug_info>:
   0:	00000074 	andeq	r0, r0, r4, ror r0
   4:	00000002 	andeq	r0, r0, r2
   8:	01040000 	mrseq	r0, (UNDEF: 4)
   c:	00000016 	andeq	r0, r0, r6, lsl r0
  10:	00008101 	andeq	r8, r0, r1, lsl #2
  14:	00002f00 	andeq	r2, r0, r0, lsl #30
  18:	00000000 	andeq	r0, r0, r0
  1c:	0000c000 	andeq	ip, r0, r0
  20:	00000000 	andeq	r0, r0, r0
  24:	000c0200 	andeq	r0, ip, r0, lsl #4
  28:	02010000 	andeq	r0, r1, #0
  2c:	00000030 	andeq	r0, r0, r0, lsr r0
  30:	00003503 	andeq	r3, r0, r3, lsl #10
  34:	07040400 	streq	r0, [r4, -r0, lsl #8]
  38:	00000088 	andeq	r0, r0, r8, lsl #1
  3c:	009a0105 	addseq	r0, sl, r5, lsl #2
  40:	09010000 	stmdbeq	r1, {}	; <UNPREDICTABLE>
  44:	00006901 	andeq	r6, r0, r1, lsl #18
  48:	00000000 	andeq	r0, r0, r0
  4c:	0000c000 	andeq	ip, r0, r0
  50:	00000000 	andeq	r0, r0, r0
  54:	00690100 	rsbeq	r0, r9, r0, lsl #2
  58:	00060000 	andeq	r0, r6, r0
  5c:	01000000 	mrseq	r0, (UNDEF: 0)
  60:	0000700c 	andeq	r7, r0, ip
  64:	74910200 	ldrvc	r0, [r1], #512	; 0x200
  68:	05040700 	streq	r0, [r4, #-1792]	; 0x700
  6c:	00746e69 	rsbseq	r6, r4, r9, ror #28
  70:	22070404 	andcs	r0, r7, #4, 8	; 0x4000000
  74:	00000000 	andeq	r0, r0, r0

Disassembly of section .debug_abbrev:

00000000 <.debug_abbrev>:
   0:	25011101 	strcs	r1, [r1, #-257]	; 0x101
   4:	030b130e 	movweq	r1, #45838	; 0xb30e
   8:	110e1b0e 	tstne	lr, lr, lsl #22
   c:	10011201 	andne	r1, r1, r1, lsl #4
  10:	02000006 	andeq	r0, r0, #6
  14:	0e030016 	mcreq	0, 0, r0, cr3, cr6, {0}
  18:	0b3b0b3a 	bleq	ec2d08 <main+0xec2d08>
  1c:	00001349 	andeq	r1, r0, r9, asr #6
  20:	49003503 	stmdbmi	r0, {r0, r1, r8, sl, ip, sp}
  24:	04000013 	streq	r0, [r0], #-19
  28:	0b0b0024 	bleq	2c00c0 <main+0x2c00c0>
  2c:	0e030b3e 	vmoveq.16	d3[0], r0
  30:	2e050000 	cdpcs	0, 0, cr0, cr5, cr0, {0}
  34:	030c3f01 	movweq	r3, #52993	; 0xcf01
  38:	3b0b3a0e 	blcc	2ce878 <main+0x2ce878>
  3c:	490c270b 	stmdbmi	ip, {r0, r1, r3, r8, r9, sl, sp}
  40:	12011113 	andne	r1, r1, #-1073741820	; 0xc0000004
  44:	97064001 	strls	r4, [r6, -r1]
  48:	13010c42 	movwne	r0, #7234	; 0x1c42
  4c:	34060000 	strcc	r0, [r6], #-0
  50:	3a0e0300 	bcc	380c58 <main+0x380c58>
  54:	490b3b0b 	stmdbmi	fp, {r0, r1, r3, r8, r9, fp, ip, sp}
  58:	000a0213 	andeq	r0, sl, r3, lsl r2
  5c:	00240700 	eoreq	r0, r4, r0, lsl #14
  60:	0b3e0b0b 	bleq	f82c94 <main+0xf82c94>
  64:	00000803 	andeq	r0, r0, r3, lsl #16
	...

Disassembly of section .debug_loc:

00000000 <.debug_loc>:
   0:	00000000 	andeq	r0, r0, r0
   4:	00000002 	andeq	r0, r0, r2
   8:	007d0002 	rsbseq	r0, sp, r2
   c:	00000002 	andeq	r0, r0, r2
  10:	00000004 	andeq	r0, r0, r4
  14:	047d0002 	ldrbteq	r0, [sp], #-2
  18:	00000004 	andeq	r0, r0, r4
  1c:	00000006 	andeq	r0, r0, r6
  20:	107d0002 	rsbsne	r0, sp, r2
  24:	00000006 	andeq	r0, r0, r6
  28:	000000c0 	andeq	r0, r0, r0, asr #1
  2c:	10770002 	rsbsne	r0, r7, r2
	...

Disassembly of section .debug_aranges:

00000000 <.debug_aranges>:
   0:	0000001c 	andeq	r0, r0, ip, lsl r0
   4:	00000002 	andeq	r0, r0, r2
   8:	00040000 	andeq	r0, r4, r0
	...
  14:	000000c0 	andeq	r0, r0, r0, asr #1
	...

Disassembly of section .debug_line:

00000000 <.debug_line>:
   0:	00000063 	andeq	r0, r0, r3, rrx
   4:	001d0002 	andseq	r0, sp, r2
   8:	01020000 	mrseq	r0, (UNDEF: 2)
   c:	000d0efb 	strdeq	r0, [sp], -fp
  10:	01010101 	tsteq	r1, r1, lsl #2
  14:	01000000 	mrseq	r0, (UNDEF: 0)
  18:	00010000 	andeq	r0, r1, r0
  1c:	6e69616d 	powvsez	f6, f1, #5.0
  20:	0000632e 	andeq	r6, r0, lr, lsr #6
  24:	00000000 	andeq	r0, r0, r0
  28:	00000205 	andeq	r0, r0, r5, lsl #4
  2c:	09030000 	stmdbeq	r3, {}	; <UNPREDICTABLE>
  30:	00763d01 	rsbseq	r3, r6, r1, lsl #26
  34:	4b020402 	blmi	81044 <main+0x81044>
  38:	02040200 	andeq	r0, r4, #0, 4
  3c:	040200b9 	streq	r0, [r2], #-185	; 0xb9
  40:	064a0601 	strbeq	r0, [sl], -r1, lsl #12
  44:	00bbbd3e 	adcseq	fp, fp, lr, lsr sp
  48:	06020402 	streq	r0, [r2], -r2, lsl #8
  4c:	0402004a 	streq	r0, [r2], #-74	; 0x4a
  50:	59064a01 	stmdbpl	r6, {r0, r9, fp, lr}
  54:	040200bb 	streq	r0, [r2], #-187	; 0xbb
  58:	004a0602 	subeq	r0, sl, r2, lsl #12
  5c:	4a010402 	bmi	4106c <main+0x4106c>
  60:	01025906 	tsteq	r2, r6, lsl #18
  64:	Address 0x00000064 is out of bounds.


Disassembly of section .debug_str:

00000000 <.debug_str>:
   0:	616c6564 	cmnvs	ip, r4, ror #10
   4:	6f635f79 	svcvs	0x00635f79
   8:	00746e75 	rsbseq	r6, r4, r5, ror lr
   c:	6e697576 	mcrvs	5, 3, r7, cr9, cr6, {3}
  10:	5f323374 	svcpl	0x00323374
  14:	4e470074 	mcrmi	0, 2, r0, cr7, cr4, {3}
  18:	20432055 	subcs	r2, r3, r5, asr r0
  1c:	2e372e34 	mrccs	14, 1, r2, cr7, cr4, {1}
  20:	6e750032 	mrcvs	0, 3, r0, cr5, cr2, {1}
  24:	6e676973 	mcrvs	9, 3, r6, cr7, cr3, {3}
  28:	69206465 	stmdbvs	r0!, {r0, r2, r5, r6, sl, sp, lr}
  2c:	4400746e 	strmi	r7, [r0], #-1134	; 0x46e
  30:	6f735c3a 	svcvs	0x00735c3a
  34:	61777466 	cmnvs	r7, r6, ror #8
  38:	4c5c6572 	cfldr64mi	mvdx6, [ip], {114}	; 0x72
  3c:	6e726165 	rpwvssz	f6, f2, f5
  40:	5f6e495f 	svcpl	0x006e495f
  44:	74706544 	ldrbtvc	r6, [r0], #-1348	; 0x544
  48:	796d5c68 	stmdbvc	sp!, {r3, r5, r6, sl, fp, ip, lr}^
  4c:	646f635f 	strbtvs	r6, [pc], #-863	; 54 <.debug_str+0x54>
  50:	555c7365 	ldrbpl	r7, [ip, #-869]	; 0x365
  54:	5f74696e 	svcpl	0x0074696e
  58:	6d655f33 	stclvs	15, cr5, [r5, #-204]!	; 0xffffff34
  5c:	64646562 	strbtvs	r6, [r4], #-1378	; 0x562
  60:	5f206465 	svcpl	0x00206465
  64:	656c5c43 	strbvs	r5, [ip, #-3139]!	; 0xc43
  68:	6e6f7373 	mcrvs	3, 3, r7, cr15, cr3, {3}
  6c:	635c345f 	cmpvs	ip, #1593835520	; 0x5f000000
  70:	7365646f 	cmnvc	r5, #1862270976	; 0x6f000000
  74:	646e615f 	strbtvs	r6, [lr], #-351	; 0x15f
  78:	7263735f 	rsbvc	r7, r3, #2080374785	; 0x7c000001
  7c:	73747069 	cmnvc	r4, #105	; 0x69
  80:	69616d00 	stmdbvs	r1!, {r8, sl, fp, sp, lr}^
  84:	00632e6e 	rsbeq	r2, r3, lr, ror #28
  88:	676e6f6c 	strbvs	r6, [lr, -ip, ror #30]!
  8c:	736e7520 	cmnvc	lr, #32, 10	; 0x8000000
  90:	656e6769 	strbvs	r6, [lr, #-1897]!	; 0x769
  94:	6e692064 	cdpvs	0, 6, cr2, cr9, cr4, {3}
  98:	616d0074 	smcvs	53252	; 0xd004
  9c:	Address 0x0000009c is out of bounds.


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
  10:	00000018 	andeq	r0, r0, r8, lsl r0
	...
  1c:	000000c0 	andeq	r0, r0, r0, asr #1
  20:	87040e41 	strhi	r0, [r4, -r1, asr #28]
  24:	100e4101 	andne	r4, lr, r1, lsl #2
  28:	00070d41 	andeq	r0, r7, r1, asr #26
