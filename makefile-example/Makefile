VERILATOR_ROOT := /usr/local/share/verilator
VM_SC := 0
VM_TRACE := 0

VERILATOR_OBJS := verilated.o verilated_threads.o verilated_dpi.o

main:main.o obj_dir/Vtop__ALL.a librubbler.a $(VERILATOR_OBJS)
	$(CXX) $^ -o $@

main.o: main.cpp obj_dir/Vtop.h rubbler.h
	$(CXX) \
	-Iobj_dir \
	-I$(VERILATOR_ROOT)/include \
	-I$(VERILATOR_ROOT)/include/vltstd \
	-c main.cpp -o $@

obj_dir/Vtop__ALL.a obj_dir/Vtop.h: top.sv
	verilator -cc --build -j top.sv

rubbler.h librubbler.a: rubbler
	cd rubbler && cargo build --release
	cp rubbler/target/rubbler.h rubbler/target/release/librubbler.a .

rubbler:
	git clone https://github.com/fuad1502/rubbler.git

include $(VERILATOR_ROOT)/include/verilated.mk

.PHONY:clean
clean:
	rm -rf obj_dir
	rm -rf rubbler
	rm librubbler.a rubbler.h
	rm *.o *.d
	rm main
