module _register3_r(clk, reset_n, d, q);	//3-bit register
	input 		 clk, reset_n;
	input  [2:0] d;
	output [2:0] q;

	//instance _dff_r & struct 3-bit register
	_dff_r U0_drr_r(clk, reset_n, d[0], q[0]);
	_dff_r U1_drr_r(clk, reset_n, d[1], q[1]);
	_dff_r U2_drr_r(clk, reset_n, d[2], q[2]);
endmodule 