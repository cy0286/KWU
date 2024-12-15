module rca4(a, b, ci, s, co);  // 4-bits RCA module
	input [3:0] a,b;
	input ci;
	output [3:0] s;
	output co;
	wire [2:0] c;
	
	// load full adder module
	fa U0_fa(a[0], b[0], ci, s[0], c[0]);
	fa U1_fa(a[1], b[1], c[0], s[1], c[1]);
	fa U2_fa(a[2], b[2], c[1], s[2], c[2]);
	fa U3_fa(a[3], b[3], c[2], s[3], co);
endmodule 