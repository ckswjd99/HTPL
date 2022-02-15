const { JSDOM } = require('jsdom');
const Element = require('./element');

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

  codeGenerate() {
    Element.recursiveCodeGenerate(this.parsed)
  }
}

module.exports = Document;
