import XCTest
import SwiftTreeSitter
import TreeSitterPowerscript

final class TreeSitterPowerscriptTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_powerscript())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading powerscript grammar")
    }
}
