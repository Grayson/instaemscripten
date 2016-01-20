#include <emscripten/bind.h>
#include <string>

class Foo {
public:
	Foo(const std::string & name)
		: m_name { name }
	{
	}
	
	const std::string & GetName() const
	{
		return m_name;
	}
	
private:
	std::string m_name;
};

int Add2(int base) {
	return base + 2;
}

EMSCRIPTEN_BINDINGS(example)
{
    emscripten::function("AddTwo", &Add2);
    emscripten::class_<Foo>("CppFoo")
		.constructor<std::string>()
		.function("GetName", &Foo::GetName);
}
