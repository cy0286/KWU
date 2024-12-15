module mx2 (d0, d1, s, y); // 2 to 1 multiplexer
	input d0, d1, s;
	output y;
	wire sb, w0, w1;

_inv iv0(s, sb); // express iv0 gate
_nand2 nd20(d0, sb, w0); // express nd20 gate
_nand2 nd21(d1, s, w1); // express nd21 gate
_nand2 nd22(w0, w1, y); // express nd22 gate
endmodule 