#pragma once

#include "antlr4-runtime.h"
#include "QuaternionLexer.h"
#include "QuaternionParser.h"

void
printLexerTokens(antlr4::CommonTokenStream& tokens, const antlr4::dfa::Vocabulary& vocabulary)
{

    for (auto token : tokens.getTokens()) {

        std::string tokenTypeName = vocabulary.getSymbolicName(token->getType());
        std::string tokenText = token->getText();
        
        std::cout << token->getLine() << ":" << token->getCharPositionInLine()
                  << " \t " << tokenTypeName 
                  << " \t '" << tokenText << "'" << std::endl;

    }

}

void
printParserTree(antlr4::tree::ParseTree *node, const std::vector<std::string>& ruleNames, int indent = 0)
{

    for (int i = 0; i < indent; ++i) std::cout << "  ";
    
    std::cout << antlr4::tree::Trees::getNodeText(node, ruleNames) << std::endl;
    
    for (size_t i = 0; i < node->children.size(); ++i) {
        printParserTree(node->children[i], ruleNames, indent + 1);
    }

}
