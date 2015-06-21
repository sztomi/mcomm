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
#define RTTI() \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Winconsistent-missing-override\"") \
    public: HIDDEN virtual uint32_t campClassId() const { return camp::detail::staticTypeId(this); } \
    public: HIDDEN virtual const char* campClassName() const {return camp::detail::staticTypeName(this);} \
    _Pragma("clang diagnostic pop") \
    private:

#endif /* end of include guard: MACROS_H_BALPZZA8 */
