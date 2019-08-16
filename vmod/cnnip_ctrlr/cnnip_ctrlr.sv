/*
 *  cnnip_ctrlr.sv -- CNN IP controller
 *  ETRI <SW-SoC AI Deep Learning HW Accelerator RTL Design> course material
 *
 *  first draft by Junyoung Park
 *  second draft by Kyungseok Jang
 */

`include "cnnip_mem_if.sv"

module cnnip_ctrlr
(
  // clock and reset signals from domain a
  input wire clk_a,
  input wire arstz_aq,

  // internal memories
  cnnip_mem_if.master to_input_mem,
  cnnip_mem_if.master to_weight_mem,
  cnnip_mem_if.slave to_feature_mem,

  // configuration registers
  input wire         CMD_START,
  input wire   [7:0] MODE_KERNEL_SIZE,
  input wire   [7:0] MODE_KERNEL_NUMS,
  input wire   [1:0] MODE_STRIDE,
  input wire         MODE_PADDING,

  output wire        Read_done,
  output wire        Conv_done,

  output wire        CMD_DONE,
  output wire        CMD_DONE_VALID

);

  // sample FSM  - modify by DOBIE
  enum { IDLE, READ, CONV, DONE } state_aq, state_next;

  // internal registers
//  reg [15:0] cnt_aq;

//  always @(posedge clk_a, negedge arstz_aq)
//    if (arstz_aq == 1'b0) cnt_aq <= 16'b0;
//    else if (state_aq == READ) cnt_aq <= cnt_aq + 1'b1;
//    else cnt_aq <= 16'b0;

  reg [10:0] input_cnt; // 1024 (32x32)
  
  always @(posedge clk_a, negedge arstz_aq) begin
    if(arstz_aq == 1'b0) input_cnt <= 11'b0;
    else if(state_aq == READ && input_cnt < 11'd1024) input_cnt <= input_cnt + 1'b1;
    else if(input_cnt >= 11'd1024) input_cnt <= 11'd0;
  end

  reg [4:0] weight_cnt; // 25 (5x5)
  
  always @(posedge clk_a, negedge arstz_aq) begin
    if(arstz_aq == 1'b0) weight_cnt <= 5'b0;
    else if(state_aq == READ && input_cnt != 11'd1024 && weight_cnt < 5'd25) weight_cnt <= weight_cnt + 1'b1;
    else if(input_cnt == 11'd1024 && weight_cnt == 5'd25) weight_cnt <= 5'd0;
  end
  
  reg [9:0] conv_cnt;  // 784 (28x28)
  
  always @(posedge clk_a, negedge arstz_aq) begin
    if(arstz_aq == 1'b0) conv_cnt <= 10'b0;
    else if(state_aq == CONV && conv_cnt < 10'd784) conv_cnt <= conv_cnt + 1'b1;
    else if(conv_cnt >= 10'd784) conv_cnt <= 10'd0;
  end
  
  // Done Signal definition
  assign Read_done = (input_cnt == 11'd1024 && weight_cnt == 5'd25) ? 1 : 0;
  assign Conv_done = (conv_cnt == 10'd784) ? 1 : 0;

  // state transition
  always @(posedge clk_a, negedge arstz_aq)
    if (arstz_aq == 1'b0) state_aq <= IDLE;
    else state_aq <= state_next;

// master (output en, output we, output addr, output din, input dout, input valid);
// slave  (input en, input we, input addr, input din, output dout, output valid);

  // state transition condition
  always @(*)
  begin
    state_next = state_aq;
    case (state_aq)
      IDLE:
        if (CMD_START) state_next = READ;
        
      READ:
        if (Read_done) state_next = CONV;
        else begin // master
            to_input_mem.en = 1'b1;
            to_input_mem.we = 1'b0;
            to_input_mem.addr = 12'd1; // input data addr
            to_input_mem.din = 32'd1;  // input data  
            
            to_weight_mem.en = 1'b1;
            to_weight_mem.we = 1'b0;
            to_weight_mem.addr = 12'd2; // weight data addr
            to_weight_mem.din = 32'd2;  // weight data
        end
      CONV:
        if (Conv_done) state_next = DONE;
        else begin // slave
            to_feature_mem.dout = 32'd3; // conv result data  - PE Modules
            to_feature_mem.valid = 1'b1;
        end

      DONE:
        state_next = IDLE;
    endcase
  end

  // output signals
  assign CMD_DONE = (state_aq == DONE);
  assign CMD_DONE_VALID = (state_aq == DONE);

//  control signals
//  assign to_input_mem.en   = 0;
//  assign to_input_mem.we   = 'b0;
//  assign to_input_mem.addr = 'b0;
//  assign to_input_mem.din  = 'b0;

//  assign to_weight_mem.en   = 0;
//  assign to_weight_mem.we   = 'b0;
//  assign to_weight_mem.addr = 'b0;
//  assign to_weight_mem.din  = 'b0;

//  assign to_feature_mem.en   = 0;
//  assign to_feature_mem.we   = 'b0;
//  assign to_feature_mem.addr = 'b0;
//  assign to_feature_mem.din  = 'b0;

endmodule // cnnip_ctrlr
