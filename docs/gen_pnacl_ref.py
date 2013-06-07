import re
import os, sys


def is_empty_line(line):
  return len(line.strip()) == 0

def is_header_line(line):
  return re.match('((=+)|(\^+)|("+)|(\-+))$', line)

def cleanup_title(line):
  return line.replace("'", "").replace("`", "")


def main():
  langref = sys.argv[1]
  htmlname = os.path.splitext(langref)[0] + '.html'
  stream = open(langref)

  # Hack to print out the whole main header + TOC
  for i in range(8):
    line = stream.readline()
    if "LLVM Language R" in line:
      line = "PNaCl IR Reference Manual\n"
    sys.stdout.write(line)

  # The link target for the following header
  linktarget = None

  line = stream.readline()
  while line:
    nextline = stream.readline()
    if nextline and is_header_line(nextline):
      title = line.strip()
      sys.stdout.write(title + '\n' + nextline + '\n')

      if linktarget:
        sys.stdout.write('`LLVM LangRef: {0} <{1}#{2}>`_\n\n'.format(
          cleanup_title(title), htmlname, linktarget))

    # Match a link target for the following header
    m = re.match('\.\.\s+_(\w+):$', line)
    if m:
      linktarget = m.group(1)
    elif not is_empty_line(line):
      linktarget = None

    line = nextline


if __name__ == '__main__':
  main()

