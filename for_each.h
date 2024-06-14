#pragma once

#define EXPAND(x) x

#define FOR_EACH_1(what, x, ...) what(x)
#define FOR_EACH_2(what, x, ...) what(x) EXPAND(FOR_EACH_1(what, __VA_ARGS__))
#define FOR_EACH_3(what, x, ...) what(x) EXPAND(FOR_EACH_2(what, __VA_ARGS__))
#define FOR_EACH_4(what, x, ...) what(x) EXPAND(FOR_EACH_3(what, __VA_ARGS__))
#define FOR_EACH_5(what, x, ...) what(x) EXPAND(FOR_EACH_4(what, __VA_ARGS__))
#define FOR_EACH_6(what, x, ...) what(x) EXPAND(FOR_EACH_5(what, __VA_ARGS__))
#define FOR_EACH_7(what, x, ...) what(x) EXPAND(FOR_EACH_6(what, __VA_ARGS__))
#define FOR_EACH_8(what, x, ...) what(x) EXPAND(FOR_EACH_7(what, __VA_ARGS__))
#define FOR_EACH_9(what, x, ...) what(x) EXPAND(FOR_EACH_8(what, __VA_ARGS__))
#define FOR_EACH_10(what, x, ...) what(x) EXPAND(FOR_EACH_9(what, __VA_ARGS__))
#define FOR_EACH_11(what, x, ...) what(x) EXPAND(FOR_EACH_10(what, __VA_ARGS__))
#define FOR_EACH_12(what, x, ...) what(x) EXPAND(FOR_EACH_11(what, __VA_ARGS__))
#define FOR_EACH_13(what, x, ...) what(x) EXPAND(FOR_EACH_12(what, __VA_ARGS__))
#define FOR_EACH_14(what, x, ...) what(x) EXPAND(FOR_EACH_13(what, __VA_ARGS__))
#define FOR_EACH_15(what, x, ...) what(x) EXPAND(FOR_EACH_14(what, __VA_ARGS__))
#define FOR_EACH_16(what, x, ...) what(x) EXPAND(FOR_EACH_15(what, __VA_ARGS__))
#define FOR_EACH_17(what, x, ...) what(x) EXPAND(FOR_EACH_16(what, __VA_ARGS__))
#define FOR_EACH_18(what, x, ...) what(x) EXPAND(FOR_EACH_17(what, __VA_ARGS__))
#define FOR_EACH_19(what, x, ...) what(x) EXPAND(FOR_EACH_18(what, __VA_ARGS__))
#define FOR_EACH_20(what, x, ...) what(x) EXPAND(FOR_EACH_19(what, __VA_ARGS__))
#define FOR_EACH_21(what, x, ...) what(x) EXPAND(FOR_EACH_20(what, __VA_ARGS__))
#define FOR_EACH_22(what, x, ...) what(x) EXPAND(FOR_EACH_21(what, __VA_ARGS__))
#define FOR_EACH_23(what, x, ...) what(x) EXPAND(FOR_EACH_22(what, __VA_ARGS__))
#define FOR_EACH_24(what, x, ...) what(x) EXPAND(FOR_EACH_23(what, __VA_ARGS__))
#define FOR_EACH_25(what, x, ...) what(x) EXPAND(FOR_EACH_24(what, __VA_ARGS__))
#define FOR_EACH_26(what, x, ...) what(x) EXPAND(FOR_EACH_25(what, __VA_ARGS__))
#define FOR_EACH_27(what, x, ...) what(x) EXPAND(FOR_EACH_26(what, __VA_ARGS__))
#define FOR_EACH_28(what, x, ...) what(x) EXPAND(FOR_EACH_27(what, __VA_ARGS__))
#define FOR_EACH_29(what, x, ...) what(x) EXPAND(FOR_EACH_28(what, __VA_ARGS__))
#define FOR_EACH_30(what, x, ...) what(x) EXPAND(FOR_EACH_29(what, __VA_ARGS__))
#define FOR_EACH_31(what, x, ...) what(x) EXPAND(FOR_EACH_30(what, __VA_ARGS__))
#define FOR_EACH_32(what, x, ...) what(x) EXPAND(FOR_EACH_31(what, __VA_ARGS__))
#define FOR_EACH_33(what, x, ...) what(x) EXPAND(FOR_EACH_32(what, __VA_ARGS__))
#define FOR_EACH_34(what, x, ...) what(x) EXPAND(FOR_EACH_33(what, __VA_ARGS__))
#define FOR_EACH_35(what, x, ...) what(x) EXPAND(FOR_EACH_34(what, __VA_ARGS__))
#define FOR_EACH_36(what, x, ...) what(x) EXPAND(FOR_EACH_35(what, __VA_ARGS__))
#define FOR_EACH_37(what, x, ...) what(x) EXPAND(FOR_EACH_36(what, __VA_ARGS__))
#define FOR_EACH_38(what, x, ...) what(x) EXPAND(FOR_EACH_37(what, __VA_ARGS__))
#define FOR_EACH_39(what, x, ...) what(x) EXPAND(FOR_EACH_38(what, __VA_ARGS__))
#define FOR_EACH_40(what, x, ...) what(x) EXPAND(FOR_EACH_39(what, __VA_ARGS__))
#define FOR_EACH_41(what, x, ...) what(x) EXPAND(FOR_EACH_40(what, __VA_ARGS__))
#define FOR_EACH_42(what, x, ...) what(x) EXPAND(FOR_EACH_41(what, __VA_ARGS__))
#define FOR_EACH_43(what, x, ...) what(x) EXPAND(FOR_EACH_42(what, __VA_ARGS__))
#define FOR_EACH_44(what, x, ...) what(x) EXPAND(FOR_EACH_43(what, __VA_ARGS__))
#define FOR_EACH_45(what, x, ...) what(x) EXPAND(FOR_EACH_44(what, __VA_ARGS__))
#define FOR_EACH_46(what, x, ...) what(x) EXPAND(FOR_EACH_45(what, __VA_ARGS__))
#define FOR_EACH_47(what, x, ...) what(x) EXPAND(FOR_EACH_46(what, __VA_ARGS__))
#define FOR_EACH_48(what, x, ...) what(x) EXPAND(FOR_EACH_47(what, __VA_ARGS__))
#define FOR_EACH_49(what, x, ...) what(x) EXPAND(FOR_EACH_48(what, __VA_ARGS__))
#define FOR_EACH_50(what, x, ...) what(x) EXPAND(FOR_EACH_49(what, __VA_ARGS__))

