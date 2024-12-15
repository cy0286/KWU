module _register8_r(clk, reset_n, d, q); //8-bits register
	input  		 clk, reset_n;
	input  [7:0] d;
	output [7:0] q;
	
	//instance _dff_r & struct 8-bits register
	_dff_r U0_dff_r(clk, reset_n, d[0], q[0]);
	_dff_r U1_dff_r(clk, reset_n, d[1], q[1]);
	_dff_r U2_dff_r(clk, reset_n, d[2], q[2]);
	_dff_r U3_dff_r(clk, reset_n, d[3], q[3]);
	_dff_r U4_dff_r(clk, reset_n, d[4], q[4]);
	_dff_r U5_dff_r(clk, reset_n, d[5], q[5]);
	_dff_r U6_dff_r(clk, reset_n, d[6], q[6]);
	_dff_r U7_dff_r(clk, reset_n, d[7], q[7]);
endmodule 