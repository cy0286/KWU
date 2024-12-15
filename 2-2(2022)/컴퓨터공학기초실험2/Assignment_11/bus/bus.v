module bus(clk, reset_n, m0_req, m0_address, m0_wr, m0_dout, m0_grant, m1_req, m1_address, m1_wr, m1_dout, m1_grant, m_din, s0_sel, s1_sel, s_address, s_wr, s_din, s0_dout, s1_dout); //bus
   input clk, reset_n, m0_req, m0_wr, m1_req, m1_wr;
   input [7:0] m0_address, m1_address;
   input [31:0] m0_dout, m1_dout, s0_dout, s1_dout;
   output m0_grant, m1_grant, s0_sel, s1_sel, s_wr;
   output [31:0] m_din, s_din;
   output [7:0] s_address;
   
	reg [1:0] sel; //temporary arbiter's output
	
	always@(posedge clk or negedge reset_n)
	begin
		if (reset_n == 0) sel = 2'b00; //reset
		else if (reset_n == 1) sel = {s0_sel, s1_sel}; //operates
		else sel = 2'bxx; //default
	end
	
	//connect modules
	bus_arbit U0_bus_arbit(m0_req, m1_req, reset_n, clk, m0_grant, m1_grant);
	bus_addr  U1_bus_addr(s_address, s0_sel, s1_sel);
	mx2		 U2_mx2(m0_wr, m1_wr, m1_grant, s_wr);
	mx2_32bit U3_mx2_32bit(m0_dout, m1_dout, m1_grant, s_din);
	mx2_8bit	 U4_mx2_8bit(m0_address, m1_address, m1_grant, s_address);
	mx3_32bit U5_mx3_32bit(32'h00, s0_dout, s1_dout, sel, m_din);
endmodule 