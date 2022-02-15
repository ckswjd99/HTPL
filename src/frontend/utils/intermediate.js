const OP_ERROR = "ERROR"
const OP_BUFFER = "BUFFER"
const OP_TAG = "TAG"
const OP_OPEN = "OPEN"
const OP_CLOSE = "CLOSE"
const OP_POP = "POP"
const OP_PUSH = "PUSH"
const OP_DUPL = "DUPL"
const OP_FLUSH = "FLUSH"
const OP_ADD = "ADD"
const OP_JUMP = "JUMP"
const OP_BREAK = "BREAK"
const OP_PRINT = "PRINT"
const OP_SCAN = "SCAN"
const OP_EXIT = "EXIT"
const OP_POPMODE = "POPMODE"

const instructionString = (opcode, operand1, operand2) => {
  if (operand1 === undefined) return `${opcode}\n`;
  if (operand2 === undefined) return `${opcode} ${operand1}\n`;
  return `${opcode} ${operand1} ${operand2}\n`;
}

module.exports = {
  OP_ERROR,
  OP_BUFFER,
  OP_TAG,
  OP_OPEN,
  OP_CLOSE,
  OP_POP,
  OP_PUSH,
  OP_DUPL,
  OP_FLUSH,
  OP_ADD,
  OP_JUMP,
  OP_BREAK,
  OP_PRINT,
  OP_SCAN,
  OP_EXIT,
  OP_POPMODE,
  instructionString
}