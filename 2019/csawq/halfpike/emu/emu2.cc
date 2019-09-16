#include <array>
#include <cstdint>
#include <functional>
#include <iostream>
#include <iomanip>
#include <optional>
#include <type_traits>
#include <unordered_map>
#include <cstring>
#include <sstream>
#include <vector>

#include <signal.h>
#include <unistd.h>

namespace bits {
// can be used for 4 or 12 bit integers
template <typename T> class machine_int {
  static_assert(std::is_same_v<T, uint8_t> || std::is_same_v<T, int8_t> ||
                std::is_same_v<T, uint16_t>);

public:
  static constexpr auto bit_mask = std::make_unsigned_t<T>(-1) << 4;

  machine_int() : value(0){};
  inline machine_int(const T val) : value(val << 4) { /* TODO check valid val */
  }
  inline machine_int<T> &operator=(const T val) { /*TODO check valid val */
    value = val << 4;
    return *this;
  }

  inline machine_int(const machine_int<T> &val) : value(val.value) {}
  inline machine_int<T> &operator=(const machine_int<T> val) {
    value = val.value;
    return *this;
  }

  // operators:
  template <typename U>
  inline machine_int<T> operator+(const machine_int<U> rhs) const {
    return ((value + rhs.value) & bit_mask) >> 4;
  }
  inline machine_int<T> operator+(const T rhs) const {
    return *this + machine_int<T>{rhs};
  }

  template <typename U>
  inline machine_int<T> &operator+=(const machine_int<U> rhs) {
    value = (*this + rhs).value;
    return *this;
  }
  inline machine_int<T> &operator+=(const T rhs) {
    return *this += machine_int<T>{rhs};
  }

  template <typename U>
  inline machine_int<T> operator-(const machine_int<U> rhs) const {
    return ((value - rhs.value) & bit_mask) >> 4;
  }
  inline machine_int<T> operator-(const T rhs) const {
    return *this - machine_int<T>{rhs};
  }

  template <typename U>
  inline machine_int<T> &operator-=(const machine_int<U> rhs) {
    value = (*this - rhs).value;
    return *this;
  }
  inline machine_int<T> &operator-=(const T rhs) {
    return *this -= machine_int<T>{rhs};
  }

  inline machine_int<T> operator<<(const size_t shift) const {
    return get() << shift;
  }
  inline machine_int<T> operator>>(const size_t shift) const {
    return get() >> shift;
  }
  inline machine_int<T> operator|(const machine_int<T> rhs) const {
    return get() | rhs.get();
  }
  inline machine_int<T> operator&(const machine_int<T> rhs) const {
    return get() & rhs.get();
  }

  inline bool operator==(const machine_int<T> rhs) const {
    return get() == rhs.get();
  }

  inline machine_int<T> &operator++() {
    *this += 1;
    return *this;
  }
  inline machine_int<T> operator++(int) {
    const auto ret = *this;
    *this += 1;
    return ret;
  }

  inline machine_int<T> &operator--() {
    *this -= 1;
    return *this;
  }
  inline machine_int<T> operator--(int) {
    const auto ret = *this;
    *this -= 1;
    return ret;
  }

  // access value
  inline T get() const { return value >> 4; }

private:
  T value; // we use the TOP 4 bits of value, and then mask off the bottom 4
};
} // namespace bits

using uint4_t = bits::machine_int<uint8_t>;
using int4_t = bits::machine_int<int8_t>;
using uint12_t = bits::machine_int<uint16_t>;

std::ostream &operator<<(std::ostream &os, uint4_t val) {
  return os << (unsigned int)val.get();
}
std::ostream &operator<<(std::ostream &os, int4_t val) {
  return os << (int)val.get();
}
std::ostream &operator<<(std::ostream &os, uint12_t val) {
  return os << (unsigned int)val.get();
}

struct Machine_State {
  uint12_t pc{0};
  std::array<uint12_t, 3> callstack{0, 0, 0};
  size_t curr_callstack_offset{0};
  std::array<uint4_t, 16> registers{0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0};
  uint4_t acc{0};
  uint4_t carry_bit{0};
  uint8_t src_reg{0}; // the register set by the SRC instruction

  std::array<uint8_t, 4096> rom{};
  std::array<std::array<uint4_t, 256>, 8> ram_banks{};
  size_t selected_ram_bank{0};

  // buffers while writing and reading with wrr and rdr instructions
  std::optional<uint4_t> write_hold{std::nullopt};
  std::optional<uint4_t> read_hold{std::nullopt};
};

enum class Opcode {
  NOP,
  JCN,
  FIM,
  SRC,
  FIN,
  JIN,
  JUN,
  JMS,
  INC,
  ISZ,
  ADD,
  SUB,
  LD,
  XCH,
  BBL,
  LDM,
  WRM,
  WMP,
  WRR,
  WPM,
  WR0,
  WR1,
  WR2,
  WR3,
  SBM,
  RDM,
  RDR,
  ADM,
  RD0,
  RD1,
  RD2,
  RD3,
  CLB,
  CLC,
  IAC,
  CMC,
  CMA,
  RAL,
  RAR,
  TCC,
  DAC,
  TCS,
  STC,
  DAA,
  KBP,
  DCL,
};

