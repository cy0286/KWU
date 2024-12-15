module BUS(clk, reset_n, M_req, M_wr, M_addr, M_dout, S0_dout, S1_dout, M_grant, S0_sel, S1_sel, S_wr, S_addr, M_din, S_din); //Bus module
	input clk, reset_n, M_req, M_wr;
	input [7:0] M_addr;
	input [31:0] M_dout, S0_dout, S1_dout;
	output M_grant, S_wr;
	output S0_sel, S1_sel;
	output [7:0] S_addr;
	output [31:0] M_din, S_din;
	
	reg [1:0] Sel;
	
	//communication with Slaves
	assign S_wr = M_wr;
	assign S_addr = M_addr;
	assign S_din = M_dout;
	
	
	always@(posedge clk or negedge reset_n)
	begin
		if (reset_n == 0) 
			Sel = 2'b00;
		else if(reset_n == 1) 
		begin
			Sel[1] <= S0_sel;
			Sel[0] <= S1_sel;
		end
		else 
			Sel = 2'bxx; //default
	end
	
	//connect modules
	bus_arbit U0_bus_arbit(clk, reset_n, M_req, M_grant);
	bus_addr	 U1_bus_addr(S_addr, S0_sel, S1_sel);
	mx3_32bit U5_mx3_32bit(32'h00, S0_dout, S1_dout, Sel, M_din);
	
endmodule 