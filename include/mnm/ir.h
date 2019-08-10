#pragma once

// This is a compatibility layer between MNM and Relay
// We will borrow basically everything from TVM/Relay to here.
// TODO(@junrushao1994): adt & patterns, op, functors, pass

#include <tvm/attrs.h>
#include <tvm/ir.h>
#include <tvm/node/container.h>
#include <tvm/relay/base.h>
#include <tvm/relay/expr.h>
#include <tvm/relay/module.h>
#include <tvm/relay/op.h>
#include <tvm/relay/type.h>

namespace mnm {
namespace ir {

using tvm::Array;
using tvm::Attrs;
using tvm::AttrsNode;
using tvm::Int;
using tvm::Integer;
using tvm::IntImm;
using tvm::make_const;
using tvm::make_node;
using tvm::Map;
using tvm::Node;
using tvm::NodePtr;
using tvm::runtime::PackedFunc;
using tvm::runtime::TypedPackedFunc;

using NodeRef = tvm::relay::NodeRef;
using NodeHash = tvm::relay::NodeHash;
using NodeEqual = tvm::relay::NodeEqual;
using IndexExpr = tvm::relay::IndexExpr;
using DataType = tvm::relay::DataType;

// Relay Expression
using Expr = tvm::relay::Expr;
using ExprNode = tvm::relay::ExprNode;

using Constant = tvm::relay::Constant;
using ConstantNode = tvm::relay::ConstantNode;

using Tuple = tvm::relay::Tuple;
using TupleNode = tvm::relay::TupleNode;

using Var = tvm::relay::Var;
using VarNode = tvm::relay::VarNode;

using GlobalVar = tvm::relay::GlobalVar;
using GlobalVarNode = tvm::relay::GlobalVarNode;

using Function = tvm::relay::Function;
using FunctionNode = tvm::relay::FunctionNode;

using Call = tvm::relay::Call;
using CallNode = tvm::relay::CallNode;

using Let = tvm::relay::Let;
using LetNode = tvm::relay::LetNode;

using If = tvm::relay::If;
using IfNode = tvm::relay::IfNode;

using TupleGetItem = tvm::relay::TupleGetItem;
using TupleGetItemNode = tvm::relay::TupleGetItemNode;

using RefCreate = tvm::relay::RefCreate;
using RefCreateNode = tvm::relay::RefCreateNode;

using RefRead = tvm::relay::RefRead;
using RefReadNode = tvm::relay::RefReadNode;

using RefWrite = tvm::relay::RefWrite;
using RefWriteNode = tvm::relay::RefWriteNode;

using TempExpr = tvm::relay::TempExpr;
using TempExprNode = tvm::relay::TempExprNode;

// Relay Types
using Kind = tvm::relay::Kind;

using Type = tvm::relay::Type;
using TypeNode = tvm::relay::TypeNode;

using BaseTensorType = tvm::relay::BaseTensorType;
using BaseTensorTypeNode = tvm::relay::BaseTensorTypeNode;

using TensorType = tvm::relay::TensorType;
using TensorTypeNode = tvm::relay::TensorTypeNode;

using TypeVar = tvm::relay::TypeVar;
using TypeVarNode = tvm::relay::TypeVarNode;

using GlobalTypeVar = tvm::relay::GlobalTypeVar;
using GlobalTypeVarNode = tvm::relay::GlobalTypeVarNode;

using TypeCall = tvm::relay::TypeCall;
using TypeCallNode = tvm::relay::TypeCallNode;

using IncompleteType = tvm::relay::IncompleteType;
using IncompleteTypeNode = tvm::relay::IncompleteTypeNode;

using FuncType = tvm::relay::FuncType;
using FuncTypeNode = tvm::relay::FuncTypeNode;

using TupleType = tvm::relay::TupleType;
using TupleTypeNode = tvm::relay::TupleTypeNode;

using RefType = tvm::relay::RefType;
using RefTypeNode = tvm::relay::RefTypeNode;

using TypeConstraint = tvm::relay::TypeConstraint;
using TypeConstraintNode = tvm::relay::TypeConstraintNode;

using TypeRelation = tvm::relay::TypeRelation;
using TypeRelationNode = tvm::relay::TypeRelationNode;

using TypeReporter = tvm::relay::TypeReporter;

}  // namespace ir
}  // namespace mnm

#define MNM_DEF_NODE_TYPE_INFO(TypeName, Parent) TVM_DECLARE_NODE_TYPE_INFO(TypeName, Parent)

#define MNM_DEF_BASE_NODE_INFO(TypeName, Parent) TVM_DECLARE_BASE_NODE_INFO(TypeName, Parent)

#define MNM_DEF_NODE_REF_METHODS(TypeName, BaseTypeName, NodeName) \
  TVM_DEFINE_NODE_REF_METHODS(TypeName, BaseTypeName, NodeName)

#define MNM_DECLARE_ATTRS TVM_DECLARE_ATTRS

#define MNM_ATTR_FIELD TVM_ATTR_FIELD

#define MNM_REGISTER_NODE_TYPE TVM_REGISTER_NODE_TYPE

#define MNM_REGISTER_OP RELAY_REGISTER_OP

#define MNM_ADD_FILELINE TVM_ADD_FILELINE

#include <mnm/ir_ext.h>