module mx8(a,b,c,d,e,f,g,h,s2,s1,s0,y); //mx8 module
   input a,b,c,d,e,f,g,h;
   input s2,s1,s0;
   output y;

   wire w0,w1,w2,w3,w4,w5;

   //load mx2 module
   mx2 U0_mx2(a, b, s0, w0);
   mx2 U1_mx2(c, d, s0, w1);
   mx2 U2_mx2(e, f, s0, w2);
   mx2 U3_mx2(g, h, s0, w3);
   mx2 U4_mx2(w0, w1, s1, w4);
   mx2 U5_mx2(w2, w3, s1, w5);
   mx2 U6_mx2(w4, w5, s2, y);
endmodule 