module _dff_r(clk, reset_n, d, q); //d flip-flop with reset
	input 		clk, reset_n, d;
	output reg  q;
	
	always@(posedge clk or negedge reset_n) //operates at posedge clk or negedge reset_n
	begin
		if(reset_n==0) q <= 1'b0; //reset
		else 				q <= d;
	end
endmodule 