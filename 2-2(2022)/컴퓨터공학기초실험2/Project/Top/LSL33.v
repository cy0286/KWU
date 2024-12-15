module LSL33(d_in, shamt, d_out); //33-bits Logic Shift Left
	input  [32:0] d_in;
	input  [1:0] shamt;
	output [32:0] d_out;

	//load mx4
	mx4 U0_mx4(d_out[32], d_in[32], d_in[31], d_in[30], d_in[29], shamt);
	mx4 U1_mx4(d_out[31], d_in[31], d_in[30], d_in[29], d_in[28], shamt);
	mx4 U2_mx4(d_out[30], d_in[30], d_in[29], d_in[28], d_in[27], shamt);
	mx4 U3_mx4(d_out[29], d_in[29], d_in[28], d_in[27], d_in[26], shamt);
	mx4 U4_mx4(d_out[28], d_in[28], d_in[27], d_in[26], d_in[25], shamt);
	mx4 U5_mx4(d_out[27], d_in[27], d_in[26], d_in[25], d_in[24], shamt);
	mx4 U6_mx4(d_out[26], d_in[26], d_in[25], d_in[24], d_in[23], shamt);
	mx4 U7_mx4(d_out[25], d_in[25], d_in[24], d_in[23], d_in[22], shamt);
	mx4 U8_mx4(d_out[24], d_in[24], d_in[23], d_in[22], d_in[21], shamt);
	mx4 U9_mx4(d_out[23], d_in[23], d_in[22], d_in[21], d_in[20], shamt);
	mx4 U10_mx4(d_out[22], d_in[22], d_in[21], d_in[20], d_in[19], shamt);
	mx4 U11_mx4(d_out[21], d_in[21], d_in[20], d_in[19], d_in[18], shamt);
	mx4 U12_mx4(d_out[20], d_in[20], d_in[19], d_in[18], d_in[17], shamt);
	mx4 U13_mx4(d_out[19], d_in[19], d_in[18], d_in[17], d_in[16], shamt);
	mx4 U14_mx4(d_out[18], d_in[18], d_in[17], d_in[16], d_in[15], shamt);
	mx4 U15_mx4(d_out[17], d_in[17], d_in[16], d_in[15], d_in[14], shamt);
	mx4 U16_mx4(d_out[16], d_in[16], d_in[15], d_in[14], d_in[13], shamt);
	mx4 U17_mx4(d_out[15], d_in[15], d_in[14], d_in[13], d_in[12], shamt);
	mx4 U18_mx4(d_out[14], d_in[14], d_in[13], d_in[12], d_in[11], shamt);
	mx4 U19_mx4(d_out[13], d_in[13], d_in[12], d_in[11], d_in[10], shamt);
	mx4 U20_mx4(d_out[12], d_in[12], d_in[11], d_in[10], d_in[9], shamt);
	mx4 U21_mx4(d_out[11], d_in[11], d_in[10], d_in[9], d_in[8], shamt);
	mx4 U22_mx4(d_out[10], d_in[10], d_in[9], d_in[8], d_in[7], shamt);
	mx4 U23_mx4(d_out[9], d_in[9], d_in[8], d_in[7], d_in[6], shamt);
	mx4 U24_mx4(d_out[8], d_in[8], d_in[7], d_in[6], d_in[5], shamt);
	mx4 U25_mx4(d_out[7], d_in[7], d_in[6], d_in[5], d_in[4], shamt);
	mx4 U26_mx4(d_out[6], d_in[6], d_in[5], d_in[4], d_in[3], shamt);
	mx4 U27_mx4(d_out[5], d_in[5], d_in[4], d_in[3], d_in[2], shamt);
	mx4 U28_mx4(d_out[4], d_in[4], d_in[3], d_in[2], d_in[1], shamt);
	mx4 U29_mx4(d_out[3], d_in[3], d_in[2], d_in[1], d_in[0], shamt);
	mx4 U30_mx4(d_out[2], d_in[2], d_in[1], d_in[0], 1'b0, shamt);
	mx4 U31_mx4(d_out[1], d_in[1], d_in[0], 1'b0, 1'b0, shamt);
	mx4 U32_mx4(d_out[0], d_in[0], 1'b0, 1'b0, 1'b0, shamt);
endmodule 