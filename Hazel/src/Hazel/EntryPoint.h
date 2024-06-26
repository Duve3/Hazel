#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();  // meaning information recieved from external sources (when the CLIENT declares it)

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!"); 
	int a = 5;
	HZ_INFO("Hello! Var={0} Var+1={1}", a, a+1);

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Hazel only supports Windows!
#endif  