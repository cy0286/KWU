module bus_arbit(clk, reset_n, M_req, M_grant); //bus Arbiter module
	input clk, reset_n, M_req;
	output reg M_grant;
	
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n == 0) M_grant = 1'b0;
		else if (reset_n == 1) M_grant <= M_req;
		else M_grant <= 1'bx; //default
	end
endmodule 