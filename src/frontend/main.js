const fs = require('fs');
const path = require('path');

const Document = require('./classes/document');

const commandLineArguments = process.argv.slice(2);

const main = (argv) => {
  // get source
  const sourcePath = argv.shift();
  const sourceAbsolute = fs.existsSync(sourcePath) ? fs.readFileSync(sourcePath).toString() : null;
  const sourceRelative = fs.existsSync(path.join('.', sourcePath)) ? fs.readFileSync(path.join('.', sourcePath)).toString() : null;
  const source = sourceAbsolute || sourceRelative;
  if (!source) throw new Error('Source not exists!');

  // parse source
  const parsedDOM = new Document(source);
  parsedDOM.body.printRecursive();
};

main(commandLineArguments);
