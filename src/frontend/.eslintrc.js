module.exports = {
  env: {
    browser: false,
    commonjs: true,
    es2021: false,
  },
  extends: [
    'airbnb-base',
    'prettier',
  ],
  parserOptions: {
    ecmaVersion: 'latest',
  },
  rules: {
    'no-console': 'off',
  },
};
