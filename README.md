# JAVM-1
The JAVM virtual machine is a stack-based machine that operates in a single-threaded mechanism. The main component of JAVM is a stack called JA Stack. Every time a function is invoked, a stack frame is created on the JA Stack and the entire function is executed in there.
Components of a stack frame include:
  • Operand stack: a stack that used to push/pop operand values, results of operations, parameters passed to functions, return values of functions, etc.
  • Local variable space: a space containing all of the local variables of the function being
    executed.
