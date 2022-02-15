const path = require('path')
const fs = require('fs')

const Document = require('./classes/document')
const parser = require('./utils/parser')

const main = () => {
  const text = fs.readFileSync(path.join(__dirname, '..', '..', 'example', 'helloWorld.html')).toString()
  const doc = new Document(text);

  doc.print()
  console.log(doc.usedVariables)
}

main()