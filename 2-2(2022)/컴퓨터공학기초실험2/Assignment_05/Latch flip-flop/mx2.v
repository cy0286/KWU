module mx2(d0, d1, s, y); // mx2 module
   input d0, d1;
   input s;
   output y;
   
   wire sb, w0, w1;

   // load _inv module and _nand2 module
   _inv U0_inv(s, sb);
   _nand2 U1_nand2(d0, sb, w0);
   _nand2 U2_nand3(d1, s, w1);
   _nand2 U3_nand4(w0, w1, y);
endmodule 