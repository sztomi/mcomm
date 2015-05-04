
// Macros for dynamic binding

#ifndef REGISTER_CLASS
#define REGISTER_CLASS(CLASS) static const RegisterClass<CLASS> FactoryRegister{CLASS::ClassName};
#endif

#ifndef DECLARE_BINDABLE
#define DECLARE_BINDABLE(THECLASS)                                     \
    static constexpr char const* ClassName = #THECLASS;                \
    std::string name() const { return ClassName; }                     \
    std::shared_ptr<MetaObject> metaObject() const {                   \
        return MetaObjectManager::instance().getMetaObject(ClassName); \
    }                                                                  \
	static void bind();                                                \

#endif

#ifndef DECLARE_BINDABLE2
#define DECLARE_BINDABLE2(THECLASS)                                    \
    static constexpr char const* ClassName = #THECLASS;                \
    std::string name() const override { return ClassName; }            \
    std::shared_ptr<MetaObject> metaObject() const override {          \
        return MetaObjectManager::instance().getMetaObject(ClassName); \
    }                                                                  \
	static void bind();                                                \

#endif

#ifndef DECLARE_DYNCLASS
#define DECLARE_DYNCLASS(THECLASS) public:                             \
	DECLARE_BINDABLE(THECLASS)                                         \
    THECLASS();                                                        \
    private:
#endif


#ifndef BIND_CLASS
#define BIND_CLASS(THECLASS)                                           \
	void THECLASS::bind()                                              \
	{																   \
		static bool bound = false;                                     \
		if (bound) return;                                             \
		auto c = lualite::class_<THECLASS>(ClassName)                  \
		           .constructor()                                      \
				   .property("name", &THECLASS::name)
#endif

#ifndef BIND_END
#define BIND_END()                                                     \
    ;auto m = mcomm::MetaObject::create(ClassName, c);                 \
    MetaObjectManager::instance().registerClass(m);                    \
    ScriptManager::instance().registerClass(c);                        \
	bound = true; }
#endif

#define BIND_GENERIC(THECLASS)    \
	REGISTER_CLASS(THECLASS)      \
    BIND_CLASS(THECLASS)
