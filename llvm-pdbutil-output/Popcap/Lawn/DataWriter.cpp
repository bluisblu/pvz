# Original PDB path: c:\Popcap\Lawn\DataWriter.cpp
# Module: c:\Popcap\Lawn\releasebeta\DataWriter.obj
# 4 | S_OBJNAME [size = 52] sig=3883098683, `c:\Popcap\Lawn\ReleaseBeta\DataWriter.obj`
# 56 | S_COMPILE2 [size = 952]
# Extra Strings:
#   cwd: c:\Popcap\Lawn
#   cl: C:\Program Files\Microsoft Visual Studio 8\VC\bin\cl.exe
#   cmd: -Ox -Ob2 -Oi -Ic:\Popcap\Lawn\TodLib -Ic:\Popcap -I"C:\Program Files\Microsoft DirectX SDK (August 2006)\Include" -DBETA_BUILD -DWIN32 -DNDEBUG -D_WINDOWS -D_CRT_SECURE_NO_DEPRECATE -D_VC80_UPGRADE=0x0700 -D_MBCS -GF -FD -EHs -EHc -MT -GS- -Gy -GR- -YuPrecompile.h -Fpc:\Popcap\Lawn\ReleaseBeta\PlantsVsZombies.pch -Foc:\Popcap\Lawn\ReleaseBeta\ -Fdc:\Popcap\Lawn\ReleaseBeta\ -W4 -WX -c -Zi -TP -nologo -errorreport:prompt -I"C:\Program Files\Microsoft Visual Studio 8\VC\include" -I"C:\Program Files\Microsoft Visual Studio 8\VC\atlmfc\include" -I"C:\Program Files\Microsoft Visual Studio 8\VC\PlatformSDK\include" -I"C:\Program Files\Microsoft Visual Studio 8\SDK\v2.0\include" -I"C:\Program Files\Microsoft DirectX SDK (August 2007)\Include" -X
#   src: .\DataWriter.cpp
# Symbols:
# 1008 | S_CONSTANT [size = 20] `_BUF_SIZE`
# type = 0x1031 (std::basic_string<wchar_t,std::c...), value = 8
# 1028 | S_UDT [size = 20] `value_type`
# original type = 0x0070 (char)
# 1048 | S_UDT [size = 20] `value_type`
# original type = 0x0070 (char)
# 1068 | S_UDT [size = 36] `_Checked_iterator_base_type`
# original type = 0x0471 (wchar_t*)
# 1104 | S_UDT [size = 36] `_Checked_iterator_base_type`
# original type = 0x0471 (wchar_t*)
# 1140 | S_UDT [size = 20] `value_type`
# original type = 0x0071 (wchar_t)
# 1160 | S_UDT [size = 20] `value_type`
# original type = 0x0071 (wchar_t)
# 1180 | S_UDT [size = 16] `_Myt`
# original type = 0x2E75
# 1196 | S_UDT [size = 16] `_Myt`
# original type = 0x2E8E
# 1212 | S_GPROC32 [size = 64] `DataWriter::DataWriter`
# parent = 0, end = 1324, addr = 0001:245840, code size = 23
# type = `0x5732 (void DataWriter::())`, debug start = 2, debug end = 22, flags = none
# 1276 | S_FRAMEPROC [size = 32]
# size = 0, padding size = 0, offset to padding = 0
# bytes of callee saved registers = 0, exception handler addr = 0000:0000
# local fp reg = NONE, param fp reg = NONE
# flags = none
# 1308 | S_REGISTER [size = 16] `this`
# register = ECX, type = 0x572C (DataWriter* const)
# 1324 | S_END [size = 4]
# 1328 | S_GPROC32 [size = 68] `DataWriter::EnsureCapacity`
# parent = 0, end = 1468, addr = 0001:245872, code size = 69
# type = `0x572D (void DataWriter::(unsigned long))`, debug start = 3, debug end = 66, flags = none
# 1396 | S_FRAMEPROC [size = 32]
# size = 0, padding size = 0, offset to padding = 0
# bytes of callee saved registers = 8, exception handler addr = 0000:0000
# local fp reg = NONE, param fp reg = NONE
# flags = none
# 1428 | S_REGISTER [size = 16] `this`
# register = ECX, type = 0x572C (DataWriter* const)
# 1444 | S_BPREL32 [size = 24] `theNumBytes`
# type = 0x0022 (unsigned long), offset = 4
# 1468 | S_END [size = 4]
# 1472 | S_GPROC32 [size = 64] `DataWriter::WriteBytes`
# parent = 0, end = 1628, addr = 0001:245952, code size = 86
# type = `0x5736 (void DataWriter::(const void*, u...)`, debug start = 3, debug end = 83, flags = none
# 1536 | S_FRAMEPROC [size = 32]
# size = 0, padding size = 0, offset to padding = 0
# bytes of callee saved registers = 8, exception handler addr = 0000:0000
# local fp reg = NONE, param fp reg = NONE
# flags = inlined
# 1568 | S_REGISTER [size = 16] `this`
# register = ECX, type = 0x572C (DataWriter* const)
# 1584 | S_BPREL32 [size = 20] `theData`
# type = 0x14DB (const void*), offset = 4
# 1604 | S_BPREL32 [size = 24] `theDataLen`
# type = 0x0022 (unsigned long), offset = 8
# 1628 | S_END [size = 4]
# 1632 | S_GPROC32 [size = 64] `DataWriter::WriteLong`
# parent = 0, end = 1764, addr = 0001:246048, code size = 70
# type = `0x572D (void DataWriter::(unsigned long))`, debug start = 3, debug end = 67, flags = none
# 1696 | S_FRAMEPROC [size = 32]
# size = 0, padding size = 0, offset to padding = 0
# bytes of callee saved registers = 4, exception handler addr = 0000:0000
# local fp reg = NONE, param fp reg = NONE
# flags = none
# 1728 | S_REGISTER [size = 16] `this`
# register = ECX, type = 0x572C (DataWriter* const)
# 1744 | S_BPREL32 [size = 20] `theLong`
# type = 0x0022 (unsigned long), offset = 4
# 1764 | S_END [size = 4]
# 1768 | S_GPROC32 [size = 64] `DataWriter::WriteShort`
# parent = 0, end = 1904, addr = 0001:246128, code size = 72
# type = `0x5737 (void DataWriter::(unsigned short...)`, debug start = 3, debug end = 69, flags = none
# 1832 | S_FRAMEPROC [size = 32]
# size = 0, padding size = 0, offset to padding = 0
# bytes of callee saved registers = 4, exception handler addr = 0000:0000
# local fp reg = NONE, param fp reg = NONE
# flags = inlined
# 1864 | S_REGISTER [size = 16] `this`
# register = ECX, type = 0x572C (DataWriter* const)
# 1880 | S_BPREL32 [size = 24] `theShort`
# type = 0x0021 (unsigned short), offset = 4
# 1904 | S_END [size = 4]
# 1908 | S_GPROC32 [size = 64] `DataWriter::~DataWriter`
# parent = 0, end = 2020, addr = 0001:246208, code size = 55
# type = `0x5732 (void DataWriter::())`, debug start = 3, debug end = 54, flags = none
# 1972 | S_FRAMEPROC [size = 32]
# size = 0, padding size = 0, offset to padding = 0
# bytes of callee saved registers = 8, exception handler addr = 0000:0000
# local fp reg = NONE, param fp reg = NONE
# flags = inlined
# 2004 | S_REGISTER [size = 16] `this`
# register = ECX, type = 0x572C (DataWriter* const)
# 2020 | S_END [size = 4]
# 2024 | S_GPROC32 [size = 64] `DataWriter::OpenMemory`
# parent = 0, end = 2168, addr = 0001:246272, code size = 80
# type = `0x572D (void DataWriter::(unsigned long))`, debug start = 3, debug end = 77, flags = none
# 2088 | S_FRAMEPROC [size = 32]
# size = 0, padding size = 0, offset to padding = 0
# bytes of callee saved registers = 8, exception handler addr = 0000:0000
# local fp reg = NONE, param fp reg = NONE
# flags = none
# 2120 | S_REGISTER [size = 16] `this`
# register = ECX, type = 0x572C (DataWriter* const)
# 2136 | S_BPREL32 [size = 32] `theReserveAmount`
# type = 0x0022 (unsigned long), offset = 4
# 2168 | S_END [size = 4]
# 2172 | S_GPROC32 [size = 80] `DataWriter::`scalar deleting destructor'`
# parent = 0, end = 2300, addr = 0001:246352, code size = 75
# type = `0x5745 (void* DataWriter::(unsigned))`, debug start = 3, debug end = 72, flags = none
# 2252 | S_FRAMEPROC [size = 32]
# size = 0, padding size = 0, offset to padding = 0
# bytes of callee saved registers = 8, exception handler addr = 0000:0000
# local fp reg = NONE, param fp reg = NONE
# flags = marked inline
# 2284 | S_REGISTER [size = 16] `this`
# register = ECX, type = 0x572C (DataWriter* const)
# 2300 | S_END [size = 4]
# 2304 | S_GPROC32 [size = 64] `DataWriter::WriteString`
# parent = 0, end = 2436, addr = 0001:246432, code size = 130
# type = `0x573C (void DataWriter::(const std::bas...)`, debug start = 12, debug end = 127, flags = none
# 2368 | S_FRAMEPROC [size = 32]
# size = 0, padding size = 0, offset to padding = 0
# bytes of callee saved registers = 8, exception handler addr = 0000:0000
# local fp reg = NONE, param fp reg = NONE
# flags = none
# 2400 | S_REGISTER [size = 16] `this`
# register = ECX, type = 0x572C (DataWriter* const)
# 2416 | S_BPREL32 [size = 20] `theStr`
# type = 0x12B2 (const std::basic_string<char,std...), offset = 4
# 2436 | S_END [size = 4]
