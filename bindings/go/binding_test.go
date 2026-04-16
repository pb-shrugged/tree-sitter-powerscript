package tree_sitter_powerscript_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_powerscript "github.com/pb-shrugged/tree-sitter-powerscript/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_powerscript.Language())
	if language == nil {
		t.Errorf("Error loading powerscript grammar")
	}
}
