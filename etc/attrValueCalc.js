const fs = require('fs')

function calc(text) {
    let base = Buffer.from(text).toString("base64")
    baseList = base.split("")
    
    baseList = baseList.map(char => char.charCodeAt(0))
    baseSum = baseList.reduce((a, b) => a+b) % 256
    
    baseChar = (32 <= baseSum % 128 && baseSum % 128 <= 126) ? baseSum == 34 ? "\\\"" : String.fromCharCode(baseSum % 128) : "NULL"
    

    return `${text}, ${base}, ${baseSum}`
}

const csvData = "Text, base64, Sum\n" + require('./simpleWords').map(text => calc(text)).join("\n")
fs.writeFileSync("./attrValueConventions.csv", csvData)