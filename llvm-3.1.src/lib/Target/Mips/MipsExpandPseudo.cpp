//===--  MipsExpandPseudo.cpp - Expand Pseudo Instructions ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This pass expands pseudo instructions into target instructions after register
// allocation but before post-RA scheduling.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "mips-expand-pseudo"

#include "Mips.h"
#include "MipsTargetMachine.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/Target/TargetInstrInfo.h"
#include "llvm/ADT/Statistic.h"

using namespace llvm;

namespace {
  struct MipsExpandPseudo : public MachineFunctionPass {

    TargetMachine &TM;
    const TargetInstrInfo *TII;

    static char ID;
    MipsExpandPseudo(TargetMachine &tm)
      : MachineFunctionPass(ID), TM(tm), TII(tm.getInstrInfo()) { }

    virtual const char *getPassName() const {
      return "Mips PseudoInstrs Expansion";
    }

    bool runOnMachineFunction(MachineFunction &F);
    bool runOnMachineBasicBlock(MachineBasicBlock &MBB);

  private:
    void ExpandBuildPairF64(MachineBasicBlock&, MachineBasicBlock::iterator);
    void ExpandExtractElementF64(MachineBasicBlock&,
                                 MachineBasicBlock::iterator);
  };
  char MipsExpandPseudo::ID = 0;
} // end of anonymous namespace

bool MipsExpandPseudo::runOnMachineFunction(MachineFunction& F) {
  bool Changed = false;

  for (MachineFunction::iterator I = F.begin(); I != F.end(); ++I)
    Changed |= runOnMachineBasicBlock(*I);

  return Changed;
}

bool MipsExpandPseudo::runOnMachineBasicBlock(MachineBasicBlock& MBB) {

  bool Changed = false;
  for (MachineBasicBlock::iterator I = MBB.begin(); I != MBB.end();) {
    const MCInstrDesc& MCid = I->getDesc();

    switch(MCid.getOpcode()) {
    default:
      ++I;
      continue;
    case Mips::SETGP2:
      // Convert "setgp2 $globalreg, $t9" to "addu $globalreg, $v0, $t9"
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::ADDu),
              I->getOperand(0).getReg())
        .addReg(Mips::V0).addReg(I->getOperand(1).getReg());
      break;
      /*  
    case Mips::SB:
      //I->dump();
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::SW)).addOperand(I->getOperand(0))
        .addReg(Mips::K0).addOperand(I->getOperand(2));
      break;*/
    case Mips::B:
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::BGEZ)).addReg(Mips::ZERO).addOperand(I->getOperand(0));
      break;
    //stupid byte operations and half word operations
    //it seems that lb and lbu will be implemented ?
    //case Mips::LB:
    //case Mips::LBu:
    //case Mips::SB:
    case Mips::SYNC:
      I->dump();
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::NOP));
      break;

    case Mips::LHu:
    case Mips::LH:
    case Mips::ULH:
    case Mips::ULHu:
      I->dump();
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::ADDiu)).addReg(Mips::K0).addOperand(I->getOperand(1)).addImm(1);
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::LBu)).addOperand(I->getOperand(0)).addOperand(I->getOperand(1)).addOperand(I->getOperand(2));
      if(MCid.getOpcode() == Mips::LHu || MCid.getOpcode() == Mips::ULHu)
        BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::LBu)).addReg(Mips::K1).addReg(Mips::K0).addOperand(I->getOperand(2));
      else
        BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::LB)).addReg(Mips::K1).addReg(Mips::K0).addOperand(I->getOperand(2));
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::SLL)).addReg(Mips::K1).addReg(Mips::K1).addImm(8);
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::OR)).addOperand(I->getOperand(0)).addOperand(I->getOperand(0)).addReg(Mips::K1);
      break;
    case Mips::SH:
    case Mips::USH:
      I->dump();
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::ANDi)).addReg(Mips::K1).addOperand(I->getOperand(0)).addImm(0xff);
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::SB)).addReg(Mips::K1).addOperand(I->getOperand(1)).addOperand(I->getOperand(2));
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::SRA)).addReg(Mips::K1).addOperand(I->getOperand(0)).addImm(8);
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::ANDi)).addReg(Mips::K1).addReg(Mips::K1).addImm(0xff);
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::ADDiu)).addReg(Mips::K0).addOperand(I->getOperand(1)).addImm(1);
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::SB)).addReg(Mips::K1).addReg(Mips::K0).addOperand(I->getOperand(2));
      break;
    //case Mips::ULW:
    //unfold to four bytes load operations
      /*
       * lbu $t, offset($s)
       * addiu k0, $s, 1
       * lbu k1, offset(k0)
       * sll k1, k1, 8
       * or $t, $t, k1
       * addiu k0, $s, 2
       * lbu k1, offset(k0)
       * sll k1, k1, 16
       * or $t, $t, k1
       * addiu k0, $s, 3
       * lbu k1, offset(k0)
       * sll k1, k1, 24
       * or $t, $t, k1
       */
      /* 
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::LBu)).addOperand(I->getOperand(0)).getOperand(I->getOperand(1)).getOperand(I->getOperand(2));
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::ADDiu)).addReg(Mips::K0).addOperand(I->getOperand(0)).addImm(1);
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::LBu)).addReg(Mips::K1).addReg(Mips::K0).addOperand(2);
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::)
      */
       
    //  break;
    //case Mips::USW:
    //unfold to four bytes store operations

    //  break;
    case Mips::LWL:
    case Mips::LWR:
    case Mips::SWL:
    case Mips::SWR:
    case Mips::LL:
    case Mips::LL_P8:
    case Mips::SC:
    case Mips::SC_P8:

    case Mips::MOVZ_I_I:
      //FIXME it is wrong!
      //BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::BNE)).addReg(Mips::ZERO).addOperand(I->getOperand(2)).addImm(4);
      //BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::ADDu), I->getOperand(0).getReg()).addReg(I->getOperand(1).getReg()).addReg(Mips::ZERO);
      //break;
    /*
    case Mips::MULT:
    case Mips::MULT:
    case Mips::MULTu:
    case Mips::SDIV:
    case Mips::UDIV:
    case Mips::MTHI:
    case Mips::MTLO:
    case Mips::MFHI:
    case Mips::MFLO:
    */

    //no operations? exists?
    //case Mips::NOP:
    

    case Mips::ROTR:
    case Mips::ROTRV:
    case Mips::EXT:
    case Mips::INS:
    case Mips::RDHWR:
    case Mips::MUL:
    case Mips::MULT:
    case Mips::MULTu:
    case Mips::SDIV:
    case Mips::UDIV:
    case Mips::MTHI:
    case Mips::MTLO:
    case Mips::MFHI:
    case Mips::MFLO:
    case Mips::LEA_ADDiu:


      I->dump();
      ++I;
      continue;
      /*
    case Mips::BuildPairF64:
      ExpandBuildPairF64(MBB, I);
      break;
    case Mips::ExtractElementF64:
      ExpandExtractElementF64(MBB, I);
      break;
      */
    }

    // delete original instr
    MBB.erase(I++);
    Changed = true;
  }

  return Changed;
}

