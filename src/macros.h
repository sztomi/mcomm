#ifndef MACROS_H_BALPZZA8
#define MACROS_H_BALPZZA8

#ifdef __CODE_GENERATOR__

    #define GET __attribute__((annotate("getter")))
    #define SET __attribute__((annotate("setter")))
    #define HIDDEN __attribute__((annotate("hidden")))

#else

    #define GET
    #define SET
    #define HIDDEN

#endif

#define REFLECT_TYPE CAMP_TYPE

#endif /* end of include guard: MACROS_H_BALPZZA8 */
