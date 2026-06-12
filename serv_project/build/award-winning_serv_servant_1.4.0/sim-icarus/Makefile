TARGET           := award-winning_serv_servant_1.4.0
TOPLEVEL         := -sservant_tb
IVERILOG_OPTIONS := 
VVP_OPTIONS := 
EXTRA_OPTIONS    ?= +vcd=1 +firmware=/home/rory/riscv_benchmark/serv_project/test_lw_cycles.hex

all: $(VPI_MODULES) $(TARGET)

$(TARGET):
	iverilog $(TOPLEVEL) -c $(TARGET).scr -o $@ $(IVERILOG_OPTIONS)

run: $(VPI_MODULES) $(TARGET)
	vvp -n -M. -l icarus.log $(patsubst %.vpi,-m%,$(VPI_MODULES)) $(VVP_OPTIONS) $(TARGET) -fst $(EXTRA_OPTIONS)

clean:
	$(RM) $(VPI_MODULES) $(TARGET)
