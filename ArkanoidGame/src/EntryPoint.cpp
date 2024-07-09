#include "EntryPoint.h"
#include "Framework/Application.h"


int main()
{

	int* a = new int(5);

	Arkanoid::Application::Instance().Run();
}