module ns_logic(load,inc,state,next_state); //next state logic

	//encode states
	parameter IDLE_STATE = 3'b000;
	parameter LOAD_STATE = 3'b001;
	parameter INC_STATE  = 3'b010;
	parameter INC2_STATE = 3'b011;
	parameter DEC_STATE  = 3'b100;
	parameter DEC2_STATE = 3'b101;
	
	input 		 load,inc; 
	input  [2:0] state;
	output [2:0] next_state;
	
	reg  	 [2:0] next_state;
	
	//case 
	always@(load,inc,state) //operates when load, inc, state changes
		begin 
			case(state)
				IDLE_STATE:
				begin
					if(load==1'b1) next_state<=LOAD_STATE;
					else if(inc==1'b1) next_state<=INC_STATE;
					else if(inc==1'b0) next_state<=DEC_STATE;
					else next_state<=3'bxxx;
				end
				LOAD_STATE:
				begin
					if(load==1'b1) next_state<=LOAD_STATE;
					else if(inc==1'b1) next_state<=INC_STATE;
					else if(inc==1'b0) next_state<=DEC_STATE;
					else next_state<=3'bxxx;
				end			
				INC_STATE:
				begin
					if(load==1'b1) next_state<=LOAD_STATE;
					else if(inc==1'b1) next_state<=INC2_STATE;
					else if(inc==1'b0) next_state<=DEC_STATE;
					else next_state<=3'bxxx;
				end
				INC2_STATE:
				begin
					if(load==1'b1) next_state<=LOAD_STATE;
					else if(inc==1'b1) next_state<=INC_STATE;
					else if(inc==1'b0) next_state<=DEC_STATE;
					else next_state<=3'bxxx;
				end			
				DEC_STATE:
					begin
					if(load==1'b1) next_state<=LOAD_STATE;
					else if(inc==1'b1) next_state<=INC_STATE;
					else if(inc==1'b0) next_state<=DEC2_STATE;
					else next_state<=3'bxxx;
				end			
				DEC2_STATE:
				begin
					if(load==1'b1) next_state<=LOAD_STATE;
					else if(inc==1'b1) next_state<=INC_STATE;
					else if(inc==1'b0) next_state<=DEC_STATE;
					else next_state<=3'bxxx;
				end			
			endcase
		end
endmodule
