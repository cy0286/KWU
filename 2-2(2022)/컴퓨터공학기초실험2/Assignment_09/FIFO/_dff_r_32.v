module _dff_r_32(clk, reset_n, d, q); //32 input d flip flop with reset 
	input clk, reset_n;
	input [31:0]d; 
	output reg [31:0]q;

	always@(posedge clk) 
	begin 
		if(reset_n == 0) 
			q <= 32'b0; 
		else 
			q <= d; 
	end 
endmodule 