void dump_insn(Machine_State &state, uint12_t decode_pc);
void dump_insn(Machine_State &state, uint12_t decode_pc, bool show_pc);

Opcode get_opcode(Machine_State &state, uint12_t pc) {
  auto opbyte1 = state.rom.at(pc.get());
  switch (opbyte1 >> 4) {
  case 0b0000:
    return Opcode::NOP;
  case 0b0001:
    return Opcode::JCN;
  case 0b0010:
    switch (opbyte1 & 1) {
    case 0b0:
      return Opcode::FIM;
    case 0b1:
      return Opcode::SRC;
    }
  case 0b0011:
    switch (opbyte1 & 1) {
    case 0b0:
      return Opcode::FIN;
    case 0b1:
      return Opcode::JIN;
    }
  case 0b0100:
    return Opcode::JUN;
  case 0b0101:
    return Opcode::JMS;
  case 0b0110:
    return Opcode::INC;
  case 0b0111:
    return Opcode::ISZ;
  case 0b1000:
    return Opcode::ADD;
  case 0b1001:
    return Opcode::SUB;
  case 0b1010:
    return Opcode::LD;
  case 0b1011:
    return Opcode::XCH;
  case 0b1100:
    return Opcode::BBL;
  case 0b1101:
    return Opcode::LDM;
  case 0b1110:
    switch (opbyte1 & 0xf) {
    case 0b0000:
      return Opcode::WRM;
    case 0b0001:
      return Opcode::WMP;
    case 0b0010:
      return Opcode::WRR;
    case 0b0011:
      return Opcode::WR0;
    case 0b0100:
      return Opcode::WR1;
    case 0b0101:
      return Opcode::WR2;
    case 0b0110:
      return Opcode::WR3;
    case 0b0111:
      return Opcode::SBM;
    case 0b1001:
      return Opcode::RDM;
    case 0b1010:
      return Opcode::RDR;
    case 0b1011:
      return Opcode::ADM;
    case 0b1100:
      return Opcode::RD0;
    case 0b1101:
      return Opcode::RD1;
    case 0b1110:
      return Opcode::RD2;
    case 0b1111:
      return Opcode::RD3;
    }
  case 0b1111:
    switch (opbyte1 & 0xf) {
    case 0b0000:
      return Opcode::CLB;
    case 0b0001:
      return Opcode::CLC;
    case 0b0010:
      return Opcode::IAC;
    case 0b0011:
      return Opcode::CMC;
    case 0b0100:
      return Opcode::CMA;
    case 0b0101:
      return Opcode::RAL;
    case 0b0110:
      return Opcode::RAR;
    case 0b0111:
      return Opcode::TCC;
    case 0b1000:
      return Opcode::DAC;
    case 0b1001:
      return Opcode::TCS;
    case 0b1010:
      return Opcode::STC;
    case 0b1011:
      return Opcode::DAA;
    case 0b1100:
      return Opcode::KBP;
    case 0b1101:
      return Opcode::DCL;
    }
  }

  std::cerr << "Failed to decode opcode!!" << std::endl;
  abort();
}

Opcode get_current_opcode(Machine_State &state) {
  return get_opcode(state, state.pc);
}

size_t get_opcode_size(const Opcode opcode) {
  const std::unordered_map<Opcode, size_t> opcodes{
      {Opcode::NOP, 1}, {Opcode::JCN, 2}, {Opcode::FIM, 2}, {Opcode::SRC, 1},
      {Opcode::FIN, 1}, {Opcode::JIN, 1}, {Opcode::JUN, 2}, {Opcode::JMS, 2},
      {Opcode::INC, 1}, {Opcode::ISZ, 2}, {Opcode::ADD, 1}, {Opcode::SUB, 1},
      {Opcode::LD, 1},  {Opcode::XCH, 1}, {Opcode::BBL, 1}, {Opcode::LDM, 1},
      {Opcode::WRM, 1}, {Opcode::WMP, 1}, {Opcode::WRR, 1}, {Opcode::WPM, 1},
      {Opcode::WR0, 1}, {Opcode::WR1, 1}, {Opcode::WR2, 1}, {Opcode::WR3, 1},
      {Opcode::SBM, 1}, {Opcode::RDM, 1}, {Opcode::RDR, 1}, {Opcode::ADM, 1},
      {Opcode::RD0, 1}, {Opcode::RD1, 1}, {Opcode::RD2, 1}, {Opcode::RD3, 1},
      {Opcode::CLB, 1}, {Opcode::CLC, 1}, {Opcode::IAC, 1}, {Opcode::CMC, 1},
      {Opcode::CMA, 1}, {Opcode::RAL, 1}, {Opcode::RAR, 1}, {Opcode::TCC, 1},
      {Opcode::DAC, 1}, {Opcode::TCS, 1}, {Opcode::STC, 1}, {Opcode::DAA, 1},
      {Opcode::KBP, 1}, {Opcode::DCL, 1}};
  return opcodes.at(opcode);
}

