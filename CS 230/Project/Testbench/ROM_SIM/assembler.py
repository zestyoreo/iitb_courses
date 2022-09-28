import re
import sys

# List of constants used throughout the program
NONE = "none"
ERROR = "error"

OP_CODE = "op_code"
REGISTER = "register_code"
COMMA = "comma"
VALUE = "bin/hex_value"
VALUE_6 = "6_bit_value"
VALUE_9 = "9_bit_value"
VALUE_8 = "8_bit_value"
MEMORY = "memory_address"

BINARY = 2
HEX = 16
DECIMAL = 10

# Data from the Instruction Set
TOKEN_DATA = {
  'add': (OP_CODE, VALUE, COMMA, VALUE, COMMA, VALUE),
  'adc': (OP_CODE, VALUE, COMMA, VALUE, COMMA, VALUE),
  'adz': (OP_CODE, VALUE, COMMA, VALUE, COMMA, VALUE),
  'adi': (OP_CODE, VALUE, COMMA, VALUE, COMMA, VALUE),
  'ndu': (OP_CODE, VALUE, COMMA, VALUE, COMMA, VALUE),
  'ndc': (OP_CODE, VALUE, COMMA, VALUE, COMMA, VALUE),
  'ndz': (OP_CODE, VALUE, COMMA, VALUE, COMMA, VALUE),
  'lhi': (OP_CODE, VALUE, COMMA, VALUE),
  'lli': (OP_CODE, VALUE, COMMA, VALUE),
  'lw' : (OP_CODE, VALUE, COMMA, VALUE, COMMA, VALUE),
  'sw' : (OP_CODE, VALUE, COMMA, VALUE, COMMA, VALUE),
  'lm' : (OP_CODE, VALUE, COMMA, VALUE),
  'sm' : (OP_CODE, VALUE, COMMA, VALUE),
  'beq': (OP_CODE, VALUE, COMMA, VALUE, COMMA, VALUE),
  'jal': (OP_CODE, VALUE, COMMA, VALUE),
  'jlr': (OP_CODE, VALUE, COMMA, VALUE),
  'org': (OP_CODE, VALUE)
}
# Provides the relative swaps of indices for opcodes
REORDER_DATA = {
  'add': ((1,3),(3,5)),
  'adc': ((1,3),(3,5)),
  'adz': ((1,3),(3,5)),
  'ndu': ((1,3),(3,5)),
  'ndz': ((1,3),(3,5)),
  'ndc': ((1,3),(3,5)),
  'adi': ((1,3),)
}
INS_DATA = {
  'add': ("0000", REGISTER, REGISTER, REGISTER, "000\n"),
  'adc': ("0000", REGISTER, REGISTER, REGISTER, "010\n"),
  'adz': ("0000", REGISTER, REGISTER, REGISTER, "001\n"),
  'adi': ("0001", REGISTER, REGISTER, VALUE_6, "\n"),
  'ndu': ("0010", REGISTER, REGISTER, REGISTER, "000\n"),
  'ndc': ("0010", REGISTER, REGISTER, REGISTER, "010\n"),
  'ndz': ("0010", REGISTER, REGISTER, REGISTER, "001\n"),
  'lhi': ("0011", REGISTER, VALUE_9, "\n"),
  'lli': ("1011", REGISTER, VALUE_9, "\n"),
  'lw' : ("0100", REGISTER, REGISTER, VALUE_6, "\n"),
  'sw' : ("0101", REGISTER, REGISTER, VALUE_6, "\n"),
  'lm' : ("0110", REGISTER, "0", VALUE_8, "\n"),
  'sm' : ("0111", REGISTER, "0", VALUE_8, "\n"),
  'beq': ("1100", REGISTER, REGISTER, VALUE_6, "\n"),
  'jal': ("1000", REGISTER, VALUE_9, "\n"),
  'jlr': ("1001", REGISTER, REGISTER, "000000\n"),
  'org': ("1111111111111111\n", MEMORY, "\n")
}

# General purpose regular expressions
REGEX_DATA = (
  (r'^\,$', COMMA, NONE),
  (r'^0b[0-1]+$', VALUE, BINARY),
  (r'^0x[0-9a-f]+$', VALUE, HEX),
  (r'^[0-9]+$', VALUE, DECIMAL),
  (r'^r[0-7]$', VALUE, REGISTER)
)

