#include "ast.hpp"

namespace jeff{

IRProgram * ProgramNode::to3AC(TypeAnalysis * ta){
	IRProgram * prog = new IRProgram(ta);
	prog->gatherGlobal(consoleSym);
	for (auto global : *myGlobals){
		global->to3AC(prog);
	}
	return prog;
}

static void formalsTo3AC(Procedure * proc,
  std::list<FormalDeclNode *> * myFormals){
	for (auto formal : *myFormals){
		formal->to3AC(proc);
	}
	unsigned int argIdx = 1;
	for (auto formal : *myFormals){
		SemSymbol * sym = formal->ID()->getSymbol();
		SymOpd * opd = proc->getSymOpd(sym);

		Quad * inQuad = new GetArgQuad(argIdx, opd, false);
		proc->addQuad(inQuad);
		argIdx += 1;
	}
}

void FnDeclNode::to3AC(IRProgram * prog){
	SemSymbol * mySym = this->ID()->getSymbol();
	Procedure * proc = prog->makeProc(mySym->getName());

	//Put the function itself into global scope
	// for function pointers
	prog->gatherGlobal(mySym);

	//Generate the getin quads
	formalsTo3AC(proc, myFormals);

	for (auto stmt : *myBody){
		stmt->to3AC(proc);
	}
}

void FnDeclNode::to3AC(Procedure * proc){
	throw new InternalError("FnDecl at a local scope");
}

//We only get to this node if we are in a stmt
// context (DeclNodes protect descent)
Opd * IDNode::flatten(Procedure * proc){
	SemSymbol * sym = this->getSymbol();
	Opd * res = proc->getSymOpd(sym);
	if (!res){
		throw new InternalError("null id sym");;
	}
	return res;
}

void FormalDeclNode::to3AC(IRProgram * prog){
	throw new InternalError("Formal at a global level");
}

void FormalDeclNode::to3AC(Procedure * proc){
	SemSymbol * sym = ID()->getSymbol();
	proc->gatherFormal(sym);
}

Opd * IntLitNode::flatten(Procedure * proc){
	return LitOpd::buildInt(myNum);
}

Opd * StrLitNode::flatten(Procedure * proc){
	Opd * res = proc->getProg()->makeString(myStr);
	return res;
}

Opd * TrueNode::flatten(Procedure * proc){
	Opd * res = new LitOpd("1", 8);
	return res;
}


Opd * FalseNode::flatten(Procedure * proc){
	Opd * res = new LitOpd("0", 8);
	return res;
}

static void argsTo3AC(Procedure * proc, std::list<ExpNode *> * args){
	std::list<std::pair<Opd *, const DataType *>> argOpds;
	for (auto argNode : *args){
		Opd * argOpd = argNode->flatten(proc);
		const DataType * argType = proc->getProg()->nodeType(argNode);
		argOpds.push_back(std::make_pair(argOpd, argType));
	}
	size_t argIdx = 1;
	for (auto argOpd : argOpds){
		Quad * argQuad = new SetArgQuad(argIdx, argOpd.first, argOpd.second);
		proc->addQuad(argQuad);
		argIdx++;
	}
}

Opd * CallExpNode::flatten(Procedure * proc){
	argsTo3AC(proc, myArgs);
	Quad * callQuad = new CallQuad(myID->getSymbol());
	proc->addQuad(callQuad);

	SemSymbol * idSym = myID->getSymbol();
	const FnType * calleeType = idSym->getDataType()->asFn();
	const DataType * retType = calleeType->getReturnType();
	if (retType->isVoid()){
		return nullptr;
	} else {
		Opd * retVal = proc->makeTmp(Opd::width(retType));
		Quad * getRet = new GetRetQuad(retVal, false);
		proc->addQuad(getRet);
		return retVal;
	}
}

Opd * NegNode::flatten(Procedure * proc){
	Opd * child = myExp->flatten(proc);
	size_t width = proc->getProg()->opWidth(this);
	Opd * dst = proc->makeTmp(width);
	UnaryOp opr = UnaryOp::NEG64;
	Quad * quad = new UnaryOpQuad(dst, opr, child);
	proc->addQuad(quad);
	return dst;
}

Opd * NotNode::flatten(Procedure * proc){
	Opd * child = myExp->flatten(proc);
	size_t width = proc->getProg()->opWidth(myExp);
	Opd * dst = proc->makeTmp(width);
	UnaryOp opr = UnaryOp::NOT64;
	Quad * quad = new UnaryOpQuad(dst, opr, child);
	proc->addQuad(quad);
	return dst;
}

Opd * PlusNode::flatten(Procedure * proc){
	Opd * childL = myExp1->flatten(proc);
	Opd * childR = myExp2->flatten(proc);
	size_t width = proc->getProg()->opWidth(this);
	Opd * dst = proc->makeTmp(width);
	BinOp opr = BinOp::ADD64;
	Quad * quad = new BinOpQuad(dst, opr, childL, childR);
	proc->addQuad(quad);
	return dst;
}

Opd * TernaryExpNode::flatten(Procedure * proc){
	Opd * condOpd = cond->flatten(proc);

	Label * falseLabel = proc->makeLabel();
	Label * afterLabel = proc->makeLabel();

	proc->addQuad(new IfzQuad(condOpd, falseLabel));

	size_t width = 8;
	Opd * res = proc->makeTmp(width);

	Opd * trueRes = expTrue->flatten(proc);
	proc->addQuad(new AssignQuad(res, trueRes));
	proc->addQuad(new GotoQuad(afterLabel));

	Quad * falseNop = new NopQuad();
	falseNop->addLabel(falseLabel);
	proc->addQuad(falseNop);
	Opd * falseRes = expFalse->flatten(proc);
	proc->addQuad(new AssignQuad(res, falseRes));

	Quad * afterNop = new NopQuad();
	afterNop->addLabel(afterLabel);
	proc->addQuad(afterNop);

	return res;
}

Opd * MinusNode::flatten(Procedure * proc){
	Opd * childL = myExp1->flatten(proc);
	Opd * childR = myExp2->flatten(proc);
	size_t width = proc->getProg()->opWidth(this);
	Opd * dst = proc->makeTmp(width);
	BinOp opr = BinOp::SUB64;
	Quad * quad = new BinOpQuad(dst, opr, childL, childR);
	proc->addQuad(quad);
	return dst;
}

Opd * TimesNode::flatten(Procedure * proc){
	Opd * childL = myExp1->flatten(proc);
	Opd * childR = myExp2->flatten(proc);
	size_t width = proc->getProg()->opWidth(this);
	Opd * dst = proc->makeTmp(width);
	BinOp opr = BinOp::MULT64;
	Quad * quad = new BinOpQuad(dst, opr, childL, childR);
	proc->addQuad(quad);
	return dst;
}

Opd * DivideNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	size_t width = proc->getProg()->opWidth(this);
	Opd * dst = proc->makeTmp(width);
	BinOp opr = BinOp::DIV64;
	BinOpQuad * quad = new BinOpQuad(dst, opr, op1, op2);
	proc->addQuad(quad);
	return dst;
}

