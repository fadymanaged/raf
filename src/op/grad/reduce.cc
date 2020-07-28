/*!
 * Copyright (c) 2020 by Contributors
 * \file src/op/grad/reduce.cc
 * \brief Declaration of gradients
 */
#include "./grad_utils.h"

namespace mnm {
namespace op {
namespace grad {

using namespace mnm::ir;

Array<Expr> MeanGrad(const Expr& orig_call, const Expr &y, const Expr& dy) {
  static auto mean_dx = Op::Get("mnm.op.mean_dx");
  const CallNode* call = orig_call.as<CallNode>();
  CHECK_GE(call->args.size(), 3);
  const Expr& x = call->args[0];
  const Expr& axis = call->args[1];
  const Expr& keepdims = call->args[2];
  return {Call(mean_dx, {x, y, dy, axis, keepdims})};
}

MNM_OP_GRAD("mnm.op.mean", MeanGrad);

}  // namespace grad
}  // namespace op
}  // namespace mnm