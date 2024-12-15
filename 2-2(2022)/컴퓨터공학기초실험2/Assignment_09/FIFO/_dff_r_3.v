module _dff_r_3(clk, reset_n, d, q); //3 input d flip flop with reset 
	input clk, reset_n;
	input [2:0]d; 
	output reg [2:0]q;

	always@(posedge clk) 
	begin 
		if(reset_n == 0) 
			q <= 3'b0; 
		else 
			q <= d; 
	end 
endmodule 