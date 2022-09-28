
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



class TreePrinter:
    def __init__(self, val):
        self.val = val
       
    
    def to_string (self):
        global outfile
        nodeptr = self.val['root']
        outfile = open("out.dot", "w+")
        outfile.write("digraph G { \n")
        outfile.write("splines=line; \n")
        print_tree(nodeptr)
        outfile.write("}") 
        outfile.close()
        return ""



def lookup_type (val):
     if str(val.type)=='btree':
         return TreePrinter(val)
     return None
 
gdb.pretty_printers.append (lookup_type)
