module fifo_ns(wr_en, rd_en, state, data_count, next_state); //fifo Next state
	input wr_en, rd_en;
	input [2:0] state;
	input [3:0] data_count;
	output reg [2:0] next_state;
	
	//set parameter
	parameter INIT = 3'b000;
	parameter WRITE = 3'b001;
	parameter READ = 3'b010;
	parameter WR_ERROR = 3'b011;
	parameter RD_ERROR = 3'b100;
	parameter NO_OP = 3'b111;
	
	always@(wr_en, rd_en, state, data_count)
	begin
		case(state)
				INIT:
				begin
					if(wr_en == 1'b1 && rd_en == 1) next_state = NO_OP;
					else if(wr_en == 1) next_state = WRITE;
					else if(rd_en == 1) next_state = RD_ERROR;
				end
				
				WRITE:
				begin
					if(wr_en == 1 && rd_en == 1) next_state = NO_OP;
					else if(wr_en == 1 && data_count == 4'b1000) next_state = WR_ERROR;
					else if(wr_en == 1) next_state = WRITE;
					else if(rd_en == 1) next_state = READ;

				end
				
				READ:
				begin
					if(wr_en == 1 && rd_en == 1) next_state = NO_OP;
					else if(rd_en == 1 && data_count == 4'b0000) next_state = RD_ERROR;
					else if(wr_en == 1) next_state = WRITE;
					else if(rd_en == 1) next_state = READ;
				end
				
				WR_ERROR:
				begin
					if(wr_en == 1 && rd_en == 1) next_state = NO_OP;		
					else if(rd_en == 1) next_state = READ;
					else if(wr_en == 1) next_state = WR_ERROR;	
				end
				
				RD_ERROR:
				begin
					if(wr_en == 1 && rd_en == 1) next_state = NO_OP;   
					else if(wr_en == 1) next_state = WRITE;
					else if(rd_en == 1) next_state = RD_ERROR;
				end
				
				default: // NO_OP
				begin
					if(wr_en ==1 && data_count != 4'b1000) next_state = WRITE;
					else if(wr_en == 1) next_state = WR_ERROR;
					
					if(rd_en==1 && data_count != 4'b0000) next_state = READ;
					else if(rd_en == 1) next_state = RD_ERROR;
				end
		endcase
	end
endmodule   