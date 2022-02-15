/* eslint-disable no-param-reassign */
const Attribute = require('./attribute');

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
}

module.exports = Element;