//std::string get_opcode_name(const Opcode opcode) {
//  const std::unordered_map<Opcode, std::string> opcodes{
//      {Opcode::NOP, "NOP"}, {Opcode::JCN, "JCN"}, {Opcode::FIM, "FIM"},
//      {Opcode::SRC, "SRC"}, {Opcode::FIN, "FIN"}, {Opcode::JIN, "JIN"},
//      {Opcode::JUN, "JUN"}, {Opcode::JMS, "JMS"}, {Opcode::INC, "INC"},
//      {Opcode::ISZ, "ISZ"}, {Opcode::ADD, "ADD"}, {Opcode::SUB, "SUB"},
//      {Opcode::LD, "LD"},   {Opcode::XCH, "XCH"}, {Opcode::BBL, "BBL"},
//      {Opcode::LDM, "LDM"}, {Opcode::WRM, "WRM"}, {Opcode::WMP, "WMP"},
//      {Opcode::WRR, "WRR"}, {Opcode::WPM, "WPM"}, {Opcode::WR0, "WR0"},
//      {Opcode::WR1, "WR1"}, {Opcode::WR2, "WR2"}, {Opcode::WR3, "WR3"},
//      {Opcode::SBM, "SBM"}, {Opcode::RDM, "RDM"}, {Opcode::RDR, "RDR"},
//      {Opcode::ADM, "ADM"}, {Opcode::RD0, "RD0"}, {Opcode::RD1, "RD1"},
//      {Opcode::RD2, "RD2"}, {Opcode::RD3, "RD3"}, {Opcode::CLB, "CLB"},
//      {Opcode::CLC, "CLC"}, {Opcode::IAC, "IAC"}, {Opcode::CMC, "CMC"},
//      {Opcode::CMA, "CMA"}, {Opcode::RAL, "RAL"}, {Opcode::RAR, "RAR"},
//      {Opcode::TCC, "TCC"}, {Opcode::DAC, "DAC"}, {Opcode::TCS, "TCS"},
//      {Opcode::STC, "STC"}, {Opcode::DAA, "DAA"}, {Opcode::KBP, "KBP"},
//      {Opcode::DCL, "DCL"},
//  };
//  return opcodes.at(opcode);
//}

// Translated
std::string get_opcode_name(const Opcode opcode) {
  const std::unordered_map<Opcode, std::string> opcodes{
      {Opcode::NOP, "NOP"}, {Opcode::JCN, "JCN"}, {Opcode::FIM, "MOV"},
      {Opcode::SRC, "MOV"}, {Opcode::FIN, "MOV"}, {Opcode::JIN, "JMP"},
      {Opcode::JUN, "JMP"}, {Opcode::JMS, "CALL"}, {Opcode::INC, "INC"},
      {Opcode::ISZ, "INC_JZ"}, {Opcode::ADD, "ADD"}, {Opcode::SUB, "SUB"},
      {Opcode::LD, "MOV"},   {Opcode::XCH, "XCHG"}, {Opcode::BBL, "RETVAL"},
      {Opcode::LDM, "MOV"}, {Opcode::WRM, "MOV"}, {Opcode::WMP, "WMP"},
      {Opcode::WRR, "PUTCHAR"}, {Opcode::WPM, "WPM"}, {Opcode::WR0, "WR0"},
      {Opcode::WR1, "WR1"}, {Opcode::WR2, "WR2"}, {Opcode::WR3, "WR3"},
      {Opcode::SBM, "SBM"}, {Opcode::RDM, "MOV"}, {Opcode::RDR, "GETCHAR"},
      {Opcode::ADM, "ADM"}, {Opcode::RD0, "RD0"}, {Opcode::RD1, "RD1"},
      {Opcode::RD2, "RD2"}, {Opcode::RD3, "RD3"}, {Opcode::CLB, "CLB"},
      {Opcode::CLC, "CLC"}, {Opcode::IAC, "INC"}, {Opcode::CMC, "CMC"},
      {Opcode::CMA, "CMA"}, {Opcode::RAL, "RAL"}, {Opcode::RAR, "RAR"},
      {Opcode::TCC, "SETC"}, {Opcode::DAC, "DEC"}, {Opcode::TCS, "TCS"},
      {Opcode::STC, "STC"}, {Opcode::DAA, "DAA"}, {Opcode::KBP, "KBP"},
      {Opcode::DCL, "MOV"},
  };
  return opcodes.at(opcode);
}


static std::vector<uint32_t> prev_states;
static std::vector<uint32_t> states;

class dump_state {
private:
  uint32_t val;
  bool changed;
  bool is_mode {false};

public: 
  dump_state(uint32_t val) : val(val) {
    if (states.size() >= prev_states.size())
      changed = true;
    else 
      changed = (prev_states[states.size()] != val);
    states.push_back(val);
  }

  dump_state(uint4_t val) : dump_state(val.get()) {}

  dump_state(uint12_t val) : dump_state(val.get()) {}

  dump_state &mode() {
    is_mode = !is_mode;
    return *this;
  }

  friend std::ostream& operator<< (std::ostream& out, const dump_state& state);
};

