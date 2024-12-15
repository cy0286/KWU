module os_logic(state, d_in, d_out); //output state logic

	//encode states
	parameter IDLE_STATE = 3'b000;
	parameter LOAD_STATE = 3'b001;
	parameter INC_STATE  = 3'b010;
	parameter INC2_STATE = 3'b011;
	parameter DEC_STATE  = 3'b100;
	parameter DEC2_STATE = 3'b101;

	input  [2:0] state;
	input  [7:0] d_in;
	output [7:0] d_out;

	reg 	 [7:0] d_out;
	wire 	 [7:0] d_inc;
	wire	 [7:0] d_dec;

	always @ (state) //operates if state changes
	begin
		case(state)
			IDLE_STATE : d_out <= 8'b00000000;
			LOAD_STATE : d_out <= d_in;
			INC_STATE  : d_out <= d_inc;
			INC2_STATE : d_out <= d_inc;
			DEC_STATE  : d_out <= d_dec;
			DEC2_STATE : d_out <= d_dec;
			default 	  : d_out <= 8'bx;
		endcase 
	end
	//instances CLA8(inc, dec)
	cla8 U0_cla8(d_out, 8'b00000001, 1'b0, d_inc, co); 
	cla8 U1_cla8(d_out, 8'b11111111, 1'b0, d_dec, co);
endmodule 