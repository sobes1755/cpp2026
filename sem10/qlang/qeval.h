#pragma once

#include "antlr4-runtime.h"
#include "QuaternionBaseVisitor.h"

#include "qgeom.h"

#include <iostream>
#include <map>
#include <variant>
#include <string>
#include <vector>
#include <numbers>

using QScalar = double;
using QVector = Vector3D<double>;
using QQuaternion = Quaternion<double>;

using QVariant = std::variant<QScalar, QVector, QQuaternion>;

template<class... T> struct overloaded : T... { using T::operator()...; };

class QEvalVisitor : public QuaternionBaseVisitor {
private:

    std::map<std::string, QVariant> memory;

public:

    QEvalVisitor()
    {
        memory["pi"] = std::numbers::pi;
        memory["e"]  = std::numbers::e;
        memory["i"]  = QQuaternion{0, 1, 0, 0};
        memory["j"]  = QQuaternion{0, 0, 1, 0};
        memory["k"]  = QQuaternion{0, 0, 0, 1};
    }

    // Печать QVariant...

    void
    printVariant(const QVariant& v) {

        std::visit(overloaded {

            [](QScalar s) { std::cout << s; },
            [](const QVector& v) { std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")"; },
            [](const QQuaternion& q) { std::cout << "(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")"; }

        }, v);

    }

    // Реализация вызова функций (println, dot, cross и т.д.)

    antlrcpp::Any
    visitFunction_call(QuaternionParser::Function_callContext *ctx) override
    {

        std::string name = ctx->ID()->getText();

        std::vector<QVariant> args;

        for (auto *expr : ctx->expression()) {
            args.push_back(visit(expr).as<QVariant>());    
        }

        if (name == "println") {

            for (const auto& arg : args) {
                printVariant(arg);
                std::cout << " ";
            }
            std::cout << std::endl;

            return args.empty() ? QVariant(0.0) : args.back();

        }
    
        if (args.empty()) throw std::runtime_error(name + "() requires arguments");

        const QVariant& arg = args[0];

        if (name == "sin" || name == "cos" || name == "sqrt" || name == "exp") {

            if (auto* s = std::get_if<QScalar>(&arg)) {
                if (name == "sin")  return QVariant(std::sin(*s));
                if (name == "cos")  return QVariant(std::cos(*s));
                if (name == "sqrt") return QVariant(std::sqrt(*s));
                if (name == "exp")  return QVariant(std::exp(*s));
            }

            throw std::runtime_error(name + " requires a scalar argument");

        }

        if (name == "conjugate" || name == "inverse") {

            if (auto* q = std::get_if<QQuaternion>(&arg)) {
                return (name == "conjugate") ? QVariant(q->conjugate()) : QVariant(q->inverse());
            }

            throw std::runtime_error(name + " requires a quaternion argument");

        }

        if (name == "norm") {

            if (auto* v = std::get_if<QVector>(&arg)) return QVariant((QScalar)v->norm());
            if (auto* q = std::get_if<QQuaternion>(&arg)) return QVariant((QScalar)q->norm());
            if (auto* s = std::get_if<QScalar>(&arg)) return QVariant(std::abs(*s));

            throw std::runtime_error("norm() is not defined for this type");

        }

        if (name == "dot" || name == "cross") {

            if (args.size() != 2) throw std::runtime_error(name + " requires 2 arguments");

            auto* v1 = std::get_if<QVector>(&args[0]);
            auto* v2 = std::get_if<QVector>(&args[1]);

            if (v1 && v2) {
                if (name == "dot") return QVariant((QScalar)v1->dot(*v2));
                if (name == "cross") return QVariant(v1->cross(*v2));
            }

            throw std::runtime_error(name + " requires two vector arguments");

        }

        throw std::runtime_error("Unknown function: " + name);

    }