Opd * AndNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	size_t width = proc->getProg()->opWidth(this);
	Opd * opRes = proc->makeTmp(width);
	BinOp opr = BinOp::AND64;
	BinOpQuad * quad = new BinOpQuad(opRes, opr, op1, op2);
	proc->addQuad(quad);
	return opRes;
}

Opd * OrNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	size_t width = proc->getProg()->opWidth(this);
	Opd * opRes = proc->makeTmp(width);
	BinOp opr = BinOp::OR64;
	BinOpQuad * quad = new BinOpQuad(opRes, opr, op1, op2);
	proc->addQuad(quad);
	return opRes;
}

Opd * EqualsNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	size_t width = proc->getProg()->opWidth(this->myExp1);
	size_t resWidth = Opd::width(BasicType::BOOL());
	Opd * dst = proc->makeTmp(resWidth);
	BinOp opr = BinOp::EQ64;
	BinOpQuad * quad = new BinOpQuad(dst, opr, op1, op2);
	proc->addQuad(quad);
	return dst;
}

Opd * NotEqualsNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	size_t width = proc->getProg()->opWidth(this->myExp1);
	size_t resWidth = Opd::width(BasicType::BOOL());
	Opd * dst = proc->makeTmp(resWidth);
	BinOp opr = BinOp::NEQ64;
	BinOpQuad * quad = new BinOpQuad(dst, opr, op1, op2);
	proc->addQuad(quad);
	return dst;
}

