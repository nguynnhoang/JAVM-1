#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarArrSize(LOCAL_VARIABLE_ARRAY_SIZE) {}

bool checkSpace(string method) {
    for (int i = 0; i < method.size(); i++) if (method[i] == ' ') return 1;
    return 0;
}

int str2int(string str) {
    //Convert string to int, Arithmetic Instructions 
    if (str == "iadd") return 1;
    else if (str == "fadd") return 2;
    else if (str == "isub") return 3;
    else if (str == "fsub") return 4;
    else if (str == "imul") return 5;

    else if (str == "fmul") return 6;
    else if (str == "idiv") return 7;
    else if (str == "fdiv") return 8;
    else if (str == "irem") return 9;
    else if (str == "ineg") return 10;

    else if (str == "fneg") return 11;
    else if (str == "iand") return 12;
    else if (str == "ior")  return 13;
    else if (str == "ieq")  return 14;
    else if (str == "feq")  return 15;

    else if (str == "ineq") return 16;
    else if (str == "fneq") return 17;
    else if (str == "ilt")  return 18;
    else if (str == "flt")  return 19;
    else if (str == "igt")  return 20;
    else if (str == "fgt")  return 21;
    else if (str == "ibnot")return 22;

    //Convert string to int, Load and Store Instructions
    else if (str == "iconst")return 23;
    else if (str == "fconst")return 24;
    else if (str == "iload") return 25;
    else if (str == "fload") return 26;
    else if (str == "istore")return 27;
    else if (str == "fstore")return 28;

    //Convert string to int, Type Conversion Instructions
    else if (str == "i2f")   return 29;
    else if (str == "f2i")   return 30;

    //Convert string to int, Operand Stack Management Instructions
    else if (str == "top")   return 31;

    //Convert string to int, Local Variable Management Instructions
    else if (str == "val")   return 32;
    return 0;

}

void StackFrame::run(string filename) {
    ifstream file_name(filename);
    string method, value, testcase;
    for (int i = 0; i < localVarArrSize; i++) LocalArr[i] = -999999;

    if (file_name.is_open()) {
        while (!file_name.eof()) {
            line++;
            getline(file_name, testcase);
            if (checkSpace(testcase))
            {
                method = testcase.substr(0, testcase.find(' '));
                value = testcase.substr(testcase.find(' ') + 1, testcase.size());
                switch (str2int(method)) {
                    //Run the method Load and Store Instructions
                case 23:
                {
                    iconst(value);
                    break;
                }
                case 24:
                {
                    fconst(value);
                    break;
                }
                case 25:
                {
                    iload(value);
                    break;
                }
                case 26:
                {
                    fload(value);
                    break;
                }
                case 27:
                {
                    istore(value);
                    break;
                }
                case 28:
                {
                    fstore(value);
                    break;
                }

                //Run the method Local Variable Management Instructions
                case 32:
                {
                    val(value);
                    break;
                }
                }
            }

            else
            {
                switch (str2int(testcase)) {
                    //Run the method Arithmetic Instructions   
                case 1:
                {
                    iadd();
                    break;
                }
                case 2:
                {
                    fadd();
                    break;
                }
                case 3:
                {
                    isub();
                    break;
                }
                case 4:
                {
                    fsub();
                    break;
                }
                case 5:
                {
                    imul();
                    break;
                }
                case 6:
                {
                    fmul();
                    break;
                }
                case 7:
                {
                    idiv();
                    break;
                }
                case 8:
                {
                    fdiv();
                    break;
                }
                case 9:
                {
                    irem();
                    break;
                }
                case 10:
                {
                    ineg();
                    break;
                }
                case 11:
                {
                    fneg();
                    break;
                }
                case 12:
                {
                    iand();
                    break;
                }
                case 13:
                {
                    ior();
                    break;
                }
                case 14:
                {
                    ieq();
                    break;
                }
                case 15:
                {
                    feq();
                    break;
                }
                case 16:
                {
                    ineq();
                    break;
                }
                case 17:
                {
                    fneq();
                    break;
                }
                case 18:
                {
                    ilt();
                    break;
                }
                case 19:
                {
                    flt();
                    break;
                }
                case 20:
                {
                    igt();
                    break;
                }
                case 21:
                {
                    fgt();
                    break;
                }
                case 22:
                {
                    ibnot();
                    break;
                }

                //Run the method Type conversion Instructions
                case 29:
                {
                    i2f();
                    break;
                }
                case 30:
                {
                    f2i();
                    break;
                }

                //Run the method Operand Stack Management Instructions
                case 31:
                {
                    top();
                    break;
                }
                }
            }
        }
    }
    else throw;
}

//Load and Store Instructions
void StackFrame::iconst(string value) {
    if (count == opStackMaxSize) throw StackFull(line);
    StackArr[count] = stoi(value);
    count++;
    StackArr[count] = 0;
    count++;
}

