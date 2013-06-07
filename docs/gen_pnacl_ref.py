import re
import os, sys


def is_header_line(line):
  return re.match('((=+)|(\^+)|("+)|(\-+))$', line)

def main():
  langref = sys.argv[1]
  stream = open(langref)

  # Hack to print out the whole main header + TOC
  for i in range(8):
    line = stream.readline()
    if "LLVM Language R" in line:
      line = "PNaCl IR Reference Manual\n"
    sys.stdout.write(line)

  line = stream.readline()
  while line:
    nextline = stream.readline()
    if nextline and is_header_line(nextline):
      sys.stdout.write(line + nextline + '\n')
    line = nextline


if __name__ == '__main__':
  main()

