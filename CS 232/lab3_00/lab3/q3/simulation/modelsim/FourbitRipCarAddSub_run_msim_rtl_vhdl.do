transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vcom -93 -work work {/home/zestyoreo/Desktop/lab3/q3/FourbitRipCarAddSub.vhd}
vcom -93 -work work {/home/zestyoreo/Desktop/lab3/q3/FourbitRipCarAdd.vhd}
vcom -93 -work work {/home/zestyoreo/Desktop/lab3/q3/OnebitFullAdd.vhd}
vcom -93 -work work {/home/zestyoreo/Desktop/lab3/q3/OnebitHalfAdd.vhd}

vcom -93 -work work {/home/zestyoreo/Desktop/lab3/q3/test.vhd}

vsim -t 1ps -L altera -L lpm -L sgate -L altera_mf -L altera_lnsim -L maxv -L rtl_work -L work -voptargs="+acc"  test

add wave *
view structure
view signals
run -all