void StackFrame::fconst(string value) {
    if (count == opStackMaxSize) throw StackFull(line);
    StackArr[count] = stof(value);
    count++;
    StackArr[count] = 1;
    count++;
}

void StackFrame::iload(string index) {
    int i = stoi(index);
    if (LocalArr[i] == -999999)         throw UndefinedVariable(line);
    if (i < 0 || i >= localVarArrSize)  throw ArrayOutOfRange(line);
    if (LocalArr[i] == 1)               throw TypeMisMatch(line);
    iconst(to_string(LocalArr[i + 1]));
}

void StackFrame::fload(string index) {
    int i = stoi(index);
    if (LocalArr[i] == -999999)         throw UndefinedVariable(line);
    if (i < 0 || i >= localVarArrSize)  throw ArrayOutOfRange(line);
    if (LocalArr[i] == 0)               throw TypeMisMatch(line);
    fconst(to_string(LocalArr[i + 1]));
}

void StackFrame::istore(string index) {
    int i = stoi(index);
    if (count == 0)                     throw StackEmpty(line);
    if (StackArr[count - 1] == 1)       throw TypeMisMatch(line);
    if (i < 0 || i >= localVarArrSize)  throw ArrayOutOfRange(line);
    LocalArr[i] = 0;
    LocalArr[i + 1] = StackArr[count - 2];
    count -= 2;
}

void StackFrame::fstore(string index) {
    int i = stoi(index);
    if (count == 0)                     throw StackEmpty(line);
    if (StackArr[count - 1] == 0)       throw TypeMisMatch(line);
    if (i < 0 || i >= localVarArrSize)  throw ArrayOutOfRange(line);
    LocalArr[i] = 1;
    LocalArr[i + 1] = StackArr[count - 2];
    count -= 2;
}

//Operand Stack Management Instructions
void StackFrame::top() {
    if (count == 0)                     throw StackEmpty(line);
    cout << StackArr[count - 2] << endl;
}

//Local Variable Management Instructions
void StackFrame::val(string index) {
    int i = stoi(index);
    if (i < 0 || i >= 256)              throw ArrayOutOfRange(line);
    if (LocalArr[i] == -999999)          throw UndefinedVariable(line);
    cout << LocalArr[i + 1] << endl;
}

//Type Conversion Instructions
void StackFrame::i2f() {
    if (count == 0)                      throw StackEmpty(line);
    if (StackArr[count - 1] == 1)        throw TypeMisMatch(line);
    float result_i2f = (float)StackArr[count - 2];
    count -= 2;
    fconst(to_string(result_i2f));
}

void StackFrame::f2i() {
    if (count == 0)                      throw StackEmpty(line);
    if (StackArr[count - 1] == 0)        throw TypeMisMatch(line);
    int result_f2i = (int)StackArr[count - 2];
    count -= 2;
    iconst(to_string(result_f2i));
}

//Arithmetic Instructions
void StackFrame::iadd() {
    if (count <= 2)                       throw StackEmpty(line);
    if (StackArr[count - 1] == 1 || StackArr[count - 3] == 1) throw TypeMisMatch(line);
    int sum = StackArr[count - 4] + StackArr[count - 2];
    count -= 4;
    iconst(to_string(sum));
}

void StackFrame::fadd() {
    if (count <= 2)                       throw StackEmpty(line);
    float sum = (float)StackArr[count - 4] + (float)StackArr[count - 2];
    count -= 4;
    fconst(to_string(sum));
}

void StackFrame::isub() {
    if (count <= 2)                       throw StackEmpty(line);
    if (StackArr[count - 1] == 1 || StackArr[count - 3] == 1) throw TypeMisMatch(line);
    int sub = StackArr[count - 4] - StackArr[count - 2];
    count -= 4;
    iconst(to_string(sub));
}

void StackFrame::fsub() {
    if (count <= 2)                       throw StackEmpty(line);
    float sub = (float)StackArr[count - 4] - (float)StackArr[count - 2];
    count -= 4;
    fconst(to_string(sub));
}

void StackFrame::imul() {
    if (count <= 2)                       throw StackEmpty(line);
    if (StackArr[count - 1] == 1 || StackArr[count - 3] == 1) throw TypeMisMatch(line);
    int mul = StackArr[count - 4] * StackArr[count - 2];
    count -= 4;
    iconst(to_string(mul));
}

void StackFrame::fmul() {
    if (count <= 2)                       throw StackEmpty(line);
    float sub = (float)StackArr[count - 4] * (float)StackArr[count - 2];
    count -= 4;
    fconst(to_string(sub));
}

void StackFrame::idiv() {
    if (count <= 2)                       throw StackEmpty(line);
    if (StackArr[count - 1] == 1 || StackArr[count - 3] == 1) throw TypeMisMatch(line);
    if (StackArr[count - 2] == 0)         throw DivideByZero(line);
    int divi = StackArr[count - 4] / StackArr[count - 2];
    count -= 4;
    iconst(to_string(divi));
}