std::ostream &operator<< (std::ostream& out, const dump_state& state) {
  if (state.changed) {
    out << "\x1b[1;31m";
  }

  if (state.is_mode) {
    std::cerr << std::hex << std::noshowbase << std::setfill('0') << std::setw(2) << state.val;
  } else {
    std::cerr << std::hex << std::showbase << state.val;
  }
  if (state.changed) {
    out << "\x1b[m";
  }

  return out;
}

void dump_machine_state(Machine_State &state) {
  // std::cerr << std::hex << std::showbase;

  states.clear();

  std::cerr << "\x1b[3J\x1b[H\x1b[2J";
  std::cerr << "* REGISTERS *************************" << std::endl;
  std::cerr << "pc: " << dump_state(state.pc) << ", ";
  for (size_t i = 0; i < state.registers.size(); i++) {
    if (i == 8) {
      std::cerr << std::endl << "   ";
    }
    std::cerr << 'r' << std::dec << i << ": " << dump_state(state.registers[i])
        << ", ";
  }
  std::cerr << std::endl << "   ";

  std::cerr << "src: " << dump_state(state.src_reg) << ", ";
  std::cerr << "bank: " << dump_state(state.selected_ram_bank) << ", ";
  std::cerr << "carry: " << dump_state(state.carry_bit) << ", ";
  std::cerr << "acc: " << dump_state(state.acc) << ", ";
  std::cerr << std::endl;
  

  for (size_t i = 0; i < 8; i++) {
    std::cerr << "state " << std::dec << i << ": ";
    for (size_t j = 0; j < 256; j += 2) {
      if (j > 0 && j % 64 == 0) {
        std::cerr << std::endl << "         ";
      }

      auto a = state.ram_banks.at(i).at(j).get() << 4;
      a |= state.ram_banks.at(i).at(j+1).get();
      std::cerr << dump_state(a).mode() << " ";
    }
    std::cerr << std::endl << "         ";
    std::cerr << "state " << std::dec << i << ": "
              << "stop: " << dump_state(state.ram_banks.at(i).at(158))
              << ", fail: " << dump_state(state.ram_banks.at(i).at(157)) << ", "
              << "pc: " << dump_state(state.ram_banks.at(i).at(159)) << ", ";
    for (size_t j = 0; j < 16; j++) {
      if (j == 8) {
        std::cerr << std::endl << "         ";
      }
      std::cerr << "r" << std::dec << j << ": "
                << dump_state(state.ram_banks.at(i).at(160 + j)) << ", ";
    }
    std::cerr << std::endl;
  }
  
  std::cerr << "* CODE ******************************" << std::endl;
  for (int i = 1; i <= 2; i++) {
    if (state.pc.get() < i)
      break;
    auto opc = get_opcode(state, state.pc - i);
    if (get_opcode_size(opc) == i) {
      dump_insn(state, state.pc - i, true);
    }
  }

  auto cur_decode = state.pc;
  for (int i = 0; i < 5; i++) {
    dump_insn(state, cur_decode, true);
    auto opc = get_opcode(state, cur_decode);
    cur_decode += get_opcode_size(opc);
  }

  std::cerr << "*************************************" << std::endl;

  prev_states = states;
}

std::string register_pair_name(uint8_t pair_idx) {
  return "r" + std::to_string(pair_idx * 2) + ":" + 
    std::to_string(pair_idx * 2 + 1);
}

void set_register_pair(Machine_State &state, uint8_t pair_idx, uint8_t value) {
  state.registers[pair_idx * 2] = value >> 4;
  state.registers[pair_idx * 2 + 1] = value & 0xf;
}

