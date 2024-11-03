CBigFloat.o: src/CBigFloat.cpp src/CBigFloat.h src/CBigNumber.h \
 src/CNumData.h src/CBigInt.h src/CVisitorAdd.h src/CVisitor.h \
 src/CVisitorSubtract.h src/CVisitorMult.h src/CVisitorDiv.h \
 src/CVisitorDivMod.h src/CVisitorExponent.h src/CNumStrOper.h
CBigInt.o: src/CBigInt.cpp src/CBigInt.h src/CBigNumber.h src/CNumData.h \
 src/CVisitorAdd.h src/CVisitor.h src/CBigFloat.h src/CVisitorSubtract.h \
 src/CVisitorMult.h src/CVisitorDiv.h src/CVisitorDivMod.h \
 src/CVisitorExponent.h src/CNumStrOper.h
CBigNumber.o: src/CBigNumber.cpp src/CBigNumber.h src/CNumData.h \
 src/CNumStrOper.h
CCalculator.o: src/CCalculator.cpp src/CCalculator.h src/CBigInt.h \
 src/CBigNumber.h src/CNumData.h src/CBigFloat.h src/CShuntingYardAlg.h
CNumData.o: src/CNumData.cpp src/CNumData.h
CNumStrOper.o: src/CNumStrOper.cpp src/CNumStrOper.h src/CNumData.h
CShuntingYardAlg.o: src/CShuntingYardAlg.cpp src/CShuntingYardAlg.h \
 src/CBigNumber.h src/CNumData.h src/CBigFloat.h src/CBigInt.h
CVisitor.o: src/CVisitor.cpp src/CVisitor.h src/CBigNumber.h \
 src/CNumData.h src/CBigInt.h src/CBigFloat.h
CVisitorAdd.o: src/CVisitorAdd.cpp src/CVisitorAdd.h src/CVisitor.h \
 src/CBigNumber.h src/CNumData.h src/CBigInt.h src/CBigFloat.h
CVisitorDiv.o: src/CVisitorDiv.cpp src/CVisitorDiv.h src/CVisitor.h \
 src/CBigNumber.h src/CNumData.h src/CBigInt.h src/CBigFloat.h
CVisitorDivMod.o: src/CVisitorDivMod.cpp src/CVisitorDivMod.h \
 src/CVisitor.h src/CBigNumber.h src/CNumData.h src/CBigInt.h \
 src/CBigFloat.h
CVisitorExponent.o: src/CVisitorExponent.cpp src/CVisitorExponent.h \
 src/CVisitor.h src/CBigNumber.h src/CNumData.h src/CBigInt.h \
 src/CBigFloat.h
CVisitorMult.o: src/CVisitorMult.cpp src/CVisitorMult.h src/CVisitor.h \
 src/CBigNumber.h src/CNumData.h src/CBigInt.h src/CBigFloat.h
CVisitorSubtract.o: src/CVisitorSubtract.cpp src/CVisitorSubtract.h \
 src/CVisitor.h src/CBigNumber.h src/CNumData.h src/CBigInt.h \
 src/CBigFloat.h
main.o: src/main.cpp src/CBigInt.h src/CBigNumber.h src/CNumData.h \
 src/CBigFloat.h src/CCalculator.h
