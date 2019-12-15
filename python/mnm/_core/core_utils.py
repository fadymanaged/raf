import inspect
from collections import deque, OrderedDict

from mnm._lib import _DLContext
from mnm._lib import _NodeBase as NodeBase  # pylint: disable=unused-import
from mnm._lib import _register_node


def register_node(type_key=None):
    assert isinstance(type_key, str)
    return _register_node(type_key)


def set_module(module):
    def decorator(func):
        if module is not None:
            func.__module__ = module
        return func

    return decorator


def _get_ctx_map():
    dev_type_mask = {
        'llvm': 1,
        'stackvm': 1,
        'cpu': 1,
        'c': 1,
        'gpu': 2,
        'cuda': 2,
        'nvptx': 2,
        'cl': 4,
        'opencl': 4,
        'aocl': 5,
        'aocl_sw_emu': 5,
        'sdaccel': 6,
        'vulkan': 7,
        'metal': 8,
        'vpi': 9,
        'rocm': 10,
        'opengl': 11,
        'ext_dev': 12,
        'micro_dev': 13,
    }
    _str2ctx = {}
    for device_type, idx in dev_type_mask.items():
        _str2ctx[device_type] = _DLContext(device_type=idx, device_id=0)
        for device_id in range(128):
            name = f"{device_type}({device_id})"
            _str2ctx[name] = _DLContext(device_type=idx, device_id=device_id)
    return _str2ctx


_STR2CTX = _get_ctx_map()


def ctx2str(ctx: _DLContext) -> str:
    mask = [
        None, "cpu", "cuda", "cpu_pinned", "cl", "aocl", 'sdaccel', 'vulkan',
        'metal', 'vpi', 'rocm', 'opengl'
    ]
    dev_type = int(ctx.device_type)
    dev_id = int(ctx.device_id)
    if dev_id == 0 and dev_type in (1, 3):
        return mask[dev_type]
    return mask[dev_type] + "(" + str(dev_id) + ")"


def str2ctx(name: str) -> _DLContext:
    return _STR2CTX[name]


def bfs(sources, on_pop, on_next, *, recursive=True):
    if not recursive:
        for item in sources:
            on_pop(item)
        return
    sources = list(sources)
    queue = deque(sources)
    visited = set(sources)
    while len(queue) > 0:
        model = queue.popleft()
        on_pop(model)
        for submodel in on_next(model):
            if submodel is not None and submodel not in visited:
                visited.add(submodel)
                queue.append(submodel)


def get_func_name(pyfunc):
    return pyfunc.__module__ + "$" + pyfunc.__qualname__


def get_bound_args(pyfunc, args, kwargs) -> inspect.BoundArguments:
    sig = inspect.signature(pyfunc)
    bound_args = sig.bind(*args, **kwargs)
    bound_args.apply_defaults()
    return bound_args


def get_attr(instance, *, name=None, check=None):
    single = False
    if name is None:
        name = dir(instance)
    elif not isinstance(name, (list, tuple)):
        single = True
        name = [name]
    ret = []
    for candidate in sorted(name):
        member = getattr(instance, candidate, None)
        if member is None:
            continue
        if (check is not None) and (not check(member)):
            continue
        ret.append(member)
    if single:
        if not ret:
            return None
        if len(ret) == 1:
            return ret[0]
        return ret
    return ret


def get_named_attr(instance, *, name=None, check=None):
    if name is None:
        name = dir(instance)
    elif not isinstance(name, (list, tuple)):
        name = [name]
    ret = OrderedDict()
    for candidate in sorted(name):
        member = getattr(instance, candidate, None)
        if member is None:
            continue
        if (check is not None) and (not check(member)):
            continue
        ret[candidate] = member
    return ret