void dump_insn(Machine_State &state, uint12_t decode_pc, bool show_pc) {
  if (show_pc) {
    if (state.pc == decode_pc) {
      std::cerr << "==>";
    } else {
      std::cerr << "   ";
    }
  }
  dump_insn(state, decode_pc);
}
void dump_insn(Machine_State &state, uint12_t decode_pc) {
  auto pc_after = decode_pc;
  const std::unordered_map<Opcode, std::function<std::string(Machine_State &)>>
      opcode_operands{
          {Opcode::JCN,
           [decode_pc, pc_after](Machine_State &state) {
             const auto target =
                 (pc_after.get() & 0xf00) | state.rom.at((decode_pc + 1).get());

             char buff[0x100];
             sprintf(buff, "loc_%x", target);
             return std::string(buff);
           }},
          {Opcode::FIM,
           [decode_pc](Machine_State &state) {
             const auto register_pair_idx =
                 (state.rom.at(decode_pc.get()) & 0b00001110) >> 1;
             const auto data = state.rom.at((decode_pc + 1).get());
             return register_pair_name(register_pair_idx) + ", " 
               + std::to_string(data);
           }},
          {Opcode::SRC,
           [decode_pc](Machine_State &state) {
             const auto register_pair_idx =
                 (state.rom.at(decode_pc.get()) & 0b00001110) >> 1;
             return std::string("SRC, ") + register_pair_name(register_pair_idx);
           }},
          {Opcode::FIN,
           [decode_pc](Machine_State &state) {
             const auto register_pair_idx =
                 (state.rom.at(decode_pc.get()) & 0b00001110) >> 1;
             return register_pair_name(register_pair_idx) + ", [PC_HIGH + " + 
               register_pair_name(0) + "]";
           }},
          {Opcode::JIN,
           [decode_pc](Machine_State &state) {
             const auto register_pair_idx =
                 (state.rom.at(decode_pc.get()) & 0b00001110) >> 1;
             return "PC_HIGH + " + register_pair_name(register_pair_idx);
           }},
          {Opcode::JUN,
           [decode_pc](Machine_State &state) {
             // Jump unconditional
             const auto target =
                 uint12_t{(uint16_t(state.rom.at(decode_pc.get())) & 0xf) << 8 |
                          uint16_t(state.rom.at((decode_pc + 1).get()))};
             char buff[0x100];
             sprintf(buff, "loc_%x", target.get());
             return std::string(buff);
           }},
          {Opcode::JMS, // call
           [decode_pc](Machine_State &state) {
             const auto target =
                 uint12_t{(uint16_t(state.rom.at(decode_pc.get())) & 0xf) << 8 |
                          uint16_t(state.rom.at((decode_pc + 1).get()))};
             char buff[0x100];
             sprintf(buff, "loc_%x", target.get());
             return std::string(buff);
           }},
          {Opcode::INC,
           [decode_pc](Machine_State &state) {
             const auto reg_number = state.rom.at(decode_pc.get()) & 0xf;
             return std::string("r") + std::to_string(reg_number);
           }},
          {Opcode::ISZ,
           [decode_pc, pc_after](Machine_State &state) {
             const auto register_idx = state.rom.at(decode_pc.get()) & 0b1111;
             const auto target =
                 (pc_after & 0xf00) | state.rom.at((decode_pc + 1).get());

             char buff[0x100];
             sprintf(buff, "r%d, loc_%x", register_idx, target.get());
             return std::string(buff);
           }},
          {Opcode::ADD,
           [decode_pc](Machine_State &state) {
             const auto reg_num = state.rom.at(decode_pc.get()) & 0xf;
             return std::string("ACC, r") + std::to_string(reg_num);
           }},
          {Opcode::SUB,
           [decode_pc](Machine_State &state) {
             const auto reg_num = state.rom.at(decode_pc.get()) & 0xf;
             return std::string("ACC, r") + std::to_string(reg_num);
           }},
          {Opcode::LD,
           [decode_pc](Machine_State &state) {
             const auto reg_num = state.rom.at(decode_pc.get()) & 0xf;
             return std::string("ACC, r") + std::to_string(reg_num);
           }},
          {Opcode::XCH,
           [decode_pc](Machine_State &state) {
             const auto reg_num = state.rom.at(decode_pc.get()) & 0xf;
             return std::string("ACC, r") + std::to_string(reg_num);
           }},
          {Opcode::BBL,
           [decode_pc](Machine_State &state) {
             return std::to_string(state.rom.at(decode_pc.get()) & 0xf);
           }},
          {Opcode::LDM,
           [decode_pc](Machine_State &state) {
             return "acc, " + std::to_string(state.rom.at(decode_pc.get()) & 0xf);
           }},
          {Opcode::IAC,
           [decode_pc](Machine_State &state) {
             return "acc";
           }},
          {Opcode::RAR,
           [decode_pc](Machine_State &state) {
             return "acc";
           }},
          {Opcode::RAL,
           [decode_pc](Machine_State &state) {
             return "acc";
           }},
          {Opcode::DAC,
           [decode_pc](Machine_State &state) {
             return "acc";
           }},
          {Opcode::TCC,
           [decode_pc](Machine_State &state) {
             return "acc";
           }},
          {Opcode::DCL,
           [decode_pc](Machine_State &state) {
             return "BANK, acc";
           }},
          {Opcode::WRM,
           [decode_pc](Machine_State &state) {
             return "[BANK + SRC], acc";
           }},
          {Opcode::RDM,
           [decode_pc](Machine_State &state) {
             return "acc, [BANK + SRC]";
           }},
      };

  auto opcode = get_opcode(state, decode_pc);
  auto operander = opcode_operands.find(opcode);

  char buff[0x100];
  sprintf(buff, "%08x: ", decode_pc.get());
  if (opcode == Opcode::JCN) {
    const auto cond_code = state.rom.at(decode_pc.get()) & 0xf;

    std::string code;

    if (cond_code & 0b0001)
      code += "X";

    // jump if carry bit = 1
    if (cond_code & 0b0010) 
      code += "C";

    // jump if acc = 0
    if (cond_code & 0b0100) 
      code += "Z";

    // invert condition
    if (cond_code & 0b1000) 
      code = "N" + code;

    std::cerr << buff << "J" << code;
  } else {
    std::cerr << buff << get_opcode_name(opcode);
  }

  if (operander != opcode_operands.end()) {
    std::cerr << " " << (*operander).second(state);
  }
  
  std::cerr << std::endl;

}
void tick0(Machine_State &state, bool dump) {
  //dump_machine_state(state);

  const auto decode_pc = state.pc;


  const std::unordered_map<Opcode, std::function<void(Machine_State &)>>
      opcode_handlers{
          {Opcode::NOP, [decode_pc](Machine_State &state) { ; }},
          {Opcode::JCN,
           [decode_pc](Machine_State &state) {
             const auto cond_code = state.rom.at(decode_pc.get()) & 0xf;
             const auto target =
                 (state.pc.get() & 0xf00) | state.rom.at((decode_pc + 1).get());
             bool should_jump = false;
             // jump if test signal = 0
             if (cond_code & 0b0001) {
               should_jump = should_jump || false; // XXX: unimplemented
             }
             // jump if carry bit = 1
             if (cond_code & 0b0010) {
               should_jump = should_jump || (state.carry_bit == 1);
             }
             // jump if acc = 0
             if (cond_code & 0b0100) {
               should_jump = should_jump || (state.acc == 0);
             }
             // invert condition
             if (cond_code & 0b1000) {
               should_jump = !should_jump;
             }

             if (should_jump) {
               state.pc = target;
             }
           }},
          {Opcode::FIM,
           [decode_pc](Machine_State &state) {
             const auto register_pair_idx =
                 (state.rom.at(decode_pc.get()) & 0b00001110) >> 1;
             const auto data = state.rom.at((decode_pc + 1).get());
             set_register_pair(state, register_pair_idx, data);
           }},
          {Opcode::SRC,
           [decode_pc](Machine_State &state) {
             const auto register_pair_idx =
                 (state.rom.at(decode_pc.get()) & 0b00001110) >> 1;
             state.src_reg =
                 (state.registers[2 * register_pair_idx].get() << 4) |
                 (state.registers[2 * register_pair_idx + 1].get());
           }},
          {Opcode::FIN,
           [decode_pc](Machine_State &state) {
             const auto register_pair_idx =
                 (state.rom.at(decode_pc.get()) & 0b00001110) >> 1;
             const uint12_t pc_high = (state.pc & 0xf00) >> 8;
             const uint12_t high_reg = uint12_t{state.registers[0].get()};
             const uint12_t low_reg = uint12_t{state.registers[1].get()};
             const uint12_t target =
                 (pc_high << 8) | (high_reg << 4) | (low_reg);
             const auto value = state.rom.at(target.get());
             set_register_pair(state, register_pair_idx, value);
           }},
          {Opcode::JIN,
           [decode_pc](Machine_State &state) {
             const auto register_pair_idx =
                 (state.rom.at(decode_pc.get()) & 0b00001110) >> 1;
             const uint8_t low_portion =
                 (state.registers[2 * register_pair_idx].get() << 4) |
                 (state.registers[2 * register_pair_idx + 1].get());
             state.pc = (state.pc & 0xf00) | low_portion;
           }},
          {Opcode::JUN,
           [decode_pc](Machine_State &state) {
             // Jump unconditional
             const auto target =
                 uint12_t{(uint16_t(state.rom.at(decode_pc.get())) & 0xf) << 8 |
                          uint16_t(state.rom.at((decode_pc + 1).get()))};
             if (decode_pc.get() == target.get()) {
               puts("INFINITE LOOP");
               kill(getpid(), SIGINT);
             }
             state.pc = target;
           }},
          {Opcode::JMS,
           [decode_pc](Machine_State &state) {
             const auto target =
                 uint12_t{(uint16_t(state.rom.at(decode_pc.get())) & 0xf) << 8 |
                          uint16_t(state.rom.at((decode_pc + 1).get()))};
             state.curr_callstack_offset =
                 (state.curr_callstack_offset + 1) % 3;
             state.callstack[state.curr_callstack_offset] = state.pc;
             state.pc = target;
           }},
          {Opcode::INC,
           [decode_pc](Machine_State &state) {
             const auto reg_number = state.rom.at(decode_pc.get()) & 0xf;
             state.registers[reg_number]++;
           }},
          {Opcode::ISZ,
           [decode_pc](Machine_State &state) {
             const auto register_idx = state.rom.at(decode_pc.get()) & 0b1111;
             const auto target =
                 (state.pc & 0xf00) | state.rom.at((decode_pc + 1).get());
             state.registers[register_idx]++;
             if (state.registers[register_idx] == 0) {
               state.pc = target;
             }
           }},
          {Opcode::ADD,
           [decode_pc](Machine_State &state) {
             const auto reg_num = state.rom.at(decode_pc.get()) & 0xf;
             const auto reg = state.registers[reg_num];
             const auto will_carry = (reg.get() + state.acc.get()) > 0xf;
             state.acc += reg;
             state.carry_bit = will_carry;
           }},
          {Opcode::SUB,
           [decode_pc](Machine_State &state) {
             const auto reg_num = state.rom.at(decode_pc.get()) & 0xf;
             // we do the subtract in full-width by adding complements of the
             // reg and state, then grab the bits we want from the result
             const auto result_full = state.acc.get() +
                                      ~state.registers[reg_num].get() +
                                      (~state.carry_bit.get() & 0b1);
             state.carry_bit = (result_full & 0x10) >> 4;
             state.acc = result_full & 0xf;
           }},
          {Opcode::LD,
           [decode_pc](Machine_State &state) {
             const auto reg_num = state.rom.at(decode_pc.get()) & 0xf;
             state.acc = state.registers[reg_num];
           }},
          {Opcode::XCH,
           [decode_pc](Machine_State &state) {
             const auto reg_number = state.rom.at(decode_pc.get()) & 0xf;
             std::swap(state.registers[reg_number], state.acc);
           }},
          {Opcode::BBL,
           [decode_pc](Machine_State &state) {
             state.acc = state.rom.at(decode_pc.get()) & 0xf;
             state.pc = state.callstack.at(state.curr_callstack_offset);
             // adjust callstack offset, wrapping around appropriately.
             if (state.curr_callstack_offset == 0) {
               state.curr_callstack_offset = 2;
             } else {
               state.curr_callstack_offset--;
             }
           }},
          {Opcode::LDM,
           [decode_pc](Machine_State &state) {
             state.acc = uint4_t{state.rom.at(decode_pc.get()) & 0xf};
           }},
          {Opcode::WRM,
           [decode_pc](Machine_State &state) {
             state.ram_banks[state.selected_ram_bank][state.src_reg] =
                 state.acc;
           }},
          {Opcode::WMP,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: FIN" << std::endl;
             abort();
           }},
          {Opcode::WRR,
           [decode_pc](Machine_State &state) {
             // this is technically not *quite* what this instruction is
             // supposed to do, but y'know, gotta get io and this does io.
             if (state.write_hold.has_value()) {
               char c = (state.write_hold->get() << 4) | state.acc.get();
               putchar(c);
               state.write_hold = std::nullopt;
             } else {
               state.write_hold = state.acc;
             }
           }},
          {Opcode::WPM,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: WPM" << std::endl;
             abort();
           }},
          {Opcode::WR0,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: WR0" << std::endl;
             abort();
           }},
          {Opcode::WR1,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: WR1" << std::endl;
             abort();
           }},
          {Opcode::WR2,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: WR2" << std::endl;
             abort();
           }},
          {Opcode::WR3,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: WR3" << std::endl;
             abort();
           }},
          {Opcode::SBM,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: SBM" << std::endl;
             abort();
           }},
          {Opcode::RDM,
           [decode_pc](Machine_State &state) {
             state.acc =
                 state.ram_banks[state.selected_ram_bank][state.src_reg];
           }},
          {Opcode::RDR,
           [decode_pc](Machine_State &state) {
             // much like WRR, this isn't quite the intended behavior of this
             // instruction. We're basically using it as a "read a character
             // from stdin, one nibble at a time" function
             if (state.read_hold.has_value()) {
               state.acc = *(state.read_hold);
               state.read_hold = std::nullopt;
             } else {
               uint8_t c = uint8_t(getchar());
               state.acc = c >> 4;
               state.read_hold = c & 0xf;
             }
           }},
          {Opcode::ADM,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: ADM" << std::endl;
             abort();
           }},
          {Opcode::RD0,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: RD0" << std::endl;
             abort();
           }},
          {Opcode::RD1,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: RD1" << std::endl;
             abort();
           }},
          {Opcode::RD2,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: RD2" << std::endl;
             abort();
           }},
          {Opcode::RD3,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: RD3" << std::endl;
             abort();
           }},
          {Opcode::CLB,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: CLB" << std::endl;
             abort();
           }},
          {Opcode::CLC,
           [decode_pc](Machine_State &state) { state.carry_bit = 0; }},
          {Opcode::IAC,
           [decode_pc](Machine_State &state) {
             state.acc++;
             if (state.acc == 0) {
               state.carry_bit = 1;
             } else {
               state.carry_bit = 0;
             }
           }},
          {Opcode::CMC,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: CMC" << std::endl;
             abort();
           }},
          {Opcode::CMA,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: CMA" << std::endl;
             abort();
           }},
          {Opcode::RAL,
           [decode_pc](Machine_State &state) {
             const auto old_acc = state.acc;
             const auto old_carry = state.carry_bit;
             state.acc = (old_acc << 1) | old_carry;
             state.carry_bit = old_acc >> 3;
           }},
          {Opcode::RAR,
           [decode_pc](Machine_State &state) {
             const auto old_acc = state.acc;
             const auto old_carry = state.carry_bit;
             state.acc = (old_acc >> 1) | (old_carry << 3);
             state.carry_bit = old_acc & 0b1;
           }},
          {Opcode::TCC,
           [decode_pc](Machine_State &state) {
             state.acc = state.carry_bit;
             state.carry_bit = 0;
           }},
          {Opcode::DAC,
           [decode_pc](Machine_State &state) {
             const auto old_value = state.acc;
             state.acc--;
             if ((old_value & 0b1000).get() != 0 &&
                 (state.acc & 0b1000).get() == 0) {
               state.carry_bit = 0;
             } else {
               state.carry_bit = 1;
             }
           }},
          {Opcode::TCS,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: TCS" << std::endl;
             abort();
           }},
          {Opcode::STC,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: STC" << std::endl;
             abort();
           }},
          {Opcode::DAA,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: DAA" << std::endl;
             abort();
           }},
          {Opcode::KBP,
           [decode_pc](Machine_State &state) {
             std::cout << "unimpl: KBP" << std::endl;
             abort();
           }},
          {Opcode::DCL,
           [decode_pc](Machine_State &state) {
             const auto bank_num = state.acc & 0b0111;
             state.selected_ram_bank = size_t(bank_num.get());
           }},
      };

  if (dump) {
    dump_insn(state, state.pc);
  }

  auto opcode = get_current_opcode(state);

  state.pc += get_opcode_size(opcode);
  opcode_handlers.at(opcode)(state);
}

