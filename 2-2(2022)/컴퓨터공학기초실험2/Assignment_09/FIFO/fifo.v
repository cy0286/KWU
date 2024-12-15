module fifo(clk, reset_n, rd_en, wr_en, d_in, d_out, data_count, full, empty, wr_ack, wr_err, rd_ack, rd_err); //fifo
	input clk, reset_n, rd_en, wr_en;
	input [31:0] d_in;
	output [31:0] d_out;
	output [3:0] data_count;
	output full, empty, wr_ack, wr_err, rd_ack, rd_err;
	
	wire [2:0] state, head, tail, next_state, next_head, next_tail;
	wire [3:0] next_data_count;
	wire [31:0] mux_, ff_;
	wire we_, re_;
	
	//struct fifo
	fifo_ns			U0_fifo_ns(wr_en, rd_en, state, data_count, next_state);
	fifo_cal_addr	U1_fifo_cal_addr(next_state, head, tail,  data_count, we_, re_, next_head, next_tail, next_data_count);
	fifo_out			U2_fifo_out(state, data_count, full, empty, wr_ack, wr_err, rd_ack, rd_err);
	Register_file	U3_Register_file(clk, reset_n, tail, d_in, we_, head, mux_);
	_dff_r_3			U4_state(clk, reset_n, next_state, state);
	_dff_r_4			U5_data_count(clk, reset_n, next_data_count, data_count);
	_dff_r_3			U6_head(clk, reset_n, next_head, head);
	_dff_r_3			U7_tail(clk, reset_n, next_tail, tail);
	_mx_2				U8_mx_2(mux_, re_, ff_);
	_dff_r_32		U9_dout(clk, reset_n, ff_, d_out);
endmodule 