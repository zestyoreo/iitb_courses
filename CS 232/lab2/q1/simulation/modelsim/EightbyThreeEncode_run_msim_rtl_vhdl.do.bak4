transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vcom -93 -work work {/home/zestyoreo/IITB/CS 232/lab2/q1/EightbyThreeEncode.vhd}
vcom -93 -work work {/home/zestyoreo/IITB/CS 232/lab2/q1/four_and_adder.vhd}
vcom -93 -work work {/home/zestyoreo/IITB/CS 232/lab2/q1/mux.vhd}

vcom -93 -work work {/home/zestyoreo/IITB/CS 232/lab2/q1/test.vhd}

vsim -t 1ps -L altera -L lpm -L sgate -L altera_mf -L altera_lnsim -L maxv -L rtl_work -L work -voptargs="+acc"  test

add wave *
view structure
view signals
run -all
