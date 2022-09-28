import io
def print_tree(nodeptr):    
    if nodeptr == 0x0:
        return ""
    else:
        node = nodeptr.dereference()
	    # create a node
        node_name = "node"+str(node['key_value'])
        outfile.write(node_name + "[ label = "+ "\"" + str(node['key_value']) + "\"" + "];\n")
        left_name = print_tree(node['left'])
        right_name = print_tree(node['right'])
        if left_name != "":
        	outfile.write(node_name + "->" + left_name + "[ label = \"L\"]" + ";\n")
        if right_name != "":
        	outfile.write(node_name + "->" + right_name + "[ label = \"R\"]" + ";\n")
        return node_name
def exit_handler (event):
    print ("event type: exit")
    print ("exit code: %d" % (event.exit_code))


def stop_handler(event):
    print(event)
    global outfile
    outfile = open("out.dot", "w+")
    outfile.write("digraph G { \n")
    outfile.write("splines=line; \n")
    rootnodeptr = gdb.parse_and_eval('(bt.root)')
    print_tree(rootnodeptr)
    outfile.write("}") 
    outfile.close()

gdb.events.stop.connect(stop_handler)
  