#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10, \
                 _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
                 _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
                 _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
                 _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, NAME, ...) NAME

// Please, do not extend over 50 classes or this may not work
#define FOR_EACH(action, ...) \
    EXPAND(GET_MACRO(__VA_ARGS__, \
        FOR_EACH_50, FOR_EACH_49, FOR_EACH_48, FOR_EACH_47, FOR_EACH_46, \
        FOR_EACH_45, FOR_EACH_44, FOR_EACH_43, FOR_EACH_42, FOR_EACH_41, \
        FOR_EACH_40, FOR_EACH_39, FOR_EACH_38, FOR_EACH_37, FOR_EACH_36, \
        FOR_EACH_35, FOR_EACH_34, FOR_EACH_33, FOR_EACH_32, FOR_EACH_31, \
        FOR_EACH_30, FOR_EACH_29, FOR_EACH_28, FOR_EACH_27, FOR_EACH_26, \
        FOR_EACH_25, FOR_EACH_24, FOR_EACH_23, FOR_EACH_22, FOR_EACH_21, \
        FOR_EACH_20, FOR_EACH_19, FOR_EACH_18, FOR_EACH_17, FOR_EACH_16, \
        FOR_EACH_15, FOR_EACH_14, FOR_EACH_13, FOR_EACH_12, FOR_EACH_11, \
        FOR_EACH_10, FOR_EACH_9, FOR_EACH_8, FOR_EACH_7, FOR_EACH_6, \
        FOR_EACH_5, FOR_EACH_4, FOR_EACH_3, FOR_EACH_2, FOR_EACH_1) \
        (action, __VA_ARGS__))