Opd * GreaterNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	size_t width = proc->getProg()->opWidth(this->myExp1);
	size_t resWidth = Opd::width(BasicType::BOOL());
	Opd * dst = proc->makeTmp(resWidth);
	BinOp opr = BinOp::GT64;
	BinOpQuad * quad = new BinOpQuad(dst, opr, op1, op2);
	proc->addQuad(quad);
	return dst;
}

Opd * GreaterEqNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	size_t width = proc->getProg()->opWidth(this->myExp1);
	size_t resWidth = Opd::width(BasicType::BOOL());
	Opd * dst = proc->makeTmp(resWidth);
	BinOp opr = BinOp::GTE64;
	BinOpQuad * quad = new BinOpQuad(dst, opr, op1, op2);
	proc->addQuad(quad);
	return dst;
}

Opd * LessNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	size_t width = proc->getProg()->opWidth(this->myExp1);
	size_t resWidth = Opd::width(BasicType::BOOL());
	Opd * dst = proc->makeTmp(resWidth);
	BinOp opr = BinOp::LT64;
	BinOpQuad * quad = new BinOpQuad(dst, opr, op1, op2);
	proc->addQuad(quad);
	return dst;
}

Opd * LessEqNode::flatten(Procedure * proc){
	Opd * op1 = this->myExp1->flatten(proc);
	Opd * op2 = this->myExp2->flatten(proc);
	size_t width = proc->getProg()->opWidth(this->myExp1);
	size_t resWidth = Opd::width(BasicType::BOOL());
	Opd * dst = proc->makeTmp(resWidth);
	BinOp opr = BinOp::LTE64;
	BinOpQuad * quad = new BinOpQuad(dst, opr, op1, op2);
	proc->addQuad(quad);
	return dst;
}

void AssignStmtNode::to3AC(Procedure * proc){
	Opd * rhs = mySrc->flatten(proc);
	Opd * lhs = myDst->flatten(proc);
	if (!lhs){
		throw InternalError("null tgt");
	}
	
	AssignQuad * quad;
	quad = new AssignQuad(lhs, rhs);

	quad->setComment("Assign");
	proc->addQuad(quad);
}

void PostIncStmtNode::to3AC(Procedure * proc){
	Opd * child = this->myLoc->flatten(proc);
	size_t width = proc->getProg()->opWidth(this->myLoc);
	BinOp opr = BinOp::ADD64;
	LitOpd * litOpd = new LitOpd("1", width);
	BinOpQuad * quad = new BinOpQuad(child, opr, child, litOpd);
	proc->addQuad(quad);
}

void PostDecStmtNode::to3AC(Procedure * proc){
	Opd * child = this->myLoc->flatten(proc);
	size_t width = proc->getProg()->opWidth(this->myLoc);
	BinOp opr = BinOp::SUB64;
	LitOpd * litOpd = new LitOpd("1", width);
	BinOpQuad * quad = new BinOpQuad(child, opr, child, litOpd);
	proc->addQuad(quad);
}

void OpenStmtNode::to3AC(Procedure * proc){
	Opd * handleOpd = handle->flatten(proc);
	Opd* strOpd = proc->getProg()->makeString(path);
	proc->addQuad(new OpenQuad(
		handleOpd,
		strOpd,
		isReadOnly
	));
}

void CloseStmtNode::to3AC(Procedure * proc){
	Opd * child = handle->flatten(proc);
	proc->addQuad(new CloseQuad(child));
}

