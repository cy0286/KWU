module _register32 (clk, d, q); //32-bits register module
	input					clk;
	input		[31:0]	d;
	output	[31:0]	q;
	
	//struct 32-bits register module
	_register8	U0_register8	(clk, d[7:0], q[7:0]);
	_register8	U1_register8	(clk, d[15:8], q[15:8]);
	_register8	U2_register8	(clk, d[23:16], q[23:16]);
	_register8	U3_register8	(clk, d[31:24], q[31:24]);
endmodule 