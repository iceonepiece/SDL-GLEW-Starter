#include "Application.h"

int main()
{
	Application app { 800, 600 };

	if (app.Initialize())
		app.Run();

	app.Shutdown();

	return 0;
}
