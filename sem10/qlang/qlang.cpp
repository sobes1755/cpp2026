#include "qlang.h"
#include "qeval.h"

#include "antlr4-runtime.h"
#include "QuaternionLexer.h"
#include "QuaternionParser.h"

#include <iostream>
#include <fstream>

int
main(int argc, char* argv[])
{

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " file.q" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream stream(argv[1]);

    if (!stream.is_open()) {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    // Лексический анализ (разбиение на токены)

    antlr4::ANTLRInputStream input(stream);

    QuaternionLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    tokens.fill();

/*

    std::cout << "--- LEXER TOKENS START ---" << std::endl;
    printLexerTokens(tokens, lexer.getVocabulary());
    std::cout << "--- LEXER TOKENS END ---" << std::endl;

*/

    // Синтаксический анализ (построение дерева)

    QuaternionParser parser(&tokens);
    antlr4::tree::ParseTree* tree = parser.program();

/*

    std::cout << "--- PARSER TREE START ---" << std::endl;
    printParserTree(tree, parser.getRuleNames());
    std::cout << "--- PARSER TREE END ---" << std::endl;

*/

    // Интерпретор (с помощью visitor)

    try {
        QEvalVisitor engine;
        engine.visit(tree);
    } catch (const std::exception& ex) {
        std::cerr << "Runtime Error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}
