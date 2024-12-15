module cla4_ov(a, b, ci, s, c3, co); //cla4_ov module
   input [3:0] a, b;
   input ci;
   output [3:0] s;
   output c3, co;
   
   wire c1, c2;
   
   //load fa_v2 module and clb4 module
   fa_v2 U0_fa (a[0], b[0], ci, s[0]);
   fa_v2 U1_fa (a[1], b[1], c1, s[1]);
   fa_v2 U2_fa (a[2], b[2], c2, s[2]);
   fa_v2 U3_fa (a[3], b[3], c3, s[3]);
   clb4 U4_clb4(a, b, ci, c1, c2, c3, co);
endmodule 