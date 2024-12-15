module _nand2 (a, b, y); // 2 input NAND gate
	input a, b;
	output y;
	
	assign y = ~(a & b)	; // express nand gate, y = NOT (a AND b)
endmodule

module _inv (a, y); // inverer gate
	input a;
	output y;
	
	assign y = ~a; // express inverter gate, y = NOT a
endmodule 