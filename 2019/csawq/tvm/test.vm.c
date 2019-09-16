BEGIN_VM
  LEAK()
  POP(KAX)
  LDF()

  ADDI(KAX, 0xb78)
  MOV(KSP, KAX)
  DST()

//  MOV(KSP, KAX)
//  DST()


//  ADDI(KSP, 0xb48)
//  DST()
END_VM
