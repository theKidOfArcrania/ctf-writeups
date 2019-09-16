/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20181031 (64-bit version)
 * Copyright (c) 2000 - 2018 Intel Corporation
 * 
 * Disassembling to symbolic ASL+ operators
 *
 * Disassembly of DSDT-GA-G1.Assassin-F3.aml, Sat Dec  8 14:38:48 2018
 *
 * Original Table Header:
 *     Signature        "DSDT"
 *     Length           0x0000324C (12876)
 *     Revision         0x01 **** 32-bit table (V1), no 64-bit math support
 *     Checksum         0x3D
 *     OEM ID           "GBT   "
 *     OEM Table ID     "GBTUACPI"
 *     OEM Revision     0x00001000 (4096)
 *     Compiler ID      "INTL"
 *     Compiler Version 0x20110623 (537986595)
 */
DefinitionBlock ("", "DSDT", 1, "GBT   ", "GBTUACPI", 0x00001000)
{
    Name (TMAC, "GA-G1.Assassin-F3 DSDT edits by MacMan at tonymacx86.com 2012-06-05")
    Method (DTGP, 5, NotSerialized)
    {
        If ((Arg0 == ToUUID ("a0b5b7c6-1318-441c-b0c9-fe695eaf949b")))
        {
            If ((Arg1 == One))
            {
                If ((Arg2 == Zero))
                {
                    Arg4 = Buffer (One)
                        {
                             0x03                                             // .
                        }
                    Return (One)
                }

                If ((Arg2 == One))
                {
                    Return (One)
                }
            }
        }

        Arg4 = Buffer (One)
            {
                 0x00                                             // .
            }
        Return (Zero)
    }

    Scope (_PR)
    {
        Processor (CPU0, 0x00, 0x00000410, 0x06){}
        Processor (CPU1, 0x01, 0x00000410, 0x06){}
        Processor (CPU2, 0x02, 0x00000410, 0x06){}
        Processor (CPU3, 0x03, 0x00000410, 0x06){}
        Processor (CPU4, 0x04, 0x00000410, 0x06){}
        Processor (CPU5, 0x05, 0x00000410, 0x06){}
        Processor (CPU6, 0x06, 0x00000410, 0x06){}
        Processor (CPU7, 0x07, 0x00000410, 0x06){}
        Processor (CPU8, 0x08, 0x00000410, 0x06){}
        Processor (CPU9, 0x09, 0x00000410, 0x06){}
        Processor (CPUA, 0x0A, 0x00000410, 0x06){}
        Processor (CPUB, 0x0B, 0x00000410, 0x06){}
        Processor (CPUC, 0x0C, 0x00000410, 0x06){}
        Processor (CPUD, 0x0D, 0x00000410, 0x06){}
        Processor (CPUE, 0x0E, 0x00000410, 0x06){}
        Processor (CPUF, 0x0F, 0x00000410, 0x06){}
    }

    Name (_S0, Package (0x04)  // _S0_: S0 System State
    {
        Zero, 
        Zero, 
        Zero, 
        Zero
    })
    Name (_S1, Package (0x04)  // _S1_: S1 System State
    {
        One, 
        Zero, 
        Zero, 
        Zero
    })
    Name (_S3, Package (0x04)  // _S3_: S3 System State
    {
        0x05, 
        Zero, 
        Zero, 
        Zero
    })
    Name (_S4, Package (0x04)  // _S4_: S4 System State
    {
        0x06, 
        Zero, 
        Zero, 
        Zero
    })
    Name (_S5, Package (0x04)  // _S5_: S5 System State
    {
        0x07, 
        Zero, 
        Zero, 
        Zero
    })
    Name (FLAG, Zero)
    Name (STAT, Zero)
    OperationRegion (SMOD, SystemMemory, 0x000FF840, One)
    Field (SMOD, ByteAcc, NoLock, Preserve)
    {
            ,   7, 
        SUSF,   1
    }

    OperationRegion (LBOC, SystemMemory, 0x000FF820, 0x02)
    Field (LBOC, ByteAcc, NoLock, Preserve)
    {
        UBMC,   1, 
        Offset (0x02)
    }

    OperationRegion (DEBG, SystemIO, 0x80, One)
    Field (DEBG, ByteAcc, NoLock, Preserve)
    {
        DBG1,   8
    }

    OperationRegion (RCRB, SystemMemory, 0xFED1C000, 0x4000)
    Field (RCRB, DWordAcc, Lock, Preserve)
    {
        Offset (0x3404), 
            ,   7, 
        HPTF,   1
    }

    OperationRegion (ELKM, SystemMemory, 0x000FFFEA, One)
    Field (ELKM, ByteAcc, NoLock, Preserve)
    {
            ,   1, 
            ,   1, 
        ELSO,   1, 
            ,   1, 
            ,   1, 
            ,   1, 
            ,   1
    }

    OperationRegion (EXTM, SystemMemory, 0x000FF830, 0x10)
    Field (EXTM, WordAcc, NoLock, Preserve)
    {
        ROM1,   16, 
        RMS1,   16, 
        ROM2,   16, 
        RMS2,   16, 
        ROM3,   16, 
        RMS3,   16, 
        AMEM,   32
    }

    OperationRegion (SMIC, SystemIO, 0xB2, One)
    Field (SMIC, ByteAcc, NoLock, Preserve)
    {
        SCP,    8
    }

    OperationRegion (GP2C, SystemIO, 0x042C, 0x02)
    Field (GP2C, ByteAcc, NoLock, Preserve)
    {
        G2C1,   8, 
        G2C2,   8
    }

    OperationRegion (APMP, SystemIO, 0xB2, 0x02)
    Field (APMP, ByteAcc, NoLock, Preserve)
    {
        APMC,   8, 
        APMD,   8
    }

    OperationRegion (PMRS, SystemIO, 0x0430, One)
    Field (PMRS, ByteAcc, NoLock, Preserve)
    {
            ,   4, 
        SLPE,   1
    }

    OperationRegion (AGPS, SystemIO, 0x0438, 0x04)
    Field (AGPS, ByteAcc, NoLock, Preserve)
    {
        GPSE,   16, 
        GPSS,   16
    }

    OperationRegion (GPCN, SystemIO, 0x0442, One)
    Field (GPCN, ByteAcc, NoLock, Preserve)
    {
            ,   1, 
        SWGC,   1, 
        Offset (0x01)
    }

    Name (OSFX, One)
    Name (LINX, Zero)
    Name (AMAC, Zero)
    Name (OSFL, One)
    Method (STRC, 2, NotSerialized)
    {
        If ((SizeOf (Arg0) != SizeOf (Arg1)))
        {
            Return (Zero)
        }

        Local0 = (SizeOf (Arg0) + One)
        Name (BUF0, Buffer (Local0){})
        Name (BUF1, Buffer (Local0){})
        BUF0 = Arg0
        BUF1 = Arg1
        While (Local0)
        {
            Local0--
            If ((DerefOf (BUF0 [Local0]) != DerefOf (BUF1 [Local0]
                )))
            {
                Return (Zero)
            }
        }

        Return (One)
    }

    OperationRegion (INFO, SystemMemory, 0x000FF840, One)
    Field (INFO, ByteAcc, NoLock, Preserve)
    {
        KBDI,   1, 
        RTCW,   1, 
        PS2F,   1, 
        IRFL,   2, 
        DISE,   1, 
        SSHU,   1
    }

    Scope (\)
    {
        Name (PICF, Zero)
        Method (_PIC, 1, NotSerialized)  // _PIC: Interrupt Model
        {
            PICF = Arg0
        }
    }

    Method (_PTS, 1, NotSerialized)  // _PTS: Prepare To Sleep
    {
        Local0 = (Arg0 | 0xF0)
        DBG1 = Local0
        OSTP ()
        If ((Arg0 == 0x05))
        {
            SMIP = 0x99
            \_SB.PCI0.LPCB.AG3E = One
            SLPE = Zero
            Sleep (0x10)
        }
        Else
        {
            \_SB.PCI0.LPCB.AG3E = Zero
        }
    }

    Method (_WAK, 1, NotSerialized)  // _WAK: Wake
    {
        DBG1 = 0xFF
        If ((Arg0 == 0x04))
        {
            If ((OSFL == One))
            {
                SMIP = 0x56
            }

            If ((OSFL == 0x02))
            {
                SMIP = 0x57
            }

            If ((OSFL == Zero))
            {
                Local0 = 0x58
                If ((OSFX == 0x03))
                {
                    Local0 = 0x59
                }

                SMIP = Local0
            }
        }

        If ((Arg0 == One)){}
        If (OSFL)
        {
            Notify (\_SB.PWRB, 0x02) // Device Wake
        }
        ElseIf ((RTCW == Zero))
        {
            Notify (\_SB.PWRB, 0x02) // Device Wake
        }

        Notify (\_SB.PCI0.UHC1, Zero) // Bus Check
        Notify (\_SB.PCI0.UHC2, Zero) // Bus Check
        Notify (\_SB.PCI0.UHC3, Zero) // Bus Check
        Notify (\_SB.PCI0.UHC4, Zero) // Bus Check
        Notify (\_SB.PCI0.UHC5, Zero) // Bus Check
        Notify (\_SB.PCI0.UHC6, Zero) // Bus Check
        Return (Package (0x02)
        {
            Zero, 
            Zero
        })
    }

    Scope (_SI)
    {
        Method (_MSG, 1, NotSerialized)  // _MSG: Message
        {
            Local0 = Zero
        }

        Method (_SST, 1, NotSerialized)  // _SST: System Status
        {
            Local0 = Zero
        }
    }

    Scope (_GPE)
    {
        Method (_L03, 0, NotSerialized)  // _Lxx: Level-Triggered GPE
        {
            Notify (\_SB.PCI0.UHC1, 0x02) // Device Wake
            Notify (\_SB.PWRB, 0x02) // Device Wake
        }

        Method (_L04, 0, NotSerialized)  // _Lxx: Level-Triggered GPE
        {
            Notify (\_SB.PCI0.UHC2, 0x02) // Device Wake
            Notify (\_SB.PWRB, 0x02) // Device Wake
        }

        Method (_L0C, 0, NotSerialized)  // _Lxx: Level-Triggered GPE
        {
            Notify (\_SB.PCI0.UHC3, 0x02) // Device Wake
            Notify (\_SB.PWRB, 0x02) // Device Wake
        }

        Method (_L0E, 0, NotSerialized)  // _Lxx: Level-Triggered GPE
        {
            Notify (\_SB.PCI0.UHC4, 0x02) // Device Wake
            Notify (\_SB.PWRB, 0x02) // Device Wake
        }

        Method (_L05, 0, NotSerialized)  // _Lxx: Level-Triggered GPE
        {
            Notify (\_SB.PCI0.UHC5, 0x02) // Device Wake
            Notify (\_SB.PWRB, 0x02) // Device Wake
        }

        Method (_L20, 0, NotSerialized)  // _Lxx: Level-Triggered GPE
        {
            Notify (\_SB.PCI0.UHC6, 0x02) // Device Wake
            Notify (\_SB.PWRB, 0x02) // Device Wake
        }

        Method (_L0D, 0, NotSerialized)  // _Lxx: Level-Triggered GPE
        {
            Notify (\_SB.PCI0.EHC1, 0x02) // Device Wake
            Notify (\_SB.PCI0.EHC2, 0x02) // Device Wake
            Notify (\_SB.PWRB, 0x02) // Device Wake
            Notify (\_SB.PCI0.AZAL, 0x02) // Device Wake
        }

        Method (_L0B, 0, NotSerialized)  // _Lxx: Level-Triggered GPE
        {
            Notify (\_SB.PCI0.HUB0, 0x02) // Device Wake
        }

        Method (_L09, 0, NotSerialized)  // _Lxx: Level-Triggered GPE
        {
            Notify (\_SB.PCI0.PEX0, 0x02) // Device Wake
            Notify (\_SB.PCI0.PEX1, 0x02) // Device Wake
            Notify (\_SB.PCI0.PEX2, 0x02) // Device Wake
            Notify (\_SB.PCI0.PEX3, 0x02) // Device Wake
            Notify (\_SB.PCI0.PEX4, 0x02) // Device Wake
            Notify (\_SB.PCI0.PEX5, 0x02) // Device Wake
        }
    }

    Scope (_SB)
    {
        Device (PWRB)
        {
            Name (_CID, EisaId ("PNP0C0C") /* Power Button Device */)  // _CID: Compatible ID
            Method (_STA, 0, NotSerialized)  // _STA: Status
            {
                Return (0x0B)
            }
        }

        Device (PCI0)
        {
            Name (_HID, EisaId ("PNP0A03") /* PCI Bus */)  // _HID: Hardware ID
            Name (_ADR, Zero)  // _ADR: Address
            Name (_UID, One)  // _UID: Unique ID
            Name (_BBN, Zero)  // _BBN: BIOS Bus Number
            Method (_S3D, 0, NotSerialized)  // _S3D: S3 Device State
            {
                If ((OSFL == 0x02))
                {
                    Return (0x02)
                }
                Else
                {
                    Return (0x03)
                }
            }

            Method (_STA, 0, NotSerialized)  // _STA: Status
            {
                Return (0x0F)
            }

            Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
            {
                Name (BUF0, ResourceTemplate ()
                {
                    WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                        0x0000,             // Granularity
                        0x0000,             // Range Minimum
                        0x003F,             // Range Maximum
                        0x0000,             // Translation Offset
                        0x0040,             // Length
                        ,, )
                    IO (Decode16,
                        0x0CF8,             // Range Minimum
                        0x0CF8,             // Range Maximum
                        0x01,               // Alignment
                        0x08,               // Length
                        )
                    WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
                        0x0000,             // Granularity
                        0x0000,             // Range Minimum
                        0x0CF7,             // Range Maximum
                        0x0000,             // Translation Offset
                        0x0CF8,             // Length
                        ,, , TypeStatic, DenseTranslation)
                    WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
                        0x0000,             // Granularity
                        0x0D00,             // Range Minimum
                        0xFFFF,             // Range Maximum
                        0x0000,             // Translation Offset
                        0xF300,             // Length
                        ,, , TypeStatic, DenseTranslation)
                    DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                        0x00000000,         // Granularity
                        0x000A0000,         // Range Minimum
                        0x000BFFFF,         // Range Maximum
                        0x00000000,         // Translation Offset
                        0x00020000,         // Length
                        ,, , AddressRangeMemory, TypeStatic)
                    DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                        0x00000000,         // Granularity
                        0x000C0000,         // Range Minimum
                        0x000DFFFF,         // Range Maximum
                        0x00000000,         // Translation Offset
                        0x00020000,         // Length
                        ,, , AddressRangeMemory, TypeStatic)
                    DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                        0x00000000,         // Granularity
                        0x00100000,         // Range Minimum
                        0xFEBFFFFF,         // Range Maximum
                        0x00000000,         // Translation Offset
                        0xFEB00000,         // Length
                        ,, _Y00, AddressRangeMemory, TypeStatic)
                })
                CreateDWordField (BUF0, \_SB.PCI0._CRS._Y00._MIN, TCMM)  // _MIN: Minimum Base Address
                CreateDWordField (BUF0, \_SB.PCI0._CRS._Y00._LEN, TOMM)  // _LEN: Length
                TCMM = (AMEM + 0x00010000)
                TCMM += 0x00020000
                TOMM = (0xFEC00000 - TCMM) /* \_SB_.PCI0._CRS.TCMM */
                Return (BUF0) /* \_SB_.PCI0._CRS.BUF0 */
            }

            Name (PICM, Package (0x2E)
            {
                Package (0x04)
                {
                    0x001BFFFF, 
                    Zero, 
                    LNK0, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    Zero, 
                    LNKA, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    One, 
                    LNKB, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    0x02, 
                    LNKC, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    0x03, 
                    LNKD, 
                    Zero
                }, 

                Package (0x04)
                {
                    0xFFFF, 
                    Zero, 
                    LNKA, 
                    Zero
                }, 

                Package (0x04)
                {
                    0xFFFF, 
                    One, 
                    LNKB, 
                    Zero
                }, 

                Package (0x04)
                {
                    0xFFFF, 
                    0x02, 
                    LNKC, 
                    Zero
                }, 

                Package (0x04)
                {
                    0xFFFF, 
                    0x03, 
                    LNKD, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0003FFFF, 
                    Zero, 
                    LNKA, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0003FFFF, 
                    One, 
                    LNKB, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0003FFFF, 
                    0x02, 
                    LNKC, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0003FFFF, 
                    0x03, 
                    LNKD, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0005FFFF, 
                    Zero, 
                    LNKA, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0005FFFF, 
                    One, 
                    LNKB, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0005FFFF, 
                    0x02, 
                    LNKC, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0005FFFF, 
                    0x03, 
                    LNKD, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    Zero, 
                    LNKA, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    One, 
                    LNKB, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    0x02, 
                    LNKC, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    0x03, 
                    LNKD, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    Zero, 
                    LNKA, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    One, 
                    LNKB, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    0x02, 
                    LNKC, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    0x03, 
                    LNKD, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0002FFFF, 
                    Zero, 
                    LNKA, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0002FFFF, 
                    One, 
                    LNKB, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0002FFFF, 
                    0x02, 
                    LNKC, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x0002FFFF, 
                    0x03, 
                    LNKD, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001CFFFF, 
                    Zero, 
                    LNKA, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001CFFFF, 
                    One, 
                    LNKB, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001CFFFF, 
                    0x02, 
                    LNKC, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001CFFFF, 
                    0x03, 
                    LNKD, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001CFFFF, 
                    Zero, 
                    LNKA, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001CFFFF, 
                    One, 
                    LNKB, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001DFFFF, 
                    Zero, 
                    LNK1, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001DFFFF, 
                    One, 
                    LNKD, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001DFFFF, 
                    0x02, 
                    LNKC, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001DFFFF, 
                    0x03, 
                    LNKA, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001FFFFF, 
                    One, 
                    LNKD, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001FFFFF, 
                    One, 
                    LNKD, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001FFFFF, 
                    0x02, 
                    LNKC, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001AFFFF, 
                    Zero, 
                    LNKA, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001AFFFF, 
                    One, 
                    LNKF, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001AFFFF, 
                    0x02, 
                    LNKC, 
                    Zero
                }, 

                Package (0x04)
                {
                    0x001AFFFF, 
                    0x02, 
                    LNKC, 
                    Zero
                }
            })
            Name (APIC, Package (0x2E)
            {
                Package (0x04)
                {
                    0xFFFF, 
                    Zero, 
                    Zero, 
                    0x10
                }, 

                Package (0x04)
                {
                    0xFFFF, 
                    One, 
                    Zero, 
                    0x11
                }, 

                Package (0x04)
                {
                    0xFFFF, 
                    0x02, 
                    Zero, 
                    0x12
                }, 

                Package (0x04)
                {
                    0xFFFF, 
                    0x03, 
                    Zero, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x001BFFFF, 
                    Zero, 
                    Zero, 
                    0x16
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    Zero, 
                    Zero, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    One, 
                    Zero, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    0x02, 
                    Zero, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    0x03, 
                    Zero, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x0003FFFF, 
                    Zero, 
                    Zero, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x0003FFFF, 
                    One, 
                    Zero, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x0003FFFF, 
                    0x02, 
                    Zero, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x0003FFFF, 
                    0x03, 
                    Zero, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x0005FFFF, 
                    Zero, 
                    Zero, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x0005FFFF, 
                    One, 
                    Zero, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x0005FFFF, 
                    0x02, 
                    Zero, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x0005FFFF, 
                    0x03, 
                    Zero, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    Zero, 
                    Zero, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    One, 
                    Zero, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    0x02, 
                    Zero, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    0x03, 
                    Zero, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    Zero, 
                    Zero, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    One, 
                    Zero, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    0x02, 
                    Zero, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    0x03, 
                    Zero, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x0002FFFF, 
                    Zero, 
                    Zero, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x0002FFFF, 
                    One, 
                    Zero, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x0002FFFF, 
                    0x02, 
                    Zero, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x0002FFFF, 
                    0x03, 
                    Zero, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x001CFFFF, 
                    Zero, 
                    Zero, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x001CFFFF, 
                    One, 
                    Zero, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x001CFFFF, 
                    0x02, 
                    Zero, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x001CFFFF, 
                    0x03, 
                    Zero, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x001CFFFF, 
                    Zero, 
                    Zero, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x001CFFFF, 
                    One, 
                    Zero, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x001DFFFF, 
                    Zero, 
                    Zero, 
                    0x17
                }, 

                Package (0x04)
                {
                    0x001DFFFF, 
                    One, 
                    Zero, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x001DFFFF, 
                    0x02, 
                    Zero, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x001DFFFF, 
                    0x03, 
                    Zero, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x001FFFFF, 
                    One, 
                    Zero, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x001FFFFF, 
                    One, 
                    Zero, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x001FFFFF, 
                    0x02, 
                    Zero, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x001AFFFF, 
                    Zero, 
                    Zero, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x001AFFFF, 
                    One, 
                    Zero, 
                    0x15
                }, 

                Package (0x04)
                {
                    0x001AFFFF, 
                    0x02, 
                    Zero, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x001AFFFF, 
                    0x02, 
                    Zero, 
                    0x12
                }
            })
            Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
            {
                If (!PICF)
                {
                    Return (PICM) /* \_SB_.PCI0.PICM */
                }
                Else
                {
                    Return (APIC) /* \_SB_.PCI0.APIC */
                }
            }

            Device (PEX0)
            {
                Name (_ADR, 0x001C0000)  // _ADR: Address
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Return (0x0F)
                }

                Method (_PRW, 0, NotSerialized)  // _PRW: Power Resources for Wake
                {
                    Return (Package (0x02)
                    {
                        0x09, 
                        0x05
                    })
                }

                Name (PIC0, Package (0x04)
                {
                    Package (0x04)
                    {
                        0xFFFF, 
                        Zero, 
                        LNKA, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        One, 
                        LNKB, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x02, 
                        LNKC, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x03, 
                        LNKD, 
                        Zero
                    }
                })
                Name (API0, Package (0x04)
                {
                    Package (0x04)
                    {
                        0xFFFF, 
                        Zero, 
                        Zero, 
                        0x10
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        One, 
                        Zero, 
                        0x11
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x02, 
                        Zero, 
                        0x12
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x03, 
                        Zero, 
                        0x13
                    }
                })
                Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
                {
                    If (!PICF)
                    {
                        Return (PIC0) /* \_SB_.PCI0.PEX0.PIC0 */
                    }
                    Else
                    {
                        Return (API0) /* \_SB_.PCI0.PEX0.API0 */
                    }
                }
            }

            Device (PEX1)
            {
                Name (_ADR, 0x001C0001)  // _ADR: Address
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Return (0x0F)
                }

                Method (_PRW, 0, NotSerialized)  // _PRW: Power Resources for Wake
                {
                    Return (Package (0x02)
                    {
                        0x09, 
                        0x05
                    })
                }

                Name (PIC1, Package (0x04)
                {
                    Package (0x04)
                    {
                        0xFFFF, 
                        Zero, 
                        LNKB, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        One, 
                        LNKC, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x02, 
                        LNKD, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x03, 
                        LNKA, 
                        Zero
                    }
                })
                Name (API1, Package (0x04)
                {
                    Package (0x04)
                    {
                        0xFFFF, 
                        Zero, 
                        Zero, 
                        0x11
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        One, 
                        Zero, 
                        0x12
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x02, 
                        Zero, 
                        0x13
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x03, 
                        Zero, 
                        0x10
                    }
                })
                Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
                {
                    If (!PICF)
                    {
                        Return (PIC1) /* \_SB_.PCI0.PEX1.PIC1 */
                    }
                    Else
                    {
                        Return (API1) /* \_SB_.PCI0.PEX1.API1 */
                    }
                }
            }

            Device (PEX2)
            {
                Name (_ADR, 0x001C0002)  // _ADR: Address
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Return (0x0F)
                }

                Method (_PRW, 0, NotSerialized)  // _PRW: Power Resources for Wake
                {
                    Return (Package (0x02)
                    {
                        0x09, 
                        0x05
                    })
                }

                Name (PIC2, Package (0x04)
                {
                    Package (0x04)
                    {
                        0xFFFF, 
                        Zero, 
                        LNKC, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        One, 
                        LNKD, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x02, 
                        LNKA, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x03, 
                        LNKB, 
                        Zero
                    }
                })
                Name (API2, Package (0x04)
                {
                    Package (0x04)
                    {
                        0xFFFF, 
                        Zero, 
                        Zero, 
                        0x12
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        One, 
                        Zero, 
                        0x13
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x02, 
                        Zero, 
                        0x10
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x03, 
                        Zero, 
                        0x11
                    }
                })
                Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
                {
                    If (!PICF)
                    {
                        Return (PIC2) /* \_SB_.PCI0.PEX2.PIC2 */
                    }
                    Else
                    {
                        Return (API2) /* \_SB_.PCI0.PEX2.API2 */
                    }
                }
            }

            Device (PEX3)
            {
                Name (_ADR, 0x001C0003)  // _ADR: Address
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Return (0x0F)
                }

                Method (_PRW, 0, NotSerialized)  // _PRW: Power Resources for Wake
                {
                    Return (Package (0x02)
                    {
                        0x09, 
                        0x05
                    })
                }

                Name (PIC3, Package (0x04)
                {
                    Package (0x04)
                    {
                        0xFFFF, 
                        Zero, 
                        LNKD, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        One, 
                        LNKA, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x02, 
                        LNKB, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x03, 
                        LNKC, 
                        Zero
                    }
                })
                Name (API3, Package (0x04)
                {
                    Package (0x04)
                    {
                        0xFFFF, 
                        Zero, 
                        Zero, 
                        0x13
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        One, 
                        Zero, 
                        0x10
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x02, 
                        Zero, 
                        0x11
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x03, 
                        Zero, 
                        0x12
                    }
                })
                Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
                {
                    If (!PICF)
                    {
                        Return (PIC3) /* \_SB_.PCI0.PEX3.PIC3 */
                    }
                    Else
                    {
                        Return (API3) /* \_SB_.PCI0.PEX3.API3 */
                    }
                }
            }

            Device (PEX4)
            {
                Name (_ADR, 0x001C0004)  // _ADR: Address
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Return (0x0F)
                }

                Method (_PRW, 0, NotSerialized)  // _PRW: Power Resources for Wake
                {
                    Return (Package (0x02)
                    {
                        0x09, 
                        0x05
                    })
                }

                Name (PIC4, Package (0x04)
                {
                    Package (0x04)
                    {
                        0xFFFF, 
                        Zero, 
                        LNKA, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        One, 
                        LNKB, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x02, 
                        LNKC, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x03, 
                        LNKD, 
                        Zero
                    }
                })
                Name (API4, Package (0x04)
                {
                    Package (0x04)
                    {
                        0xFFFF, 
                        Zero, 
                        Zero, 
                        0x10
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        One, 
                        Zero, 
                        0x11
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x02, 
                        Zero, 
                        0x12
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x03, 
                        Zero, 
                        0x13
                    }
                })
                Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
                {
                    If (!PICF)
                    {
                        Return (PIC4) /* \_SB_.PCI0.PEX4.PIC4 */
                    }
                    Else
                    {
                        Return (API4) /* \_SB_.PCI0.PEX4.API4 */
                    }
                }
            }

            Device (PEX5)
            {
                Name (_ADR, 0x001C0005)  // _ADR: Address
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Return (0x0F)
                }

                Method (_PRW, 0, NotSerialized)  // _PRW: Power Resources for Wake
                {
                    Return (Package (0x02)
                    {
                        0x09, 
                        0x05
                    })
                }

                Name (PIC5, Package (0x04)
                {
                    Package (0x04)
                    {
                        0xFFFF, 
                        Zero, 
                        LNKB, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        One, 
                        LNKC, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x02, 
                        LNKD, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x03, 
                        LNKA, 
                        Zero
                    }
                })
                Name (API5, Package (0x04)
                {
                    Package (0x04)
                    {
                        0xFFFF, 
                        Zero, 
                        Zero, 
                        0x11
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        One, 
                        Zero, 
                        0x12
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x02, 
                        Zero, 
                        0x13
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x03, 
                        Zero, 
                        0x10
                    }
                })
                Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
                {
                    If (!PICF)
                    {
                        Return (PIC5) /* \_SB_.PCI0.PEX5.PIC5 */
                    }
                    Else
                    {
                        Return (API5) /* \_SB_.PCI0.PEX5.API5 */
                    }
                }
            }

            Device (HUB0)
            {
                Name (_ADR, 0x001E0000)  // _ADR: Address
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Return (0x0F)
                }

                Name (PICM, Package (0x04)
                {
                    Package (0x04)
                    {
                        0xFFFF, 
                        Zero, 
                        LNKA, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        One, 
                        LNKB, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x02, 
                        LNKC, 
                        Zero
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x03, 
                        LNKD, 
                        Zero
                    }
                })
                Name (APIC, Package (0x04)
                {
                    Package (0x04)
                    {
                        0xFFFF, 
                        Zero, 
                        Zero, 
                        0x10
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        One, 
                        Zero, 
                        0x11
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x02, 
                        Zero, 
                        0x12
                    }, 

                    Package (0x04)
                    {
                        0xFFFF, 
                        0x03, 
                        Zero, 
                        0x13
                    }
                })
                Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
                {
                    If (!PICF)
                    {
                        Return (PICM) /* \_SB_.PCI0.HUB0.PICM */
                    }
                    Else
                    {
                        Return (APIC) /* \_SB_.PCI0.HUB0.APIC */
                    }
                }

                Method (_PRW, 0, NotSerialized)  // _PRW: Power Resources for Wake
                {
                    Return (Package (0x02)
                    {
                        0x0B, 
                        0x05
                    })
                }
            }

            Device (LPCB)
            {
                Name (_ADR, 0x001F0000)  // _ADR: Address
                Method (_DSM, 4, NotSerialized)  // _DSM: Device-Specific Method
                {
                    Local0 = Package (0x02)
                        {
                            "device-id", 
                            Buffer (0x04)
                            {
                                 0x18, 0x3A, 0x00, 0x00                           // .:..
                            }
                        }
                    DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))
                    Return (Local0)
                }

                OperationRegion (LPC0, PCI_Config, 0xA4, 0x02)
                Field (LPC0, ByteAcc, NoLock, Preserve)
                {
                    AG3E,   1
                }

                OperationRegion (PREV, PCI_Config, 0x08, One)
                Scope (\)
                {
                    Field (\_SB.PCI0.LPCB.PREV, ByteAcc, NoLock, Preserve)
                    {
                        REV0,   8
                    }
                }

                OperationRegion (PIRQ, PCI_Config, 0x60, 0x04)
                Scope (\)
                {
                    Field (\_SB.PCI0.LPCB.PIRQ, ByteAcc, NoLock, Preserve)
                    {
                        PIRA,   8, 
                        PIRB,   8, 
                        PIRC,   8, 
                        PIRD,   8
                    }
                }

                OperationRegion (PIR2, PCI_Config, 0x68, 0x04)
                Scope (\)
                {
                    Field (\_SB.PCI0.LPCB.PIR2, ByteAcc, NoLock, Preserve)
                    {
                        PIRE,   8, 
                        PIRF,   8, 
                        PIRG,   8, 
                        PIRH,   8
                    }
                }

                OperationRegion (LPIO, PCI_Config, 0x80, 0x0E)
                Scope (\)
                {
                    Field (\_SB.PCI0.LPCB.LPIO, ByteAcc, NoLock, Preserve)
                    {
                        UAIO,   8, 
                        PRIO,   8, 
                        LPE1,   8, 
                        LPE2,   8, 
                        GN1L,   8, 
                        GN1H,   8, 
                        GN2L,   8, 
                        GN2H,   8
                    }

                    Method (DISD, 1, NotSerialized)
                    {
                        If ((Arg0 == Zero))
                        {
                            LPE1 &= 0xFE
                        }

                        If ((Arg0 == One))
                        {
                            LPE1 &= 0xFD
                        }

                        If ((Arg0 == 0x02))
                        {
                            LPE1 &= 0xFB
                        }

                        If ((Arg0 == 0x03))
                        {
                            LPE1 &= 0xF7
                        }

                        If ((Arg0 == 0x04))
                        {
                            LPE2 &= 0xFC
                        }

                        If ((Arg0 == 0x05))
                        {
                            LPE1 &= 0xDF
                        }

                        If ((Arg0 == 0x06))
                        {
                            GN2L &= 0xFE
                        }
                    }

                    Method (CKIO, 2, NotSerialized)
                    {
                        If ((Arg1 == Zero))
                        {
                            LPE1 |= One
                            Local0 = (UAIO & 0xF0)
                            If ((Arg0 == 0x03F8))
                            {
                                UAIO = (Local0 | Zero)
                            }

                            If ((Arg0 == 0x02F8))
                            {
                                UAIO = (Local0 | One)
                            }

                            If ((Arg0 == 0x02E8))
                            {
                                UAIO = (Local0 | 0x05)
                            }

                            If ((Arg0 == 0x03E8))
                            {
                                UAIO = (Local0 | 0x07)
                            }
                        }

                        If ((Arg1 == One))
                        {
                            LPE1 |= 0x02
                            Local0 = (UAIO & 0x0F)
                            If ((Arg0 == 0x03F8))
                            {
                                UAIO = (Local0 | Zero)
                            }

                            If ((Arg0 == 0x02F8))
                            {
                                UAIO = (Local0 | 0x10)
                            }

                            If ((Arg0 == 0x02E8))
                            {
                                UAIO = (Local0 | 0x50)
                            }

                            If ((Arg0 == 0x03E8))
                            {
                                UAIO = (Local0 | 0x70)
                            }
                        }

                        If ((Arg1 == 0x02))
                        {
                            LPE1 |= 0x04
                            Local0 = (PRIO & 0xFC)
                            If ((Arg0 == 0x0378))
                            {
                                PRIO = (Local0 | Zero)
                            }

                            If ((Arg0 == 0x0278))
                            {
                                PRIO = (Local0 | One)
                            }

                            If ((Arg0 == 0x03BC))
                            {
                                PRIO = (Local0 | 0x02)
                            }
                        }

                        If ((Arg1 == 0x03))
                        {
                            LPE1 |= 0x08
                        }

                        If ((Arg1 == 0x04))
                        {
                            If ((Arg0 == 0x0201))
                            {
                                LPE2 |= One
                            }

                            If ((Arg0 == 0x0209))
                            {
                                LPE2 |= 0x02
                            }
                        }

                        If ((Arg1 == 0x06))
                        {
                            If ((Arg0 != 0xFFFF))
                            {
                                Local0 = (Arg0 & 0xFF)
                                GN2L = (Local0 | One)
                                GN2H = (Arg0 >> 0x08)
                            }
                            Else
                            {
                                GN2H = Zero
                                GN2L = Zero
                            }
                        }
                    }
                }

                Scope (\)
                {
                    Method (SLDM, 2, NotSerialized)
                    {
                    }
                }

                Scope (^^PCI0)
                {
                    Name (SLIC, Buffer (0x9E)
                    {
                        "987134512781Genuine NVIDIA Certified SLI Ready Motherboard for GIGABYTE GA EX58 EXT1426-Copyright 2008 NVIDIA Corporation All Rights Reserved-765289891023(R)"
                    })
                    Device (WMI1)
                    {
                        Name (_HID, "PNP0C14" /* Windows Management Instrumentation Device */)  // _HID: Hardware ID
                        Name (_UID, "MXM2")  // _UID: Unique ID
                        Name (_WDG, Buffer (0x14)
                        {
                            /* 0000 */  0x3C, 0x5C, 0xCB, 0xF6, 0xAE, 0x9C, 0xBD, 0x4E,  // <\.....N
                            /* 0008 */  0xB5, 0x77, 0x93, 0x1E, 0xA3, 0x2A, 0x2C, 0xC0,  // .w...*,.
                            /* 0010 */  0x4D, 0x58, 0x01, 0x02                           // MX..
                        })
                        Method (WMMX, 3, NotSerialized)
                        {
                            CreateDWordField (Arg2, Zero, FUNC)
                            If ((FUNC == 0x41494C53))
                            {
                                Return (SLIC) /* \_SB_.PCI0.SLIC */
                            }

                            Return (Zero)
                        }
                    }
                }

                Scope (\)
                {
                    OperationRegion (SCPP, SystemIO, 0xB2, One)
                    Field (SCPP, ByteAcc, NoLock, Preserve)
                    {
                        SMIP,   8
                    }
                }

                Method (^_INI, 0, NotSerialized)  // _INI: Initialize
                {
                    If (STRC (_OS, "Microsoft Windows"))
                    {
                        SMIP = 0x56
                    }
                    ElseIf (STRC (_OS, "Microsoft Windows NT"))
                    {
                        If (CondRefOf (\_OSI, Local0))
                        {
                            Local2 = Zero
                            If (_OSI ("Windows 2001"))
                            {
                                OSFL = Zero
                                Local1 = 0x59
                                OSFX = 0x03
                                Local2 = One
                            }

                            If (_OSI ("Windows 2006")){}
                            If (_OSI ("Windows 2009")){}
                            If ((Local2 != Zero))
                            {
                                SMIP = Local1
                            }
                        }
                        Else
                        {
                            SMIP = 0x58
                            OSFL = Zero
                        }
                    }
                    Else
                    {
                        If (CondRefOf (\_OSI, Local0))
                        {
                            If (_OSI ("Linux"))
                            {
                                LINX = One
                            }

                            If (_OSI ("Darwin"))
                            {
                                AMAC = One
                            }
                        }

                        SMIP = 0x57
                        OSFL = 0x02
                    }
                }

                Scope (\)
                {
                    Method (OSTP, 0, NotSerialized)
                    {
                        If ((OSFL == One))
                        {
                            SMIP = 0x56
                        }

                        If ((OSFL == 0x02))
                        {
                            SMIP = 0x57
                        }

                        If ((OSFL == Zero))
                        {
                            Local1 = 0x58
                            If ((OSFX >= 0x03))
                            {
                                Local1 = 0x59
                            }

                            SMIP = Local1
                        }
                    }
                }

                Device (SYSR)
                {
                    Name (_HID, EisaId ("PNP0C02") /* PNP Motherboard Resources */)  // _HID: Hardware ID
                    Name (_UID, One)  // _UID: Unique ID
                    Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
                    {
                        IO (Decode16,
                            0x0010,             // Range Minimum
                            0x0010,             // Range Maximum
                            0x01,               // Alignment
                            0x10,               // Length
                            )
                        IO (Decode16,
                            0x0022,             // Range Minimum
                            0x0022,             // Range Maximum
                            0x01,               // Alignment
                            0x1E,               // Length
                            )
                        IO (Decode16,
                            0x0044,             // Range Minimum
                            0x0044,             // Range Maximum
                            0x01,               // Alignment
                            0x1C,               // Length
                            )
                        IO (Decode16,
                            0x0062,             // Range Minimum
                            0x0062,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x0065,             // Range Minimum
                            0x0065,             // Range Maximum
                            0x01,               // Alignment
                            0x0B,               // Length
                            )
                        IO (Decode16,
                            0x0074,             // Range Minimum
                            0x0074,             // Range Maximum
                            0x01,               // Alignment
                            0x0C,               // Length
                            )
                        IO (Decode16,
                            0x0091,             // Range Minimum
                            0x0091,             // Range Maximum
                            0x01,               // Alignment
                            0x03,               // Length
                            )
                        IO (Decode16,
                            0x00A2,             // Range Minimum
                            0x00A2,             // Range Maximum
                            0x01,               // Alignment
                            0x1E,               // Length
                            )
                        IO (Decode16,
                            0x00E0,             // Range Minimum
                            0x00E0,             // Range Maximum
                            0x01,               // Alignment
                            0x10,               // Length
                            )
                        IO (Decode16,
                            0x04D0,             // Range Minimum
                            0x04D0,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x0290,             // Range Minimum
                            0x0290,             // Range Maximum
                            0x01,               // Alignment
                            0x10,               // Length
                            )
                        IO (Decode16,
                            0x0800,             // Range Minimum
                            0x0800,             // Range Maximum
                            0x01,               // Alignment
                            0x80,               // Length
                            )
                        IO (Decode16,
                            0x0290,             // Range Minimum
                            0x0290,             // Range Maximum
                            0x01,               // Alignment
                            0x05,               // Length
                            )
                        IO (Decode16,
                            0x0880,             // Range Minimum
                            0x0880,             // Range Maximum
                            0x01,               // Alignment
                            0x10,               // Length
                            )
                    })
                }

                Device (PIC)
                {
                    Name (_HID, EisaId ("PNP0000") /* 8259-compatible Programmable Interrupt Controller */)  // _HID: Hardware ID
                    Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
                    {
                        IO (Decode16,
                            0x0020,             // Range Minimum
                            0x0020,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x00A0,             // Range Minimum
                            0x00A0,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                    })
                }

                Device (DMA1)
                {
                    Name (_HID, EisaId ("PNP0200") /* PC-class DMA Controller */)  // _HID: Hardware ID
                    Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
                    {
                        DMA (Compatibility, BusMaster, Transfer8, )
                            {4}
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x01,               // Alignment
                            0x10,               // Length
                            )
                        IO (Decode16,
                            0x0080,             // Range Minimum
                            0x0080,             // Range Maximum
                            0x01,               // Alignment
                            0x11,               // Length
                            )
                        IO (Decode16,
                            0x0094,             // Range Minimum
                            0x0094,             // Range Maximum
                            0x01,               // Alignment
                            0x0C,               // Length
                            )
                        IO (Decode16,
                            0x00C0,             // Range Minimum
                            0x00C0,             // Range Maximum
                            0x01,               // Alignment
                            0x20,               // Length
                            )
                    })
                }

                Device (TMR)
                {
                    Name (_HID, EisaId ("PNP0100") /* PC-class System Timer */)  // _HID: Hardware ID
                    Name (ATT5, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0040,             // Range Minimum
                            0x0040,             // Range Maximum
                            0x00,               // Alignment
                            0x04,               // Length
                            )
                        IRQNoFlags ()
                            {0}
                    })
                    Name (ATT6, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0040,             // Range Minimum
                            0x0040,             // Range Maximum
                            0x00,               // Alignment
                            0x04,               // Length
                            )
                    })
                    Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                    {
                        Return (ATT6) /* \_SB_.PCI0.LPCB.TMR_.ATT6 */
                    }
                }

                Device (HPET)
                {
                    Name (_HID, EisaId ("PNP0103") /* HPET System Timer */)  // _HID: Hardware ID
                    Name (ATT3, ResourceTemplate ()
                    {
                        IRQNoFlags ()
                            {0}
                        IRQNoFlags ()
                            {8}
                        Memory32Fixed (ReadWrite,
                            0xFED00000,         // Address Base
                            0x00000400,         // Address Length
                            )
                    })
                    Name (ATT4, Buffer (0x02)
                    {
                         0x79, 0x00                                       // y.
                    })
                    Method (_STA, 0, NotSerialized)  // _STA: Status
                    {
                        Return (0x0F)
                    }

                    Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                    {
                        Return (ATT3) /* \_SB_.PCI0.LPCB.HPET.ATT3 */
                    }
                }

                Device (RTC)
                {
                    Name (_HID, EisaId ("PNP0B00") /* AT Real-Time Clock */)  // _HID: Hardware ID
                    Name (ATT0, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0070,             // Range Minimum
                            0x0070,             // Range Maximum
                            0x00,               // Alignment
                            0x04,               // Length
                            )
                        IRQNoFlags ()
                            {8}
                    })
                    Name (ATT1, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0070,             // Range Minimum
                            0x0070,             // Range Maximum
                            0x00,               // Alignment
                            0x04,               // Length
                            )
                    })
                    Name (ATT2, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0070,             // Range Minimum
                            0x0070,             // Range Maximum
                            0x00,               // Alignment
                            0x02,               // Length
                            )
                        IRQNoFlags ()
                            {8}
                    })
                    Name (ATT3, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0070,             // Range Minimum
                            0x0070,             // Range Maximum
                            0x00,               // Alignment
                            0x02,               // Length
                            )
                    })
                    Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                    {
                        If ((OSFX >= 0x03))
                        {
                            If (HPTF)
                            {
                                Return (ATT1) /* \_SB_.PCI0.LPCB.RTC_.ATT1 */
                            }
                            Else
                            {
                                Return (ATT0) /* \_SB_.PCI0.LPCB.RTC_.ATT0 */
                            }
                        }
                        Else
                        {
                            If ((AMAC == One))
                            {
                                Return (ATT2) /* \_SB_.PCI0.LPCB.RTC_.ATT2 */
                            }

                            Return (ATT0) /* \_SB_.PCI0.LPCB.RTC_.ATT0 */
                        }
                    }
                }

                Device (SPKR)
                {
                    Name (_HID, EisaId ("PNP0800") /* Microsoft Sound System Compatible Device */)  // _HID: Hardware ID
                    Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
                    {
                        IO (Decode16,
                            0x0061,             // Range Minimum
                            0x0061,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                    })
                }

                Device (COPR)
                {
                    Name (_HID, EisaId ("PNP0C04") /* x87-compatible Floating Point Processing Unit */)  // _HID: Hardware ID
                    Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
                    {
                        IO (Decode16,
                            0x00F0,             // Range Minimum
                            0x00F0,             // Range Maximum
                            0x01,               // Alignment
                            0x10,               // Length
                            )
                        IRQNoFlags ()
                            {13}
                    })
                }

                Scope (\)
                {
                    OperationRegion (WIN1, SystemIO, 0x2E, 0x02)
                    Field (WIN1, ByteAcc, NoLock, Preserve)
                    {
                        INDP,   8, 
                        DATP,   8
                    }

                    OperationRegion (GPIO, SystemIO, 0x0800, 0x05)
                    Field (GPIO, ByteAcc, NoLock, Preserve)
                    {
                        GO01,   8, 
                        GO02,   8, 
                        GO03,   8, 
                        GO04,   8, 
                        GO05,   8
                    }

                    IndexField (INDP, DATP, ByteAcc, NoLock, Preserve)
                    {
                        Offset (0x02), 
                        CFG,    8, 
                        Offset (0x07), 
                        LDN,    8, 
                        Offset (0x20), 
                        IDHI,   8, 
                        IDLO,   8, 
                        POWC,   8, 
                        Offset (0x30), 
                        ACTR,   8, 
                        Offset (0x60), 
                        IOAH,   8, 
                        IOAL,   8, 
                        IO2H,   8, 
                        IO2L,   8, 
                        Offset (0x70), 
                        INTR,   8, 
                        Offset (0x72), 
                        INT1,   8, 
                        Offset (0x74), 
                        DMCH,   8, 
                        Offset (0xC0), 
                        GP40,   8, 
                        Offset (0xF0), 
                        OPT1,   8, 
                        OPT2,   8, 
                        OPT3,   8, 
                        OPT4,   8
                    }

                    Method (ENFG, 0, NotSerialized)
                    {
                        INDP = 0x87
                        INDP = One
                        INDP = 0x55
                        INDP = 0x55
                    }

                    Method (EXFG, 0, NotSerialized)
                    {
                        CFG = 0x02
                    }

                    Method (GSRG, 1, NotSerialized)
                    {
                        INDP = Arg0
                        Return (DATP) /* \DATP */
                    }

                    Method (SSRG, 2, NotSerialized)
                    {
                        INDP = Arg0
                        DATP = Arg1
                    }
                }

                Device (FDC0)
                {
                    Name (_HID, EisaId ("PNP0700"))  // _HID: Hardware ID
                    Method (_STA, 0, NotSerialized)  // _STA: Status
                    {
                        ENFG ()
                        LDN = Zero
                        If (ACTR)
                        {
                            EXFG ()
                            Return (0x0F)
                        }
                        ElseIf ((IOAH || IOAL))
                        {
                            EXFG ()
                            Return (0x0D)
                        }
                        Else
                        {
                            EXFG ()
                            Return (Zero)
                        }
                    }

                    Method (_DIS, 0, NotSerialized)  // _DIS: Disable Device
                    {
                        ENFG ()
                        LDN = Zero
                        ACTR = Zero
                        SLDM (DMCH, 0x04)
                        EXFG ()
                        DISD (0x03)
                    }

                    Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                    {
                        Name (BUF0, ResourceTemplate ()
                        {
                            IO (Decode16,
                                0x03F0,             // Range Minimum
                                0x03F0,             // Range Maximum
                                0x01,               // Alignment
                                0x06,               // Length
                                _Y01)
                            IO (Decode16,
                                0x03F7,             // Range Minimum
                                0x03F7,             // Range Maximum
                                0x01,               // Alignment
                                0x01,               // Length
                                )
                            IRQNoFlags ()
                                {6}
                            DMA (Compatibility, NotBusMaster, Transfer8, )
                                {2}
                        })
                        CreateByteField (BUF0, \_SB.PCI0.LPCB.FDC0._CRS._Y01._MIN, IOLO)  // _MIN: Minimum Base Address
                        CreateByteField (BUF0, 0x03, IOHI)
                        CreateByteField (BUF0, \_SB.PCI0.LPCB.FDC0._CRS._Y01._MAX, IORL)  // _MAX: Maximum Base Address
                        CreateByteField (BUF0, 0x05, IORH)
                        ENFG ()
                        EXFG ()
                        Return (BUF0) /* \_SB_.PCI0.LPCB.FDC0._CRS.BUF0 */
                    }

                    Name (_PRS, ResourceTemplate ()  // _PRS: Possible Resource Settings
                    {
                        StartDependentFnNoPri ()
                        {
                            IO (Decode16,
                                0x03F0,             // Range Minimum
                                0x03F0,             // Range Maximum
                                0x01,               // Alignment
                                0x06,               // Length
                                )
                            IO (Decode16,
                                0x03F7,             // Range Minimum
                                0x03F7,             // Range Maximum
                                0x01,               // Alignment
                                0x01,               // Length
                                )
                            IRQNoFlags ()
                                {6}
                            DMA (Compatibility, NotBusMaster, Transfer8, )
                                {2}
                        }
                        EndDependentFn ()
                    })
                    Method (_SRS, 1, NotSerialized)  // _SRS: Set Resource Settings
                    {
                        CreateByteField (Arg0, 0x02, IOLO)
                        CreateByteField (Arg0, 0x03, IOHI)
                        CreateWordField (Arg0, 0x02, IOAD)
                        CreateWordField (Arg0, 0x19, IRQW)
                        CreateByteField (Arg0, 0x1C, DMAV)
                        ENFG ()
                        LDN = Zero
                        ACTR = One
                        SLDM (DMCH, DMCH)
                        CKIO (IOAD, 0x03)
                        EXFG ()
                    }
                }

                OperationRegion (KBCT, SystemIO, 0x60, 0x05)
                Field (KBCT, ByteAcc, NoLock, Preserve)
                {
                    P060,   8, 
                    Offset (0x04), 
                    P064,   8
                }

                Device (PS2M)
                {
                    Name (_HID, EisaId ("PNP0F13") /* PS/2 Mouse */)  // _HID: Hardware ID
                    Method (_STA, 0, NotSerialized)  // _STA: Status
                    {
                        If ((PS2F == Zero))
                        {
                            Return (0x0F)
                        }
                        Else
                        {
                            Return (Zero)
                        }
                    }

                    Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                    {
                        Name (BUF1, ResourceTemplate ()
                        {
                            IRQNoFlags ()
                                {12}
                        })
                        Name (BUF2, ResourceTemplate ()
                        {
                            IO (Decode16,
                                0x0060,             // Range Minimum
                                0x0060,             // Range Maximum
                                0x01,               // Alignment
                                0x01,               // Length
                                )
                            IO (Decode16,
                                0x0064,             // Range Minimum
                                0x0064,             // Range Maximum
                                0x01,               // Alignment
                                0x01,               // Length
                                )
                            IRQNoFlags ()
                                {12}
                        })
                        If ((KBDI == One))
                        {
                            If ((OSFL == 0x02))
                            {
                                Return (BUF1) /* \_SB_.PCI0.LPCB.PS2M._CRS.BUF1 */
                            }

                            If ((OSFL == One))
                            {
                                Return (BUF1) /* \_SB_.PCI0.LPCB.PS2M._CRS.BUF1 */
                            }
                            Else
                            {
                                Return (BUF2) /* \_SB_.PCI0.LPCB.PS2M._CRS.BUF2 */
                            }
                        }
                        Else
                        {
                            Return (BUF1) /* \_SB_.PCI0.LPCB.PS2M._CRS.BUF1 */
                        }
                    }
                }

                Device (PS2K)
                {
                    Name (_HID, EisaId ("PNP0303") /* IBM Enhanced Keyboard (101/102-key, PS/2 Mouse) */)  // _HID: Hardware ID
                    Method (_STA, 0, NotSerialized)  // _STA: Status
                    {
                        If ((KBDI == One))
                        {
                            Return (Zero)
                        }
                        Else
                        {
                            Return (0x0F)
                        }
                    }

                    Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
                    {
                        IO (Decode16,
                            0x0060,             // Range Minimum
                            0x0060,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0064,             // Range Minimum
                            0x0064,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IRQNoFlags ()
                            {1}
                    })
                }

                Device (PSMR)
                {
                    Name (_HID, EisaId ("PNP0C02") /* PNP Motherboard Resources */)  // _HID: Hardware ID
                    Name (_UID, 0x03)  // _UID: Unique ID
                    Method (_STA, 0, NotSerialized)  // _STA: Status
                    {
                        If ((KBDI == Zero))
                        {
                            Return (Zero)
                        }

                        If ((PS2F == Zero))
                        {
                            If ((OSFL == 0x02))
                            {
                                Return (0x0F)
                            }

                            If ((OSFL == One))
                            {
                                Return (0x0F)
                            }

                            Return (Zero)
                        }

                        Return (Zero)
                    }

                    Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
                    {
                        IO (Decode16,
                            0x0060,             // Range Minimum
                            0x0060,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0064,             // Range Minimum
                            0x0064,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                    })
                }

                Device (PMIO)
                {
                    Name (_HID, EisaId ("PNP0C02") /* PNP Motherboard Resources */)  // _HID: Hardware ID
                    Name (_UID, 0x02)  // _UID: Unique ID
                    Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                    {
                        Name (BUF0, ResourceTemplate ()
                        {
                            IO (Decode16,
                                0x0400,             // Range Minimum
                                0x0400,             // Range Maximum
                                0x01,               // Alignment
                                0x80,               // Length
                                )
                            IO (Decode16,
                                0x0580,             // Range Minimum
                                0x0580,             // Range Maximum
                                0x01,               // Alignment
                                0x80,               // Length
                                )
                        })
                        Return (BUF0) /* \_SB_.PCI0.LPCB.PMIO._CRS.BUF0 */
                    }
                }
            }

            Device (UHC1)
            {
                Name (_ADR, 0x001D0000)  // _ADR: Address
                Method (_S3D, 0, NotSerialized)  // _S3D: S3 Device State
                {
                    If ((OSFL == 0x02))
                    {
                        Return (0x02)
                    }

                    Return (0x03)
                }

                Name (_PRW, Package (0x02)  // _PRW: Power Resources for Wake
                {
                    0x03, 
                    One
                })
            }

            Device (UHC2)
            {
                Name (_ADR, 0x001D0001)  // _ADR: Address
                Method (_S3D, 0, NotSerialized)  // _S3D: S3 Device State
                {
                    If ((OSFL == 0x02))
                    {
                        Return (0x02)
                    }

                    Return (0x03)
                }

                Name (_PRW, Package (0x02)  // _PRW: Power Resources for Wake
                {
                    0x04, 
                    One
                })
            }

            Device (UHC3)
            {
                Name (_ADR, 0x001D0002)  // _ADR: Address
                Method (_S3D, 0, NotSerialized)  // _S3D: S3 Device State
                {
                    If ((OSFL == 0x02))
                    {
                        Return (0x02)
                    }

                    Return (0x03)
                }

                Name (_PRW, Package (0x02)  // _PRW: Power Resources for Wake
                {
                    0x0C, 
                    One
                })
            }

            Device (UHC4)
            {
                Name (_ADR, 0x001A0000)  // _ADR: Address
                Method (_S3D, 0, NotSerialized)  // _S3D: S3 Device State
                {
                    If ((OSFL == 0x02))
                    {
                        Return (0x02)
                    }

                    Return (0x03)
                }

                Name (_PRW, Package (0x02)  // _PRW: Power Resources for Wake
                {
                    0x0E, 
                    One
                })
            }

            Device (UHC5)
            {
                Name (_ADR, 0x001A0001)  // _ADR: Address
                Method (_S3D, 0, NotSerialized)  // _S3D: S3 Device State
                {
                    If ((OSFL == 0x02))
                    {
                        Return (0x02)
                    }

                    Return (0x03)
                }

                Name (_PRW, Package (0x02)  // _PRW: Power Resources for Wake
                {
                    0x05, 
                    One
                })
            }

            Device (UHC6)
            {
                Name (_ADR, 0x001A0002)  // _ADR: Address
                Method (_S3D, 0, NotSerialized)  // _S3D: S3 Device State
                {
                    If ((OSFL == 0x02))
                    {
                        Return (0x02)
                    }

                    Return (0x03)
                }

                Name (_PRW, Package (0x02)  // _PRW: Power Resources for Wake
                {
                    0x20, 
                    One
                })
            }

            Device (EHC1)
            {
                Name (_ADR, 0x001D0007)  // _ADR: Address
                Method (_S3D, 0, NotSerialized)  // _S3D: S3 Device State
                {
                    If ((OSFL == 0x02))
                    {
                        Return (0x02)
                    }

                    Return (0x03)
                }

                Name (_PRW, Package (0x02)  // _PRW: Power Resources for Wake
                {
                    0x0D, 
                    One
                })
            }

            Device (EHC2)
            {
                Name (_ADR, 0x001A0007)  // _ADR: Address
                Method (_S3D, 0, NotSerialized)  // _S3D: S3 Device State
                {
                    If ((OSFL == 0x02))
                    {
                        Return (0x02)
                    }

                    Return (0x03)
                }

                Name (_PRW, Package (0x02)  // _PRW: Power Resources for Wake
                {
                    0x0D, 
                    One
                })
            }

            Device (SATA)
            {
                Name (_ADR, 0x001F0002)  // _ADR: Address
                OperationRegion (PCI, PCI_Config, 0x40, 0x20)
                Field (PCI, DWordAcc, NoLock, Preserve)
                {
                    ITM0,   16, 
                    ITM1,   16, 
                    SIT0,   4, 
                    SIT1,   4, 
                    Offset (0x08), 
                    UDC0,   2, 
                    UDC1,   2, 
                    Offset (0x0A), 
                    UDT0,   8, 
                    UDT1,   8, 
                    Offset (0x14), 
                    ICF0,   2, 
                    ICF1,   2, 
                        ,   6, 
                    WPPE,   1, 
                        ,   1, 
                    FAS0,   2, 
                    FAS1,   2
                }

                Method (_DSM, 4, NotSerialized)  // _DSM: Device-Specific Method
                {
                    Local0 = Package (0x02)
                        {
                            "device-id", 
                            Buffer (0x04)
                            {
                                 0x81, 0x26, 0x00, 0x00                           // .&..
                            }
                        }
                    DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))
                    Return (Local0)
                }

                Device (PRT0)
                {
                    Name (_ADR, Zero)  // _ADR: Address
                    Method (_GTM, 0, NotSerialized)  // _GTM: Get Timing Mode
                    {
                        Local0 = GTM (ITM0, SIT0, UDC0, UDT0, ICF0, FAS0)
                        Return (Local0)
                    }

                    Method (_STM, 3, NotSerialized)  // _STM: Set Timing Mode
                    {
                        Local0 = STM (Arg0, Arg1, Arg2)
                        CreateDWordField (Local0, Zero, ITM)
                        CreateDWordField (Local0, 0x04, SIT)
                        CreateDWordField (Local0, 0x08, UDC)
                        CreateDWordField (Local0, 0x0C, UDT)
                        CreateDWordField (Local0, 0x10, ICF)
                        CreateDWordField (Local0, 0x14, FAS)
                        UDC0 = UDC /* \_SB_.PCI0.SATA.PRT0._STM.UDC_ */
                        UDT0 = UDT /* \_SB_.PCI0.SATA.PRT0._STM.UDT_ */
                        ICF0 = ICF /* \_SB_.PCI0.SATA.PRT0._STM.ICF_ */
                        FAS0 = FAS /* \_SB_.PCI0.SATA.PRT0._STM.FAS_ */
                    }

                    Device (DRV0)
                    {
                        Name (_ADR, Zero)  // _ADR: Address
                        Name (H15F, Zero)
                        Method (_GTF, 0, NotSerialized)  // _GTF: Get Task File
                        {
                            Local0 = GTF0 (ITM0, SIT0, UDC0, UDT0, ICF0, H15F, FAS0)
                            Return (Local0)
                        }
                    }

                    Device (DRV1)
                    {
                        Name (_ADR, One)  // _ADR: Address
                        Name (H15F, Zero)
                        Method (_GTF, 0, NotSerialized)  // _GTF: Get Task File
                        {
                            Local0 = GTF1 (ITM0, SIT0, UDC0, UDT0, ICF0, H15F, FAS0)
                            Return (Local0)
                        }
                    }
                }

                Device (PRT1)
                {
                    Name (_ADR, One)  // _ADR: Address
                    Method (_GTM, 0, NotSerialized)  // _GTM: Get Timing Mode
                    {
                        Local0 = GTM (ITM1, SIT1, UDC1, UDT1, ICF1, FAS1)
                        Return (Local0)
                    }

                    Method (_STM, 3, NotSerialized)  // _STM: Set Timing Mode
                    {
                        Local0 = STM (Arg0, Arg1, Arg2)
                        CreateDWordField (Local0, Zero, ITM)
                        CreateDWordField (Local0, 0x04, SIT)
                        CreateDWordField (Local0, 0x08, UDC)
                        CreateDWordField (Local0, 0x0C, UDT)
                        CreateDWordField (Local0, 0x10, ICF)
                        CreateDWordField (Local0, 0x14, FAS)
                        UDC1 = UDC /* \_SB_.PCI0.SATA.PRT1._STM.UDC_ */
                        UDT1 = UDT /* \_SB_.PCI0.SATA.PRT1._STM.UDT_ */
                        ICF1 = ICF /* \_SB_.PCI0.SATA.PRT1._STM.ICF_ */
                        FAS1 = FAS /* \_SB_.PCI0.SATA.PRT1._STM.FAS_ */
                    }

                    Device (DRV0)
                    {
                        Name (_ADR, Zero)  // _ADR: Address
                        Name (H15F, Zero)
                        Method (_GTF, 0, NotSerialized)  // _GTF: Get Task File
                        {
                            Local0 = GTF0 (ITM1, SIT1, UDC1, UDT1, ICF1, H15F, FAS1)
                            Return (Local0)
                        }
                    }

                    Device (DRV1)
                    {
                        Name (_ADR, One)  // _ADR: Address
                        Name (H15F, Zero)
                        Method (_GTF, 0, NotSerialized)  // _GTF: Get Task File
                        {
                            Local0 = GTF1 (ITM1, SIT1, UDC1, UDT1, ICF1, H15F, FAS1)
                            Return (Local0)
                        }
                    }
                }
            }

            Method (GTM, 6, NotSerialized)
            {
                Local0 = Buffer (0x14){}
                CreateDWordField (Local0, Zero, PIO0)
                CreateDWordField (Local0, 0x04, DMA0)
                CreateDWordField (Local0, 0x08, PIO1)
                CreateDWordField (Local0, 0x0C, DMA1)
                CreateDWordField (Local0, 0x10, FLAG)
                FLAG = 0x10
                If (((Arg0 & 0x08) || !(Arg0 & One)))
                {
                    PIO0 = 0x0384
                }
                Else
                {
                    Local1 = (((Arg0 & 0x0300) >> 0x08) + ((Arg0 & 
                        0x3000) >> 0x0C))
                    PIO0 = ((0x09 - Local1) * 0x1E)
                }

                If (((Arg0 && 0x4000) || (Arg2 && One)))
                {
                    If (((Arg0 & 0x80) || !(Arg0 & 0x10)))
                    {
                        PIO1 = 0x0384
                    }
                    Else
                    {
                        Local1 = ((Arg1 & 0x03) + ((Arg1 & 0x0C) >> 0x02
                            ))
                        PIO1 = ((0x09 - Local1) * 0x1E)
                    }
                }
                Else
                {
                    PIO1 = PIO0 /* \_SB_.PCI0.GTM_.PIO0 */
                }

                If ((Arg2 & One))
                {
                    Local1 = (0x04 - (Arg3 & 0x03))
                    If ((Arg5 & One))
                    {
                        DMA0 = 0x14
                    }
                    ElseIf ((Arg4 & One))
                    {
                        DMA0 = (Local1 * 0x0F)
                    }
                    Else
                    {
                        DMA0 = (Local1 * 0x1E)
                    }
                }
                Else
                {
                    DMA0 = PIO0 /* \_SB_.PCI0.GTM_.PIO0 */
                }

                If (((Arg0 && 0x4000) || (Arg2 && One)))
                {
                    If ((Arg2 & 0x02))
                    {
                        Local1 = (0x04 - ((Arg3 & 0x30) >> 0x04))
                        If ((Arg5 & 0x02))
                        {
                            DMA1 = 0x14
                        }
                        ElseIf ((Arg4 & 0x02))
                        {
                            DMA1 = (Local1 * 0x0F)
                        }
                        Else
                        {
                            DMA1 = (Local1 * 0x1E)
                        }
                    }
                    Else
                    {
                        DMA1 = PIO1 /* \_SB_.PCI0.GTM_.PIO1 */
                    }
                }
                Else
                {
                    DMA1 = DMA0 /* \_SB_.PCI0.GTM_.DMA0 */
                }

                FLAG = Zero
                If ((Arg0 & One))
                {
                    FLAG |= 0x10
                }

                If ((Arg2 & One))
                {
                    FLAG |= One
                }

                If ((Arg0 & 0x02))
                {
                    FLAG |= 0x02
                }

                If ((Arg2 & 0x02))
                {
                    FLAG |= 0x04
                }

                If ((Arg0 & 0x20))
                {
                    FLAG |= 0x08
                }

                Return (Local0)
            }

            Method (STM, 3, NotSerialized)
            {
                Local7 = Buffer (0x18){}
                CreateDWordField (Local7, Zero, ITM)
                CreateDWordField (Local7, 0x04, SIT)
                CreateDWordField (Local7, 0x08, UDC)
                CreateDWordField (Local7, 0x0C, UDT)
                CreateDWordField (Local7, 0x10, ICF)
                CreateDWordField (Local7, 0x14, FAS)
                CreateDWordField (Arg0, Zero, PIO0)
                CreateDWordField (Arg0, 0x04, DMA0)
                CreateDWordField (Arg0, 0x08, PIO1)
                CreateDWordField (Arg0, 0x0C, DMA1)
                CreateDWordField (Arg0, 0x10, FLAG)
                Local4 = FLAG /* \_SB_.PCI0.STM_.FLAG */
                Local0 = 0x8000
                If ((Local4 & 0x02))
                {
                    Local0 |= 0x07
                }

                If ((Local4 & 0x08))
                {
                    Local0 |= 0x4000
                    Local0 |= 0x70
                }

                If (((DMA0 < PIO0) && !(Local4 & One)))
                {
                    Local0 |= 0x08
                }

                If (((DMA1 < PIO1) && !(Local4 & 0x04)))
                {
                    Local0 |= 0x80
                }

                If (PIO0)
                {
                    If ((PIO0 < 0x0384))
                    {
                        Local0 |= One
                    }
                }

                If (PIO1)
                {
                    If ((PIO1 < 0x0384))
                    {
                        Local0 |= 0x10
                    }
                }

                If ((Local4 & One))
                {
                    Local1 = PIO0 /* \_SB_.PCI0.STM_.PIO0 */
                }
                Else
                {
                    Local1 = DMA0 /* \_SB_.PCI0.STM_.DMA0 */
                }

                If (Local1)
                {
                    If ((Local1 <= 0x78))
                    {
                        Local0 |= 0x2300
                    }
                    ElseIf ((Local1 <= 0xB4))
                    {
                        Local0 |= 0x2100
                    }
                    ElseIf ((Local1 <= 0xF0))
                    {
                        Local0 |= 0x1000
                    }
                }

                ITM = Local0
                Local0 = Zero
                If ((Local4 & 0x04))
                {
                    Local1 = PIO1 /* \_SB_.PCI0.STM_.PIO1 */
                }
                Else
                {
                    Local1 = DMA1 /* \_SB_.PCI0.STM_.DMA1 */
                }

                If (Local1)
                {
                    If ((Local1 <= 0x78))
                    {
                        Local0 = 0x0B
                    }
                    ElseIf ((Local1 <= 0xB4))
                    {
                        Local0 = 0x09
                    }
                    ElseIf ((Local1 <= 0xF0))
                    {
                        Local0 = 0x04
                    }
                }

                SIT = Local0
                Local0 = Zero
                If ((Local4 & One))
                {
                    Local0 |= One
                }

                If ((Local4 & 0x04))
                {
                    Local0 |= 0x02
                }

                UDC = Local0
                Local0 = Zero
                If ((Local4 & One))
                {
                    If ((DMA0 == 0x14))
                    {
                        Local0 = One
                    }
                    Else
                    {
                        If ((DMA0 < 0x3C))
                        {
                            Local1 = (DMA0 / 0x0F)
                        }
                        Else
                        {
                            Local1 = (DMA0 / 0x1E)
                        }

                        Local0 = (0x04 - Local1)
                    }
                }

                If ((Local4 & 0x04))
                {
                    If ((DMA1 == 0x14))
                    {
                        Local1 = One
                    }
                    Else
                    {
                        If ((DMA1 < 0x3C))
                        {
                            Local1 = (DMA1 / 0x0F)
                        }
                        Else
                        {
                            Local1 = (DMA1 / 0x1E)
                        }

                        Local1 = (0x04 - Local1)
                    }

                    Local1 <<= 0x04
                    Local0 |= Local1
                }

                UDT = Local0
                Local0 = Zero
                If (DMA0)
                {
                    If ((DMA0 > 0x14))
                    {
                        If ((DMA0 < 0x3C))
                        {
                            Local0 |= One
                        }
                    }
                }

                If (DMA1)
                {
                    If ((DMA1 > 0x14))
                    {
                        If ((DMA1 < 0x3C))
                        {
                            Local0 |= 0x02
                        }
                    }
                }

                ICF = Local0
                Local0 = Zero
                If ((DMA0 == 0x14))
                {
                    Local0 |= One
                }

                If ((DMA1 == 0x14))
                {
                    Local0 |= 0x02
                }

                FAS = Local0
                Return (Local7)
            }

            Method (H15P, 1, NotSerialized)
            {
                Name (BUFF, Buffer (0x08)
                {
                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00   // ........
                })
                Local0 = Arg0
                Local1 = BUFF /* \_SB_.PCI0.H15P.BUFF */
                Concatenate (Local0, Local1, Local7)
                CreateWordField (Local7, 0x02, CYL)
                CreateWordField (Local7, 0x06, HEAD)
                CreateWordField (Local7, 0x0C, SPT)
                If (((HEAD >= 0x10) && (CYL >= 0x2000)))
                {
                    Return (SPT) /* \_SB_.PCI0.H15P.SPT_ */
                }
                Else
                {
                    Return (Zero)
                }
            }

            Method (GTF0, 7, NotSerialized)
            {
                Local7 = Buffer (0x07)
                    {
                         0x03, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF         // .......
                    }
                CreateByteField (Local7, One, MODE)
                If ((Arg2 & One))
                {
                    Local0 = (Arg3 & 0x03)
                    If ((Arg6 & One))
                    {
                        Local0 += 0x04
                    }
                    ElseIf ((Arg4 & One))
                    {
                        Local0 += 0x02
                    }

                    MODE = (Local0 | 0x40)
                }
                Else
                {
                    Local0 = (((Arg0 & 0x0300) >> 0x08) + ((Arg0 & 
                        0x3000) >> 0x0C))
                    If ((Local0 >= 0x05))
                    {
                        MODE = 0x22
                    }
                    ElseIf ((Local0 >= 0x03))
                    {
                        MODE = 0x21
                    }
                    Else
                    {
                        MODE = 0x20
                    }
                }

                Concatenate (Local7, Local7, Local6)
                If (((Arg0 & 0x08) || !(Arg0 & One)))
                {
                    If ((Arg0 & 0x02))
                    {
                        MODE = Zero
                    }
                    Else
                    {
                        MODE = One
                    }
                }
                Else
                {
                    Local0 = (((Arg0 & 0x0300) >> 0x08) + ((Arg0 & 
                        0x3000) >> 0x0C))
                    If ((Local0 >= 0x05))
                    {
                        MODE = 0x0C
                    }
                    ElseIf ((Local0 >= 0x03))
                    {
                        MODE = 0x0B
                    }
                    Else
                    {
                        MODE = 0x0A
                    }
                }

                Concatenate (Local6, Local7, Local5)
                If (Arg5)
                {
                    Local4 = Buffer (0x07)
                        {
                             0x00, 0x00, 0x00, 0x00, 0x00, 0xAE, 0x91         // .......
                        }
                    CreateByteField (Local4, One, SPT)
                    SPT = Arg5
                    Concatenate (Local5, Local4, Local6)
                    Return (Local6)
                }
                Else
                {
                    Return (Local5)
                }
            }

            Method (GTF1, 7, NotSerialized)
            {
                Local7 = Buffer (0x07)
                    {
                         0x03, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xEF         // .......
                    }
                CreateByteField (Local7, One, MODE)
                If ((Arg2 & 0x02))
                {
                    Local0 = ((Arg3 & 0x30) >> 0x04)
                    If ((Arg6 & 0x02))
                    {
                        Local0 += 0x04
                    }
                    ElseIf ((Arg4 & 0x02))
                    {
                        Local0 += 0x02
                    }

                    MODE = (Local0 | 0x40)
                }
                Else
                {
                    Local0 = (((Arg1 & 0x03) >> 0x02) + (Arg1 & 0x0C
                        ))
                    If ((Local0 >= 0x05))
                    {
                        MODE = 0x22
                    }
                    ElseIf ((Local0 >= 0x03))
                    {
                        MODE = 0x21
                    }
                    Else
                    {
                        MODE = 0x20
                    }
                }

                Concatenate (Local7, Local7, Local6)
                If (((Arg0 & 0x80) || !(Arg0 & 0x10)))
                {
                    If ((Arg0 & 0x20))
                    {
                        MODE = Zero
                    }
                    Else
                    {
                        MODE = One
                    }
                }
                Else
                {
                    Local0 = (((Arg1 & 0x03) >> 0x02) + (Arg1 & 0x0C
                        ))
                    If ((Local0 >= 0x05))
                    {
                        MODE = 0x0C
                    }
                    ElseIf ((Local0 >= 0x03))
                    {
                        MODE = 0x0B
                    }
                    Else
                    {
                        MODE = 0x0A
                    }
                }

                Concatenate (Local6, Local7, Local5)
                If (Arg5)
                {
                    Local4 = Buffer (0x07)
                        {
                             0x00, 0x00, 0x00, 0x00, 0x00, 0xBE, 0x91         // .......
                        }
                    CreateByteField (Local4, One, SPT)
                    SPT = Arg5
                    Concatenate (Local5, Local4, Local6)
                    Return (Local6)
                }
                Else
                {
                    Return (Local5)
                }
            }

            Device (SBUS)
            {
                Name (_ADR, 0x001F0003)  // _ADR: Address
                OperationRegion (PBAS, PCI_Config, 0x20, 0x02)
                Field (PBAS, ByteAcc, NoLock, Preserve)
                {
                    BAS0,   16
                }

                Method (SMBB, 0, NotSerialized)
                {
                    Local0 = (BAS0 & 0xFFFE)
                    Return (Local0)
                }

                Device (BUS0)
                {
                    Name (_CID, "smbus")  // _CID: Compatible ID
                    Name (_ADR, Zero)  // _ADR: Address
                    Device (DVL0)
                    {
                        Name (_ADR, 0x57)  // _ADR: Address
                        Name (_CID, "diagsvault")  // _CID: Compatible ID
                        Method (_DSM, 4, NotSerialized)  // _DSM: Device-Specific Method
                        {
                            Local0 = Package (0x02)
                                {
                                    "address", 
                                    0x57
                                }
                            DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))
                            Return (Local0)
                        }
                    }
                }
            }

            Device (AZAL)
            {
                Name (_ADR, 0x001B0000)  // _ADR: Address
                Method (_PRW, 0, NotSerialized)  // _PRW: Power Resources for Wake
                {
                    Return (Package (0x02)
                    {
                        0x0D, 
                        0x05
                    })
                }
            }

            Name (BUFA, ResourceTemplate ()
            {
                IRQ (Level, ActiveLow, Shared, )
                    {3,4,5,6,7,9,10,11,12,14,15}
            })
            Name (BUFB, ResourceTemplate ()
            {
                IRQ (Level, ActiveLow, Shared, )
                    {}
            })
            CreateWordField (BUFB, One, IRQV)
            Device (LNKA)
            {
                Name (_HID, EisaId ("PNP0C0F") /* PCI Interrupt Link Device */)  // _HID: Hardware ID
                Name (_UID, One)  // _UID: Unique ID
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Local0 = (PIRA & 0x80)
                    If ((Local0 == 0x80))
                    {
                        Return (0x09)
                    }
                    Else
                    {
                        Return (0x0B)
                    }
                }

                Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
                {
                    Return (BUFA) /* \_SB_.PCI0.BUFA */
                }

                Method (_DIS, 0, NotSerialized)  // _DIS: Disable Device
                {
                    PIRA |= 0x80
                }

                Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                {
                    Local0 = (PIRA & 0x0F)
                    IRQV = (One << Local0)
                    Return (BUFB) /* \_SB_.PCI0.BUFB */
                }

                Method (_SRS, 1, NotSerialized)  // _SRS: Set Resource Settings
                {
                    CreateWordField (Arg0, One, IRQ1)
                    FindSetRightBit (IRQ1, Local0)
                    Local0--
                    PIRA = Local0
                }
            }

            Device (LNKB)
            {
                Name (_HID, EisaId ("PNP0C0F") /* PCI Interrupt Link Device */)  // _HID: Hardware ID
                Name (_UID, 0x02)  // _UID: Unique ID
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Local0 = (PIRB & 0x80)
                    If ((Local0 == 0x80))
                    {
                        Return (0x09)
                    }
                    Else
                    {
                        Return (0x0B)
                    }
                }

                Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
                {
                    Return (BUFA) /* \_SB_.PCI0.BUFA */
                }

                Method (_DIS, 0, NotSerialized)  // _DIS: Disable Device
                {
                    PIRB |= 0x80
                }

                Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                {
                    Local0 = (PIRB & 0x0F)
                    IRQV = (One << Local0)
                    Return (BUFB) /* \_SB_.PCI0.BUFB */
                }

                Method (_SRS, 1, NotSerialized)  // _SRS: Set Resource Settings
                {
                    CreateWordField (Arg0, One, IRQ1)
                    FindSetRightBit (IRQ1, Local0)
                    Local0--
                    PIRB = Local0
                }
            }

            Device (LNKC)
            {
                Name (_HID, EisaId ("PNP0C0F") /* PCI Interrupt Link Device */)  // _HID: Hardware ID
                Name (_UID, 0x03)  // _UID: Unique ID
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Local0 = (PIRC & 0x80)
                    If ((Local0 == 0x80))
                    {
                        Return (0x09)
                    }
                    Else
                    {
                        Return (0x0B)
                    }
                }

                Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
                {
                    Return (BUFA) /* \_SB_.PCI0.BUFA */
                }

                Method (_DIS, 0, NotSerialized)  // _DIS: Disable Device
                {
                    PIRC |= 0x80
                }

                Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                {
                    Local0 = (PIRC & 0x0F)
                    IRQV = (One << Local0)
                    Return (BUFB) /* \_SB_.PCI0.BUFB */
                }

                Method (_SRS, 1, NotSerialized)  // _SRS: Set Resource Settings
                {
                    CreateWordField (Arg0, One, IRQ1)
                    FindSetRightBit (IRQ1, Local0)
                    Local0--
                    PIRC = Local0
                }
            }

            Device (LNKD)
            {
                Name (_HID, EisaId ("PNP0C0F") /* PCI Interrupt Link Device */)  // _HID: Hardware ID
                Name (_UID, 0x04)  // _UID: Unique ID
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Local0 = (PIRD & 0x80)
                    If ((Local0 == 0x80))
                    {
                        Return (0x09)
                    }
                    Else
                    {
                        Return (0x0B)
                    }
                }

                Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
                {
                    Return (BUFA) /* \_SB_.PCI0.BUFA */
                }

                Method (_DIS, 0, NotSerialized)  // _DIS: Disable Device
                {
                    PIRD |= 0x80
                }

                Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                {
                    Local0 = (PIRD & 0x0F)
                    IRQV = (One << Local0)
                    Return (BUFB) /* \_SB_.PCI0.BUFB */
                }

                Method (_SRS, 1, NotSerialized)  // _SRS: Set Resource Settings
                {
                    CreateWordField (Arg0, One, IRQ1)
                    FindSetRightBit (IRQ1, Local0)
                    Local0--
                    PIRD = Local0
                }
            }

            Device (LNKE)
            {
                Name (_HID, EisaId ("PNP0C0F") /* PCI Interrupt Link Device */)  // _HID: Hardware ID
                Name (_UID, 0x05)  // _UID: Unique ID
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Local0 = (PIRE & 0x80)
                    If ((Local0 == 0x80))
                    {
                        Return (0x09)
                    }
                    Else
                    {
                        Return (0x0B)
                    }
                }

                Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
                {
                    Return (BUFA) /* \_SB_.PCI0.BUFA */
                }

                Method (_DIS, 0, NotSerialized)  // _DIS: Disable Device
                {
                    PIRE |= 0x80
                }

                Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                {
                    Local0 = (PIRE & 0x0F)
                    IRQV = (One << Local0)
                    Return (BUFB) /* \_SB_.PCI0.BUFB */
                }

                Method (_SRS, 1, NotSerialized)  // _SRS: Set Resource Settings
                {
                    CreateWordField (Arg0, One, IRQ1)
                    FindSetRightBit (IRQ1, Local0)
                    Local0--
                    PIRE = Local0
                }
            }

            Device (LNKF)
            {
                Name (_HID, EisaId ("PNP0C0F") /* PCI Interrupt Link Device */)  // _HID: Hardware ID
                Name (_UID, 0x06)  // _UID: Unique ID
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Local0 = (PIRF & 0x80)
                    If ((Local0 == 0x80))
                    {
                        Return (0x09)
                    }
                    Else
                    {
                        Return (0x0B)
                    }
                }

                Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
                {
                    Return (BUFA) /* \_SB_.PCI0.BUFA */
                }

                Method (_DIS, 0, NotSerialized)  // _DIS: Disable Device
                {
                    PIRF |= 0x80
                }

                Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                {
                    Local0 = (PIRF & 0x0F)
                    IRQV = (One << Local0)
                    Return (BUFB) /* \_SB_.PCI0.BUFB */
                }

                Method (_SRS, 1, NotSerialized)  // _SRS: Set Resource Settings
                {
                    CreateWordField (Arg0, One, IRQ1)
                    FindSetRightBit (IRQ1, Local0)
                    Local0--
                    PIRF = Local0
                }
            }

            Device (LNK0)
            {
                Name (_HID, EisaId ("PNP0C0F") /* PCI Interrupt Link Device */)  // _HID: Hardware ID
                Name (_UID, 0x07)  // _UID: Unique ID
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Local0 = (PIRG & 0x80)
                    If ((Local0 == 0x80))
                    {
                        Return (0x09)
                    }
                    Else
                    {
                        Return (0x0B)
                    }
                }

                Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
                {
                    Return (BUFA) /* \_SB_.PCI0.BUFA */
                }

                Method (_DIS, 0, NotSerialized)  // _DIS: Disable Device
                {
                    PIRG |= 0x80
                }

                Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                {
                    Local0 = (PIRG & 0x0F)
                    IRQV = (One << Local0)
                    Return (BUFB) /* \_SB_.PCI0.BUFB */
                }

                Method (_SRS, 1, NotSerialized)  // _SRS: Set Resource Settings
                {
                    CreateWordField (Arg0, One, IRQ1)
                    FindSetRightBit (IRQ1, Local0)
                    Local0--
                    PIRG = Local0
                }
            }

            Device (LNK1)
            {
                Name (_HID, EisaId ("PNP0C0F") /* PCI Interrupt Link Device */)  // _HID: Hardware ID
                Name (_UID, 0x08)  // _UID: Unique ID
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Local0 = (PIRH & 0x80)
                    If ((Local0 == 0x80))
                    {
                        Return (0x09)
                    }
                    Else
                    {
                        Return (0x0B)
                    }
                }

                Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
                {
                    Return (BUFA) /* \_SB_.PCI0.BUFA */
                }

                Method (_DIS, 0, NotSerialized)  // _DIS: Disable Device
                {
                    PIRH |= 0x80
                }

                Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                {
                    Local0 = (PIRH & 0x0F)
                    IRQV = (One << Local0)
                    Return (BUFB) /* \_SB_.PCI0.BUFB */
                }

                Method (_SRS, 1, NotSerialized)  // _SRS: Set Resource Settings
                {
                    CreateWordField (Arg0, One, IRQ1)
                    FindSetRightBit (IRQ1, Local0)
                    Local0--
                    PIRH = Local0
                }
            }

            Method (_PRW, 0, NotSerialized)  // _PRW: Power Resources for Wake
            {
                Return (Package (0x02)
                {
                    0x0B, 
                    0x05
                })
            }
        }

        Device (MEM)
        {
            Name (_HID, EisaId ("PNP0C01") /* System Board */)  // _HID: Hardware ID
            Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
            {
                Name (BUF0, ResourceTemplate ()
                {
                    Memory32Fixed (ReadWrite,
                        0x000F0000,         // Address Base
                        0x00004000,         // Address Length
                        _Y03)
                    Memory32Fixed (ReadWrite,
                        0x000F4000,         // Address Base
                        0x00004000,         // Address Length
                        _Y04)
                    Memory32Fixed (ReadWrite,
                        0x000F8000,         // Address Base
                        0x00004000,         // Address Length
                        _Y05)
                    Memory32Fixed (ReadWrite,
                        0x000FC000,         // Address Base
                        0x00004000,         // Address Length
                        _Y06)
                    Memory32Fixed (ReadWrite,
                        0x00000000,         // Address Base
                        0x00010000,         // Address Length
                        _Y02)
                    Memory32Fixed (ReadWrite,
                        0x00000000,         // Address Base
                        0x000A0000,         // Address Length
                        )
                    Memory32Fixed (ReadWrite,
                        0x00100000,         // Address Base
                        0x00000000,         // Address Length
                        _Y08)
                    Memory32Fixed (ReadWrite,
                        0x00000000,         // Address Base
                        0x00000000,         // Address Length
                        _Y09)
                    Memory32Fixed (ReadWrite,
                        0xFEC00000,         // Address Base
                        0x00001000,         // Address Length
                        )
                    Memory32Fixed (ReadWrite,
                        0xFED10000,         // Address Base
                        0x0000E000,         // Address Length
                        )
                    Memory32Fixed (ReadWrite,
                        0xFED20000,         // Address Base
                        0x00070000,         // Address Length
                        )
                    Memory32Fixed (ReadWrite,
                        0xFEE00000,         // Address Base
                        0x00001000,         // Address Length
                        )
                    Memory32Fixed (ReadWrite,
                        0xFFB00000,         // Address Base
                        0x00080000,         // Address Length
                        )
                    Memory32Fixed (ReadWrite,
                        0xFFF00000,         // Address Base
                        0x00100000,         // Address Length
                        )
                    Memory32Fixed (ReadWrite,
                        0x000E0000,         // Address Base
                        0x00010000,         // Address Length
                        _Y07)
                })
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y02._BAS, ACMM)  // _BAS: Base Address
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y03._BAS, RMA1)  // _BAS: Base Address
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y03._LEN, RSS1)  // _LEN: Length
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y04._BAS, RMA2)  // _BAS: Base Address
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y04._LEN, RSS2)  // _LEN: Length
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y05._BAS, RMA3)  // _BAS: Base Address
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y05._LEN, RSS3)  // _LEN: Length
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y06._BAS, RMA4)  // _BAS: Base Address
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y06._LEN, RSS4)  // _LEN: Length
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y07._BAS, ERMA)  // _BAS: Base Address
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y07._LEN, ERMS)  // _LEN: Length
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y08._LEN, EXTM)  // _LEN: Length
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y09._BAS, USMA)  // _BAS: Base Address
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y09._LEN, USMS)  // _LEN: Length
                USMA = (AMEM + 0x00010000)
                USMS += 0x00020000
                EXTM = (AMEM - 0x00100000)
                If ((ROM1 != Zero))
                {
                    RMA2 = RMA1 /* \_SB_.MEM_._CRS.RMA1 */
                    Local0 = (ROM1 << 0x08)
                    RMA1 = Local0
                    Local0 = (RMS1 << 0x08)
                    RSS1 = Local0
                    RSS2 = 0x8000
                }

                If ((ROM2 != Zero))
                {
                    RMA3 = RMA2 /* \_SB_.MEM_._CRS.RMA2 */
                    Local0 = (ROM2 << 0x08)
                    RMA2 = Local0
                    Local0 = (RMS2 << 0x08)
                    RSS2 = Local0
                    RSS3 = 0xC000
                }

                If ((ROM3 != Zero))
                {
                    RMA4 = RMA3 /* \_SB_.MEM_._CRS.RMA3 */
                    Local0 = (ROM3 << 0x08)
                    RMA3 = Local0
                    Local0 = (RMS3 << 0x08)
                    RSS3 = Local0
                    RSS4 = 0x00010000
                }

                Local1 = ERMA /* \_SB_.MEM_._CRS.ERMA */
                If ((RMA1 > 0x000D0000))
                {
                    If ((RMA1 < 0x000F0000))
                    {
                        Local0 = (RMA1 + RSS1) /* \_SB_.MEM_._CRS.RSS1 */
                        If ((Local0 > 0x000E0000))
                        {
                            If ((Local0 > Local1))
                            {
                                Local1 = Local0
                            }
                        }
                    }
                }

                If ((RMA2 > 0x000D0000))
                {
                    If ((RMA2 < 0x000F0000))
                    {
                        Local0 = (RMA2 + RSS2) /* \_SB_.MEM_._CRS.RSS2 */
                        If ((Local0 > 0x000E0000))
                        {
                            If ((Local0 > Local1))
                            {
                                Local1 = Local0
                            }
                        }
                    }
                }

                If ((RMA3 > 0x000D0000))
                {
                    If ((RMA3 < 0x000F0000))
                    {
                        Local0 = (RMA3 + RSS3) /* \_SB_.MEM_._CRS.RSS3 */
                        If ((Local0 > 0x000E0000))
                        {
                            If ((Local0 > Local1))
                            {
                                Local1 = Local0
                            }
                        }
                    }
                }

                If ((Local1 > ERMA))
                {
                    Local0 = (Local1 - ERMA) /* \_SB_.MEM_._CRS.ERMA */
                    If ((Local0 <= 0x00010000))
                    {
                        ERMA = Local1
                        ERMS = (0x00010000 - Local0)
                    }
                }

                ACMM = AMEM /* \AMEM */
                Return (BUF0) /* \_SB_.MEM_._CRS.BUF0 */
            }
        }

        Device (FWH)
        {
            Name (_HID, EisaId ("INT0800") /* Intel 82802 Firmware Hub Device */)  // _HID: Hardware ID
            Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
            {
                Name (FWH0, ResourceTemplate ()
                {
                    Memory32Fixed (ReadWrite,
                        0xFFB80000,         // Address Base
                        0x00080000,         // Address Length
                        )
                })
                Return (FWH0) /* \_SB_.FWH_._CRS.FWH0 */
            }
        }

        Device (PCI0.EXPL)
        {
            Name (_HID, EisaId ("PNP0C02") /* PNP Motherboard Resources */)  // _HID: Hardware ID
            Name (_UID, 0x04)  // _UID: Unique ID
            Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
            {
                Name (BUF0, ResourceTemplate ()
                {
                    Memory32Fixed (ReadWrite,
                        0x1458ABCD,         // Address Base
                        0x1458ABC1,         // Address Length
                        )
                })
                Return (BUF0) /* \_SB_.PCI0.EXPL._CRS.BUF0 */
            }
        }
    }
}

