module _dff_r_4(clk, reset_n, d, q); //4 input d flip flop with reset 
	input clk, reset_n;
	input [3:0]d; 
	output reg [3:0]q;

	always@(posedge clk) 
	begin 
		if(reset_n == 0) 
			q <= 4'b0; 
		else 
			q <= d; 
	end 
endmodule 