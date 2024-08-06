#pragma once

#define Expand(x) x

#define AddSem(x) x,

#define x1(what, x, ...) what(x)
#define x2(what, op, x, ...) op(what(x)) Expand(x1(what, __VA_ARGS__))
#define x3(what, op, x, ...) op(what(x)) Expand(x2(what, op, __VA_ARGS__))
#define x4(what, op, x, ...) op(what(x)) Expand(x3(what, op, __VA_ARGS__))
#define x5(what, op, x, ...) op(what(x)) Expand(x4(what, op, __VA_ARGS__))
#define x6(what, op, x, ...) op(what(x)) Expand(x5(what, op, __VA_ARGS__))
#define x7(what, op, x, ...) op(what(x)) Expand(x6(what, op, __VA_ARGS__))
#define x8(what, op, x, ...) op(what(x)) Expand(x7(what, op, __VA_ARGS__))
#define x9(what, op, x, ...) op(what(x)) Expand(x8(what, op, __VA_ARGS__))
#define x10(what, op, x, ...) op(what(x)) Expand(x9(what, op, __VA_ARGS__))
#define x11(what, op, x, ...) op(what(x)) Expand(x10(what, op, __VA_ARGS__))
#define x12(what, op, x, ...) op(what(x)) Expand(x11(what, op, __VA_ARGS__))
#define x13(what, op, x, ...) op(what(x)) Expand(x12(what, op, __VA_ARGS__))
#define x14(what, op, x, ...) op(what(x)) Expand(x13(what, op, __VA_ARGS__))
#define x15(what, op, x, ...) op(what(x)) Expand(x14(what, op, __VA_ARGS__))
#define x16(what, op, x, ...) op(what(x)) Expand(x15(what, op, __VA_ARGS__))
#define x17(what, op, x, ...) op(what(x)) Expand(x16(what, op, __VA_ARGS__))
#define x18(what, op, x, ...) op(what(x)) Expand(x17(what, op, __VA_ARGS__))
#define x19(what, op, x, ...) op(what(x)) Expand(x18(what, op, __VA_ARGS__))
#define x20(what, op, x, ...) op(what(x)) Expand(x19(what, op, __VA_ARGS__))
#define x21(what, op, x, ...) op(what(x)) Expand(x20(what, op, __VA_ARGS__))
#define x22(what, op, x, ...) op(what(x)) Expand(x21(what, op, __VA_ARGS__))
#define x23(what, op, x, ...) op(what(x)) Expand(x22(what, op, __VA_ARGS__))
#define x24(what, op, x, ...) op(what(x)) Expand(x23(what, op, __VA_ARGS__))
#define x25(what, op, x, ...) op(what(x)) Expand(x24(what, op, __VA_ARGS__))
#define x26(what, op, x, ...) op(what(x)) Expand(x25(what, op, __VA_ARGS__))
#define x27(what, op, x, ...) op(what(x)) Expand(x26(what, op, __VA_ARGS__))
#define x28(what, op, x, ...) op(what(x)) Expand(x27(what, op, __VA_ARGS__))
#define x29(what, op, x, ...) op(what(x)) Expand(x28(what, op, __VA_ARGS__))
#define x30(what, op, x, ...) op(what(x)) Expand(x29(what, op, __VA_ARGS__))
#define x31(what, op, x, ...) op(what(x)) Expand(x30(what, op, __VA_ARGS__))
#define x32(what, op, x, ...) op(what(x)) Expand(x31(what, op, __VA_ARGS__))
#define x33(what, op, x, ...) op(what(x)) Expand(x32(what, op, __VA_ARGS__))
#define x34(what, op, x, ...) op(what(x)) Expand(x33(what, op, __VA_ARGS__))
#define x35(what, op, x, ...) op(what(x)) Expand(x34(what, op, __VA_ARGS__))
#define x36(what, op, x, ...) op(what(x)) Expand(x35(what, op, __VA_ARGS__))
#define x37(what, op, x, ...) op(what(x)) Expand(x36(what, op, __VA_ARGS__))
#define x38(what, op, x, ...) op(what(x)) Expand(x37(what, op, __VA_ARGS__))
#define x39(what, op, x, ...) op(what(x)) Expand(x38(what, op, __VA_ARGS__))
#define x40(what, op, x, ...) op(what(x)) Expand(x39(what, op, __VA_ARGS__))
#define x41(what, op, x, ...) op(what(x)) Expand(x40(what, op, __VA_ARGS__))
#define x42(what, op, x, ...) op(what(x)) Expand(x41(what, op, __VA_ARGS__))
#define x43(what, op, x, ...) op(what(x)) Expand(x42(what, op, __VA_ARGS__))
#define x44(what, op, x, ...) op(what(x)) Expand(x43(what, op, __VA_ARGS__))
#define x45(what, op, x, ...) op(what(x)) Expand(x44(what, op, __VA_ARGS__))
#define x46(what, op, x, ...) op(what(x)) Expand(x45(what, op, __VA_ARGS__))
#define x47(what, op, x, ...) op(what(x)) Expand(x46(what, op, __VA_ARGS__))
#define x48(what, op, x, ...) op(what(x)) Expand(x47(what, op, __VA_ARGS__))
#define x49(what, op, x, ...) op(what(x)) Expand(x48(what, op, __VA_ARGS__))
#define x50(what, op, x, ...) op(what(x)) Expand(x49(what, op, __VA_ARGS__))

#define GetMacro(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10, \
                 _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
                 _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
                 _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
                 _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, macro, ...) macro

#define ForEach(action, ...) \
    Expand(GetMacro(__VA_ARGS__, \
        x50, x49, x48, x47, x46, \
        x45, x44, x43, x42, x41, \
        x40, x39, x38, x37, x36, \
        x35, x34, x33, x32, x31, \
        x30, x29, x28, x27, x26, \
        x25, x24, x23, x22, x21, \
        x20, x19, x18, x17, x16, \
        x15, x14, x13, x12, x11, \
        x10, x9, x8, x7, x6, \
        x5, x4, x3, x2, x1) \
        (action, Expand, __VA_ARGS__))

#define ForEachWS(action, ...) \
    Expand(GetMacro(__VA_ARGS__, \
        x50, x49, x48, x47, x46, \
        x45, x44, x43, x42, x41, \
        x40, x39, x38, x37, x36, \
        x35, x34, x33, x32, x31, \
        x30, x29, x28, x27, x26, \
        x25, x24, x23, x22, x21, \
        x20, x19, x18, x17, x16, \
        x15, x14, x13, x12, x11, \
        x10, x9, x8, x7, x6, \
        x5, x4, x3, x2, x1) \
        (action, AddSem, __VA_ARGS__))
