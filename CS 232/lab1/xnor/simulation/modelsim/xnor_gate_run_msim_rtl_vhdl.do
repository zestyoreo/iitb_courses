transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vcom -93 -work work {/home/zestyoreo/IITB/CS 232/lab1/xnor/xnor_gate.vhd}