def reorder_tokens(tokens):
  for i in range(0, len(tokens)):
    if tokens[i][1] in REORDER_DATA:
      swaps = REORDER_DATA[tokens[i][1]]
      for swap in swaps:
        if i+swap[0] >= len(tokens) or i+swap[1] >= len(tokens):
          return
        else:
          tokens[i+swap[0]], tokens[i+swap[1]] = tokens[i+swap[1]], tokens[i+swap[0]]
          
def bin_to_hex(binary):
  '''
  This function converts a binary string to a hexadecimal string
  Expexted input is a string of ones and zeros
  Output is HEX written in ASCII
  '''
  dec = 0;
  out = [];
  for bit in range(len(binary)):
    if binary[bit] == "1":
      dec = dec + int(2**((len(binary)-bit-1)))
       
  return dec_to_hex(dec,4)
  
def hex_string_to_uint8(hex):
  uint8 = []
  for i in range(0,len(hex),2):
    if i+1==len(hex):
      print("Invalid HEX String.")
      return []
    uint8.append(hex_to_dec(hex[i:i+2]))
    
  return uint8
    
def hex_to_dec(inp):
  hex = "0123456789ABCDEF";
  dec = 0;
  for nibble in range(len(inp)):
    if not inp[nibble] == "0":
      dec = dec + int((16**((len(inp)-nibble-1)))*hex.index(inp[nibble]))
  
  return dec
  
def dec_to_hex(decimal, length):
  '''
  This function converts a decimal integer
  into a string of its HEX equivalent
  '''
  
  out = []
  hex = "0123456789ABCDEF";
  for i in range(length):
    out.insert(0,hex[int(decimal%16)])
    decimal = decimal//16;
    
  return "".join(out)
  
def checksum_gen(hex_string):
  return ~(sum(hex_string_to_uint8(hex_string))%256) + 1
    
def get_peripherals(bin_format, format_pointer):
  '''
  This function is used to append constant binary sequences,
  (besides values / op_codes) in the output. Denoted in
  quotes in the INS_DATA dictionary.
  '''
  # Return list of peripheral strings
  peripherals = []
  # Strings which aren't peripherals
  BLACKLIST = [REGISTER, VALUE_6, VALUE_8, VALUE_9, MEMORY]

  while format_pointer < len(bin_format) and \
        bin_format[format_pointer] not in BLACKLIST:
    peripherals.append(bin_format[format_pointer])
    format_pointer += 1

  return peripherals

def get_binary(token, next_type):
  '''
  Returns the binary representation of a value depending on
  the type of expected data. (eg, 3 bits for Registers, 16
  bits for memory). In case of overflow / underflow, exits
  assembler.
  '''
  # defaults
  value_type = DECIMAL
  value = 0

  # Trying to identify HEX / DECIMAL / BINARY
  for data in REGEX_DATA:
    regex = re.compile(data[0])
    if regex.search(token[1]) != None:
      value_type = data[2]

  # Getting decimal form of the number
  if value_type == BINARY:
    value = int(token[1][2:], 2)
  elif value_type == DECIMAL:
    value = int(token[1], 10)
  elif value_type == HEX:
    value = int(token[1][2:], 16)
  elif value_type == REGISTER:
    value = int(token[1][1:], 10)
  else:
    # This should never happen
    print ("Something is wrong with this code")
    return 0

  # Return final binary output based on expected data size.
  # Check for overflows
  if next_type == REGISTER:
    # 3 bit register data
    if value >= 2**3 or value < 0:
      print ("Register out of bounds in " + token[1] + " of line " + str(token[2]))
      sys.exit(0)
    return '{:03b}'.format(value)
  elif next_type == VALUE_6:
    # 6 bit immediate value data
    if (value >= 2**6 or value < 0):
      print ("6 bit value out of bounds in " + token[1] + " of line " + str(token[2]))
      sys.exit(0)
    return '{:06b}'.format(value)
  elif next_type == VALUE_8:
    # 8 bit immediate value data used in LM / SM
    if (value >= 2**8 or value < 0):
      print ("8 bit value out of bounds in " + token[1] + " of line " + str(token[2]))
      sys.exit(0)
    return '{:08b}'.format(value)
  elif next_type == VALUE_9:
    # 9 bit immediate value data
    if (value >= 2**9 or value < 0):
      print ("9 bit value out of bounds in " + token[1] + " of line " + str(token[2]))
      sys.exit(0)
    return '{:09b}'.format(value)
  elif next_type == MEMORY:
    # 16 bit memory addresses
    if (value >= 2**16 or value < 0):
      print ("Memory value out of bounds in " + token[1] + " of line " + str(token[2]))
      sys.exit(0)
    return '{:016b}'.format(value)

