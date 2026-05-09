#include "tree_sitter/parser.h"

#include <stdbool.h>
#include <stdint.h>

enum TokenType {
  INLINE_THEN_MARKER,
};

static void skip_horizontal_whitespace(TSLexer *lexer) {
  while (lexer->lookahead == ' ' || lexer->lookahead == '\t' ||
         lexer->lookahead == '\v' || lexer->lookahead == '\f') {
    lexer->advance(lexer, true);
  }
}

static bool consume_newline(TSLexer *lexer) {
  if (lexer->lookahead == '\r') {
    lexer->advance(lexer, true);
    if (lexer->lookahead == '\n') {
      lexer->advance(lexer, true);
    }
    return true;
  }

  if (lexer->lookahead == '\n') {
    lexer->advance(lexer, true);
    return true;
  }

  return false;
}

static bool skip_inline_block_comment(TSLexer *lexer) {
  lexer->advance(lexer, true);

  if (lexer->lookahead != '*') {
    return false;
  }

  lexer->advance(lexer, true);

  while (!lexer->eof(lexer)) {
    if (lexer->lookahead == '\r' || lexer->lookahead == '\n') {
      return false;
    }

    if (lexer->lookahead == '*') {
      lexer->advance(lexer, true);
      if (lexer->lookahead == '/') {
        lexer->advance(lexer, true);
        return true;
      }
      continue;
    }

    lexer->advance(lexer, true);
  }

  return false;
}

static bool skip_inline_line_comment(TSLexer *lexer) {
  lexer->advance(lexer, true);

  if (lexer->lookahead != '/') {
    return false;
  }

  while (!lexer->eof(lexer)) {
    lexer->advance(lexer, true);
    if (lexer->lookahead == '\r' || lexer->lookahead == '\n') {
      return false;
    }
  }

  return true;
}

static bool scan_inline_then_marker(TSLexer *lexer) {
  bool expects_continued_line = false;

  lexer->mark_end(lexer);

  for (;;) {
    skip_horizontal_whitespace(lexer);
    lexer->mark_end(lexer);

    if (expects_continued_line) {
      if (!consume_newline(lexer)) {
        return false;
      }
      expects_continued_line = false;
      lexer->mark_end(lexer);
      continue;
    }

    if (consume_newline(lexer)) {
      return false;
    }

    if (lexer->lookahead == '&') {
      expects_continued_line = true;
      lexer->advance(lexer, true);
      lexer->mark_end(lexer);
      continue;
    }

    if (lexer->lookahead == '/') {
      if (!skip_inline_block_comment(lexer) && !skip_inline_line_comment(lexer)) {
        return false;
      }
      lexer->mark_end(lexer);
      continue;
    }

    lexer->result_symbol = INLINE_THEN_MARKER;
    return true;
  }
}

void *tree_sitter_powerscript_external_scanner_create(void) {
  return NULL;
}

void tree_sitter_powerscript_external_scanner_destroy(void *payload) {
  (void)payload;
}

unsigned tree_sitter_powerscript_external_scanner_serialize(void *payload, char *buffer) {
  (void)payload;
  (void)buffer;
  return 0;
}

void tree_sitter_powerscript_external_scanner_deserialize(void *payload, const char *buffer, unsigned length) {
  (void)payload;
  (void)buffer;
  (void)length;
}

bool tree_sitter_powerscript_external_scanner_scan(void *payload, TSLexer *lexer, const bool *valid_symbols) {
  (void)payload;
  if (valid_symbols[INLINE_THEN_MARKER]) {
    return scan_inline_then_marker(lexer);
  }

  (void)lexer;
  return false;
}
