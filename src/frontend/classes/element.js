/* eslint-disable no-param-reassign */
const Attribute = require('./attribute');
const { attrNameParser, attrValueParser } = require('../utils/parser')
const {
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
} = require('../utils/intermediate')

class Element {
  constructor(tagName, attributes) {
    this.tag = tagName;
    this.attributes = [];
    this.parent = null;
    this.children = [];

    for (let i = 0; i < attributes.length; i += 1) {
      const nowName = attributes[`${i}`].name;
      const nowValue = attributes[`${i}`].value;
      this.attributes.push(new Attribute(nowName, nowValue));
    }
  }

  pushChildren(...args) {
    for (let i = 0; i < args.length; i += 1) {
      args[i].parent = this;
      this.children.push(args[i]);
    }
  }

  static parse(htmlElement) {
    const temp = new Element(htmlElement.tagName, htmlElement.attributes);
    const { children } = htmlElement;
    for (let i = 0; i < children.length; i += 1) {
      temp.pushChildren(Element.parse(children[i]))
    }

    return temp
  }

  static recursivePrint(elem) {
    let tagOpenString = `TAG OPEN: ${elem.tag} with attr `;

    for (let i = 0; i < elem.attributes.length; i += 1) {
      tagOpenString = tagOpenString.concat(`${elem.attributes[i].name}="${elem.attributes[i].value}" `);
    }

    console.log(tagOpenString)

    for (let i = 0; i < elem.children.length; i += 1) {
      Element.recursivePrint(elem.children[i]);
    }

    console.log(`TAG CLOSE: ${elem.tag}`);
  }

  static usedVariables(elem, set) {
    set.add(elem.tag)
    elem.children.forEach(child => Element.usedVariables(child, set))
    return set
  }

  static generateCode(elem, variableToNum, instructions) {
    const elemIndex = variableToNum.get(elem.tag);
    const parentIndex = elem.parent ? variableToNum.get(elem.parent.tag) : 0;

    let popMode = 1;
    const instAfterOpen = [];
    const instAfterClose = [];

    // make instructions
    elem.attributes.forEach(attr => {
      const operation = attrNameParser(attr.name)
      const value = attrValueParser(attr.value)
      switch (operation) {
        case 0: { // Print
          instAfterOpen.push(instructionString(OP_POPMODE, popMode));
          instAfterOpen.push(instructionString(OP_POP, elemIndex, 0));
          instAfterOpen.push(instructionString(OP_POPMODE, 1));
          instAfterOpen.push(instructionString(OP_ADD, 0, value));
          instAfterOpen.push(instructionString(OP_PRINT, 0));
          instAfterOpen.push(instructionString(OP_POPMODE, popMode));
          break;
        }
        case 1: { // Input
          instAfterOpen.push(instructionString(OP_SCAN, elemIndex));
          break;
        }
        case 2: { // Flush
          instAfterOpen.push(instructionString(OP_FLUSH, elemIndex, value));
          break;
        }
        case 3: { // Add
          instAfterOpen.push(instructionString(OP_ADD, elemIndex, value));
          break;
        }
        case 4: { // Offset
          instAfterOpen.push(instructionString(OP_PUSH, elemIndex, value));
          break;
        }
        case 5: { // Conditional Jump
          instAfterOpen.push(instructionString(OP_JUMP, elemIndex, value));
          break;
        }
        case 6: { // Conditional Break
          instAfterOpen.push(instructionString(OP_BREAK, elemIndex));
          break;
        }
        case 7: { // Pop Mode
          instAfterOpen.push(instructionString(OP_POPMODE, value));
          popMode = value === 0 ? 0 : 1;
          break;
        }
        default: {

          break;
        }
      }
    })

    instAfterClose.push(instructionString(OP_POPMODE, popMode))
    instAfterClose.push(instructionString(OP_POP, elemIndex, parentIndex))

    instructions.push(instructionString(OP_OPEN, elemIndex))
    instructions.push(instructionString(OP_POPMODE, 1))
    instructions.push(...instAfterOpen)
    elem.children.forEach(child => Element.generateCode(child, variableToNum, instructions))
    instructions.push(instructionString(OP_CLOSE, elemIndex))
    instructions.push(...instAfterClose)

  }
}

module.exports = Element;
