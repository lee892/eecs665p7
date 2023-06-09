#include <ostream>
#include "3ac.hpp"

namespace jeff{

void IRProgram::allocGlobals(){
	//Choose a label for each global
	for (auto itr : globals) {
		SemSymbol* semSymbol = itr.first;
		SymOpd* symOpd = itr.second;
		std::string lbl = "gbl_" + semSymbol->getName();
		symOpd->setMemoryLoc(lbl);
	}
}

void IRProgram::datagenX64(std::ostream& out){
	out << ".data\n";
	for (auto itr : globals) {
		if (itr.first->getName() == "console") { continue; }
		SymOpd* symOpd = itr.second;
		out << symOpd->getMemoryLoc() << ": .quad 0\n";
	}

	for (auto itr : strings) {
		LitOpd* strLbl = itr.first;
		std::string myContent = itr.second;
		out << strLbl->valString() + ": .asciz "
			<< myContent << "\n";
	}
	//Put this directive after you write out strings
	// so that everything is aligned to a quadword value
	// again
	out << ".align 8\n";
}

void IRProgram::toX64(std::ostream& out){
	allocGlobals();
	datagenX64(out);

	out << ".globl main\n";
	out << ".text\n";
	// Iterate over each procedure and codegen it
	for (auto p : *procs) {
		p->toX64(out);
	}
}

void Procedure::allocLocals(){
	//Allocate space for locals
	// Iterate over each procedure and codegen it
	int count = -24;
	for (auto itr : locals) {
		SymOpd* symOpd = itr.second;
		std::string memLoc = std::to_string(count) + "(%rbp)";
		symOpd->setMemoryLoc(memLoc);
		count -= int(symOpd->getWidth());
	}
	for (auto temp : temps) {
		AuxOpd* auxOpd = temp;
		std::string memLoc = std::to_string(count) + "(%rbp)";
		auxOpd->setMemoryLoc(memLoc);
		count -= int(auxOpd->getWidth());
	}
	for (auto formal : formals) {
		SymOpd* symOpd = formal;
		std::string memLoc = std::to_string(count) + "(%rbp)";
		symOpd->setMemoryLoc(memLoc);
		count -= int(symOpd->getWidth());
	}
}

void Procedure::toX64(std::ostream& out){
	//Allocate all locals
	allocLocals();

	enter->codegenLabels(out);
	enter->codegenX64(out);
	out << "#Fn body " << myName << "\n";
	for (auto quad : *bodyQuads){
		quad->codegenLabels(out);
		out << "#" << quad->toString() << "\n";
		quad->codegenX64(out);
	}
	out << "#Fn epilogue " << myName << "\n";
	leave->codegenLabels(out);
	leave->codegenX64(out);
}

void Quad::codegenLabels(std::ostream& out){
	if (labels.empty()){ return; }

	size_t numLabels = labels.size();
	size_t labelIdx = 0;
	for ( Label * label : labels){
		out << label->getName() << ": ";
		if (labelIdx != numLabels - 1){ out << "\n"; }
		labelIdx++;
	}
}

void BinOpQuad::codegenX64(std::ostream& out){
	src1->genLoadVal(out, A);
	src2->genLoadVal(out, B);
	BinOp op = getOp();
	switch (op) {
		case BinOp::ADD64:
			out << "addq " << RegUtils::reg64(A) << ", " << RegUtils::reg64(B) << "\n";
			break;
		case BinOp::SUB64:
			out << "subq " << RegUtils::reg64(B) << ", " << RegUtils::reg64(A) << "\n";
			dst->genStoreVal(out, A);
			return;
		case BinOp::DIV64:
			out << "cqto\n";
			out << "idivq " << RegUtils::reg64(B) << "\n";
			dst->genStoreVal(out, A);
			return;
		case BinOp::MULT64:
			out << "imulq " << RegUtils::reg64(B) << "\n";
			dst->genStoreVal(out, A);
			return;
		case BinOp::EQ64:
			out << "cmpq " << RegUtils::reg64(A) << ", " << RegUtils::reg64(B) << "\n";
			out << "movq $0, " << RegUtils::reg64(B) << "\n";
			out << "sete " << RegUtils::reg8(B) << "\n";
			break;
		case BinOp::NEQ64:
			out << "cmpq " << RegUtils::reg64(A) << ", " << RegUtils::reg64(B) << "\n";
			out << "movq $0, " << RegUtils::reg64(B) << "\n";
			out << "setne " << RegUtils::reg8(B) << "\n";
			break;
		case BinOp::LT64:
			out << "cmpq " << RegUtils::reg64(B) << ", " << RegUtils::reg64(A) << "\n";
			out << "movq $0, " << RegUtils::reg64(B) << "\n";
			out << "setl " << RegUtils::reg8(B) << "\n";
			break;
		case BinOp::GT64:
			out << "cmpq " << RegUtils::reg64(B) << ", " << RegUtils::reg64(A) << "\n";
			out << "movq $0, " << RegUtils::reg64(B) << "\n";
			out << "setg " << RegUtils::reg8(B) << "\n";
			break;
		case BinOp::LTE64:
			out << "cmpq " << RegUtils::reg64(B) << ", " << RegUtils::reg64(A) << "\n";
			out << "movq $0, " << RegUtils::reg64(B) << "\n";
			out << "setle " << RegUtils::reg8(B) << "\n";
			break;
		case BinOp::GTE64:
			out << "cmpq " << RegUtils::reg64(B) << ", " << RegUtils::reg64(A) << "\n";
			out << "movq $0, " << RegUtils::reg64(B) << "\n";
			out << "setge " << RegUtils::reg8(B) << "\n";
			break;
		case BinOp::OR64:
			out << "orq " << RegUtils::reg64(A) << ", " << RegUtils::reg64(B) << "\n";
			break;
		case BinOp::AND64:
			out << "andq " << RegUtils::reg64(A) << ", " << RegUtils::reg64(B) << "\n";
			break;
	}
	dst->genStoreVal(out, B);
}

void UnaryOpQuad::codegenX64(std::ostream& out){
	src->genLoadVal(out, A);
	UnaryOp op = getOp();
	switch (op) {
		case UnaryOp::NEG64:
			out << "negq " << RegUtils::reg64(A) << "\n";
			break;
		case UnaryOp::NOT64:
			out << "cmpq $0, " << RegUtils::reg64(A) << "\n";
			out << "sete " << RegUtils::reg8(A) << "\n";
			break;
	}
	dst->genStoreVal(out, A);
}

void AssignQuad::codegenX64(std::ostream& out){
	src->genLoadVal(out, A);
	dst->genStoreVal(out, A);
}

void ReadQuad::codegenX64(std::ostream& out){
	if (myHandle->locString() != "console") {
		myHandle->genLoadVal(out, DI);
	} else {
		out << "movq $1, %rdi\n";
	}
	if (myDstType->isInt()) {
		out << "callq stdJeff_readInt\n";
	} else if (myDstType->isFile()) {
		myDst->genLoadVal(out, SI);
		out << "callq stdJeff_readString\n";
		return;
	} else if (myDstType->isBool()) {
		out << "callq stdJeff_readBool\n";
	}
	myDst->genStoreVal(out, A);
}

void WriteQuad::codegenX64(std::ostream& out){
	if (myHandle->locString() != "console") {

		myHandle->genLoadVal(out, SI);
	} else {
		out << "movq $0, %rsi\n";
	}
	mySrc->genLoadVal(out, DI);
	if (mySrcType->isInt()) {
		out << "callq stdJeff_writeInt\n";
	} else if (mySrcType->isString()) {
		out << "callq stdJeff_writeString\n";
	} else if (mySrcType->isBool()) {
		out << "callq stdJeff_writeBool\n";
	}
}

void OpenQuad::codegenX64(std::ostream& out){
	myPath->genLoadVal(out, DI); // Load th sstring address  into argument
	if (myReadOnly) {
		out << "movq $0, %rsi\n";
	} else {
		out << "movq $1, %rsi\n";
	}
	out << "callq stdJeff_openFP\n";
	myHandle->genStoreVal(out, A); // Retrieve the FILE* pointer
}

void CloseQuad::codegenX64(std::ostream& out){
	myHandle->genLoadVal(out, DI); // Load the file pointer
	out << "callq stdJeff_closeFP\n"; // Close file
}

void GotoQuad::codegenX64(std::ostream& out){
	out << "jmp " << tgt->getName() << "\n";
}

void IfzQuad::codegenX64(std::ostream& out){
    cnd->genLoadVal(out, DI);
    out << "cmpq $0, %rdi\n";
    out << "je " << tgt->toString();
}

void NopQuad::codegenX64(std::ostream& out){
	out << "nop" << "\n";
}

void CallQuad::codegenX64(std::ostream& out){
	if (numArgs >= 7 && numArgs % 2 != 0) {
		out << "pushq $0 \n";
	}
	out << "callq fun_" << sym->getName() << "\n";
	size_t cleanup;
	if (numArgs >= 7) {
		cleanup = 8*(numArgs-6);
		if (cleanup % 16 != 0) cleanup = cleanup + 8;
		out << "addq $" << cleanup << ", %rsp\n";
	}
}

void EnterQuad::codegenX64(std::ostream& out){
	out << "pushq %rbp\n";
	out << "movq %rsp, %rbp\n";
	out << "addq $16, %rbp\n";
	out << "subq $" << myProc->arSize() << ", %rsp\n";
}

void LeaveQuad::codegenX64(std::ostream& out){
	out << "addq $" << myProc->arSize() << ", %rsp\n";
	out << "popq %rbp\n";
	out << "retq\n";
}

void SetArgQuad::codegenX64(std::ostream& out){
	switch (index) { 
		case 1:
			opd->genLoadVal(out,DI);
			break;
		case 2:
			opd->genLoadVal(out,SI);
			break;
		case 3:
			opd->genLoadVal(out,D);	
			break;
		case 4:
			opd->genLoadVal(out,C);
			break;
		case 5:
			opd->genLoadVal(out, R8);
			break;	
		case 6:
			opd->genLoadVal(out, R9);
			break;
		default:
			opd->genLoadVal(out, A);
			out << "pushq %rax\n";
	}
}

void GetArgQuad::codegenX64(std::ostream& out){
	std::string memLoc = opd->getMemoryLoc();
	
	switch (index) { 
		case 1:
			out << "movq " << "%rdi, " << memLoc << "\n";
			break;
		case 2:
			out << "movq " << "%rsi, " << memLoc << "\n";
			break;
		case 3:
			out << "movq " << "%rdx, " << memLoc << "\n";
			break;
		case 4:
			out << "movq " << "%rcx, " << memLoc << "\n";
			break;
		case 5:
			out << "movq " << "%r8, " << memLoc << "\n";
			break;
		case 6:
			out << "movq " << "%r9, " << memLoc << "\n";
			break;
		default:
			size_t numArgs = myProc->getFormals().size();
			if (numArgs % 2 != 0) numArgs = numArgs + 1;
			size_t stackIndex = 8 * (numArgs - index);
			out << "movq " << stackIndex << "(%rbp), %rbx\n";
			out << "movq %rbx, " << memLoc << "\n";
			break;
	}
}

void SetRetQuad::codegenX64(std::ostream& out){
	opd->genLoadVal(out, A);
}

void GetRetQuad::codegenX64(std::ostream& out){
	opd->genStoreVal(out, A);
}

void LocQuad::codegenX64(std::ostream& out){
	TODO(not needed)
}

void SymOpd::genLoadVal(std::ostream& out, Register reg){
	out << getMovOp() << " " << getMemoryLoc() << ", " << getReg(reg) << "\n";
}

void SymOpd::genStoreVal(std::ostream& out, Register reg){
	out << getMovOp() << " " << getReg(reg) << ", " << getMemoryLoc() << "\n";
}

void SymOpd::genLoadAddr(std::ostream& out, Register reg) {
	TODO(Implement me if necessary)
}

void AuxOpd::genLoadVal(std::ostream& out, Register reg){
	out << getMovOp() << " " << getMemoryLoc() << ", " << getReg(reg) << "\n";
}

void AuxOpd::genStoreVal(std::ostream& out, Register reg){
	out << getMovOp() << " " << getReg(reg) << ", " << getMemoryLoc() << "\n";
}
void AuxOpd::genLoadAddr(std::ostream& out, Register reg){
	TODO(Implement me not needed)
}


void AddrOpd::genStoreVal(std::ostream& out, Register reg){
	TODO(not needed)
}

void AddrOpd::genLoadVal(std::ostream& out, Register reg){
	TODO(not needed)
}

void AddrOpd::genStoreAddr(std::ostream& out, Register reg){
	TODO(not needed)
}

void AddrOpd::genLoadAddr(std::ostream & out, Register reg){
	TODO(not needed)
}

void LitOpd::genLoadVal(std::ostream & out, Register reg){
	out << getMovOp() << " $" << val << ", " << getReg(reg) << "\n";
}

}
