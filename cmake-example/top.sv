module top (
);
  export "DPI-C" function write_mem;
  export "DPI-C" function read_mem;

  logic [31:0] mem[1024];

  function automatic write_mem(string file_name);
    $readmemh(file_name, mem);
  endfunction
	
  function automatic int read_mem(int addr, int number_of_bytes);
    read_mem = 0;
    for (int i = 0; i < number_of_bytes; i++) begin
      read_mem += int'(mem[addr+i][7:0]) << (8 * i);
    end
  endfunction

endmodule
