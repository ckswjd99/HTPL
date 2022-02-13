/**
 * Parse attribute name.
 * @param {String} attrName
 * @returns {number}
 */
const attrNameParser = (attrName) => {
  let value = 0;
  let sign = 1;
  const signReverser = ['_', '-', '.'];
  for (let i = 0; i < attrName.length; i += 1) {
    if (signReverser.indexOf(attrName[i]) !== -1) sign *= -1;
    else value += sign;
  }
  return value;
};

/**
 * Parse attribute value.
 * @param {String} attrValue
 * @returns {number}
 */
const attrValueParser = (attrValue) => {
  const base64Encoded = Buffer.from(attrValue).toString('base64');
  const base64Chars = Array.from(base64Encoded).map((char) => char.charCodeAt(0));
  const baseSum = base64Chars.reduce((a, b) => a + b, 0) % 256;

  return baseSum;
};

module.exports = { attrNameParser, attrValueParser };
