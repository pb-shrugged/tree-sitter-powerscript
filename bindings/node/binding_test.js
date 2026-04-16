const assert = require('node:assert');
const { test } = require('node:test');

const Parser = require('tree-sitter');
const PowerscriptLanguage = require('./index');

const fs = require('node:fs');
const path = require('node:path');

test('can load grammar', () => {
  const parser = new Parser();
  assert.doesNotThrow(() => parser.setLanguage(PowerscriptLanguage));
});

test('can parse ../../examples/playground.srf', () => {
  const parser = new Parser();
  assert.doesNotThrow(() => parser.setLanguage(PowerscriptLanguage));

  const filePath = path.join(__dirname, '../../examples/playground.srf');
  const fileText = fs.readFileSync(filePath, 'utf8');
  const tree = parser.parse(fileText, null);

  assert.equal(tree.rootNode.type, 'source_file');
});