    antlrcpp::Any
    visitPrimary_expression(QuaternionParser::Primary_expressionContext *ctx) override
    {

        // Вычисляем числа, переменные, константы...

        if (ctx->NUMBER())   return QVariant(std::stod(ctx->NUMBER()->getText()));
        if (ctx->CONSTANT()) return memory.at(ctx->CONSTANT()->getText());
        if (ctx->ID())       return memory.at(ctx->ID()->getText());

        // Вычисляем выражения в скобках...

        auto exprs = ctx->expression();
    
        if (exprs.size() == 1) {
            return visit(exprs[0]); 
        }

        if (exprs.size() == 3) {
            return QVariant(QVector{
                std::get<QScalar>(visit(exprs[0]).as<QVariant>()),
                std::get<QScalar>(visit(exprs[1]).as<QVariant>()),
                std::get<QScalar>(visit(exprs[2]).as<QVariant>())
            });
        }
        if (exprs.size() == 4) {
            return QVariant(QQuaternion{
                std::get<QScalar>(visit(exprs[0]).as<QVariant>()),
                std::get<QScalar>(visit(exprs[1]).as<QVariant>()),
                std::get<QScalar>(visit(exprs[2]).as<QVariant>()),
                std::get<QScalar>(visit(exprs[3]).as<QVariant>())
            });
        }

        // Больше ничего подходящего в грамматике нет...

        throw std::runtime_error("Unexpected primary expression structure!");

    }

    antlrcpp::Any
    visitAssignment_expression(QuaternionParser::Assignment_expressionContext *ctx) override
    {

        // postfix_expression -> primary_expression -> ID

        auto* post = ctx->postfix_expression();
        auto* primary = post->primary_expression();

        if (!primary || !primary->ID()) {
            throw std::runtime_error("L-value error: can only assign to a variable.");
        }

        std::string id = primary->ID()->getText();
    
        QVariant val = visit(ctx->expression()).as<QVariant>();

        if (!post->component()) {

            memory[id] = val;

        } else {

            if (!memory.contains(id)) {
                throw std::runtime_error("Variable '" + id + "' not found.");
            }

            std::string comp = post->component()->ID()->getText();

            QVariant &target = memory[id];
        
            if (!std::holds_alternative<QScalar>(val)) {
                throw std::runtime_error("Component assignment requires a scalar value.");
            }

            double s = std::get<QScalar>(val);

            if (auto* v = std::get_if<QVector>(&target)) {

                if (comp == "x") v->x = s;
                else if (comp == "y") v->y = s;
                else if (comp == "z") v->z = s;
                else throw std::runtime_error("Vector has no component: " + comp);

            } else if (auto* q = std::get_if<QQuaternion>(&target)) {

                if (comp == "w") q->w = s;
                else if (comp == "x") q->x = s;
                else if (comp == "y") q->y = s;
                else if (comp == "z") q->z = s;
                else throw std::runtime_error("Quaternion has no component: " + comp);
        
	    } else {

                throw std::runtime_error("Scalar variable '" + id + "' has no components.");

            }
        }

        return val;

    }

    antlrcpp::Any
    visitPostfix_expression(QuaternionParser::Postfix_expressionContext *ctx) override
    {

        if (ctx->primary_expression()) {
            return visit(ctx->primary_expression());
        }

        if (ctx->function_call()) {
            return visit(ctx->function_call());
        }

        QVariant val = visit(ctx->postfix_expression()).as<QVariant>();
        std::string comp = ctx->component()->ID()->getText();

        if (auto* v = std::get_if<QVector>(&val)) {

            if (comp == "x") return QVariant(v->x);
            if (comp == "y") return QVariant(v->y);
            if (comp == "z") return QVariant(v->z);

        } 
        else if (auto* q = std::get_if<QQuaternion>(&val)) {

            if (comp == "w") return QVariant(q->w);
            if (comp == "x") return QVariant(q->x);
            if (comp == "y") return QVariant(q->y);
            if (comp == "z") return QVariant(q->z);

        }

        throw std::runtime_error("Component access error: type has no such component.");

    }

