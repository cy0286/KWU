module bus_arbit(m0_req, m1_req, reset_n, clk, m0_grant, m1_grant); //bus Arbiter
	input m0_req, m1_req, reset_n, clk;
	output reg m0_grant, m1_grant;
	
	reg state, next_state;
	
	//binary encoding
	parameter M0_Grant = 1'b0;
	parameter M1_Grant = 1'b1;
	
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n == 0) state <= M0_Grant;
		else if (reset_n == 1) state <= next_state;
		else state <= 1'bx; //default
	end
	
	always@(m0_req, m1_req, m0_grant, m1_grant, state) //determine next state
	begin
		case(state)
		M0_Grant:
		begin
			m0_grant <= 1'b1; m1_grant <= 1'b0;
			if(m0_req == 0 && m1_req == 1)
				next_state <= M1_Grant; 
			else if((m0_req == 0 && m1_req == 0) || (m0_req ==1))
				next_state <= M0_Grant; //keep current state
			else
				next_state <= 1'bx; //default
		end
		
		M1_Grant:
		begin
			m0_grant <= 1'b0; m1_grant <=1'b1;
			if(m1_req == 0)
				next_state <= M0_Grant;
			else if(m1_req == 1)
				next_state <= M1_Grant; //keep current state
			else
			next_state <= 1'bx; //default
		end
		endcase
	end
endmodule 