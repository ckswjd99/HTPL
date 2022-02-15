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

  // prepare output file
  const sourceName = path.parse(path.basename(sourcePath))
  const outputDirectory = path.parse(sourcePath).dir;
  const outputFilePath = path.join(outputDirectory, sourceName.name.concat('.htal'));

  // generate code
  const parsedDOM = new Document(source);
  const outputString = parsedDOM.generateCode();

  // write code
  fs.writeFileSync(outputFilePath, outputString);
};

main(commandLineArguments);
