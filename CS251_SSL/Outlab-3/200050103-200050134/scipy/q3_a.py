import argparse
import scipy
from scipy import integrate

parser = argparse.ArgumentParser()
parser.add_argument('x_lower',type = float)
parser.add_argument('x_upper',type = float)
parser.add_argument('y_lower',type = float)
parser.add_argument('y_upper',type = float)
parser.add_argument('z_lower',type = float)
parser.add_argument('z_upper',type = float)
args = parser.parse_args()

x_lower, x_upper, y_lower, y_upper, z_lower, z_upper = float(args.x_lower),float(args.x_upper),float(args.y_lower),float(args.y_upper),float(args.z_lower),float(args.z_upper)
func = lambda z, y, x: (x**2)*(y**2)*(z**2)

integral = scipy.integrate.tplquad(func, x_lower, x_upper, y_lower, y_upper, z_lower, z_upper)
print(integral[0])
