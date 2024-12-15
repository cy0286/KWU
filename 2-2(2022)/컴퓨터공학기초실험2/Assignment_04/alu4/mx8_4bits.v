module mx8_4bits(a,b,c,d,e,f,g,h,s2,s1,s0,y); //4bits mx8 module
   input [3:0] a,b,c,d,e,f,g,h;
   input s2,s1,s0;
   output [3:0] y;
   
   //load mx8 module
   mx8 U0_mx8(a[0], b[0], c[0], d[0], e[0], f[0], g[0], h[0], s2, s1, s0, y[0]);
   mx8 U1_mx8(a[1], b[1], c[1], d[1], e[1], f[1], g[1], h[1], s2, s1, s0, y[1]);
   mx8 U2_mx8(a[2], b[2], c[2], d[2], e[2], f[2], g[2], h[2], s2, s1, s0, y[2]);
   mx8 U3_mx8(a[3], b[3], c[3], d[3], e[3], f[3], g[3], h[3], s2, s1, s0, y[3]);   
endmodule 