/*
void MipsExpandPseudo::ExpandBuildPairF64(MachineBasicBlock& MBB,
                                            MachineBasicBlock::iterator I) {
  unsigned DstReg = I->getOperand(0).getReg();
  unsigned LoReg = I->getOperand(1).getReg(), HiReg = I->getOperand(2).getReg();
  const MCInstrDesc& Mtc1Tdd = TII->get(Mips::MTC1);
  DebugLoc dl = I->getDebugLoc();
  const uint16_t* SubReg =
    TM.getRegisterInfo()->getSubRegisters(DstReg);

  // mtc1 Lo, $fp
  // mtc1 Hi, $fp + 1
  BuildMI(MBB, I, dl, Mtc1Tdd, *SubReg).addReg(LoReg);
  BuildMI(MBB, I, dl, Mtc1Tdd, *(SubReg + 1)).addReg(HiReg);
}

void MipsExpandPseudo::ExpandExtractElementF64(MachineBasicBlock& MBB,
                                               MachineBasicBlock::iterator I) {
  unsigned DstReg = I->getOperand(0).getReg();
  unsigned SrcReg = I->getOperand(1).getReg();
  unsigned N = I->getOperand(2).getImm();
  const MCInstrDesc& Mfc1Tdd = TII->get(Mips::MFC1);
  DebugLoc dl = I->getDebugLoc();
  const uint16_t* SubReg = TM.getRegisterInfo()->getSubRegisters(SrcReg);

  BuildMI(MBB, I, dl, Mfc1Tdd, DstReg).addReg(*(SubReg + N));
}
*/

/// createMipsMipsExpandPseudoPass - Returns a pass that expands pseudo
/// instrs into real instrs
FunctionPass *llvm::createMipsExpandPseudoPass(MipsTargetMachine &tm) {
  return new MipsExpandPseudo(tm);
}
