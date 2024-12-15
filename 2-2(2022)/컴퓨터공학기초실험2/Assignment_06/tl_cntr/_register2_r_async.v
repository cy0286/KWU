module _register2_r_async(clk, reset_n, d, q); //2-bits register module
	input  clk, reset_n;
	input  [1:0]d;
	output [1:0]q;
	
	//struct 2-bits register module
	_dff_r_async U0_dff_r_async(clk, reset_n, d[0], q[0]);
	_dff_r_async U1_dff_r_async(clk, reset_n, d[1], q[1]); 
endmodule 