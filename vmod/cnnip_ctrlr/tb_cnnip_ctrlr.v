`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/08/15 21:55:52
// Design Name: 
// Module Name: tb_cnnip_ctrlr
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module tb_cnnip_ctrlr;

integer i;

reg clk_a;
reg arstz_aq;

cnnip_mem_if a();
cnnip_mem_if b();
cnnip_mem_if c();

logic CMD_START;
logic [7:0] MODE_KERNEL_SIZE;
logic [7:0] MODE_KERNEL_NUMS;
logic [1:0] MODE_STRIDE;
logic MODE_PADDING;

logic CMD_DONE;
logic CMD_DONE_VALID;

cnnip_ctrlr tb_cnnip_ctrlr
(
  .clk_a(clk_a),
  .arstz_aq(arstz_aq),
  
  .to_input_mem(a),
  .to_weight_mem(b),
  .to_feature_mem(c),
  
  .CMD_START(CMD_START),
  .MODE_KERNEL_SIZE(MODE_KERNEL_SIZE),
  .MODE_KERNEL_NUMS(MODE_KERNEL_NUMS),
  .MODE_STRIDE(MODE_STRIDE),
  .MODE_PADDING(MODE_PADDING),
  .CMD_DONE(CMD_DONE),
  .CMD_DONE_VALID(CMD_DONE_VALID)
);

always #10 clk_a = ~clk_a;

initial begin

    clk_a = 0;
    arstz_aq = 0;

    CMD_START = 0;
    
    a.en = 0;
    a.we = 0;
    a.addr = 0;
    a.din = 0;

    b.en = 0;
    b.we = 0;
    b.addr = 0;
    b.din = 0;
    
    c.dout = 0;
    c.valid = 0;

    @(posedge clk_a);
    #1 arstz_aq = 1;
    
    @(posedge clk_a);
    #1 CMD_START = 1;
    
    @(posedge clk_a);
    #1 CMD_START = 0;
    
    @(posedge clk_a);
    #1     a.en = 1; a.we = 0; a.addr = 12'd1; a.din = 32'd1;
           b.en = 1; b.we = 0; b.addr = 12'd1; b.din = 32'd1;
    
    repeat (1024) @(posedge clk_a);
     
    @(posedge clk_a)
    #1     a.en = 0; a.we = 0; a.addr = 12'd0; a.din = 32'd0;
           b.en = 0; b.we = 0; b.addr = 12'd0; b.din = 32'd0;
           
    @(posedge clk_a);
    #1     c.valid = 1;
    
    repeat (784) @(posedge clk_a);
    
    @(posedge clk_a);
    #1     c.valid = 0;
    
    repeat (10) @(posedge clk_a);
    
    $finish;

end

endmodule
