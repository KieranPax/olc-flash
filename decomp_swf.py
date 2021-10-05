import sys

def decomp(fn:str):
  with open(fn,'rb') as fs:
    head = fs.read(8)
    h = head[0:1]
    if h == b'F':
      return 'Already Decompressed'
    elif h == b'C':
      import zlib
      with open(fn.rsplit('.',1)[0]+'.d.swf','wb') as ofs:
        ofs.write(b'F' + head[1:])
        ofs.write(zlib.decompress(fs.read()))
      return 'Decompressed ZLIB'
    else:
      return 'Unknown Compression / Invalid file: '+repr(h)

def main(args):
  if len(args) < 1:
    print(decomp(input('File:')))
  else:
    print(decomp(args[0]))
  
if __name__=='__main__':
  main(sys.argv[1:])