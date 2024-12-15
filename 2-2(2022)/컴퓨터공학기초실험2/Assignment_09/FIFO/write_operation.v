module write_operation(Addr,we,to_reg); //write operation
	input			 we;
	input  [2:0] Addr;
	output [7:0] to_reg;
	
	wire	 [7:0] w_a;
	
	//struct write operation
	_3_to_8_decoder	U0_3_to_8_decoder(Addr, w_a);
	_and2 				U1_and(we, w_a[0], to_reg[0]);
	_and2 				U2_and(we, w_a[1], to_reg[1]);
	_and2 				U3_and(we, w_a[2], to_reg[2]);
	_and2 				U4_and(we, w_a[3], to_reg[3]);
	_and2 				U5_and(we, w_a[4], to_reg[4]);
	_and2 				U6_and(we, w_a[5], to_reg[5]);
	_and2 				U7_and(we, w_a[6], to_reg[6]);
	_and2 				U8_and(we, w_a[7], to_reg[7]);
endmodule 