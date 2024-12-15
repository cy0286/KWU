	AREA term_project, CODE, READONLY
		ENTRY
		
Main
	LDR r0, =Sampled_Data ; save the data(480) using Sampled_Data label(32bit, double word).
	LDR r1, Save_Result_Address
	LDR r2, =h ; filter
	ADD r13, r0, #1920
	
loop
	LDR r3, [r0], #4 ; sampled data + 1
	LDR r4, [r2], #4 ; filter + 1
	BL multiplication
	LDR r3, [r0], #4 ; sampled data + 1
	LDR r4, [r2], #4 ; filter + 1
	BL multiplication
	LDR r3, [r0], #4 ; sampled data + 1
	LDR r4, [r2], #4 ; filter + 1
	BL multiplication
	LDR r3, [r0], #4 ; sampled data + 1
	LDR r4, [r2], #4 ; filter + 1
	BL multiplication
	LDR r3, [r0], #4 ; sampled data + 1
	LDR r4, [r2], #4 ; filter + 1
	BL multiplication
	LDR r3, [r0], #4 ; sampled data + 1
	LDR r4, [r2], #4 ; filter + 1
	
	CMP r0,r13
	BEQ stop
	BL multiplication
	SUB r0,r0,#20
	SUB r2,r2,#24
	BL Result
	B loop
	
multiplication
	; store sign bit, exponent, mantissa
	MOV r5, r3, LSR #31 ; sign bit
	MOV r6, r3, LSR #23 ; exponent
	MOV r6, r6, LSL #24
	MOV r6, r6, LSR #24
	MOV r7, r3, LSL #9 ; mantissa
	MOV r7, r7, LSR #9 ; +1
	ADD r7, r7, #0x00800000 ; +1
	
	; store sign bit, exponent, mantissa
	MOV r8, r4, LSR #31 ; sign bit
	MOV r9, r4, LSR #23 ; exponent
	MOV r9, r9, LSL #24
	MOV r9, r9, LSR #24
	MOV r10, r4, LSL #9 ; mantissa
	MOV r10, r10, LSR #9 ; +1
	ADD r10, r10, #0x00800000 ; +1
	
	CMP r5, r8 ; compare signbit 
	MOVEQ r5, #0x00000000
	MOVNE r5, #0x80000000
	
	ADD r6, r6, r9 ; exponent add
	SUB r6, r6, #127
	
	UMULL r3, r4, r7, r10 ; mantissa multiplication
	CMP r4, #0x00008000
	
	MOVGE r4, r4, LSL #8
	ADDGE r6, r6, #1
	
	MOVGE r3, r3, LSR #24
	
	MOVLT r4, r4,LSL #9
	MOVLT r3, r3,LSR #23
	
	ADD r4, r4, r3
	SUB r4, r4, #0x00800000
	
	MOV r6,r6,LSL #23
	ADD r4, r4, r6
	ADD r4, r4, r5
	
addition
	CMP r12,#0
	MOVEQ r12,r4
	MOVEQ pc,lr
	;r4+r12
	; store sign bit, exponent, mantissa
	MOV r5, r4, LSR #31 ; sign bit
	MOV r6, r4, LSR #23 ; exponent
	MOV r6, r6, LSL #24
	MOV r6, r6, LSR #1
	MOV r7, r4, LSL #9 ;mantissa
	MOV r7, r7, LSR #9
	ADD r7, r7, #0x00800000 ; add 1 to mantissa
	
	;store sign bit, exponenet, mantissa
	MOV r8, r12, LSR #31 ; sign bit
	MOV r9, r12, LSR #23 ; exponent
	MOV r9, r9, LSL #24
	MOV r9, r9, LSR #1
	MOV r10, r12, LSL #9 ;mantissa
	MOV r10, r10, LSR #9
	ADD r10, r10 , #0x00800000 ; add 1 to mantissa
	
	CMP r6, r9 ;compare exponent
	SUBGT r11, r6, r9
	SUBLT r11, r9, r6
	MOV r11, r11, LSR #23
	MOVLT r7, r7, LSR r11
	MOVGT r10, r10, LSR r11

	MOVLT r6, r9
	
	CMP r5, r8 ;compare signbit
	BEQ equal
	BNE notequal
	
equal ;sign same
	ADD r3, r7, r10 
	B normalize
	
notequal ;sign differnt
	CMP r7, r10
	BEQ endline ;r7=r10
	
	SUBGT r3, r7, r10 
	SUBLT r3, r10, r7
	MOVLT r5, r8

