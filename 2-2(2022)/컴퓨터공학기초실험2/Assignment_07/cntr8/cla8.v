module cla8(a,b,ci,s,co); //8-bits CLA
	input	 [7:0] a,b;
	input 		 ci;
	output [7:0] s;
	output 		 co;
	
	wire 			 c1;
	
	//instance cla4 & struct 8-bits CLA
	cla4 U0_cla4(a[3:0], b[3:0], ci, s[3:0], c1);
	cla4 U1_cla4(a[7:4], b[7:4], c1, s[7:4], co);
endmodule 