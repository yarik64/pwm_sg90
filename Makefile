
GEN    = Ninja
BLDDIR = build
OCDCP  = ocd/
PRJNME = pwm_sg90

all:
	cmake . \
		-G $(GEN) \
		-B $(BLDDIR) \
		-DCMAKE_BUILD_TYPE=Debug

	ninja-build -C $(BLDDIR)


flash:
	openocd \
		-f interface/cmsis-dap.cfg \
		-f target/rp2040.cfg \
		-c "adapter speed 5000" \
		-c "program $(BLDDIR)/$(PRJNME).elf verify reset exit"


clean:
	$(RM) -r $(wildcard ./*~ $(BLDDIR))
