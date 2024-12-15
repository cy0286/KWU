module fifo_out(state, data_count, full, empty, wr_ack, wr_err, rd_ack, rd_err); //Output logic
	input [2:0] state;
	input [3:0] data_count;
	output reg full, empty, wr_ack, wr_err, rd_ack, rd_err;
	
	//set state
	parameter INIT = 3'b000;
	parameter WRITE = 3'b001;
	parameter READ = 3'b010;
	parameter WR_ERROR = 3'b011;
	parameter RD_ERROR = 3'b100;
	parameter NO_OP = 3'b111;
	
	always@(state, data_count)
	begin
		case(state)
			INIT:
			begin
				full = 1'b0; 
				empty = 1'b1; 
				wr_ack = 1'b0; 
				wr_err = 1'b0; 
				rd_ack = 1'b0; 
				rd_err = 1'b0;
			end
			
			WRITE:
			begin
				if (data_count == 4'b1000)
				begin
					full = 1'b1; 
					empty = 1'b0; 
					wr_ack = 1'b0; 
					wr_err = 1'b1; 
					rd_ack = 1'b0; 
					rd_err = 1'b0;
				end
				
				else
				begin
					full = 1'b0; 
					empty = 1'b0; 
					wr_ack = 1'b1; 
					wr_err = 1'b0; 
					rd_ack = 1'b0; 
					rd_err = 1'b0;
				end
			end
			
			READ:
			begin
				if	(data_count == 4'b0000)
				begin
					full = 1'b0; 
					empty = 1'b1; 
					wr_ack = 1'b0; 
					wr_err = 1'b0; 
					rd_ack = 1'b0; 
					rd_err = 1'b1;
				end
				
				else
				begin
					full = 1'b0; 
					empty = 1'b0; 
					wr_ack = 1'b0; 
					wr_err = 1'b0; 
					rd_ack = 1'b1; 
					rd_err = 1'b0;
				end
			end
			
			WR_ERROR:
			begin
				full = 1'b1; 
				empty = 1'b0; 
				wr_ack = 1'b0; 
				wr_err = 1'b1; 
				rd_ack = 1'b0; 
				rd_err = 1'b0;
			end
			
			RD_ERROR:
			begin
				full = 1'b0; 
				empty = 1'b1; 
				wr_ack = 1'b0;
				wr_err = 1'b0; 
				rd_ack = 1'b0; 
				rd_err = 1'b1;
			end
			
			NO_OP:
			begin
				if (data_count == 4'b0000)
				begin
					full = 1'b0; 
					empty = 1'b1; 
					wr_ack = 1'b0; 
					wr_err = 1'b0; 
					rd_ack = 1'b0; 
					rd_err = 1'b0;
				end
				
				else if (data_count == 4'b1000)
				begin
					full = 1'b1; 
					empty = 1'b0; 
					wr_ack = 1'b0;
					wr_err = 1'b0;
					rd_ack = 1'b0; 
					rd_err = 1'b0;
				end
				
				else
				begin
					full = 1'b0; 
					empty = 1'b0; 
					wr_ack = 1'b0;
					wr_err = 1'b0; 
					rd_ack = 1'b0; 
					rd_err = 1'b0;
				end
			end
			
			default:
			begin
				full = 1'bx; 
				empty = 1'bx; 
				wr_ack = 1'bx; 
				wr_err = 1'bx; 
				rd_ack = 1'bx; 
				rd_err = 1'bx;
			end		
		endcase
	end
endmodule 