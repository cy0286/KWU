module _dff_rs_sync_async(clk,set_n,reset_n,d,q_sync,q_async);//synchronous and asynchronous set/resettable d flip-flop modules
	input  clk,set_n,reset_n,d;
	output q_sync,q_async;
	
	//load _dff_rs modules
	_dff_rs_sync	U0_dff_rs_sync(clk, set_n, reset_n, d, q_sync);
	_dff_rs_async	U1_dff_rs_async(clk, set_n, reset_n, d, q_async);
endmodule 