normalize ;normalize mantissa
	CMP r3, #0x01000000
	MOVGE r3, r3, LSR #1
	ADDGE r6, r6, #0x00800000
	SUBGE r3,r3,#0x00800000
	BGE finish
	
	CMP r3, #0x01000000
	MOVLT r3, r3, LSL #1
	SUBLT r6, r6, #0x00800000
	BLT normalize

finish

	MOV r5, r5, LSL #31
	ADD r3, r3, r5 ;add sign bit 
	ADD r3, r3, r6 ;add exponent 
	MOV r12, r3 ;store into r12 
	MOV pc, lr ;mark end of file

endline
	MOV r12, #0
	MOV pc, lr ;mark end of file

Result ; Store less that -4.7 of the convolution results(32bit, double word) and their indices(word).
	STR r12, [r1], #4
	MOV r12, #0
	MOV pc,lr
	
stop
	MOV pc, #0
	
Save_Result_Address DCD &F0000000

;6 filter
h DCD 0xBE589375, 0xBF4D5CFB, 0xBFA39581, 0xBEDCAC08, 0x3FDC28F6, 0x3FF9999A
	
Sampled_Data
	DCD 0xBF20C60C, 0xBB08B8D8, 0x3F1A6D0B, 0x3F96A4D0
	DCD 0x3FDAB3A4, 0x400C165A, 0x4026FE23, 0x403D9B3C
	DCD 0x404F8DD9, 0x405C8E13, 0x40646D24, 0x40671628
	DCD 0x40648E4D, 0x405CF47D, 0x40508084, 0x403F81B4
	DCD 0x402A5D12, 0x40118B12, 0x3FEB29FA, 0x3FAE23F3
	DCD 0x3F5A8F67, 0x3EA79DBF, 0xBE551889, 0xBF3DFB17
	DCD 0xBFA1D441, 0xBFE1E0C5, 0xC00EF836, 0xC02A7523
	DCD 0xC042EA38, 0xC057EC65, 0xC0692464, 0xC0765036
	DCD 0xC07F4435, 0xC081F5CD, 0xC082244C, 0xC08039FB
	DCD 0xC0789C34, 0xC06D0440, 0xC05E01C1, 0xC04BFB0F
	DCD 0xC03764C9, 0xC020BF3A, 0xC008937D, 0xBFDEE10D
	DCD 0xBFABD023, 0xBF722E4C, 0xBF0FA4CA, 0xBE488E71
	DCD 0x3E116448, 0x3EE40582, 0x3F35417F, 0x3F6CBB89
	DCD 0x3F8BADC0, 0x3F9A2A8D, 0x3FA19423, 0x3FA1D150
	DCD 0x3F9AEFAF, 0x3F8D22C6, 0x3F7184D6, 0x3F3C90D8
	DCD 0x3EF93646, 0x3E4C3067, 0xBDF42987, 0xBEECB7D0
	DCD 0xBF529EFD, 0xBF98B18C, 0xBFC85A59, 0xBFF75116
	DCD 0xC012516B, 0xC027B3A2, 0xC03B6288, 0xC04CFAF6
	DCD 0xC05C2514, 0xC06895DA, 0xC0721050, 0xC078667C
	DCD 0xC07B7A01, 0xC07B3C6F, 0xC077AF3F, 0xC070E381
	DCD 0xC066F943, 0xC05A1EAD, 0xC04A8EE1, 0xC03890A4
	DCD 0xC02474D8, 0xC00E94CA, 0xBFEEA0DC, 0xBFBE18FD
	DCD 0xBF8C612E, 0xBF349547, 0xBEA2934C, 0x3D78C33E
	DCD 0x3ED8D292, 0x3F43E21F, 0x3F8A542B, 0x3FAEC7C2
	DCD 0x3FCEC8AA, 0x3FE9E869, 0x3FFFCE74, 0x40081C7F
	DCD 0x400D7EAF, 0x40100408, 0x400FAE28, 0x400C89AC
	DCD 0x4006ADA7, 0x3FFC75E8, 0x3FE6B6C8, 0x3FCC81A2
	DCD 0x3FAE4843, 0x3F8C8865, 0x3F4F92F3, 0x3F0134CA
	DCD 0x3E3C79B9, 0xBE16089E, 0xBEF6FB0B, 0xBF51A6F3
	DCD 0xBF936C32, 0xBFBCFB1B, 0xBFE4F945, 0xC0057417
	DCD 0xC0172993, 0xC027683B, 0xC0360134, 0xC042CC12
	DCD 0xC04DA727, 0xC05677C8, 0xC05D2A75, 0xC061B2F1
	DCD 0xC0640C42, 0xC06438A7, 0xC0624173, 0xC05E36DE
	DCD 0xC0582FC3, 0xC0504950, 0xC046A6A5, 0xC03B7066
	DCD 0xC02ED43E, 0xC0210454, 0xC01236B8, 0xC002A4B8
	DCD 0xBFE5146A, 0xBFC449C8, 0xBFA36715, 0xBF82EA5D
	DCD 0xBF46A106, 0xBF0A2710, 0xBEA2A344, 0xBDE7F688
	DCD 0x3D901BA9, 0x3E6BEB09, 0x3EBA86BF, 0x3EF0A699
	DCD 0x3F0BBD04, 0x3F1731E2, 0x3F1A8439, 0x3F15A8E3
	DCD 0x3F08B868, 0x3EE7DF14, 0x3EAF5E85, 0x3E51F08C
	DCD 0x00000000, 0x3EAFBCA1, 0x3F2E46B1, 0x3F80E603
	DCD 0x3FA8894F, 0x3FCD6C2C, 0x3FEEFE0A, 0x40066112
	DCD 0x40132922, 0x401DB07A, 0x4025DD7C, 0x402BA41A
	DCD 0x402F05DD, 0x403011A1, 0x402EE2F0, 0x402BA10B
	DCD 0x40267DAA, 0x401FB377, 0x4017844E, 0x400E375A
	DCD 0x4004170D, 0x3FF2DE18, 0x3FDD142E, 0x3FC7600B
	DCD 0x3FB247B5, 0x3F9E4408, 0x3F8BBDA4, 0x3F7614AA
	DCD 0x3F58D639, 0x3F40159B, 0x3F2BFAB5, 0x3F1C7FA3
	DCD 0x3F117205, 0x3F0A759D, 0x3F07082A, 0x3F06865F
	DCD 0x3F0831D4, 0x3F0B37B8, 0x3F0EB82C, 0x3F11CDF4
	DCD 0x3F139654, 0x3F1338E0, 0x3F0FEEFB, 0x3F090AD8
	DCD 0x3EFBFB7F, 0x3EDCBAE2, 0x3EB3D0EC, 0x3E81128B
	DCD 0x3E09606A, 0xBAC90C27, 0xBE1CE2AA, 0xBEA30A50
	DCD 0xBEFD0636, 0xBF2D489B, 0xBF5CCE81, 0xBF85FB8F
	DCD 0xBF9CCAD6, 0xBFB23B25, 0xBFC5B326, 0xBFD69E4F
	DCD 0xBFE47104, 0xBFEEAC86, 0xBFF4E29E, 0xBFF6B8D7
	DCD 0xBFF3EB47, 0xBFEC4EC1, 0xBFDFD265, 0xBFCE8087
	DCD 0xBFB87EDD, 0xBF9E0DFF, 0xBF7F1053, 0xBF3ABEBB
	DCD 0xBEE06B6D, 0xBE02A083, 0x3E4A6799, 0x3F082AD6
	DCD 0x3F5E982A, 0x3F9A358F, 0x3FC418C8, 0x3FEC4359
	DCD 0x400906DA, 0x401A6F86, 0x402A1866, 0x4037C8CD
	DCD 0x404353E7, 0x404C999E, 0x4053872E, 0x4058175C
	DCD 0x405A5253, 0x405A4D2A, 0x40582910, 0x40541230
	DCD 0x404E3E43, 0x4046EAF5, 0x403E5C05, 0x4034D958
	DCD 0x402AACE4, 0x4020209C, 0x40157C69, 0x400B042E
	DCD 0x4000F5FA, 0x3FEF10D0, 0x3FDDD270, 0x3FCE786F
	DCD 0x3FC134D7, 0x3FB62333, 0x3FAD483D, 0x3FA69241
	DCD 0x3FA1DA2C, 0x3F9EE537, 0x3F9D6730, 0x3F9D0539
	DCD 0x3F9D5906, 0x3F9DF46A, 0x3F9E651A, 0x3F9E38A0
	DCD 0x3F9D0045, 0x3F9A54E4, 0x3F95DA8A, 0x3F8F43C2
	DCD 0x3F865478, 0x3F75C8BA, 0x3F59C16B, 0x3F389B1D
	DCD 0x3F128C84, 0x3ECFF54C, 0x3E65DCC0, 0x3CF7AED7
	DCD 0xBE31470E, 0xBEC36B5E, 0xBF1753CE, 0xBF4BFF24
	DCD 0xBF7E8008, 0xBF96CE31, 0xBFAC100D, 0xBFBE72B7
	DCD 0xBFCD6E90, 0xBFD88B04, 0xBFDF61FD, 0xBFE1A2E6
	DCD 0xBFDF1522, 0xBFD799E7, 0xBFCB2D74, 0xBFB9E792
	DCD 0xBFA3FB5E, 0xBF89B665, 0xBF56FE0B, 0xBF13A46D
	DCD 0xBE9502B6, 0x3C4A3B0D, 0x3EA7FDCC, 0x3F2693FA
	DCD 0x3F79731D, 0x3FA593D3, 0x3FCD230F, 0x3FF2BA64
	DCD 0x400ADCEC, 0x401AC902, 0x4028E3A6, 0x4034FA49
	DCD 0x40400000, 0x40756413, 0x4093E595, 0x40AA38E3
	DCD 0x40BC8125, 0x40C9DFCC, 0x40D1D121, 0x40D432EE
	DCD 0x40D142BF, 0x40C99413, 0x40BDFF91, 0x40AF8CF9
	DCD 0x409F5A02, 0x408E80A2, 0x407BFE46, 0x405D48B6
	DCD 0x4042036C, 0x402AC8A9, 0x4017AB51, 0x40084682
	DCD 0x3FF7B2E7, 0x3FE2D8BA, 0x3FCFF44C, 0x3FBD3489
	DCD 0x3FA94C48, 0x3F93ABF4, 0x3F794725, 0x3F4AD260
	DCD 0x3F200558, 0x3EFC5311, 0x3ED670A6, 0x3EDA5EF9
	DCD 0x3F09597D, 0x3F439CCF, 0x3F8EF273, 0x3FCBDAB6
	DCD 0x400B7D0D, 0x4036BC5C, 0x4065ABD2, 0x408AEC86
	DCD 0x40A245A9, 0x40B77C23, 0x40C93E08, 0x40D667E9
	DCD 0x40DE1CC0, 0x40DFD84C, 0x40DB7A2E, 0x40D148C8
	DCD 0x40C1EB7D, 0x40AE5CFD, 0x4097D6C0, 0x407F6F5C
	DCD 0x404ED067, 0x40207CC4, 0x3FED923F, 0x3FA712F0
	DCD 0x3F5FD3E4, 0x3F12645D, 0x3ECAE575, 0x3EAC9259
	DCD 0x3EC0BA7C, 0x3EFBE3F3, 0x3F28CE12, 0x3F5AF2FF
	DCD 0x3F87A11B, 0x3FA0FFDB, 0x3FB8928B, 0x3FCE3E99
	DCD 0x3FE2C334, 0x3FF78FC1, 0x40074235, 0x4014D1ED
	DCD 0x40255F6E, 0x40399198, 0x4051AB54, 0x406D7343
	DCD 0x40861437, 0x409642D8, 0x40A669F4, 0x40B584D6
	DCD 0x40C27ACC, 0x40CC37C3, 0x40D1C5E8, 0x40D265E2
	DCD 0x40CDA347, 0x40C3632C, 0x40B3EB4F, 0x409FE10D
	DCD 0x40883FFC, 0x405C91E4, 0x4026D5BB, 0x3FE49DDE
	DCD 0x3F83D8EF, 0x3EC283C4, 0xBE0615F4, 0xBEF552FE
	DCD 0xBF2723D3, 0xBF270189, 0xBEFA7DB8, 0xBE3D91CA
	DCD 0x3E6C3DC5, 0x3F39649B, 0x3FA13B7A, 0x3FE6C191
	DCD 0x4014B78F, 0x403321F0, 0x404DA230, 0x4063C630
	DCD 0x4075A19B, 0x4081DD15, 0x40877440, 0x408C1895
	DCD 0x40904D24, 0x40948137, 0x4098FEA7, 0x409DDD0D
	DCD 0x40A2FB3A, 0x40A7FFB6, 0x40AC605E, 0x40AF705A
	DCD 0x40B07312, 0x40AEB232, 0x40A99476, 0x40A0B2DD
	DCD 0x4093E9ED, 0x40836536, 0x405F472E, 0x4032E759
	DCD 0x4003D0D4, 0x3FA91B1B, 0x3F1F6FD3, 0x3BF1A611
	DCD 0xBEF8C529, 0xBF530DDA, 0xBF7C3518, 0xBF74D9E3
	DCD 0xBF3D2BFF, 0xBEB111CC, 0x3E4B21A7, 0x3F5C1925
	DCD 0x3FCC8307, 0x401792FC, 0x40482A77, 0x40756F2C
	DCD 0x408E9802, 0x409EE484, 0x40AB1D6B, 0x40B31930
	DCD 0x40B70051, 0x40B741EA, 0x40B48249, 0x40AF857C
	DCD 0x40A91818, 0x40A1F8A3, 0x409AC3EB, 0x4093E648
	DCD 0x408D932F, 0x4087C3DF, 0x40823D2B, 0x40793743
	
	END