module Register_file(clk, reset_n, wAddr, wData, we, rAddr, rData); //Register file
	input  clk, reset_n, we;
	input  [2:0]  wAddr, rAddr;
	input  [31:0] wData;
	output [31:0] rData;
	
	wire   [7:0]  to_reg;
	wire   [31:0] from_reg[7:0];
	
	//struct Register file
	write_operation	 U0_write_operation(wAddr, we, to_reg);	
	register32_8 		 U1_register32_8(clk, reset_n, to_reg, wData, from_reg[0], from_reg[1], from_reg[2], from_reg[3], from_reg[4], from_reg[5], from_reg[6], from_reg[7]);
	read_operation 	 U2_read_operation(rAddr, rData, from_reg[0], from_reg[1], from_reg[2], from_reg[3], from_reg[4], from_reg[5], from_reg[6], from_reg[7]);
endmodule
