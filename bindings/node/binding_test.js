import assert from "node:assert";
import { test } from "node:test";
import Parser from "tree-sitter";

import fs from "node:fs";
import path from "node:path";

test("can load grammar", () => {
  const parser = new Parser();
  assert.doesNotReject(async () => {
    const { default: language } = await import("./index.js");
    parser.setLanguage(language);
  });
});

test('can parse ../../examples/playground.srf', async () => {
  const parser = new Parser();

  const { default: language } = await import("./index.js");
  parser.setLanguage(language);

  const filePath = path.join('./examples/playground.srf');
  const fileText = fs.readFileSync(filePath, 'utf8');
  const tree = parser.parse(fileText, null);

  assert.equal(tree.rootNode.type, 'source_file');

});