void StackFrame::fdiv() {
    if (count <= 2)                       throw StackEmpty(line);
    if (StackArr[count - 2] == 0)         throw DivideByZero(line);
    float divi = (float)StackArr[count - 4] / (float)StackArr[count - 2];
    count -= 4;
    fconst(to_string(divi));
}

void StackFrame::irem() {
    if (count <= 2)                       throw StackEmpty(line);
    if (StackArr[count - 1] == 1 || StackArr[count - 3] == 1) throw TypeMisMatch(line);
    if (StackArr[count - 2] == 0)         throw DivideByZero(line);
    int rem = (int)StackArr[count - 4] % (int)StackArr[count - 2];
    count -= 4;
    iconst(to_string(rem));
}

void StackFrame::ineg() {
    if (count == 0)                      throw StackEmpty(line);
    if (StackArr[count - 1] == 1)        throw TypeMisMatch(line);
    int neg = StackArr[count - 2] * -1;
    count -= 2;
    iconst(to_string(neg));
}

void StackFrame::fneg() {
    if (count == 0)                      throw StackEmpty(line);
    float neg = float(StackArr[count - 2] * -1);
    count -= 2;
    fconst(to_string(neg));
}

void StackFrame::iand() {
    if (count <= 2)                       throw StackEmpty(line);
    if (StackArr[count - 1] == 1 || StackArr[count - 3] == 1)        throw TypeMisMatch(line);
    int result_and = (int)StackArr[count - 4] & (int)StackArr[count - 2];
    count -= 4;
    iconst(to_string(result_and));
}

void StackFrame::ior() {
    if (count <= 2)                       throw StackEmpty(line);
    if (StackArr[count - 1] == 1 || StackArr[count - 3] == 1)        throw TypeMisMatch(line);
    int result_or = (int)StackArr[count - 4] | (int)StackArr[count - 2];
    count -= 4;
    iconst(to_string(result_or));
}

void StackFrame::ieq() {
    if (count <= 2)                       throw StackEmpty(line);
    if (StackArr[count - 1] == 1 || StackArr[count - 3] == 1)        throw TypeMisMatch(line);
    if (StackArr[count - 4] == StackArr[count - 2]) {
        count -= 4;
        iconst("1");
    }
    else {
        count -= 4;
        iconst("0");
    }
}

void StackFrame::feq() {
    if (count <= 2)                       throw StackEmpty(line);
    if (StackArr[count - 4] == StackArr[count - 2]) {
        count -= 4;
        iconst("1.0");
    }
    else {
        count -= 4;
        iconst("0.0");
    }
}

void StackFrame::ineq() {
    if (count <= 2)                       throw StackEmpty(line);
    if (StackArr[count - 1] == 1 || StackArr[count - 3] == 1)        throw TypeMisMatch(line);
    if (StackArr[count - 4] != StackArr[count - 2]) {
        count -= 4;
        iconst("1");
    }
    else {
        count -= 4;
        iconst("0");
    }
}

void StackFrame::fneq() {
    if (count <= 2)                       throw StackEmpty(line);
    if ((float)StackArr[count - 4] != (float)StackArr[count - 2]) {
        count -= 4;
        iconst("1.0");
    }
    else {
        count -= 4;
        iconst("0.0");
    }
}

void StackFrame::ilt() {
    if (count <= 2)                        throw StackEmpty(line);
    if (StackArr[count - 1] == 1 || StackArr[count - 3] == 1)         throw TypeMisMatch(line);
    if (StackArr[count - 4] < StackArr[count - 2]) {
        count -= 4;
        iconst("1");
    }
    else {
        count -= 4;
        iconst("0");
    }
}

void StackFrame::flt() {
    if (count <= 2)                       throw StackEmpty(line);
    if ((float)StackArr[count - 4] < (float)StackArr[count - 2]) {
        count -= 4;
        iconst("1");
    }
    else {
        count -= 4;
        iconst("0");
    }
}

void StackFrame::igt() {
    if (count <= 2)                        throw StackEmpty(line);
    if (StackArr[count - 1] == 1 || StackArr[count - 3] == 1)         throw TypeMisMatch(line);
    if (StackArr[count - 4] > StackArr[count - 2]) {
        count -= 4;
        iconst("1");
    }
    else {
        count -= 4;
        iconst("0");
    }
}

void StackFrame::fgt() {
    if (count <= 2)                        throw StackEmpty(line);
    if ((float)StackArr[count - 4] > (float)StackArr[count - 2]) {
        count -= 4;
        iconst("1");
    }
    else {
        count -= 4;
        iconst("0");
    }
}

void StackFrame::ibnot() {
    if (count < 2)                        throw StackEmpty(line);
    if (StackArr[count - 1] == 1)         throw TypeMisMatch(line);
    if (!StackArr[count - 2]) {
        count -= 2;
        iconst("1");
    }
    else {
        count -= 2;
        iconst("0");
    }
}