void ReadStmtNode::to3AC(Procedure * proc){
	Opd * childOpd = myDst->flatten(proc);
	Opd * handleOpd = myHandle->flatten(proc);
	proc->addQuad(new ReadQuad(
		handleOpd,
		childOpd,
		proc->getProg()->nodeType(myDst)
	));
}

void WriteStmtNode::to3AC(Procedure * proc){
	Opd * childOpd = mySrc->flatten(proc);
	Opd * handleOpd = myHandle->flatten(proc);
	proc->addQuad(new WriteQuad(
		handleOpd,
		childOpd, 
		proc->getProg()->nodeType(mySrc)
	));
}

void IfStmtNode::to3AC(Procedure * proc){
	Opd * cond = myCond->flatten(proc);
	Label * afterLabel = proc->makeLabel();
	Quad * afterNop = new NopQuad();
	afterNop->addLabel(afterLabel);

	proc->addQuad(new IfzQuad(cond, afterLabel));
	for (auto stmt : *myBody){
		stmt->to3AC(proc);
	}
	proc->addQuad(afterNop);
}

void IfElseStmtNode::to3AC(Procedure * proc){
	Label * elseLabel = proc->makeLabel();
	Quad * elseNop = new NopQuad();
	elseNop->addLabel(elseLabel);
	Label * afterLabel = proc->makeLabel();
	Quad * afterNop = new NopQuad();
	afterNop->addLabel(afterLabel);

	Opd * cond = myCond->flatten(proc);

	Quad * jmpFalse = new IfzQuad(cond, elseLabel);
	proc->addQuad(jmpFalse);
	for (auto stmt : *myBodyTrue){
		stmt->to3AC(proc);
	}

	Quad * skipFall = new GotoQuad(afterLabel);
	proc->addQuad(skipFall);

	proc->addQuad(elseNop);

	for (auto stmt : *myBodyFalse){
		stmt->to3AC(proc);
	}

	proc->addQuad(afterNop);
}

void WhileStmtNode::to3AC(Procedure * proc){
	Quad * headNop = new NopQuad();
	Label * headLabel = proc->makeLabel();
	headNop->addLabel(headLabel);

	Label * afterLabel = proc->makeLabel();
	Quad * afterQuad = new NopQuad();
	afterQuad->addLabel(afterLabel);

	proc->addQuad(headNop);
	Opd * cond = myCond->flatten(proc);
	Quad * jmpFalse = new IfzQuad(cond, afterLabel);
	proc->addQuad(jmpFalse);

	for (auto stmt : *myBody){
		stmt->to3AC(proc);
	}

	Quad * loopBack = new GotoQuad(headLabel);
	proc->addQuad(loopBack);
	proc->addQuad(afterQuad);
}

void CallStmtNode::to3AC(Procedure * proc){
	Opd * res = myCallExp->flatten(proc);
	//Since we're in a callStmt, the GetRet quad
	// generated as the last action of the subtree
	// was unnecessary. Remove it from the procedure.
	if (res != nullptr){
		//A void call will not generate a getout
		Quad * last = proc->popQuad();
	}
	//Should probably delete the last quad, but
	// we've leaked so much memory why start worrying now?
}

void ReturnStmtNode::to3AC(Procedure * proc){
	if (myExp != nullptr){
		Opd * res = myExp->flatten(proc);

		const DataType * type = proc->getProg()->nodeType(myExp);
		Quad * setOut = new SetRetQuad(res, false);

		proc->addQuad(setOut);
	}

	Label * leaveLbl = proc->getLeaveLabel();
	Quad * jmpLeave = new GotoQuad(leaveLbl);
	proc->addQuad(jmpLeave);
}

void VarDeclNode::to3AC(Procedure * proc){
	SemSymbol * sym = ID()->getSymbol();
	if (sym == nullptr){
		throw new InternalError("null sym");
	}
	proc->gatherLocal(sym);
}

void VarDeclNode::to3AC(IRProgram * prog){
	SemSymbol * sym = ID()->getSymbol();
	if (sym == nullptr){
		throw new InternalError("null sym");
	}

	prog->gatherGlobal(sym);
}

}
