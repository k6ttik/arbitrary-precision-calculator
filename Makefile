CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++17

HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
TESTS = $(wildcard tests/*.test.cpp)

.DEFAULT_GOAL := all

.PHONY: all
all: compile doc

.PHONY: run
run: compile
	./laiykali

.PHONY: compile
compile: laiykali

laiykali: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	$(CXX) $^ -o $@

build/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -c -o $@

debug/%.test: tests/%.test.cpp $(filter-out build/main.o,$(OBJECTS))
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< $(filter-out build/main.o,$(OBJECTS)) -I src/ -o $@

.PHONY: doc
doc: Doxyfile $(HEADERS)
	doxygen Doxyfile
	mv doc/html/* doc/
	rm -rf html

Doxyfile:
	doxygen -g Doxyfile

.PHONY: clean
clean:
	rm -rf laiykali build/ doc/ 2>/dev/null

.PHONY: test_all
test_all: $(TESTS:tests/%.test.cpp=debug/%.test)
	for TEST in debug/*.test; do ./$$TEST; done

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

debug/CBigNumber.test.o: tests/CBigNumber.test.cpp src/CBigNumber.cpp src/CBigNumber.h src/CNumData.h \
 src/CNumStrOper.h