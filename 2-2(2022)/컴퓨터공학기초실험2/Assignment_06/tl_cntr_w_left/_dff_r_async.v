module _dff_r_async(clk, reset_n, d, q); //d flip-flop with reset module
	input clk, reset_n, d;
	output q;
	reg q;

always@(posedge clk or negedge reset_n) begin//operates at posedge clk or negedge reset_n
	
	if(reset_n==0) q <= 1'b0; //reset
	else q <= d; //output is input value
	end
endmodule 