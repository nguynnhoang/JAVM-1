#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>
using namespace std;
/*
StackFrame declaration
*/
class StackFrame {
private:
    int opStackMaxSize; // max size of operand stack
    int localVarArrSize; // size of local variable array
    float StackArr[32];
    float LocalArr[256];
    int line = 0;
    int count = 0;
public:
    /*
    Constructor of StackFrame
    */
    StackFrame();

    /*
    Run the method written in the testcase
    @param filename name of the file
    */
    void run(string filename);

    //Run the method Arithmetic Instructions   
    void iadd();
    void fadd();
    void isub();
    void fsub();
    void imul();
    void fmul();
    void idiv();
    void fdiv();
    void irem();
    void ineg();
    void fneg();
    void iand();
    void ior();
    void ieq();
    void feq();
    void ineq();
    void fneq();
    void ilt();
    void flt();
    void igt();
    void fgt();
    void ibnot();

    //Run the method Load and Store Instructions
    void iconst(string val);
    void fconst(string val);
    void iload(string index);
    void fload(string index);
    void istore(string index);
    void fstore(string index);

    //Run the method Type conversion Instructions
    void i2f();
    void f2i();

    //Run the method Operand Stack Management Instructions
    void top();
    void val(string index);
};

#endif // !__STACK_FRAME_H__