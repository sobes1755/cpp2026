grammar Quaternion;

// Parser

program : (statement)* EOF;

statement 
    : assignment_expression ';'
    | expression ';'
    ;

assignment_expression
    : postfix_expression '=' expression
    ;

expression
    : additive_expression
    ;

additive_expression
    : multiplicative_expression ((PLUS | MINUS) multiplicative_expression)*
    ;

multiplicative_expression
    : unary_expression ((MUL | DIV) unary_expression)*
    ;

unary_expression
    : MINUS unary_expression
    | postfix_expression
    ;

postfix_expression
    : primary_expression
    | function_call
    | postfix_expression '.' component
    ;

primary_expression
    : NUMBER
    | CONSTANT
    | ID
    | '(' expression ')'
    | '(' expression ',' expression ',' expression ')'                   // Vector
    | '(' expression ',' expression ',' expression ',' expression ')'    // Quaternion
    ;

function_call
    : ID '(' (expression (',' expression)*)? ')'
    ;

component : ID;

// Lexer

CONSTANT : 'pi' | 'e' | 'i' | 'j' | 'k';
ID       : [a-zA-Z_][a-zA-Z0-9_]*;
NUMBER   : [0-9]+ ('.' [0-9]*)?;
PLUS     : '+';
MINUS    : '-';
MUL      : '*';
DIV      : '/';
WS       : [ \t\r\n]+ -> skip;
