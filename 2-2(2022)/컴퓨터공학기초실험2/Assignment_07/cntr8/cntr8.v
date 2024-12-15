module cntr8(clk, reset_n, inc, load, d_in, d_out, o_state); //8-bit loadable up/down counter
	input 		 clk, reset_n, inc, load; 
	input  [7:0] d_in;
	output [7:0] d_out; 
	output [2:0] o_state;
	
	wire 	 [2:0] next_state; 
	wire 	 [2:0] state;
	
	assign o_state = state;
	
	//instance _register3_r, ns_logic, os_logic
	_register3_r U0_reg3r (clk, reset_n, next_state, state);		
	ns_logic U1_ns_logic  (load, inc, o_state, next_state);								
	os_logic U2_os_logic  (state, d_in, d_out); 
endmodule 