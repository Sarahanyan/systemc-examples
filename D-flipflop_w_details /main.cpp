#include <systemc.h>
#include "dff.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<bool> s_din, sig1, sig2, sig3, s_dout;
	sc_clock clock("clk",5,SC_NS,0.5);

	dff dff1("dff_instance_1");
	driver dr("driver");
	monitor mon("monitor");

	dr.d_din(s_din);
	dff1.din(s_din);
	mon.m_din(s_din);
	
	dff1.dout(s_dout);
	mon.m_dout(s_dout);
	
	dff1.clk(clock);

	sc_trace_file *fp;
	fp=sc_create_vcd_trace_file("vcd_trace");
	fp->set_time_unit(100, SC_PS);

	sc_trace(fp, s_din, "D");
	sc_trace(fp, clock, "CLK");
	sc_trace(fp, s_dout, "Q1");

	sc_start(60, SC_NS);
	sc_close_vcd_trace_file(fp);
	return 0;
}