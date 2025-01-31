module _register3_r(clk, reset_n, d, q); //3-bits register module
	input  clk, reset_n;
	input  [2:0]d;
	output [2:0]q;

	//struct 3-bits register module
	_dff_r_async U0_dff_r_async(clk, reset_n, d[0], q[0]);
	_dff_r_async U1_dff_r_async(clk, reset_n, d[1], q[1]); 
	_dff_r_async U2_dff_r_async(clk, reset_n, d[2], q[2]); 
 endmodule 