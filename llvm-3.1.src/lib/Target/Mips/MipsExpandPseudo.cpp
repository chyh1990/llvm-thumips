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
      I->dump();
      BuildMI(MBB, I, I->getDebugLoc(), TII->get(Mips::BGEZ)).addReg(Mips::ZERO).addOperand(I->getOperand(0));
      break;
    //stupid byte operations
    case Mips::LB:
    case Mips::LBu:
    case Mips::LH:
    case Mips::LHu:
    case Mips::SB:
    case Mips::SH:
    case Mips::ULH:
    case Mips::ULHu:
    case Mips::ULW:
    case Mips::USH:
    case Mips::USW:
    case Mips::LWL:
    case Mips::LWR:
    case Mips::SWL:
    case Mips::SWR:
    case Mips::SYNC:
    case Mips::LL:
    case Mips::LL_P8:
    case Mips::SC:
    case Mips::SC_P8:

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
