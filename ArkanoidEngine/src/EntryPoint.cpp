#include "EntryPoint.h"
#include "Framework/Application.h"

int main()
{
	Arkanoid::Application* application = new Arkanoid::Application();
	application->Run();
	delete application;
}