def get_token_type(token=""):
  '''
  Returns the token type. The different token types are
  OP_CODE, COMMA and VALUE
  '''
  if token == '':
    return NONE
  if token in TOKEN_DATA:
    return OP_CODE
  else:
    for data in REGEX_DATA:
      regex = re.compile(data[0])
      if regex.search(token) != None:
        return data[1]
    # Nothing found, so return NONE
    return ERROR


def get_tokens(word="", number=0):
  '''
  Breaks up a word into a list of tokens.
  Separation is performed on , symbols.
  '''
  # since word can have multiple tokens
  tokens = []
  sequence = word.split(",")
  for s in sequence:
    token_type = get_token_type(s)
    if token_type == ERROR:
      print ("Token " + s + " couldn't be identified in line " + str(number))
      sys.exit(0)
    # Empty character ''
    if token_type != NONE:
      tokens.append((token_type, s, number))
    # Adding comma after every token
    tokens.append((COMMA, ",", number))
  # Removing final comma
  tokens.pop()
  return tokens

file_name = sys.argv[1]
with open(file_name, 'r') as f:
  # List of all tokens in the file
  tokens = []
  for number, line in enumerate(f):
    words = line.split()
    if ((not words == []) and (words[0][0] == ";")):
      continue
    for word in words:
      word_tokens = get_tokens(word.lower(), number+1)
      tokens.extend(word_tokens)

# Needed as some instructions have a different order of tokens
reorder_tokens(tokens)

# An OP_CODE needed in the start
next_expected = OP_CODE
instruction = ()
bin_format = ()
format_pointer = 0
token_pointer = 0
# Final output hex sequence
output = ""
for num, token in enumerate(tokens):
  # Throw an error if ordering of tokens in not correct
  if token[0] != next_expected:
    print ("Expected " + next_expected + " but found " + token[0] + " in " + token[1] + " of line " + str(token[2]))
  # Start a new instruction
  if token[0] == OP_CODE:
    # load the instruction token sequence and binary format
    instruction = TOKEN_DATA[token[1]]
    bin_format = INS_DATA[token[1]]
    token_pointer = 1
    format_pointer = 1
    # Append op_code
    output += bin_format[0]
  elif token[0] == VALUE:
    # Append value
    output += get_binary(token, bin_format[format_pointer])
    format_pointer += 1

  # Add all peripheral bits in the instruction
  # Most of the times, this will be an empty list
  peripherals = get_peripherals(bin_format, format_pointer)
  for p in peripherals:
    output += p
    format_pointer += 1

  if token_pointer == len(instruction):
    # End of instruction, wait for next instruction
    next_expected = OP_CODE
    token_pointer = 0
    
  else:
    # Expect next token of current instruction
    next_expected = instruction[token_pointer]
    token_pointer += 1
# Write the hex output to a file
hex_output = [bin_to_hex(i) for i in output[:len(output)-1].split("\n")]
hex_file = open(sys.argv[2],'w')
address = 0

while hex_output:

  if("FFFF" in hex_output):
    branch = hex_output.index("FFFF")
  else:
    branch = len(hex_output)
    
  to_print = ""
  if(branch+1>32):
    to_print += ":" + dec_to_hex(64,2) + dec_to_hex(address,4) + "00" + "".join(hex_output[0:32])
    hex_output = hex_output[32:]
    address += 32;
  else:  
    to_print += ":" + dec_to_hex((branch)*2,2) + dec_to_hex(address,4) + "00" + "".join(hex_output[0:branch])
    hex_output = hex_output[branch+1:]
    if(hex_output):
      address = hex_to_dec(hex_output[0])
      del hex_output[0]
  checksum = checksum_gen(to_print[1:])
  to_print += dec_to_hex(checksum,2)
  hex_file.write(to_print + "\n")
  
#Hex File Terminator  
hex_file.write(":00000001FF")
hex_file.close()