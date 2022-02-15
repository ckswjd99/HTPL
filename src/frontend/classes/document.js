const { JSDOM } = require('jsdom');
const Element = require('./element');
const { OP_BUFFER, OP_TAG, instructionString, OP_EXIT } = require('../utils/intermediate')

class Document {
  constructor(rawText) {
    this.raw = rawText;

    const { window } = new JSDOM(rawText, { contentType: "text/html" })
    const { document } = window

    this.window = window;
    this.document = document;

    this.inputBufferLength = this.document.head.children.length;

    this.parsed = Element.parse(this.document.body)

    this.usedVariables = Element.usedVariables(this.parsed, new Set())
  }

  print() {
    Element.recursivePrint(this.parsed)
  }

  generateCode() {
    const variableToNum = new Map();
    const variableNames = Array.from(this.usedVariables);
    for (let i = 0; i < variableNames.length; i += 1) {
      variableToNum.set(variableNames[i], i + 1);
    }

    const instructions = [];

    instructions.push(instructionString(OP_BUFFER, this.inputBufferLength));
    instructions.push(instructionString(OP_TAG, this.usedVariables.size));

    Element.generateCode(this.parsed, variableToNum, instructions);

    instructions.push(instructionString(OP_EXIT));

    return instructions.join("");
  }
}

module.exports = Document;
