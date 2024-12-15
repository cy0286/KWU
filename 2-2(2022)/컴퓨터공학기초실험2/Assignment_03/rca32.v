module rca32(a,b,ci,s,co); // 32-bits RCA module
	input [31:0] a,b;
	input ci;
	output [31:0] s;
	output co;
	wire c1,c2,c3,c4,c5,c6,c7;
	
	// load 4-input RCA module
	rca4 U0_rca4(a[3:0], b[3:0], ci, s[3:0], c1);
	rca4 U1_rca4(a[7:4], b[7:4], c1, s[7:4], c2);
	rca4 U2_rca4(a[11:8], b[11:8], c2, s[11:8], c3);
	rca4 U3_rca4(a[15:12], b[15:12], c3, s[15:12], c4);
	rca4 U4_rca4(a[19:16], b[19:16], c4, s[19:16], c5);
	rca4 U5_rca4(a[23:20], b[23:20], c5, s[23:20], c6);
	rca4 U6_rca4(a[27:24], b[27:24], c6, s[27:24], c7);
	rca4 U7_rca4(a[31:28], b[31:28], c7, s[31:28], co);
endmodule 