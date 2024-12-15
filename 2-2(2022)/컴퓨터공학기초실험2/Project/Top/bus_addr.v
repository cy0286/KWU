module bus_addr(S_addr, S0_sel, S1_sel); //bus Address decoder module
	input [7:0] S_addr;
	output reg S0_sel, S1_sel;
	
	wire [2:0] upper_3bit;
	
	assign upper_3bit = S_addr[7:5]; //3bit upper of s_address
	
	always@(upper_3bit, S_addr)
	begin
		if(upper_3bit == 3'b000)
		begin
			S0_sel <= 1'b1;
			S1_sel <= 1'b0;
		end
		
		else if(upper_3bit == 3'b001)
		begin	
			S0_sel <= 1'b0;
			S1_sel <= 1'b1;
		end
	
		else
		begin
			S0_sel <= 1'b0;
			S1_sel <= 1'b0;
		end
	end
endmodule