module _dff(clk, d, q, q_bar); //d flip-flop module
	input 	clk, d;
	output	q, q_bar;
	wire		clk_bar, w_q;
	
	//struct d flip-flop
	_inv		U0_inv		(clk, clk_bar);
	_dlatch	U1_dlatch	(clk_bar, d, w_q);
	_dlatch	U2_dlatch	(clk, w_q, q, q_bar);
endmodule 