    antlrcpp::Any
    visitMultiplicative_expression(QuaternionParser::Multiplicative_expressionContext *ctx) override
    {

        // Берём первый операнд
        QVariant curr = visit(ctx->unary_expression(0)).as<QVariant>();
        size_t currIndex = ctx->unary_expression(0)->getStart()->getTokenIndex();

        // Берём следующие операндам
        for (size_t i = 1; i < ctx->unary_expression().size(); ++i) {

            QVariant next = visit(ctx->unary_expression(i)).as<QVariant>();
            size_t nextIndex = ctx->unary_expression(i)->getStart()->getTokenIndex();
        
            bool isMul = false;

            if (!ctx->MUL().empty()) {

                for (auto* mulNode : ctx->MUL()) {
                    if (currIndex < mulNode->getSymbol()->getTokenIndex() && mulNode->getSymbol()->getTokenIndex() < nextIndex) {
                        isMul = true;
                        break;
                    }
                }

            }

            if (isMul) {

                curr = std::visit(overloaded {
                    [](QScalar a, QScalar b) -> QVariant { return a * b; },
                    [](const QQuaternion& a, const QQuaternion& b) -> QVariant { return a * b; },
                    [](const QVector& a, QScalar b) -> QVariant { return QVariant(QVector(a * b)); },
                    [](QScalar a, const QVector& b) -> QVariant { return QVariant(QVector(b * a)); },
                    [](const QQuaternion& q, QScalar s) -> QVariant { return QVariant(QQuaternion(q * s)); },
                    [](QScalar s, const QQuaternion& q) -> QVariant { return QVariant(QQuaternion(q * s)); },
                    [](const QQuaternion& q, const QVector& v) -> QVariant { return QVariant(q * QQuaternion(0, v.x, v.y, v.z)); },
                    [](const QVector& v, const QQuaternion& q) -> QVariant { return QVariant(QQuaternion(0, v.x, v.y, v.z) * q); },
                    [](auto, auto) -> QVariant { throw std::runtime_error("Invalid multiplication types"); }
                }, curr, next);

            } else {

                curr = std::visit(overloaded {
                    [](QScalar a, QScalar b) -> QVariant { 
                        if (b == 0) throw std::runtime_error("Division by zero");
                        return a / b; 
                    },
                    [](const QQuaternion& a, const QQuaternion& b) -> QVariant {
                        if (b.normsquared() == 0) throw std::runtime_error("Division by zero quaternion");
                        return a / b;
                    },
                    [](const QVector& a, QScalar b) -> QVariant { 
                        if (b == 0) throw std::runtime_error("Division by zero");
                        return QVariant(QVector(a / b)); 
                    },
                    [](const QQuaternion& q, QScalar s) -> QVariant { 
                        if (s == 0) throw std::runtime_error("Division by zero");
                        return QVariant(QQuaternion(q / s)); 
                    },
                    [](auto, auto) -> QVariant { throw std::runtime_error("Invalid division types"); }
                }, curr, next);

            }

            currIndex = nextIndex;

        }

        return curr;

    }

    antlrcpp::Any
    visitExpression(QuaternionParser::ExpressionContext *ctx) override {
        return visit(ctx->additive_expression());
    }

    antlrcpp::Any
    visitAdditive_expression(QuaternionParser::Additive_expressionContext *ctx) override {

        if (ctx->multiplicative_expression().size() == 1) {
            return visit(ctx->multiplicative_expression(0));
        }

        QVariant curr = visit(ctx->multiplicative_expression(0)).as<QVariant>();
        size_t currIndex = ctx->multiplicative_expression(0)->getStart()->getTokenIndex();

        for (size_t i = 1; i < ctx->multiplicative_expression().size(); ++i) {

            QVariant next = visit(ctx->multiplicative_expression(i)).as<QVariant>();
            size_t nextIndex = ctx->multiplicative_expression(i)->getStart()->getTokenIndex();

            bool isPlus = false;

            if (!ctx->PLUS().empty()) {
                for (auto* plusNode : ctx->PLUS()) {
                    size_t opIndex = plusNode->getSymbol()->getTokenIndex();
                    if (currIndex < opIndex && opIndex < nextIndex) {
                        isPlus = true;
                        break;
                    }
                }
            }

            if (isPlus) {

                curr = std::visit(overloaded {
                    [](QScalar a, QScalar b) -> QVariant { return a + b; },
                    [](const QQuaternion& a, const QQuaternion& b) -> QVariant { return a + b; },
                    [](const QVector& a, const QVector& b) -> QVariant { return a + b; },
                    [](auto, auto) -> QVariant { throw std::runtime_error("Invalid addition types"); }
                }, curr, next);

            } else {

                curr = std::visit(overloaded {
                    [](QScalar a, QScalar b) -> QVariant { return a - b; },
                    [](const QQuaternion& a, const QQuaternion& b) -> QVariant { return a - b; },
                    [](const QVector& a, const QVector& b) -> QVariant { return a - b; },
                    [](auto, auto) -> QVariant { throw std::runtime_error("Invalid subtraction types"); }
                }, curr, next);

            }

            currIndex = nextIndex;
        }

        return curr;

    }

};