static bool interrupted = false;
void tick(Machine_State &state, bool dump) {
  interrupted = false;
  tick0(state, dump);
  if (interrupted)
    std::cerr << "Interrupted!" << std::endl;
}

void tick(Machine_State &state) {
  tick(state, false);
}


static void sig_interrupt(int num) {
  interrupted = true;
}

static std::vector<long> bps;
bool reached_bp(Machine_State &state) {
  for (auto bp : bps) {
    if (bp == state.pc.get()) {
      return true;
    }
  }
  return false;
}

void debug_once(Machine_State &state) {
  static std::string prev;
  static bool running = false;
  std::string tok;

  std::cerr << "tinydb> ";
  if (!std::getline(std::cin, tok)) 
    exit(0);

  if (!tok.size())
    tok = prev;
  else 
    prev = tok;

  std::stringstream ss(tok);

  tok = "";
  ss >> tok;

  if (!tok.size())
    return;

  if (tok == "break") {
    ss >> tok;
    long addr = strtol(tok.c_str(), 0, 0);
    bps.push_back(addr);
    std::cerr << "Created breakpoint " << (bps.size() - 1) << std::endl;
  } else if (tok == "run" || tok == "r" || tok == "c" || tok == "continue") {
    running = true;
    interrupted = false;
    while (!interrupted) {
      tick(state);

      if (reached_bp(state)) {
        std::cerr << "Hit breakpoint!" << std::endl;
        break;
      }
    }
    dump_machine_state(state);
  } else if (tok == "del") {
    char *end;
    ss >> tok;
    long del = strtol(tok.c_str(), &end, 0);
    if (*end || del < 0 || del >= bps.size()) {
      std::cerr << "Invalid breakpoint" << std::endl;
      return;
    }
      
    bps[del] = -1;
  } else if (tok == "si" || tok == "stepi" || tok == "step") {
    if (!running) {
      std::cerr << "Not running" << std::endl;
      return;
    }
step:
    tick(state);
    dump_machine_state(state);
  } else if (tok == "ni" || tok == "nexti" || tok == "next") {
    if (!running) {
      std::cerr << "Not running" << std::endl;
      return;
    }

    auto opc = get_current_opcode(state);
    if (opc != Opcode::JMS)
      goto step;

    auto next = state.pc + get_opcode_size(get_current_opcode(state));
    interrupted = false;
    while (!interrupted) {
      tick(state);

      if (reached_bp(state)) {
        std::cerr << "Hit breakpoint!" << std::endl;
        break;
      }

      if (state.pc == next) {
        break;
      }
    }
    dump_machine_state(state);
  } else if (tok == "set") {
    std::string iden;
    ss >> iden;

    ss >> tok;
    long val = strtol(tok.c_str(), 0, 0);

    if (iden[0] == 'r') 
      state.registers[atoi(iden.substr(1, iden.size() - 1).c_str())] = val;
    else if (iden == "src") 
      state.src_reg = val;
    else if (iden == "acc")
      state.acc = val;
    else if (iden == "pc")
      state.pc = val;
    else 
      std::cerr << "Bad Identifier!" <<std::endl;
    
  } else if (tok == "quit") {
    exit(0);
  } else if (tok == "start") {
    dump_machine_state(state);
    running = true;
  } else {
    std::cerr << "Bad Command!" << std::endl;
  }
}

int main(int argc, char **argv) {
  // unbuffer
  setbuf(stdin, NULL);
  setbuf(stdout, NULL);

  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <rom file>" << std::endl;
    return 1;
  }


  Machine_State state;
  if (argc >= 3) {
    state.pc = strtol(argv[2], 0, 0);
  }

  // load rom:
  FILE *fd = fopen(argv[1], "r");
  if (!fd) {
    perror("Open:");
    return 1;
  }
  if (fread(state.rom.data(), 1, state.rom.size(), fd) != state.rom.size()) {
    perror("Read:");
    return 1;
  }

  if (strstr(argv[0], "tinydb")) {
    signal(SIGINT, sig_interrupt);
    signal(SIGABRT, sig_interrupt);
    while (true) {
      debug_once(state);
    }
  } else if (strstr(argv[0], "dump")) {
    // emulate and dump
    while (true) {
      tick(state, true);
    }
  } else {
    // emulate
    while (true) {
      tick(state);
    }
  }
}
